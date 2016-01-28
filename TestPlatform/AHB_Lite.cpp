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

void AHB_Lite::do_transfer()	{
	HADDR_S = HADDR_M;
	HBURST_S = HBURST_M;
	HLOCK_S = HLOCK_M;
	HPROT_S = HPROT_M;
	HSIZE_S = HSIZE_M;
	HTRANS_S = HTRANS_M;
	HWDATA_S = HWDATA_M;
	HWRITE_S = HWRITE_M;
	HREADY_S = HREADY_M;
}

BDDI* AHB_Lite::GetBDDI()
{
	return bddi;
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

	// Master(Cortex-M0DS) Interface
	HADDR_M.set_port_name("HADDR_M");
	HBURST_M.set_port_name("HBURST_M");
	HLOCK_M.set_port_name("HLOCK_M");
	HPROT_M.set_port_name("HPROT_M");
	HSIZE_M.set_port_name("HSIZE_M");
	HTRANS_M.set_port_name("HTRANS_M");
	HWDATA_M.set_port_name("HWDATA_M");
	HWRITE_M.set_port_name("HWRITE_M");
	HRDATA_M.set_port_name("HRDATA_M");
	HREADY_M.set_port_name("HREADY_M");
	HRESP_M.set_port_name("HRESP_M");

	// Common Slave Interface
	HADDR_S.set_port_name("HADDR_S");
	HBURST_S.set_port_name("HBURST_S");
	HLOCK_S.set_port_name("HLOCK_S");
	HPROT_S.set_port_name("HPROT_S");
	HSIZE_S.set_port_name("HSIZE_S");
	HTRANS_S.set_port_name("HTRANS_S");
	HWDATA_S.set_port_name("HWDATA_S");
	HWRITE_S.set_port_name("HWRITE_S");
	HREADY_S.set_port_name("HREADY_S");

	// Slave 0 Interface
	HSEL_S0.set_port_name("HSEL_S0");
	HREADYOUT_S0.set_port_name("HREADYOUT_S0");
	HRESP_S0.set_port_name("HRESP_S0");
	HRDATA_S0.set_port_name("HRDATA_S0");

	// Slave 1 Interface
	HSEL_S1.set_port_name("HSEL_S1");
	HREADYOUT_S1.set_port_name("HREADYOUT_S1");
	HRESP_S1.set_port_name("HRESP_S1");
	HRDATA_S1.set_port_name("HRDATA_S1");

	// Slave 2 Interface
	HSEL_S2.set_port_name("HSEL_S2");
	HREADYOUT_S2.set_port_name("HREADYOUT_S2");
	HRESP_S2.set_port_name("HRESP_S2");
	HRDATA_S2.set_port_name("HRDATA_S2");

	// Slave 3 Interface
	HSEL_S3.set_port_name("HSEL_S3");
	HREADYOUT_S3.set_port_name("HREADYOUT_S3");
	HRESP_S3.set_port_name("HRESP_S3");
	HRDATA_S3.set_port_name("HRDATA_S3");

	// Slave 4 Interface
	HSEL_S4.set_port_name("HSEL_S4");
	HREADYOUT_S4.set_port_name("HREADYOUT_S4");
	HRESP_S4.set_port_name("HRESP_S4");
	HRDATA_S4.set_port_name("HRDATA_S4");

	// Slave 5 Interface
	HSEL_S5.set_port_name("HSEL_S5");
	HREADYOUT_S5.set_port_name("HREADYOUT_S5");
	HRESP_S5.set_port_name("HRESP_S5");
	HRDATA_S5.set_port_name("HRDATA_S5");

	// Slave 6 Interface
	HSEL_S6.set_port_name("HSEL_S6");
	HREADYOUT_S6.set_port_name("HREADYOUT_S6");
	HRESP_S6.set_port_name("HRESP_S6");
	HRDATA_S6.set_port_name("HRDATA_S6");

	// Slave 7 Interface
	HSEL_S7.set_port_name("HSEL_S7");
	HREADYOUT_S7.set_port_name("HREADYOUT_S7");
	HRESP_S7.set_port_name("HRESP_S7");
	HRDATA_S7.set_port_name("HRDATA_S7");

	// Slave 8 Interface
	HSEL_S8.set_port_name("HSEL_S8");
	HREADYOUT_S8.set_port_name("HREADYOUT_S8");
	HRESP_S8.set_port_name("HRESP_S8");
	HRDATA_S8.set_port_name("HRDATA_S8");

	// Slave 9 Interface
	HSEL_S9.set_port_name("HSEL_S9");
	HREADYOUT_S9.set_port_name("HREADYOUT_S9");
	HRESP_S9.set_port_name("HRESP_S9");
	HRDATA_S9.set_port_name("HRDATA_S9");

	HSEL_NOMAP.set_port_name("HSEL_NOMAP");

	bddi = new AHB_Lite_BDDI(this);
}

//extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
//{
	//return new AHB_Lite(ModuleInstanceName);
//}
