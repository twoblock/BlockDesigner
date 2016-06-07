#include "MemoryUtility.h"

// Place parameter definitions here:
//defineParameter( "Enable Debug Messages", "false", eslapi::CASI_PARAM_BOOL);
//defineParameter( "Addr_Size", "0x1000", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "Base_Addr", "0x40000000", eslapi::CASI_PARAM_VALUE, 0);
//defineParameter( "Data Width", "32", eslapi::CASI_PARAM_VALUE, 0);

#define Base_Addr 0x40000000
#define Addr_Size 0x1000


void MemoryUtility::update()
{

	// ************************************ //
	// ******  FSM implementation   ******* //
	// ************************************ //

	switch(c_STATE)
	{
		case S_ILDE:
			SRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);
			DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);
	/*		if( Debug_Flag_Read == true )
			{
				Debug_Flag_Read = false;
			}
			if( Debug_Flag_Write == true )
			{
				Debug_Flag_Write = false;
			}*/
			Select_NextState();
			break;
		case S_SRAM_MEMSET:	
			S_MemsetBusrt_And_Select_NextState();	
			break;
		case S_DRAM_MEMSET:	
			D_MemsetBusrt_And_Select_NextState();	
			break;
		case S_MEMCOPY_Read:    // DMA Read
			// SRAM Access
			if( 0x20000000 <= r_MU_SRC_ADDR && r_MU_SRC_ADDR <= 0x3fffffff )
			{
					//if( Debug_Flag_Read == false)
					//{
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,"\nSRAM_Read 0x%x\n",r_MU_SRC_ADDR);
						//Debug_Flag_Read = true;
					//}

				S_MemCopy_Busrt_And_Select_NextState( r_MU_SRC_ADDR );
			}
			// DRAM Access
			else if( 0x60000000 <= r_MU_SRC_ADDR && r_MU_SRC_ADDR <= 0x9fffffff )
			{
				//if( Debug_Flag_Read == false)
				//{
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,"\nDRAM_Read 0x%x\n",r_MU_SRC_ADDR);
					//Debug_Flag_Read = true;
				//}
				D_MemCopy_Busrt_And_Select_NextState( r_MU_SRC_ADDR );
			}

			break;
		case S_MEMCOPY_Write:   // DMA Write
			// SRAM Access
			if( 0x20000000 <= r_MU_DST_ADDR && r_MU_DST_ADDR <= 0x3fffffff )
            {			
				//if( Debug_Flag_Write == false)
				//{
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,"SRAM_Write 0x%x\n",r_MU_DST_ADDR);
					//Debug_Flag_Write = true;
				//}
				S_MemCopy_Busrt_And_Select_NextState( r_MU_DST_ADDR );
			}
				
				// DRAM Access
		else if( 0x60000000 <= r_MU_DST_ADDR && r_MU_DST_ADDR <= 0x9fffffff )
		{
			
		//if( Debug_Flag_Write == false)
				//{
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW,"DRAM_Write 0x%x\n",r_MU_DST_ADDR);
					//Debug_Flag_Write = true;
				//}

			
			D_MemCopy_Busrt_And_Select_NextState( r_MU_DST_ADDR );
		}
		break;
	case S_SRAM_Search_MIN:
		S_MemSearch_Burst_And_Select_NextState(MIN);
		break;
	case S_SRAM_Search_MAX:
		S_MemSearch_Burst_And_Select_NextState(MAX);
		break;
	case S_SRAM_Search_Equal:
		S_MemSearch_Burst_And_Select_NextState(EQUAL);
		break;
	case S_DRAM_Search_MIN:
		D_MemSearch_Burst_And_Select_NextState(MIN);
		break;
	case S_DRAM_Search_MAX:
		D_MemSearch_Burst_And_Select_NextState(MAX);
		break;
	case S_DRAM_Search_Equal:
		D_MemSearch_Burst_And_Select_NextState(EQUAL);
		break;
	default :
		break;
	}


	// *** Memory Utility Register I/O **** //

	RegisterIO();

}

// ******************** //
// *** SRAM Memset  *** //
// ******************** //

bool MemoryUtility::S_Memset_OneBurst()
{
	bool c_SRAM_Granted = SRAM_M_AHBv2_mpms->getSig(BD_HGRANT);
	bool HReady = SRAM_M_AHBv2_mpms->getSig(BD_HREADY);

	SRAM_M_AHBv2_mpms->clear();
	SRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, true); //default

	// ********************************** //
	// *** SRAM AHB Master Interface **** //
	// ********************************** //
	if(c_SRAM_Granted)
	{
		//***** Data phase *****//
		if(c_SRAM_DataPhase)
		{
			SRAM_M_AHBv2_mpms->setWData( r_MU_VALUE , 0);
			if(HReady) 
			{
				c_Index = c_Index + 4;
			}
		}
		// Finish condition
		if( c_Index == c_Excute_Bytes)
		{
			// IDLE
			SRAM_M_AHBv2_mpms->setAddr( 0x20000000 , AHB2_TRANS_IDLE,Read, AHB2_SIZE_DATA8 , AHB2_BURST_SINGLE, 0, false);
			SRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);
			return true;
		}
		//***** Address phase *****//
		if( c_Index == 0 && HReady)
		{
			SRAM_M_AHBv2_mpms->setAddr( r_MU_DST_ADDR + c_Index , AHB2_TRANS_NONSEQ, c_SRAM_write , AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
			c_SRAM_DataPhase = true; 
		}
		else 
		{
			SRAM_M_AHBv2_mpms->setAddr( r_MU_DST_ADDR + c_Index , AHB2_TRANS_SEQ, c_SRAM_write, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
		}
	}
	return false;
}

// ************************* //
// *** SRAM Memset Busrt *** //
// ************************* //

void MemoryUtility::S_MemsetBusrt_And_Select_NextState()
{
	c_WriteBusrtComplete = S_Memset_OneBurst();   // 16 times Busrt

	if( c_Remain_Bytes != 0 && c_WriteBusrtComplete == true ){       // Keep Memset State
		Calculate_Bytes();
		Inc_64Bytes_Dst();

		SRAM_Init(Write);

		c_WriteBusrtComplete	  = false;
		c_ReadBusrtComplete 	  = false;
		c_Index              = 0;
	}
	else if( c_Remain_Bytes == 0 && c_WriteBusrtComplete == true ){  // Select IDLE State

	    Regitser_Initialize();
		
		c_STATE_temp         = S_ILDE;

		SRAM_Init(Read);

		c_WriteBusrtComplete	  = false;
		c_ReadBusrtComplete 	  = false;
		c_Index              = 0;
	}
}

// ******************** //
// *** DRAM Memset  *** //
// ******************** //

bool MemoryUtility::D_Memset_OneBurst()
{
	bool c_DRAM_Granted = DRAM_M_AHBv2_mpms->getSig(BD_HGRANT);
	bool HReady = DRAM_M_AHBv2_mpms->getSig(BD_HREADY);

	DRAM_M_AHBv2_mpms->clear();
	DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, true); //default

	// ********************************** //
	// *** DRAM AHB Master Interface **** //
	// ********************************** //

	if(c_DRAM_Granted)
	{
		//***** Data phase *****//
		if(c_DRAM_DataPhase)
		{
			DRAM_M_AHBv2_mpms->setWData( r_MU_VALUE , 0);
			if(HReady) 
			{
				c_Index = c_Index + 4;
			}
		}
		// Finish condition
		if( c_Index == c_Excute_Bytes)
		{
			// IDLE
			DRAM_M_AHBv2_mpms->setAddr( 0x60000000 , AHB2_TRANS_IDLE ,Read, AHB2_SIZE_DATA8, AHB2_BURST_SINGLE, 0, false);
			DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);
			return true;
		}
		//***** Address phase *****//
		if( c_Index == 0 && HReady)
		{
			DRAM_M_AHBv2_mpms->setAddr( r_MU_DST_ADDR + c_Index , AHB2_TRANS_NONSEQ, c_DRAM_write , AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
			c_DRAM_DataPhase = true; 
		}
		else 
		{
			DRAM_M_AHBv2_mpms->setAddr( r_MU_DST_ADDR + c_Index , AHB2_TRANS_SEQ, c_DRAM_write, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
		}
	}
	return false;
}


// ************************* //
// *** DRAM Memset Busrt *** //
// ************************* //

void MemoryUtility::D_MemsetBusrt_And_Select_NextState()
{
	c_WriteBusrtComplete = D_Memset_OneBurst();   // 16 times Busrt

	if( c_Remain_Bytes != 0 && c_WriteBusrtComplete == true ){       // Keep Memset State
		Calculate_Bytes();
		Inc_64Bytes_Dst();

		DRAM_Init(Write);

		c_WriteBusrtComplete	  = false;
		c_ReadBusrtComplete 	  = false;
		c_Index              	  = 0;
	}
	else if( c_Remain_Bytes == 0 && c_WriteBusrtComplete == true ){  // Select IDLE State
		
	    Regitser_Initialize();
		c_STATE_temp         	  = S_ILDE;

		DRAM_Init(Read);

		c_WriteBusrtComplete	  = false;
		c_ReadBusrtComplete 	  = false;
		c_Index              	  = 0;
	}
}

// ******************** //
// *** SRAM Memcopy *** //
// ******************** //

bool MemoryUtility::SRAM_Memcopy( uint32_t Addr)
{

	bool c_SRAM_Granted = SRAM_M_AHBv2_mpms->getSig(BD_HGRANT);
	bool HReady = SRAM_M_AHBv2_mpms->getSig(BD_HREADY);

	uint32_t l_Index ;

	SRAM_M_AHBv2_mpms->clear();
	SRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, true); //default

	// ********************************** //
	// *** SRAM AHB Master Interface **** //
	// ********************************** //	

	if(c_SRAM_Granted)
	{
		//***** Data phase *****//
		if(c_SRAM_DataPhase)
		{
			l_Index = c_Index/4 ;

			if(c_SRAM_write)
			{
				SRAM_M_AHBv2_mpms->setWData( c_Copy_Data[l_Index] , 0);
				if(HReady) 
				{
					c_Index = c_Index + 4;
				}
			}
			else             // Wait 1cycle
			{
				if(HReady)
				{	//Slave is Ready
					if(c_SRAM_wait_DataPhase)
					{
						c_Copy_Data[l_Index-1] = SRAM_M_AHBv2_mpms->getRData(0);
						c_Index = c_Index + 4;

						if( c_Index == c_Excute_Bytes + 4)
						{
							return true; 
						}
					}
					else 
					{
						c_SRAM_wait_DataPhase = true;
						c_Index = c_Index + 4;
					}
				}
			}
		}
		// Finish condition
		if( c_Index == c_Excute_Bytes)
		{
			// IDLE
			SRAM_M_AHBv2_mpms->setAddr( 0x20000000 , AHB2_TRANS_IDLE ,Read, AHB2_SIZE_DATA8, AHB2_BURST_SINGLE, 0, false);
			SRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);

			if( c_SRAM_write == Write)
				return true; 
		}
		//***** Address phase *****//
		if( c_Index == 0 && HReady)
		{
			SRAM_M_AHBv2_mpms->setAddr( Addr + c_Index , AHB2_TRANS_NONSEQ, c_SRAM_write , AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
			c_SRAM_DataPhase = true; 
		}
		else if( c_Index != c_Excute_Bytes )
		{
			SRAM_M_AHBv2_mpms->setAddr( Addr + c_Index , AHB2_TRANS_SEQ, c_SRAM_write, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
		}
	}
	return false;

}

// ************************** //
// *** SRAM Memcopy Burst *** //
// ************************** //

void MemoryUtility::S_MemCopy_Busrt_And_Select_NextState( uint32_t Addr )
{

	c_WriteBusrtComplete = SRAM_Memcopy( Addr );   // 16 times Busrt

	if( c_Remain_Bytes != 0 && c_WriteBusrtComplete == true ){       // Keep Memset State

		SRAM_DRAM_Master_Init();

		if( c_STATE == S_MEMCOPY_Write )
		{
			Calculate_Bytes();
			Inc_64Bytes_Dst();
			Inc_64Bytes_Src();
			c_SRAM_write              = Read;
			c_DRAM_write              = Read;
			c_STATE_temp         	  = S_MEMCOPY_Read;
		}
		if( c_STATE == S_MEMCOPY_Read )
		{
			c_SRAM_write              = Write;
			c_DRAM_write              = Write;
			c_STATE_temp         	  = S_MEMCOPY_Write;
		}
	}
	else if( c_Remain_Bytes == 0 && c_WriteBusrtComplete == true ){  // Select IDLE State

		SRAM_DRAM_Master_Init();

		if( c_STATE == S_MEMCOPY_Write )
		{
			c_SRAM_write              = Read;
			c_DRAM_write              = Read;
	    
			Regitser_Initialize();

			c_STATE_temp         	  = S_ILDE;
		}
		if( c_STATE == S_MEMCOPY_Read )
		{
			c_SRAM_write              = Write;
			c_DRAM_write              = Write;
			c_STATE_temp         	  = S_MEMCOPY_Write;
		}


	}

}

// ******************** //
// *** DRAM Memcopy *** //
// ******************** //

bool MemoryUtility::DRAM_Memcopy( uint32_t Addr  )
{ 
	bool c_DRAM_Granted = DRAM_M_AHBv2_mpms->getSig(BD_HGRANT);
	bool HReady = DRAM_M_AHBv2_mpms->getSig(BD_HREADY);

	uint32_t l_Index ;

	DRAM_M_AHBv2_mpms->clear();
	DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, true); //default

	// ********************************** //
	// *** DRAM AHB Master Interface **** //
	// ********************************** //

	if(c_DRAM_Granted)
	{
		//***** Data phase *****//
		if(c_DRAM_DataPhase)
		{
			l_Index = c_Index/4 ;

			if(c_DRAM_write)
			{
				DRAM_M_AHBv2_mpms->setWData( c_Copy_Data[l_Index] , 0);
				if(HReady) 
				{
					c_Index = c_Index + 4;
				}
			}
			else             // Wait 1cycle
			{
				if(HReady)
				{	//Slave is Ready
					if(c_DRAM_wait_DataPhase)
					{
						c_Copy_Data[l_Index-1] = DRAM_M_AHBv2_mpms->getRData(0);
						c_Index = c_Index + 4;

						if( c_Index == c_Excute_Bytes + 4)
						{
							return true; 
						}
					}
					else 
					{
						c_DRAM_wait_DataPhase = true;
						c_Index = c_Index + 4;
					}
				}
			}
		}
		// Finish condition
		if( c_Index == c_Excute_Bytes)
		{
			// IDLE
			DRAM_M_AHBv2_mpms->setAddr( 0x60000000 , AHB2_TRANS_IDLE ,Read, AHB2_SIZE_DATA8, AHB2_BURST_SINGLE, 0, false);
			DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);

			if( c_DRAM_write == Write)
				return true; 
		}
		//***** Address phase *****//
		if( c_Index == 0 && HReady)
		{
			DRAM_M_AHBv2_mpms->setAddr( Addr + c_Index , AHB2_TRANS_NONSEQ, c_DRAM_write , AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
			c_DRAM_DataPhase = true; 
		}
		else if( c_Index != c_Excute_Bytes )
		{
			DRAM_M_AHBv2_mpms->setAddr( Addr + c_Index , AHB2_TRANS_SEQ, c_DRAM_write, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
		}
	}
	return false;
}

// ************************** //
// *** DRAM Memcopy Burst *** //
// ************************** //

void MemoryUtility::D_MemCopy_Busrt_And_Select_NextState( uint32_t Addr)
{
	c_WriteBusrtComplete = DRAM_Memcopy( Addr );   // 16 times Busrt

	if( c_Remain_Bytes != 0 && c_WriteBusrtComplete == true ){       // Keep Memset State

		SRAM_DRAM_Master_Init();
		c_DRAM_write              = Write;
 
		if( c_STATE == S_MEMCOPY_Write )
		{
			Calculate_Bytes();
			Inc_64Bytes_Dst();
			Inc_64Bytes_Src();
			c_DRAM_write              = Read;
			c_SRAM_write              = Read;
			c_STATE_temp         	  = S_MEMCOPY_Read;
		}
		if( c_STATE == S_MEMCOPY_Read )
		{
			c_DRAM_write              = Write;
			c_SRAM_write              = Write;
			c_STATE_temp         	  = S_MEMCOPY_Write;
		}
	}
	else if( c_Remain_Bytes == 0 && c_WriteBusrtComplete == true ){  // Select IDLE State

		SRAM_DRAM_Master_Init();

		if( c_STATE == S_MEMCOPY_Write )
		{
			c_DRAM_write              = Read;
			c_SRAM_write              = Read;
			
			Regitser_Initialize();
			
			c_STATE_temp         	  = S_ILDE;
		}
		if( c_STATE == S_MEMCOPY_Read )
		{
			c_DRAM_write              = Write;
			c_SRAM_write              = Write;
			c_STATE_temp         	  = S_MEMCOPY_Write;
		}
	}
}


// ********************** //
// *** SRAM MemSearch *** //
// ********************** //

bool MemoryUtility::SRAM_MemSearch(uint32_t Min_Max_Equal)
{
	bool c_SRAM_Granted = SRAM_M_AHBv2_mpms->getSig(BD_HGRANT);
	bool HReady = SRAM_M_AHBv2_mpms->getSig(BD_HREADY);

	int32_t l_Data;

	SRAM_M_AHBv2_mpms->clear();
	SRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, true); //default

	// ********************************** //
	// *** SRAM AHB Master Interface **** //
	// ********************************** //

	if(c_SRAM_Granted)
	{
		//***** Data phase *****//
		if(c_SRAM_DataPhase)
		{
			// Read 
			if(HReady)
			{	//Slave is Ready
				if(c_SRAM_wait_DataPhase)
				{
					l_Data = SRAM_M_AHBv2_mpms->getRData(0);
					
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, " Addr 0x%x,  Data : 0x%x \n", ( r_MU_SRC_ADDR + c_Index ) , l_Data ) ;	

					Compare_And_Select( l_Data , Min_Max_Equal);

					c_Index = c_Index + 4;

					if( c_Index == c_Excute_Bytes + 4)
					{
						return true; 
					}
				}
				else 
				{
					c_SRAM_wait_DataPhase = true;
					c_Index = c_Index + 4;
				}
			}

		}
		
		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, " Finish Condition  c_Index : 0x%x,  c_Excute_Bytes : 0x%x \n", c_Index , c_Excute_Bytes ) ;	
		
		// Check Finish
		if( c_Index == c_Excute_Bytes)
		{
			// IDLE
			SRAM_M_AHBv2_mpms->setAddr( 0x20000000 , AHB2_TRANS_IDLE ,Read, AHB2_SIZE_DATA8, AHB2_BURST_SINGLE, 0, false);
			SRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);
		}
		//***** Address phase *****//
		if( c_Index == 0 && HReady)
		{
			SRAM_M_AHBv2_mpms->setAddr( r_MU_SRC_ADDR + c_Index , AHB2_TRANS_NONSEQ, Read , AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
			c_SRAM_DataPhase = true; 
		}
		else if( c_Index != c_Excute_Bytes )
		{
			SRAM_M_AHBv2_mpms->setAddr( r_MU_SRC_ADDR + c_Index , AHB2_TRANS_SEQ, Read, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
		}
	}
	return false;
}


// **************************** //
// *** SRAM MemSearch Busrt *** //
// **************************** //

void MemoryUtility::S_MemSearch_Burst_And_Select_NextState(uint32_t Min_Max_Equal)
{

	c_ReadBusrtComplete = SRAM_MemSearch(Min_Max_Equal);   // 16 times Busrt

	if( c_Remain_Bytes != 0 && c_ReadBusrtComplete == true ){       // Keep Memset State
		
		SRAM_Init(Read);

		c_WriteBusrtComplete	  = false;
		c_Index              = 0;

		Calculate_Bytes();
		Inc_64Bytes_Dst();
		Inc_64Bytes_Src();
	}
	else if( c_Remain_Bytes == 0 && c_ReadBusrtComplete == true ){  // Select IDLE State

		SRAM_Init(Read);

		c_ReadBusrtComplete 	  = false;
		c_Index              = 0;

		Regitser_Initialize();
		
		r_MU_RESULT_temp     = c_Result_Index; // c_Index_of_MinMaxEqual;
		c_STATE_temp         = S_ILDE;
	}
}



// ********************** //
// *** DRAM MemSearch *** //
// ********************** //

bool MemoryUtility::DRAM_MemSearch(uint32_t Min_Max_Equal)
{
	bool c_DRAM_Granted = DRAM_M_AHBv2_mpms->getSig(BD_HGRANT);
	bool HReady = DRAM_M_AHBv2_mpms->getSig(BD_HREADY);

	int32_t l_Data;

	DRAM_M_AHBv2_mpms->clear();
	DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, true); //default

	// ********************************** //
	// *** DRAM AHB Master Interface **** //
	// ********************************** //

	/*hhhhhhhhhh
    if( c_Index_of_MinMaxEqual >= r_MU_SIZE ) 
	{	
		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, " Finish !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n ") ;	
	
		// IDLE
		DRAM_M_AHBv2_mpms->setAddr( 0x60000000 , AHB2_TRANS_IDLE ,Read, AHB2_SIZE_DATA8, AHB2_BURST_SINGLE, 0, false);
		DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);

		c_Remain_Bytes = 0;
		return true;
	}
*/

	if(c_DRAM_Granted)
	{		
		//***** Data phase *****//
		if(c_DRAM_DataPhase)
		{
			// Read 
			if(HReady)
			{	//Slave is Ready
				if(c_DRAM_wait_DataPhase)
				{
					l_Data = DRAM_M_AHBv2_mpms->getRData(0);

					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, " Addr 0x%x,  Data : 0x%x \n", ( r_MU_SRC_ADDR + c_Index ) , l_Data ) ;	

					Compare_And_Select( l_Data , Min_Max_Equal);

					c_Index = c_Index + 4;

					if( c_Index == c_Excute_Bytes + 4)
					{
						return true; 
					}
				}
				else 
				{
					c_DRAM_wait_DataPhase = true;
					c_Index = c_Index + 4;
				}
			}
		}

		//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, " Finish Condition  c_Index : 0x%x,  c_Excute_Bytes : 0x%x \n", c_Index , c_Excute_Bytes ) ;	

    	// Finish condition
		if( c_Index == c_Excute_Bytes)
		{
			// IDLE
			DRAM_M_AHBv2_mpms->setAddr( 0x60000000 , AHB2_TRANS_IDLE ,Read, AHB2_SIZE_DATA8, AHB2_BURST_SINGLE, 0, false);
			DRAM_M_AHBv2_mpms->setSig(BD_HBUSREQ, false);
		}
		//***** Address phase *****//
		if( c_Index == 0 && HReady)
		{
			DRAM_M_AHBv2_mpms->setAddr( r_MU_SRC_ADDR + c_Index , AHB2_TRANS_NONSEQ, Read , AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
			c_DRAM_DataPhase = true; 
		}
		else if( c_Index != c_Excute_Bytes )
		{
			DRAM_M_AHBv2_mpms->setAddr( r_MU_SRC_ADDR + c_Index , AHB2_TRANS_SEQ, Read, AHB2_SIZE_DATA32 , AHB2_BURST_INCR, 0, false);
		}
	}
	return false;
}


// **************************** //
// *** DRAM MemSearch Busrt *** //
// **************************** //

void MemoryUtility::D_MemSearch_Burst_And_Select_NextState(uint32_t Min_Max_Equal)
{

	c_ReadBusrtComplete = DRAM_MemSearch(Min_Max_Equal);   // 16 times Busrt

	if( c_Remain_Bytes != 0 && c_ReadBusrtComplete == true ){       // Keep Memset State

		DRAM_Init(Read);

		c_WriteBusrtComplete	  = false;
		c_Index              = 0;

		Calculate_Bytes();
		Inc_64Bytes_Dst();
		Inc_64Bytes_Src();
	}
	else if( c_Remain_Bytes == 0 && c_ReadBusrtComplete == true ){  // Select IDLE State

		DRAM_Init(Read);

		c_ReadBusrtComplete 	  = false;
		c_Index              = 0;
		
		Regitser_Initialize();

		r_MU_RESULT_temp     = c_Result_Index;//  c_Index_of_MinMaxEqual;
		c_STATE_temp         = S_ILDE;
	}	
}


// ********************************** //
// *** Mem Search Assist function *** //
// ********************************** //

void MemoryUtility::Compare_And_Select( int32_t Data , uint32_t Min_Max_Equal )
{
	int32_t Data1 ;		
	int32_t Data2 ;		
	int32_t Data3 ;		
	int32_t Data4 ;		

	// ********************************** //
	// ***    Mem Search Min value    *** //
	// ********************************** //
	if( Min_Max_Equal == MIN )
	{
		if( r_MU_UNITSTEP == Unit32 )
		{	
			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				c_Min = Data;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/4 ;
			/*	if (p_enableDbgMsg == true)
				{
					 
					(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Min\n");
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR  + c_Index - 4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data : 0x%x \n", Data );
				 
				}	*/
			}

			if( Data < c_Min )
			{
				c_Min = Data;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/4 ;
				/*
					if (p_enableDbgMsg == true)
				{
			 
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Change MIN! \n");	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data : 0x%x \n", Data );
						 
				}		*/	
			}
		}
		else if( r_MU_UNITSTEP == Unit16 )
		{

			Data1  =   Data & 0x0000FFFF        ; 
			Data2  = ( Data & 0xFFFF0000 ) >> 16 ;		
				
			c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/2 ;

				//if (p_enableDbgMsg == true)
				//{
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);	
				//}

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				//if (p_enableDbgMsg == true)
				//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Min\n");

				c_Result_Index = 0;	

				if( Data1 <= Data2 )
				{
					c_Min = Data1;
					
					//if (p_enableDbgMsg == true)
					//{
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%x \n", c_Addr_of_MinMaxEqual);	
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					//}
				}
				else if( Data1 > Data2 &&  1 != r_MU_SIZE )
				{
			        c_Result_Index = 1;	
					c_Min = Data2;
				
					//if (p_enableDbgMsg == true)
					//{
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);			
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%x \n", c_Addr_of_MinMaxEqual);	
						//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					//}
				}
			}


			if( Data1 < c_Min )
			{
				c_Result_Index = c_Index_of_MinMaxEqual;	
				c_Min = Data1;
			
				//if (p_enableDbgMsg == true)
				//{
//
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Change Min! \n");	
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%x \n", c_Addr_of_MinMaxEqual);	
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				//}
			}
			
			if( Data2 < c_Min && ( c_Index_of_MinMaxEqual + 1 ) != r_MU_SIZE )
			{
				
				c_Result_Index = c_Index_of_MinMaxEqual+1;	
				c_Min = Data2;
				
				//if (p_enableDbgMsg == true)
				//{
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Change Min! \n");	
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);			
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				//}

			}
		}
		else if( r_MU_UNITSTEP == Unit8 )
		{

			Data1  =   Data & 0x000000FF        ; 
			Data2  = ( Data & 0x0000FF00 ) >> 8 ;		
			Data3  = ( Data & 0x00FF0000 ) >> 16;		
			Data4  = ( Data & 0xFF000000 ) >> 24;	

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) ;

			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Min\n");

				if( Data1 <= Data2 )
				{
					c_Min = Data1;
					/*
					if (p_enableDbgMsg == true)
					{
					 
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					 
					}	*/
				}
				else 
				{
					c_Min = Data2;
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 1;
					
					/*
					if (p_enableDbgMsg == true)
					{
					
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);

					}
					*/
				}
				if( Data3 < c_Min )
				{
					c_Min = Data3;
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 2;
						/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data3 : 0x%x \n", Data3);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
					*/
				}

				if( Data4 < c_Min )
				{
					c_Min = Data4;
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 3;
					/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data4 : 0x%x \n", Data4);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
						*/
				}
			}

			if( Data1 < c_Min)
			{
				c_Min = Data1;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) ;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
					*/
			}

			if( Data2 < c_Min) 
			{
				c_Min = Data2;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 1;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
					*/
			}

			if( Data3 < c_Min )
			{
				c_Min = Data3;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 2;
				/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data3 : 0x%x \n", Data3);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
					*/
			}

			if( Data4 < c_Min )
			{
				c_Min = Data4;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 3;
				/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data4 : 0x%x \n", Data4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
					*/
			}
		}
	}

// ********************************** //
// ***    Mem Search Max value    *** //
// ********************************** //
	if( Min_Max_Equal == MAX )
	{
		if( r_MU_UNITSTEP == Unit32 )
		{

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{

				c_Max = Data;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/4 ;
/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Max\n");
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR  + c_Index - 4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data : 0x%x \n", Data );
				}
					*/
			}

			if( Data > c_Max )
			{
				c_Max = Data;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/4 ;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Change Max! \n");	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data : 0x%x \n", Data );
				}
					*/
			}
		}
		else if(r_MU_UNITSTEP == Unit16 )
		{
			Data1  =   Data & 0x0000FFFF        ; 
			Data2  = ( Data & 0xFFFF0000 ) >> 16 ;		

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/2 ;

			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Max\n");

				if( Data1 >= Data2 )
				{
					c_Max = Data1;
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
						*/
				}
				else if( Data1 < Data2)
				{
					c_Max = Data2;
					c_Index_of_MinMaxEqual += 1;	
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);			
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
					*/
				}
			}

			if( Data1 > c_Max )
			{
			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Change Max! \n");	
				c_Max = Data1;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/2 ;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
				*/
			}
			else if( Data2 > c_Max )
			{
			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Change Max! \n");	
				c_Max = Data2;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/2 ;
				c_Index_of_MinMaxEqual += 1;	
			/*	
			if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);			
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
				*/
			}
		}	
		else if( r_MU_UNITSTEP == Unit8 )
		{
			Data1  =   Data & 0x000000FF        ; 
			Data2  = ( Data & 0x0000FF00 ) >> 8 ;		
			Data3  = ( Data & 0x00FF0000 ) >> 16;		
			Data4  = ( Data & 0xFF000000 ) >> 24;	

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) ;

			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Max\n");

				if( Data1 >= Data2 )
				{
					c_Max = Data1;
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
					*/
				}
				else 
				{
					c_Max = Data2;
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 1;
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
				*/
				}

				if( Data3 > c_Max )
				{
					c_Max = Data3;
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 2;
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data3 : 0x%x \n", Data3);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
				*/
				}

				if( Data4 > c_Max )
				{
					c_Max = Data4;
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 3;
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data4 : 0x%x \n", Data4);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
				*/
				}
			}

			if( Data1 > c_Max)
			{
				c_Max = Data1;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) ;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}

			if( Data2 > c_Max) 
			{
				c_Max = Data2;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 1;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}

			if( Data3 > c_Max )
			{
				c_Max = Data3;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 2;
			/*	if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data3 : 0x%x \n", Data3);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}

			if( Data4 > c_Max )
			{
				c_Max = Data4;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 3;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data4 : 0x%x \n", Data4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}
		}
	}
// ********************************** //
// ***   Mem Search Equal value   *** //
// ********************************** //
	if( Min_Max_Equal == EQUAL)
	{
		if( r_MU_UNITSTEP == Unit32 )
		{	

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				//c_Min = Data;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/4 ;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Equal\n");
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR  + c_Index - 4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data : 0x%x \n", Data );
				}
				*/
			
			}
			/*if (p_enableDbgMsg == true)
			{
				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data : 0x%x \n", Data );
				message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Equal: 0x%x \n", c_Equal);
			}
          */
		  
			if( Data == c_Equal )
			{
				//c_Min = Data;
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/4 ;
		   /*
		 		if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Change Equal! \n");	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data : 0x%x \n", Data );
				}
			*/
			}
		}
		else if( r_MU_UNITSTEP == Unit16 )
		{
			Data1  =   Data & 0x0000FFFF        ; 
			Data2  = ( Data & 0xFFFF0000 ) >> 16 ;		

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/2 ;

		//		message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Equal\n");

				if( Data1 == c_Equal )
				{
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
					*/
				}
				else if( Data2 == c_Equal )
				{
					c_Index_of_MinMaxEqual += 1;	
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);			
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
				*/
				}
			}


			if( Data1 == c_Equal )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/2 ;
				/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}*/
			}
			else if( Data2 == c_Equal )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual )/2 ;
				c_Index_of_MinMaxEqual += 1;	
				/* if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);			
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				} */
			}
		}
		else if( r_MU_UNITSTEP == Unit8 )
		{

			Data1  =   Data & 0x000000FF        ; 
			Data2  = ( Data & 0x0000FF00 ) >> 8 ;		
			Data3  = ( Data & 0x00FF0000 ) >> 16;		
			Data4  = ( Data & 0xFF000000 ) >> 24;	

			if( ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) == 0 )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) ;

			//	message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Initial Equal\n");

				if( Data1 == c_Equal )
				{
				/*	if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
					*/
				}
				else if( Data2 == c_Equal )
				{
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 1;
				
				/*	if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
					*/
				}

				if( Data3 == c_Equal )
				{
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 2;
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data3 : 0x%x \n", Data3);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
				*/
				}

				if( Data4 == c_Equal )
				{
					c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 3;
				/*
					if (p_enableDbgMsg == true)
					{
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data4 : 0x%x \n", Data4);
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual );	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
						message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
					}
				*/
				}
			}


			if( Data1 == c_Equal )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) ;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data1 : 0x%x \n", Data1);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}

			if( Data2 == c_Equal ) 
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 1;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data2 : 0x%x \n", Data2);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}

			if( Data3 == c_Equal )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 2;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data3 : 0x%x \n", Data3);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}

			if( Data4 == c_Equal )
			{
				c_Index_of_MinMaxEqual = ( ( r_MU_SRC_ADDR + c_Index - 4 ) - c_Addr_of_MinMaxEqual ) + 3;
			/*
				if (p_enableDbgMsg == true)
				{
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Data4 : 0x%x \n", Data4);
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Index_of_MinMaxEqual : %d \n", c_Index_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "c_Addr_of_MinMaxEqual  : 0x%d \n", c_Addr_of_MinMaxEqual);	
					message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "Addr : 0x%x \n", r_MU_SRC_ADDR + c_Index - 4);
				}
			*/
			}
		}
	}
}

	// ********************************** //
	// *******  In IDLE State      ****** //
	// *******  Select Next State  ****** //
	// ********************************** //

void MemoryUtility::Select_NextState()
{
	switch( r_MU_CMD )
	{
	case MU_CMD_SET_REPT_SRAM:	
		SRAM_Init( Write ); 
		Master_Init(); 
		Calculate_Bytes();		
		r_MU_RESULT_temp          = 0xFFFFFFFF; 
		c_STATE_temp              = S_SRAM_MEMSET;    
		break; 
	case MU_CMD_SET_REPT_DRAM:	
		DRAM_Init( Write ); 
		Master_Init(); 
		Calculate_Bytes();		
		r_MU_RESULT_temp          = 0xFFFFFFFF; 
		c_STATE_temp			  = S_DRAM_MEMSET; 
		break; 
	case MU_CMD_COPY:	
		SRAM_Init( Read ); 
		DRAM_Init( Read );
		Master_Init();
		Calculate_Bytes();		

		r_MU_RESULT_temp          = 0xFFFFFFFF;
		c_STATE_temp 			  = S_MEMCOPY_Read;
		break;
	case MU_CMD_SEARCH_MAX_SRAM:	

		SRAM_Init( Read );
		Master_Init();
		Calculate_Bytes();		

		c_Index_of_MinMaxEqual    = 0;
		c_Addr_of_MinMaxEqual	  = r_MU_SRC_ADDR;
		c_UnitStep				  = r_MU_UNITSTEP;	
		r_MU_RESULT_temp          = 0xFFFFFFFF;
		c_STATE_temp 			  = S_SRAM_Search_MAX;			
		break;
	case MU_CMD_SEARCH_MIN_SRAM:	

		SRAM_Init( Read );
		Master_Init();
		Calculate_Bytes();		

		c_Index_of_MinMaxEqual    = 0;
		c_Addr_of_MinMaxEqual	  = r_MU_SRC_ADDR;
		c_UnitStep				  = r_MU_UNITSTEP;	
		r_MU_RESULT_temp          = 0xFFFFFFFF;
		c_STATE_temp			  = S_SRAM_Search_MIN;


		break;
	case MU_CMD_SEARCH_EQU_SRAM:	

		SRAM_Init( Read );
		Master_Init();
		Calculate_Bytes();		

		c_Index_of_MinMaxEqual    = 0;
		c_Addr_of_MinMaxEqual	  = r_MU_SRC_ADDR;
		c_UnitStep				  = r_MU_UNITSTEP;	
		c_Equal                   = r_MU_VALUE; 
		r_MU_RESULT_temp          = 0xFFFFFFFF;
		c_STATE_temp			  = S_SRAM_Search_Equal;

		break;
	case MU_CMD_SEARCH_MAX_DRAM:	

		DRAM_Init( Read );
		Master_Init();
		Calculate_Bytes();		

		c_Index_of_MinMaxEqual    = 0;
		c_Addr_of_MinMaxEqual	  = r_MU_SRC_ADDR;
		c_UnitStep				  = r_MU_UNITSTEP;	
		r_MU_RESULT_temp          = 0xFFFFFFFF;
		c_STATE_temp			  = S_DRAM_Search_MAX;
		break;
	case MU_CMD_SEARCH_MIN_DRAM:	

		DRAM_Init( Read );
		Master_Init();
		Calculate_Bytes();		

		c_Index_of_MinMaxEqual    = 0;
		c_Addr_of_MinMaxEqual	  = r_MU_SRC_ADDR;
		c_UnitStep				  = r_MU_UNITSTEP;	
		r_MU_RESULT_temp          = 0xFFFFFFFF;
		c_STATE_temp 			  = S_DRAM_Search_MIN;
		break;
	case MU_CMD_SEARCH_EQU_DRAM:	

		DRAM_Init( Read );
		Master_Init();
		Calculate_Bytes();		

		c_Index_of_MinMaxEqual    = 0;
		c_Addr_of_MinMaxEqual	  = r_MU_SRC_ADDR;
		c_UnitStep				  = r_MU_UNITSTEP;	
		c_Equal                   = r_MU_VALUE; 
		r_MU_RESULT_temp          = 0xFFFFFFFF;
		c_STATE_temp			  = S_DRAM_Search_Equal;
		break;
	default:
		if(r_MU_RESULT == 0xFFFFFFFF)
		  r_MU_RESULT_temp        = 0x0;
		c_STATE_temp			  = S_ILDE;
		break;
	}
}


void MemoryUtility::Calculate_Bytes()
{
	if( c_Remain_Bytes > 64 )
	{
		c_Excute_Bytes = 64;
		c_Remain_Bytes = c_Remain_Bytes- 64;
	}
	else
	{
		c_Excute_Bytes = c_Remain_Bytes;
		c_Remain_Bytes = 0;
	}
}

void MemoryUtility::Inc_64Bytes_Src()
{
	r_MU_SRC_ADDR_temp = r_MU_SRC_ADDR + 64;
}

void MemoryUtility::Inc_64Bytes_Dst()
{
	r_MU_DST_ADDR_temp = r_MU_DST_ADDR + 64;
}


void MemoryUtility::SRAM_Init(bool IsWrite)
{
	c_SRAM_wait_DataPhase	  = false;
	c_SRAM_DataPhase          = false;
	c_SRAM_write              = IsWrite;
	c_SRAM_Granted			  = false;
}
void MemoryUtility::DRAM_Init(bool IsWrite)
{
	c_DRAM_wait_DataPhase	  = false;
	c_DRAM_DataPhase          = false;
	c_DRAM_write              = IsWrite;	
	c_DRAM_Granted			  = false;
}
void MemoryUtility::Master_Init()
{
	c_WriteBusrtComplete	  = false;
	c_ReadBusrtComplete 	  = false;
	c_Index 				  = 0;			
	c_Excute_Bytes			  = 0;
	c_Remain_Bytes			  = r_MU_SIZE;

	if(
    r_MU_CMD == MU_CMD_SEARCH_MAX_SRAM || 
	r_MU_CMD == MU_CMD_SEARCH_EQU_SRAM ||
	r_MU_CMD == MU_CMD_SEARCH_MIN_SRAM ||
    r_MU_CMD == MU_CMD_SEARCH_MAX_DRAM || 
	r_MU_CMD == MU_CMD_SEARCH_EQU_DRAM ||
	r_MU_CMD == MU_CMD_SEARCH_MIN_DRAM  
	)
	{

		if( r_MU_UNITSTEP == Unit8 )
		c_Remain_Bytes = c_Remain_Bytes * 4;
	else if( r_MU_UNITSTEP == Unit16 )
	{
		c_Remain_Bytes = c_Remain_Bytes * 2;

		if( c_Remain_Bytes % 4 != 0 )
		{
			c_Remain_Bytes = c_Remain_Bytes + c_Remain_Bytes % 4;
		}

	}
	else if( r_MU_UNITSTEP == Unit32 )
		c_Remain_Bytes = c_Remain_Bytes * 4;
	}	
}

void MemoryUtility::SRAM_DRAM_Master_Init()
{
	c_SRAM_wait_DataPhase	  = false;
	c_SRAM_DataPhase          = false;
	c_SRAM_Granted			  = false;
	
	c_DRAM_wait_DataPhase	  = false;
	c_DRAM_DataPhase          = false;	
	c_DRAM_Granted			  = false;

	c_WriteBusrtComplete	  = false;
	c_ReadBusrtComplete 	  = false;
	c_Index 				  = 0;			
}

void MemoryUtility::Regitser_Initialize ()
{

	r_MU_SRC_ADDR_temp   = 0;
	r_MU_DST_ADDR_temp   = 0;
	r_MU_SIZE_temp       = 0;
    r_MU_VALUE_temp      = 0;
	r_MU_UNITSTEP_temp   = 0;
	r_MU_CMD_temp        = 0xFFFFFFFF;
}

	// ********************************** //
	// *******    Register I/O    ******* //
	// ********************************** //

void MemoryUtility::RegisterIO()
{
	uint32_t offset = 0; 
	uint32_t write_data = 0;

	S_AHBv2_spss->clear();
	S_AHBv2_spss->setSig(BD_HREADYOUT, true);

	// ********************************** //
	// ******* AHB Slave Interface ****** //
	// ********************************** //

	// ******** Data Phase ********* // 
	if(c_Slave_isDataCycleActive)
	{
		// we're handling a DATA transfer. check for wait states.
		if(--c_Slave_currentWait <= 0)
		{
			// done with this DATA transfer
			c_Slave_currentWait = c_Slave_waitCycles;
			c_Slave_isDataCycleActive = false;

			offset = c_Slave_addr - (uint32_t)p_Base_Addr;
			write_data = S_AHBv2_spss->getWData(0);

			if (c_Slave_isWrite)
			{
				WriteRegieter(offset, write_data);
			}
			else
			{
				ReadRegister(offset);	
			}

			S_AHBv2_spss->setSig(BD_HREADYOUT, true);
		} //if wait == 0
	}  
	else
	{
		S_AHBv2_spss->setSig(BD_HREADYOUT, false);
	}

	// ******** Address Phase ********* // 
	if ((S_AHBv2_spss->getSig(BD_HTRANS) != AHB2_TRANS_IDLE) && 
		(S_AHBv2_spss->getSig(BD_HTRANS) != AHB2_TRANS_BUSY) &&
		(S_AHBv2_spss->getSig(BD_HSEL)) && 
		(S_AHBv2_spss->getSig(BD_HREADY)))
	{
		c_Slave_addr = (uint32_t)S_AHBv2_spss->getSig(BD_HADDR);

		if (S_AHBv2_spss->getSig(BD_HWRITE))
		{
			c_Slave_isWrite = true;
		}
		else
		{
			c_Slave_isWrite = false;
			//zero wait	
			if( c_Slave_currentWait <= 0)
			{
				offset = c_Slave_addr - (uint32_t)p_Base_Addr;
				ReadRegister(offset);
			}
		}
		c_Slave_isDataCycleActive = true;

		if( c_Slave_currentWait <= 0)
		{
			//read
			S_AHBv2_spss->setSig(BD_HREADYOUT, true);
		}
		else
		{
			S_AHBv2_spss->setSig(BD_HREADYOUT, false);
		}
	}
	else
	{		
		c_Slave_isDataCycleActive = false;
	}

	r_MU_SRC_ADDR   =  r_MU_SRC_ADDR_temp;
	r_MU_DST_ADDR   =  r_MU_DST_ADDR_temp;
	r_MU_VALUE      =  r_MU_VALUE_temp;
	r_MU_SIZE       =  r_MU_SIZE_temp;
	r_MU_RESULT     =  r_MU_RESULT_temp;
	r_MU_CMD        =  r_MU_CMD_temp;
	r_MU_UNITSTEP   =  r_MU_UNITSTEP_temp;
	c_STATE         =  c_STATE_temp;


}

	// ********************************** //
	// *******   Write Register   ******* //
	// ********************************** //

void MemoryUtility::WriteRegieter(uint32_t offset, uint32_t w_data)
{
	switch(offset){
	case MU_SRC_ADDR: 
		r_MU_SRC_ADDR_temp= w_data;
		break;
	case MU_DST_ADDR:    
		r_MU_DST_ADDR_temp= w_data;
		break;
	case MU_VALUE: 	
		r_MU_VALUE_temp = w_data;
		break;
	case MU_SIZE:		
		r_MU_SIZE_temp = w_data;
		break;
	case MU_RESULT:   	// Read Only
		//if (p_enableDbgMsg == true)
		//{
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "(Attempt to write to read only register - ignoring request(offset : 0x%X))\n",offset);
		//}
		break;
	case MU_CMD:	
		r_MU_CMD_temp = w_data;
		break;
	case MU_UNITSTEP: 	
		r_MU_UNITSTEP_temp= w_data;
		break;
	default :
		//if (p_enableDbgMsg == true)
		//{
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "(Error! Access to out of range!(offset : 0x%x))\n", offset);
		//}
		break;
	}	


}

	// ********************************** //
	// *******   Read Register    ******* //
	// ********************************** //

void MemoryUtility::ReadRegister(uint32_t offset)
{

	switch(offset){
	case MU_SRC_ADDR:		
		S_AHBv2_spss->setRData(r_MU_SRC_ADDR );
		break;
	case MU_DST_ADDR:
		S_AHBv2_spss->setRData( r_MU_DST_ADDR);
		break;
	case MU_VALUE:     
		S_AHBv2_spss->setRData( r_MU_VALUE);
		break;
	case MU_SIZE:		
		S_AHBv2_spss->setRData(r_MU_SIZE );
		break;
	case MU_RESULT:
		S_AHBv2_spss->setRData(r_MU_RESULT );
		break;
	case MU_CMD:
		S_AHBv2_spss->setRData(r_MU_CMD );
		break;
	case MU_UNITSTEP:
		S_AHBv2_spss->setRData(r_MU_UNITSTEP );
		break;
	default: 
		//if (p_enableDbgMsg == true)
		//{
			//message(eslapi::CASI_MSG_FPUTS_CONSOLE_WINDOW, "(Error! Access to out of range!(offset : 0x%x))\n", offset);
		//}
		S_AHBv2_spss->setRData( 0 );
		break;
	}
}

BDDI* MemoryUtility::GetBDDI()
{
	return bddi;
}

char* MemoryUtility::GetModuleName()
{
	return (char*)"MemoryUtility";
}

void MemoryUtility::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	SRAM_M_AHBv2_mpms = new BD_AHBPort_MM((char*)"MM_M0");
	DRAM_M_AHBv2_mpms = new BD_AHBPort_MM((char*)"MM_M1");
	S_AHBv2_spss = new BD_AHBPort_SS((char*)"SS_S0");

	// for BDDI
	bddi = new MemoryUtility_BDDI(this);

	r_MU_SRC_ADDR	  =		r_MU_SRC_ADDR_temp	   =	 0;
	r_MU_DST_ADDR	  =		r_MU_DST_ADDR_temp	   =	 0;
	r_MU_VALUE		  =		r_MU_VALUE_temp		   =	 0;
	r_MU_SIZE		  =		r_MU_SIZE_temp		   =	 0;
	r_MU_RESULT		  =		r_MU_RESULT_temp	   =	 0;
	r_MU_CMD		  =		r_MU_CMD_temp		   =	 0xFFFFFFFF;
	r_MU_UNITSTEP	  =		r_MU_UNITSTEP_temp	   =	 0;

	c_Slave_waitCycles        = 0;
	c_Slave_currentWait       = c_Slave_waitCycles;
	c_Slave_addr			  = 0;
	c_Slave_isWrite	 		  = false;
	c_Slave_isDataCycleActive = false; 


	c_DRAM_wait_DataPhase	  = false;
	c_DRAM_DataPhase          = false;
	c_DRAM_write         	  = Read;	
	c_DRAM_Granted       	  = false;

	c_SRAM_wait_DataPhase 	  = false;
	c_SRAM_DataPhase      	  = false;
	c_SRAM_write          	  = Read;	
	c_SRAM_Granted        	  = false;

	c_STATE               	  = S_ILDE ;
	c_STATE_temp         	  =  S_ILDE ; 

	c_WriteBusrtComplete      = false;
	c_ReadBusrtComplete       = false;
	c_Index               	  = 0;          
	c_Excute_Bytes        	  = 0;
	c_Remain_Bytes        	  = 0;

	Debug_Flag_Read = false;
	Debug_Flag_Write= false;
	
	for( int i = 0; i<16 ; i++ )
	{
		c_Copy_Data[i] = 0;
	}
}

MemoryUtility::~MemoryUtility()
{
	delete SRAM_M_AHBv2_mpms;
	delete DRAM_M_AHBv2_mpms;
	delete S_AHBv2_spss;
	delete bddi;
}
extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new MemoryUtility(ModuleInstanceName);
}
