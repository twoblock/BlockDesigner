//-------------------------------------------------------------
// Design	: AHB_Lite
// Author	: Harold Ko
// Email	: harold.ko@twoblock.co
// File		: AHB_Lite.h
// Date		: 2015. 11. 20
// Reference	: AHB_Lite.v (by Changwon Choi)
//------------------------------------------------------------
// Copyright (C) 2015 TwoBlock Co.
//-------------------------------------------------------------
// Description	: AHB Lite for processor
//-------------------------------------------------------------

#ifndef __AHB_LITE_H__
#define __AHB_LITE_H__

#include "systemc.h"
#include "type.h"
#include "AHBDCD.h"
#include "AHBMUX.h"

SC_MODULE(AHB_Lite)	{
	// Global Clock & Resetn
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	// Master(Cortex-M0DS) Interface
	sc_in<UINT32>		HADDR_M;
	sc_in<UINT32>		HBURST_M;
	sc_in<bool>		HLOCK_M;
	sc_in<UINT32>		HPROT_M;
	sc_in<UINT32>		HSIZE_M;
	sc_in<UINT32>		HTRANS_M;
	sc_in<UINT32>		HWDATA_M;
	sc_in<bool>		HWRITE_M;
	sc_out<UINT32>		HRDATA_M;
	sc_out<bool>		HREADY_M;
	sc_out<bool>		HRESP_M;

	// Common Slave Interface
	sc_out<UINT32>		HADDR_S;
	sc_out<UINT32>		HBURST_S;
	sc_out<bool>		HLOCK_S;
	sc_out<UINT32>		HPROT_S;
	sc_out<UINT32>		HSIZE_S;
	sc_out<UINT32>		HTRANS_S;
	sc_out<UINT32>		HWDATA_S;
	sc_out<bool>		HWRITE_S;
	sc_out<bool>		HREADY_S;

	// Slave 0 Interface
	sc_out<bool>		HSEL_S0;
	sc_in<bool>		HREADYOUT_S0;
	sc_in<bool>		HRESP_S0;
	sc_in<UINT32>		HRDATA_S0;

	// Slave 1 Interface
	sc_out<bool>		HSEL_S1;
	sc_in<bool>		HREADYOUT_S1;
	sc_in<bool>		HRESP_S1;
	sc_in<UINT32>		HRDATA_S1;

	// Slave 2 Interface
	sc_out<bool>		HSEL_S2;
	sc_in<bool>		HREADYOUT_S2;
	sc_in<bool>		HRESP_S2;
	sc_in<UINT32>		HRDATA_S2;

	// Slave 3 Interface
	sc_out<bool>		HSEL_S3;
	sc_in<bool>		HREADYOUT_S3;
	sc_in<bool>		HRESP_S3;
	sc_in<UINT32>		HRDATA_S3;

	// Slave 4 Interface
	sc_out<bool>		HSEL_S4;
	sc_in<bool>		HREADYOUT_S4;
	sc_in<bool>		HRESP_S4;
	sc_in<UINT32>		HRDATA_S4;

	// Slave 5 Interface
	sc_out<bool>		HSEL_S5;
	sc_in<bool>		HREADYOUT_S5;
	sc_in<bool>		HRESP_S5;
	sc_in<UINT32>		HRDATA_S5;

	// Slave 6 Interface
	sc_out<bool>		HSEL_S6;
	sc_in<bool>		HREADYOUT_S6;
	sc_in<bool>		HRESP_S6;
	sc_in<UINT32>		HRDATA_S6;

	// Slave 7 Interface
	sc_out<bool>		HSEL_S7;
	sc_in<bool>		HREADYOUT_S7;
	sc_in<bool>		HRESP_S7;
	sc_in<UINT32>		HRDATA_S7;

	// Slave 8 Interface
	sc_out<bool>		HSEL_S8;
	sc_in<bool>		HREADYOUT_S8;
	sc_in<bool>		HRESP_S8;
	sc_in<UINT32>		HRDATA_S8;

	// Slave 9 Interface
	sc_out<bool>		HSEL_S9;
	sc_in<bool>		HREADYOUT_S9;
	sc_in<bool>		HRESP_S9;
	sc_in<UINT32>		HRDATA_S9;

	sc_out<bool>		HSEL_NOMAP;

	sc_signal<UINT32>	MUX_SEL;

	AHBDCD*	BD_AHBDCD;
	AHBMUX* BD_AHBMUX;

	BDDI*						bddi;

	BDDI* GetBDDI();
	char* GetModuleName();
	void BDInit();

	void do_transfer();

	SC_CTOR(AHB_Lite)	{
	
		BDInit();

		// AHBDCD Port Connection
		BD_AHBDCD = new AHBDCD("ahbdcd");
		BD_AHBDCD->HADDR		(HADDR_M);
		BD_AHBDCD->HSEL_S0		(HSEL_S0);
		BD_AHBDCD->HSEL_S1		(HSEL_S1);
		BD_AHBDCD->HSEL_S2		(HSEL_S2);
		BD_AHBDCD->HSEL_S3		(HSEL_S3);
		BD_AHBDCD->HSEL_S4		(HSEL_S4);
		BD_AHBDCD->HSEL_S5		(HSEL_S5);
		BD_AHBDCD->HSEL_S6		(HSEL_S6);
		BD_AHBDCD->HSEL_S7		(HSEL_S7);
		BD_AHBDCD->HSEL_S8		(HSEL_S8);
		BD_AHBDCD->HSEL_S9		(HSEL_S9);
		BD_AHBDCD->HSEL_NOMAP		(HSEL_NOMAP);
		BD_AHBDCD->MUX_SEL		(MUX_SEL);

		// AHBMUX Port Connection
		BD_AHBMUX = new AHBMUX("ahbmux");
		BD_AHBMUX->HCLK			(HCLK);
		BD_AHBMUX->HRESETn		(HRESETn);
		BD_AHBMUX->MUX_SEL		(MUX_SEL);
		BD_AHBMUX->HREADYOUT_S0		(HREADYOUT_S0);
		BD_AHBMUX->HREADYOUT_S1		(HREADYOUT_S1);
		BD_AHBMUX->HREADYOUT_S2		(HREADYOUT_S2);
		BD_AHBMUX->HREADYOUT_S3		(HREADYOUT_S3);
		BD_AHBMUX->HREADYOUT_S4		(HREADYOUT_S4);
		BD_AHBMUX->HREADYOUT_S5		(HREADYOUT_S5);
		BD_AHBMUX->HREADYOUT_S6		(HREADYOUT_S6);
		BD_AHBMUX->HREADYOUT_S7		(HREADYOUT_S7);
		BD_AHBMUX->HREADYOUT_S8		(HREADYOUT_S8);
		BD_AHBMUX->HREADYOUT_S9		(HREADYOUT_S9);
		BD_AHBMUX->HRDATA_S0		(HRDATA_S0);
		BD_AHBMUX->HRDATA_S1		(HRDATA_S1);
		BD_AHBMUX->HRDATA_S2		(HRDATA_S2);
		BD_AHBMUX->HRDATA_S3		(HRDATA_S3);
		BD_AHBMUX->HRDATA_S4		(HRDATA_S4);
		BD_AHBMUX->HRDATA_S5		(HRDATA_S5);
		BD_AHBMUX->HRDATA_S6		(HRDATA_S6);
		BD_AHBMUX->HRDATA_S7		(HRDATA_S7);
		BD_AHBMUX->HRDATA_S8		(HRDATA_S8);
		BD_AHBMUX->HRDATA_S9		(HRDATA_S9);
		BD_AHBMUX->HRESP_S0		(HRESP_S0);
		BD_AHBMUX->HRESP_S1		(HRESP_S1);
		BD_AHBMUX->HRESP_S2		(HRESP_S2);
		BD_AHBMUX->HRESP_S3		(HRESP_S3);
		BD_AHBMUX->HRESP_S4		(HRESP_S4);
		BD_AHBMUX->HRESP_S5		(HRESP_S5);
		BD_AHBMUX->HRESP_S6		(HRESP_S6);
		BD_AHBMUX->HRESP_S7		(HRESP_S7);
		BD_AHBMUX->HRESP_S8		(HRESP_S8);
		BD_AHBMUX->HRESP_S9		(HRESP_S9);
		BD_AHBMUX->HREADY		(HREADY_M);
		BD_AHBMUX->HRDATA		(HRDATA_M);
		BD_AHBMUX->HRESP		(HRESP_M);

		SC_METHOD(do_transfer);
		sensitive << HADDR_M;
		sensitive << HBURST_M;
		sensitive << HLOCK_M;
		sensitive << HPROT_M;
		sensitive << HSIZE_M;
		sensitive << HTRANS_M;
		sensitive << HWDATA_M;
		sensitive << HWRITE_M;
		sensitive << HREADY_M;
	}
};

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName);

#endif	// __AHB_LITE_H___
