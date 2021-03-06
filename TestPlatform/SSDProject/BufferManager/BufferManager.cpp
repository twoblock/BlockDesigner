/*
 *    Class implementation of the SoC Designer component <BufferManager>
 *
 *    This code has been generated by the SoC Designer Component Wizard.
 *    Copyright (c)  2008-2012 by Carbon Design Systems Inc.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF CARBON
 * DESIGN SYSTEMS, INC.  PERMISSION IS HEREBY GRANTED TO USE, MODIFY, AND/OR COPY
 * THIS SOFTWARE FOR INTERNAL USE ONLY PROVIDED THAT THE ABOVE COPYRIGHT NOTICE
 * APPEARS IN ALL COPIES OF THIS SOFTWARE.
 */

#include "BufferManager.h"

#include <stdio.h>

void BufferManager::communicate()
{
	uint32_t BM_W_size = 0; 
	uint32_t BM_R_size = 0; 
	uint32_t bm_read_inc = 0;	
	uint32_t bm_write_inc = 0;

	PreFlash_Read_Inc  = Flash_Read_Inc ;   // check 1 bit
	PreFlash_Write_Inc = Flash_Write_Inc ;  

	Flash_Read_Inc  = bm_read_inc_SSlave;
	Flash_Write_Inc = bm_write_inc_SSlave; 
	BM_R_size       = BM_R_size_SSlave;
	BM_W_size       = BM_W_size_SSlave;

	BM_read_limit_SMaster = r_BM_READ_LIMIT;
	BM_write_limit_SMaster = r_BM_WRITE_LIMIT;


	if(Flash_Write_Inc== 0x1)   // rising edge Increase
	{
		if(BM_W_size == ++r_BM_WRITE_LIMIT)	{ r_BM_WRITE_LIMIT_temp =  0; }
		else                                { r_BM_WRITE_LIMIT_temp += 1; }
	}
	if( Flash_Read_Inc== 0x1)
	{	
		if(BM_R_size == ++r_BM_READ_LIMIT)	{ r_BM_READ_LIMIT_temp =  0; }
		else								{ r_BM_READ_LIMIT_temp += 1; }
	}


	if( r_BM_STACK_RESET  & 0x01 ||  r_BM_STACK_RESET & 0x02)
	{
		if( r_BM_STACK_RESET & 0x01 )
		{ r_BM_WRITE_LIMIT_temp = r_BM_STACK_WRSET;}

		if( r_BM_STACK_RESET & 0x02 )
		{ r_BM_READ_LIMIT_temp = r_BM_STACK_RDSET;}

		r_BM_STACK_RESET_temp = 0x0;
	}

}

void BufferManager::update()
{
	uint64_t offset = 0; 
	uint64_t w_data = 0;

	AHBv2_spss->clear();

	AHBv2_spss->setSig(BD_HREADYOUT, true);

	if(_isDataCycleActive)
	{
		// we're handling a DATA transfer. check for wait states.
		if(--_currentWait <= 0)
		{
			// done with this DATA transfer
			_currentWait = _waitCycles;
			_isDataCycleActive = false;


			offset = _addr - p_BM_Base_addr;

			if (_isWrite)
			{

				w_data = AHBv2_spss->getWData(0);

				switch(offset){
					case BM_WRITE_LIMIT:   // Read Only
						break;

					case BM_READ_LIMIT:    // Read Only
						break;

					case BM_STACK_RESET: 	
						r_BM_STACK_RESET_temp = w_data;
						break;

					case BM_STACK_WRSET:		
						r_BM_STACK_WRSET_temp = w_data;
						break;

					case BM_STACK_RDSET:	
						r_BM_STACK_RDSET_temp = w_data;
						break;

					default :
						break;
				}	


			}
			else
			{

				switch(offset){
					case BM_WRITE_LIMIT:		
						AHBv2_spss->setRData( r_BM_WRITE_LIMIT);
						break;
					case BM_READ_LIMIT:
						AHBv2_spss->setRData( r_BM_READ_LIMIT);
						break;
					case BM_STACK_RESET:     // Write Only
						break;
					case BM_STACK_WRSET:		
						AHBv2_spss->setRData( r_BM_STACK_WRSET);
						break;
					case BM_STACK_RDSET:
						AHBv2_spss->setRData( r_BM_STACK_RDSET);
						break;
					default: 
						AHBv2_spss->setRData( 0 );
						break;
				}

			}

			AHBv2_spss->setSig(BD_HREADYOUT, true);

		} //if wait == 0

	}  // data phase

	AHBv2_spss->setSig(BD_HREADYOUT, false);

	if ((AHBv2_spss->getSig(BD_HTRANS) != AHB2_TRANS_IDLE) && 
			(AHBv2_spss->getSig(BD_HTRANS) != AHB2_TRANS_BUSY) &&
			(AHBv2_spss->getSig(BD_HSEL)) && 
			(AHBv2_spss->getSig(BD_HREADY)))
	{

		_addr = AHBv2_spss->getSig(BD_HADDR);

		if (AHBv2_spss->getSig(BD_HWRITE))
		{
			_isWrite = true;
		}
		else
		{
			_isWrite = false;

			//zero wait	

			if( _currentWait <= 0)
			{
				//read

				offset = _addr - p_BM_Base_addr;

				switch(offset){
					case BM_WRITE_LIMIT:		
						AHBv2_spss->setRData( r_BM_WRITE_LIMIT);
						break;
					case BM_READ_LIMIT:
						AHBv2_spss->setRData( r_BM_READ_LIMIT);
						break;
					case BM_STACK_RESET:     // Write Only
						break;
					case BM_STACK_WRSET:		
						AHBv2_spss->setRData( r_BM_STACK_WRSET);
						break;
					case BM_STACK_RDSET:
						AHBv2_spss->setRData( r_BM_STACK_RDSET);
						break;
					default: 
						AHBv2_spss->setRData( 0 );
						break;
				}
			}
		}

		_isDataCycleActive = true;

		if( _currentWait <= 0)
		{
			//read
			AHBv2_spss->setSig(BD_HREADYOUT, true);
		}
		else
		{
			AHBv2_spss->setSig(BD_HREADYOUT, false);
		}

	}
	else
	{		
		_isDataCycleActive = false;
	}

	r_BM_WRITE_LIMIT = r_BM_WRITE_LIMIT_temp ;
	r_BM_READ_LIMIT  = r_BM_READ_LIMIT_temp;
	r_BM_STACK_RESET = r_BM_STACK_RESET_temp ;
	r_BM_STACK_WRSET = r_BM_STACK_WRSET_temp ;
	r_BM_STACK_RDSET = r_BM_STACK_RDSET_temp ;

}

BDDI* BufferManager::GetBDDI()
{
	return bddi;
}

char* BufferManager::GetModuleName()
{
	return (char*)"BufferManager";
}

void BufferManager::BDInit()
{

	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	bm_read_inc_SSlave.set_port_name("bm_read_inc_SSlave");
	bm_write_inc_SSlave.set_port_name("bm_write_inc_SSlave");
	BM_R_size_SSlave.set_port_name("BM_R_size_SSlave");
	BM_W_size_SSlave.set_port_name("BM_W_size_SSlave");
                                                                       
	BM_read_limit_SMaster.set_port_name("BM_read_limit_SMaster");
	BM_write_limit_SMaster.set_port_name("BM_write_limit_SMaster");

	AHBv2_spss = new BD_AHBPort_SS((char*)"SS_S0");

	// for BDDI
	bddi = new BufferManager_BDDI(this);

	r_BM_WRITE_LIMIT = 0;
	r_BM_READ_LIMIT = 0;
	r_BM_STACK_RESET = 0;
	r_BM_STACK_WRSET = 0;
	r_BM_STACK_RDSET = 0;

	_addr = 0;
	_isWrite = false;
	_isDataCycleActive = false; 
	_waitCycles = 0;
	_currentWait=_waitCycles;

	BM_W_size= 0;
	BM_R_size= 0;
	Flash_Read_Inc = 0;
	Flash_Write_Inc= 0;

	PreFlash_Read_Inc  = 0;
	PreFlash_Write_Inc = 0;

	r_BM_WRITE_LIMIT_temp = 0 ; 
	r_BM_READ_LIMIT_temp = 0 ;	
	r_BM_STACK_RESET_temp = 0 ; 
	r_BM_STACK_WRSET_temp = 0 ;
	r_BM_STACK_RDSET_temp = 0 ;

  p_BM_Base_addr = 0xc0020000; 
}

BufferManager::~BufferManager()
{
	delete AHBv2_spss;
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new BufferManager(ModuleInstanceName);
}
