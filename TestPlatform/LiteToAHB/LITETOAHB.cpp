//-------------------------------------------------------------
// Design	: LITETOAHB
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: LITETOAHB.cpp
// Date		: 2015. 11. 20
// Reference	: LITETOAHB.v (by Changwon Choi)
//------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: AHB Lite for processor
//-------------------------------------------------------------

#include "LITETOAHB.h"

BDDI* LITETOAHB::GetBDDI()
{
	return bddi;
}

BDMMI* LITETOAHB::GetBDMMI()
{
	return bdmmi;
}

void LITETOAHB::do_transfer()	
{
	assign_signals(AHBMaster_M0, AHBLiteMaster_M0);
}

void LITETOAHB::assign_signals(BD_AHBPort_MM *Master, BD_AHBLitePort_MS *Slave)
{
	Master->HADDR = Slave->HADDR;
	Master->HBURST = Slave->HBURST;
	Master->HPROT = Slave->HPROT;
	Master->HSIZE = Slave->HSIZE;
	Master->HTRANS = Slave->HTRANS;
	Master->HWDATA = Slave->HWDATA;
	Master->HWRITE = Slave->HWRITE;
	Master->HLOCK = Slave->HLOCK;

	switch(state){
		case IDLE: 
			First = false;
			Master->HBUSREQ = false;
			Slave->HREADY = (Master->HREADY && Master->HGRANT);
			break;
		case REQ: 
			Master->HBUSREQ = true;
			Slave->HREADY = false;
			break;
		case GRANTED: 
			if(Slave->HTRANS == 0x2){
				Master->HBUSREQ = true;
			}
			else{
				Master->HBUSREQ = false;
			}

			if(Master->HGRANT == false){
				if(Slave->HTRANS == 0x0){
					Slave->HREADY = Master->HREADY;
				}
				else if(Slave->HTRANS == 0x2){
					Slave->HREADY = Master->HREADY;
				}
			}
			else if(First == false){
				Slave->HREADY = false;
				First = true;	
			}
			else
				Slave->HREADY = (Master->HREADY && Master->HGRANT);
			break;
		case LASTDATA: 
			Slave->HREADY = Master->HREADY;
			if(Master->HREADY == true)
				//state = IDLE;
			break;
		default: 
			//state = IDLE;
			Slave->HREADY = (Master->HREADY && Master->HGRANT);
			break;
	}

	Slave->HRESP = Master->HRESP;
	Slave->HRDATA = Master->HRDATA;
}

void LITETOAHB::FSM()
{
	switch(state){
		case IDLE: 
			IdleCount++;
			if(IdleCount == 0x10){
				IdleCount = 0;
				state = REQ;
			}
			break;
		case REQ: 
			ReqCount++;
			if(ReqCount == 0x10){
				ReqCount = 0;
				state = IDLE;
			}
			if(AHBMaster_M0->HGRANT && AHBMaster_M0->HREADY){
				state = GRANTED;
			}			
			break;
		case GRANTED: 
			if(AHBMaster_M0->HGRANT == false){
				if(AHBLiteMaster_M0->HTRANS == 0x0){
					if(AHBMaster_M0->HREADY == true)
						state = IDLE;
				}
				else if(AHBLiteMaster_M0->HTRANS == 0x2){
					if(AHBMaster_M0->HREADY == true)
						state = LASTDATA;
				}
			}
			break;
		case LASTDATA: 
			if(AHBMaster_M0->HREADY == true)
				state = IDLE;
			break;
		default: 
			state = IDLE;
			break;
	}
}

char* LITETOAHB::GetModuleName()
{
	return (char*)"LITETOAHB";
}

void LITETOAHB::BDInit()
{
	// Global Clock & Resetn
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	// Master(Cortex-M0DS) Interface
	AHBMaster_M0 = new BD_AHBPort_MM((char*)"MM_M0");
	// Slave 0 Interface
	AHBLiteMaster_M0 = new BD_AHBLitePort_MS((char*)"MS_M0");

	bddi = new LITETOAHB_BDDI(this);
	bdmmi = new LITETOAHB_BDMMI(this);
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new LITETOAHB(ModuleInstanceName);
}
