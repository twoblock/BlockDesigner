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
	HADDR_S0 = HADDR_M;
	HBURST_S0 = HBURST_M;
	HLOCK_S0 = HLOCK_M;
	HPROT_S0 = HPROT_M;
	HSIZE_S0 = HSIZE_M;
	HTRANS_S0 = HTRANS_M;
	HWDATA_S0 = HWDATA_M;
	HWRITE_S0 = HWRITE_M;
	HREADY_S0 = HREADY_M;

	HADDR_S1 = HADDR_M;
	HBURST_S1 = HBURST_M;
	HLOCK_S1 = HLOCK_M;
	HPROT_S1 = HPROT_M;
	HSIZE_S1 = HSIZE_M;
	HTRANS_S1 = HTRANS_M;
	HWDATA_S1 = HWDATA_M;
	HWRITE_S1 = HWRITE_M;
	HREADY_S1 = HREADY_M;

	HADDR_S2 = HADDR_M;
	HBURST_S2 = HBURST_M;
	HLOCK_S2 = HLOCK_M;
	HPROT_S2 = HPROT_M;
	HSIZE_S2 = HSIZE_M;
	HTRANS_S2 = HTRANS_M;
	HWDATA_S2 = HWDATA_M;
	HWRITE_S2 = HWRITE_M;
	HREADY_S2 = HREADY_M;

	HADDR_S3 = HADDR_M;
	HBURST_S3 = HBURST_M;
	HLOCK_S3 = HLOCK_M;
	HPROT_S3 = HPROT_M;
	HSIZE_S3 = HSIZE_M;
	HTRANS_S3 = HTRANS_M;
	HWDATA_S3 = HWDATA_M;
	HWRITE_S3 = HWRITE_M;
	HREADY_S3 = HREADY_M;

	HADDR_S4 = HADDR_M;
	HBURST_S4 = HBURST_M;
	HLOCK_S4 = HLOCK_M;
	HPROT_S4 = HPROT_M;
	HSIZE_S4 = HSIZE_M;
	HTRANS_S4 = HTRANS_M;
	HWDATA_S4 = HWDATA_M;
	HWRITE_S4 = HWRITE_M;
	HREADY_S4 = HREADY_M;

	HADDR_S5 = HADDR_M;
	HBURST_S5 = HBURST_M;
	HLOCK_S5 = HLOCK_M;
	HPROT_S5 = HPROT_M;
	HSIZE_S5 = HSIZE_M;
	HTRANS_S5 = HTRANS_M;
	HWDATA_S5 = HWDATA_M;
	HWRITE_S5 = HWRITE_M;
	HREADY_S5 = HREADY_M;

	HADDR_S6 = HADDR_M;
	HBURST_S6 = HBURST_M;
	HLOCK_S6 = HLOCK_M;
	HPROT_S6 = HPROT_M;
	HSIZE_S6 = HSIZE_M;
	HTRANS_S6 = HTRANS_M;
	HWDATA_S6 = HWDATA_M;
	HWRITE_S6 = HWRITE_M;
	HREADY_S6 = HREADY_M;

	HADDR_S7 = HADDR_M;
	HBURST_S7 = HBURST_M;
	HLOCK_S7 = HLOCK_M;
	HPROT_S7 = HPROT_M;
	HSIZE_S7 = HSIZE_M;
	HTRANS_S7 = HTRANS_M;
	HWDATA_S7 = HWDATA_M;
	HWRITE_S7 = HWRITE_M;
	HREADY_S7 = HREADY_M;

	HADDR_S8 = HADDR_M;
	HBURST_S8 = HBURST_M;
	HLOCK_S8 = HLOCK_M;
	HPROT_S8 = HPROT_M;
	HSIZE_S8 = HSIZE_M;
	HTRANS_S8 = HTRANS_M;
	HWDATA_S8 = HWDATA_M;
	HWRITE_S8 = HWRITE_M;
	HREADY_S8 = HREADY_M;

	HADDR_S9 = HADDR_M;
	HBURST_S9 = HBURST_M;
	HLOCK_S9 = HLOCK_M;
	HPROT_S9 = HPROT_M;
	HSIZE_S9 = HSIZE_M;
	HTRANS_S9 = HTRANS_M;
	HWDATA_S9 = HWDATA_M;
	HWRITE_S9 = HWRITE_M;
	HREADY_S9 = HREADY_M;
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

	// Slave 0 Interface
	HADDR_S0.set_port_name("HADDR_S0");
	HBURST_S0.set_port_name("HBURST_S0");
	HLOCK_S0.set_port_name("HLOCK_S0");
	HPROT_S0.set_port_name("HPROT_S0");
	HSIZE_S0.set_port_name("HSIZE_S0");
	HTRANS_S0.set_port_name("HTRANS_S0");
	HWDATA_S0.set_port_name("HWDATA_S0");
	HWRITE_S0.set_port_name("HWRITE_S0");
	HREADY_S0.set_port_name("HREADY_S0");
	HSEL_S0.set_port_name("HSEL_S0");
	HREADYOUT_S0.set_port_name("HREADYOUT_S0");
	HRESP_S0.set_port_name("HRESP_S0");
	HRDATA_S0.set_port_name("HRDATA_S0");

	// Slave 1 Interface
	HADDR_S1.set_port_name("HADDR_S1");
	HBURST_S1.set_port_name("HBURST_S1");
	HLOCK_S1.set_port_name("HLOCK_S1");
	HPROT_S1.set_port_name("HPROT_S1");
	HSIZE_S1.set_port_name("HSIZE_S1");
	HTRANS_S1.set_port_name("HTRANS_S1");
	HWDATA_S1.set_port_name("HWDATA_S1");
	HWRITE_S1.set_port_name("HWRITE_S1");
	HREADY_S1.set_port_name("HREADY_S1");
	HSEL_S1.set_port_name("HSEL_S1");
	HREADYOUT_S1.set_port_name("HREADYOUT_S1");
	HRESP_S1.set_port_name("HRESP_S1");
	HRDATA_S1.set_port_name("HRDATA_S1");

	// Slave 2 Interface
	HADDR_S2.set_port_name("HADDR_S2");
	HBURST_S2.set_port_name("HBURST_S2");
	HLOCK_S2.set_port_name("HLOCK_S2");
	HPROT_S2.set_port_name("HPROT_S2");
	HSIZE_S2.set_port_name("HSIZE_S2");
	HTRANS_S2.set_port_name("HTRANS_S2");
	HWDATA_S2.set_port_name("HWDATA_S2");
	HWRITE_S2.set_port_name("HWRITE_S2");
	HREADY_S2.set_port_name("HREADY_S2");
	HSEL_S2.set_port_name("HSEL_S2");
	HREADYOUT_S2.set_port_name("HREADYOUT_S2");
	HRESP_S2.set_port_name("HRESP_S2");
	HRDATA_S2.set_port_name("HRDATA_S2");

	// Slave 3 Interface
	HADDR_S3.set_port_name("HADDR_S3");
	HBURST_S3.set_port_name("HBURST_S3");
	HLOCK_S3.set_port_name("HLOCK_S3");
	HPROT_S3.set_port_name("HPROT_S3");
	HSIZE_S3.set_port_name("HSIZE_S3");
	HTRANS_S3.set_port_name("HTRANS_S3");
	HWDATA_S3.set_port_name("HWDATA_S3");
	HWRITE_S3.set_port_name("HWRITE_S3");
	HREADY_S3.set_port_name("HREADY_S3");
	HSEL_S3.set_port_name("HSEL_S3");
	HREADYOUT_S3.set_port_name("HREADYOUT_S3");
	HRESP_S3.set_port_name("HRESP_S3");
	HRDATA_S3.set_port_name("HRDATA_S3");

	// Slave 4 Interface
	HADDR_S4.set_port_name("HADDR_S4");
	HBURST_S4.set_port_name("HBURST_S4");
	HLOCK_S4.set_port_name("HLOCK_S4");
	HPROT_S4.set_port_name("HPROT_S4");
	HSIZE_S4.set_port_name("HSIZE_S4");
	HTRANS_S4.set_port_name("HTRANS_S4");
	HWDATA_S4.set_port_name("HWDATA_S4");
	HWRITE_S4.set_port_name("HWRITE_S4");
	HREADY_S4.set_port_name("HREADY_S4");
	HSEL_S4.set_port_name("HSEL_S4");
	HREADYOUT_S4.set_port_name("HREADYOUT_S4");
	HRESP_S4.set_port_name("HRESP_S4");
	HRDATA_S4.set_port_name("HRDATA_S4");

	// Slave 5 Interface
	HADDR_S5.set_port_name("HADDR_S5");
	HBURST_S5.set_port_name("HBURST_S5");
	HLOCK_S5.set_port_name("HLOCK_S5");
	HPROT_S5.set_port_name("HPROT_S5");
	HSIZE_S5.set_port_name("HSIZE_S5");
	HTRANS_S5.set_port_name("HTRANS_S5");
	HWDATA_S5.set_port_name("HWDATA_S5");
	HWRITE_S5.set_port_name("HWRITE_S5");
	HREADY_S5.set_port_name("HREADY_S5");
	HSEL_S5.set_port_name("HSEL_S5");
	HREADYOUT_S5.set_port_name("HREADYOUT_S5");
	HRESP_S5.set_port_name("HRESP_S5");
	HRDATA_S5.set_port_name("HRDATA_S5");

	// Slave 6 Interface
	HADDR_S6.set_port_name("HADDR_S6");
	HBURST_S6.set_port_name("HBURST_S6");
	HLOCK_S6.set_port_name("HLOCK_S6");
	HPROT_S6.set_port_name("HPROT_S6");
	HSIZE_S6.set_port_name("HSIZE_S6");
	HTRANS_S6.set_port_name("HTRANS_S6");
	HWDATA_S6.set_port_name("HWDATA_S6");
	HWRITE_S6.set_port_name("HWRITE_S6");
	HREADY_S6.set_port_name("HREADY_S6");
	HSEL_S6.set_port_name("HSEL_S6");
	HREADYOUT_S6.set_port_name("HREADYOUT_S6");
	HRESP_S6.set_port_name("HRESP_S6");
	HRDATA_S6.set_port_name("HRDATA_S6");

	// Slave 7 Interface
	HADDR_S7.set_port_name("HADDR_S7");
	HBURST_S7.set_port_name("HBURST_S7");
	HLOCK_S7.set_port_name("HLOCK_S7");
	HPROT_S7.set_port_name("HPROT_S7");
	HSIZE_S7.set_port_name("HSIZE_S7");
	HTRANS_S7.set_port_name("HTRANS_S7");
	HWDATA_S7.set_port_name("HWDATA_S7");
	HWRITE_S7.set_port_name("HWRITE_S7");
	HREADY_S7.set_port_name("HREADY_S7");
	HSEL_S7.set_port_name("HSEL_S7");
	HREADYOUT_S7.set_port_name("HREADYOUT_S7");
	HRESP_S7.set_port_name("HRESP_S7");
	HRDATA_S7.set_port_name("HRDATA_S7");

	// Slave 8 Interface
	HADDR_S8.set_port_name("HADDR_S8");
	HBURST_S8.set_port_name("HBURST_S8");
	HLOCK_S8.set_port_name("HLOCK_S8");
	HPROT_S8.set_port_name("HPROT_S8");
	HSIZE_S8.set_port_name("HSIZE_S8");
	HTRANS_S8.set_port_name("HTRANS_S8");
	HWDATA_S8.set_port_name("HWDATA_S8");
	HWRITE_S8.set_port_name("HWRITE_S8");
	HREADY_S8.set_port_name("HREADY_S8");
	HSEL_S8.set_port_name("HSEL_S8");
	HREADYOUT_S8.set_port_name("HREADYOUT_S8");
	HRESP_S8.set_port_name("HRESP_S8");
	HRDATA_S8.set_port_name("HRDATA_S8");

	// Slave 9 Interface
	HADDR_S9.set_port_name("HADDR_S9");
	HBURST_S9.set_port_name("HBURST_S9");
	HLOCK_S9.set_port_name("HLOCK_S9");
	HPROT_S9.set_port_name("HPROT_S9");
	HSIZE_S9.set_port_name("HSIZE_S9");
	HTRANS_S9.set_port_name("HTRANS_S9");
	HWDATA_S9.set_port_name("HWDATA_S9");
	HWRITE_S9.set_port_name("HWRITE_S9");
	HREADY_S9.set_port_name("HREADY_S9");
	HSEL_S9.set_port_name("HSEL_S9");
	HREADYOUT_S9.set_port_name("HREADYOUT_S9");
	HRESP_S9.set_port_name("HRESP_S9");
	HRDATA_S9.set_port_name("HRDATA_S9");

	HSEL_NOMAP.set_port_name("HSEL_NOMAP");

	bddi = new AHB_Lite_BDDI(this);
	bdmmi = new AHB_Lite_BDMMI(this);
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new AHB_Lite(ModuleInstanceName);
}
