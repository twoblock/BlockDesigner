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

	if(Slave->HTRANS == 0x2)
		Master->HBUSREQ = true;
	else
		Master->HBUSREQ = false;

	//Slave->HREADY = (Master->HREADY && Master->HGRANT);
	Slave->HREADY = Master->HREADY;
	Slave->HRESP = Master->HRESP;
	Slave->HRDATA = Master->HRDATA;
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
