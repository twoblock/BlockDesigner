//-------------------------------------------------------------
// Design	: AHB_Lite
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: AHB_Lite.h
// Date		: 2015. 11. 20
// Reference	: AHB_Lite.v (by Changwon Choi)
//------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: AHB Lite for processor
//-------------------------------------------------------------

#ifndef __AHB_LITE_H__
#define __AHB_LITE_H__

#include "systemc.h"
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

	// Slave 0 Interface
	sc_out<UINT32>  HADDR_S0;
	sc_out<UINT32>	HBURST_S0;
	sc_out<bool>		HLOCK_S0;
	sc_out<UINT32>	HPROT_S0;
	sc_out<UINT32>	HSIZE_S0;
	sc_out<UINT32>	HTRANS_S0;
	sc_out<UINT32>	HWDATA_S0;
	sc_out<bool>		HWRITE_S0;
	sc_out<bool>		HREADY_S0;
	sc_out<bool>		HSEL_S0;
	sc_in<bool>			HREADYOUT_S0;
	sc_in<bool>			HRESP_S0;
	sc_in<UINT32>		HRDATA_S0;

	// Slave 1 Interface
	sc_out<UINT32>  HADDR_S1;
	sc_out<UINT32>	HBURST_S1;
	sc_out<bool>		HLOCK_S1;
	sc_out<UINT32>	HPROT_S1;
	sc_out<UINT32>	HSIZE_S1;
	sc_out<UINT32>	HTRANS_S1;
	sc_out<UINT32>	HWDATA_S1;
	sc_out<bool>		HWRITE_S1;
	sc_out<bool>		HREADY_S1;
	sc_out<bool>		HSEL_S1;
	sc_in<bool>			HREADYOUT_S1;
	sc_in<bool>			HRESP_S1;
	sc_in<UINT32>		HRDATA_S1;

	// Slave 2 Interface
	sc_out<UINT32>  HADDR_S2;
	sc_out<UINT32>	HBURST_S2;
	sc_out<bool>		HLOCK_S2;
	sc_out<UINT32>	HPROT_S2;
	sc_out<UINT32>	HSIZE_S2;
	sc_out<UINT32>	HTRANS_S2;
	sc_out<UINT32>	HWDATA_S2;
	sc_out<bool>		HWRITE_S2;
	sc_out<bool>		HREADY_S2;
	sc_out<bool>		HSEL_S2;
	sc_in<bool>			HREADYOUT_S2;
	sc_in<bool>			HRESP_S2;
	sc_in<UINT32>		HRDATA_S2;

	// Slave 3 Interface
	sc_out<UINT32>  HADDR_S3;
	sc_out<UINT32>	HBURST_S3;
	sc_out<bool>		HLOCK_S3;
	sc_out<UINT32>	HPROT_S3;
	sc_out<UINT32>	HSIZE_S3;
	sc_out<UINT32>	HTRANS_S3;
	sc_out<UINT32>	HWDATA_S3;
	sc_out<bool>		HWRITE_S3;
	sc_out<bool>		HREADY_S3;
	sc_out<bool>		HSEL_S3;
	sc_in<bool>			HREADYOUT_S3;
	sc_in<bool>			HRESP_S3;
	sc_in<UINT32>		HRDATA_S3;

	// Slave 4 Interface
	sc_out<UINT32>  HADDR_S4;
	sc_out<UINT32>	HBURST_S4;
	sc_out<bool>		HLOCK_S4;
	sc_out<UINT32>	HPROT_S4;
	sc_out<UINT32>	HSIZE_S4;
	sc_out<UINT32>	HTRANS_S4;
	sc_out<UINT32>	HWDATA_S4;
	sc_out<bool>		HWRITE_S4;
	sc_out<bool>		HREADY_S4;
	sc_out<bool>		HSEL_S4;
	sc_in<bool>			HREADYOUT_S4;
	sc_in<bool>			HRESP_S4;
	sc_in<UINT32>		HRDATA_S4;

	// Slave 5 Interface
	sc_out<UINT32>  HADDR_S5;
	sc_out<UINT32>	HBURST_S5;
	sc_out<bool>		HLOCK_S5;
	sc_out<UINT32>	HPROT_S5;
	sc_out<UINT32>	HSIZE_S5;
	sc_out<UINT32>	HTRANS_S5;
	sc_out<UINT32>	HWDATA_S5;
	sc_out<bool>		HWRITE_S5;
	sc_out<bool>		HREADY_S5;
	sc_out<bool>		HSEL_S5;
	sc_in<bool>			HREADYOUT_S5;
	sc_in<bool>			HRESP_S5;
	sc_in<UINT32>		HRDATA_S5;

	// Slave 6 Interface
	sc_out<UINT32>  HADDR_S6;
	sc_out<UINT32>	HBURST_S6;
	sc_out<bool>		HLOCK_S6;
	sc_out<UINT32>	HPROT_S6;
	sc_out<UINT32>	HSIZE_S6;
	sc_out<UINT32>	HTRANS_S6;
	sc_out<UINT32>	HWDATA_S6;
	sc_out<bool>		HWRITE_S6;
	sc_out<bool>		HREADY_S6;
	sc_out<bool>		HSEL_S6;
	sc_in<bool>			HREADYOUT_S6;
	sc_in<bool>			HRESP_S6;
	sc_in<UINT32>		HRDATA_S6;

	// Slave 7 Interface
	sc_out<UINT32>  HADDR_S7;
	sc_out<UINT32>	HBURST_S7;
	sc_out<bool>		HLOCK_S7;
	sc_out<UINT32>	HPROT_S7;
	sc_out<UINT32>	HSIZE_S7;
	sc_out<UINT32>	HTRANS_S7;
	sc_out<UINT32>	HWDATA_S7;
	sc_out<bool>		HWRITE_S7;
	sc_out<bool>		HREADY_S7;
	sc_out<bool>		HSEL_S7;
	sc_in<bool>			HREADYOUT_S7;
	sc_in<bool>			HRESP_S7;
	sc_in<UINT32>		HRDATA_S7;

	// Slave 8 Interface
	sc_out<UINT32>  HADDR_S8;
	sc_out<UINT32>	HBURST_S8;
	sc_out<bool>		HLOCK_S8;
	sc_out<UINT32>	HPROT_S8;
	sc_out<UINT32>	HSIZE_S8;
	sc_out<UINT32>	HTRANS_S8;
	sc_out<UINT32>	HWDATA_S8;
	sc_out<bool>		HWRITE_S8;
	sc_out<bool>		HREADY_S8;
	sc_out<bool>		HSEL_S8;
	sc_in<bool>			HREADYOUT_S8;
	sc_in<bool>			HRESP_S8;
	sc_in<UINT32>		HRDATA_S8;

	// Slave 9 Interface
	sc_out<UINT32>  HADDR_S9;
	sc_out<UINT32>	HBURST_S9;
	sc_out<bool>		HLOCK_S9;
	sc_out<UINT32>	HPROT_S9;
	sc_out<UINT32>	HSIZE_S9;
	sc_out<UINT32>	HTRANS_S9;
	sc_out<UINT32>	HWDATA_S9;
	sc_out<bool>		HWRITE_S9;
	sc_out<bool>		HREADY_S9;
	sc_out<bool>		HSEL_S9;
	sc_in<bool>			HREADYOUT_S9;
	sc_in<bool>			HRESP_S9;
	sc_in<UINT32>		HRDATA_S9;

	sc_out<bool>		HSEL_NOMAP;

	sc_signal<UINT32>	MUX_SEL;

	AHBDCD*	BD_AHBDCD;
	AHBMUX* BD_AHBMUX;

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

#endif	// __AHB_LITE_H___
