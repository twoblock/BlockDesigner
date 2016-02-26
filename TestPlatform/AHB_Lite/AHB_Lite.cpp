//-------------------------------------------------------------
// Design	: AHB_Lite
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: AHB_Lite.cpp
// Date		: 2015. 11. 20
// Reference	: AHB_Lite.v (by Changwon Choi)
//------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: AHB Lite for processor
//-------------------------------------------------------------

#include "AHB_Lite.h"

void AHB_Lite::do_transfer()	
{
  assign_signals(AHBSlave_S0, AHBMaster_M0);
  assign_signals(AHBSlave_S1, AHBMaster_M0);
  assign_signals(AHBSlave_S2, AHBMaster_M0);
  assign_signals(AHBSlave_S3, AHBMaster_M0);
  assign_signals(AHBSlave_S4, AHBMaster_M0);
  assign_signals(AHBSlave_S5, AHBMaster_M0);
  assign_signals(AHBSlave_S6, AHBMaster_M0);
  assign_signals(AHBSlave_S7, AHBMaster_M0);
  assign_signals(AHBSlave_S8, AHBMaster_M0);
  assign_signals(AHBSlave_S9, AHBMaster_M0);
}

void AHB_Lite::assign_signals(BD_AHBPort_SM *Slave, BD_AHBPort_MS *Master)
{
	Slave->HADDR = Master->HADDR;
	Slave->HBURST = Master->HBURST;
	Slave->HLOCK = Master->HLOCK;
	Slave->HPROT = Master->HPROT;
	Slave->HSIZE = Master->HSIZE;
	Slave->HTRANS = Master->HTRANS;
	Slave->HWDATA = Master->HWDATA;
	Slave->HWRITE = Master->HWRITE;
	Slave->HREADY = Master->HREADY;
}

BDDI* AHB_Lite::GetBDDI()
{
	return bddi;
}

BDMMI* AHB_Lite::GetBDMMI()
{
	return bdmmi;
}

char* AHB_Lite::GetModuleName()
{
	return (char*)"AHB_Lite";
}

void AHB_Lite::BDInit()
{
	// Global Clock & Resetn
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");
	HSEL_NOMAP.set_port_name("HSEL_NOMAP");

	// Master(Cortex-M0DS) Interface
	AHBMaster_M0 = new BD_AHBPort_MS((char*)"M0");

	// Slave 0 Interface
	AHBSlave_S0 = new BD_AHBPort_SM((char*)"S0");
	AHBSlave_S1 = new BD_AHBPort_SM((char*)"S1");
	AHBSlave_S2 = new BD_AHBPort_SM((char*)"S2");
	AHBSlave_S3 = new BD_AHBPort_SM((char*)"S3");
	AHBSlave_S4 = new BD_AHBPort_SM((char*)"S4");
	AHBSlave_S5 = new BD_AHBPort_SM((char*)"S5");
	AHBSlave_S6 = new BD_AHBPort_SM((char*)"S6");
	AHBSlave_S7 = new BD_AHBPort_SM((char*)"S7");
	AHBSlave_S8 = new BD_AHBPort_SM((char*)"S8");
	AHBSlave_S9 = new BD_AHBPort_SM((char*)"S9");

	bddi = new AHB_Lite_BDDI(this);
	bdmmi = new AHB_Lite_BDMMI(this);
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new AHB_Lite(ModuleInstanceName);
}
