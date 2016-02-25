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

#include "BlockDesigner.h"
#include "AHBDCD.h"
#include "AHBMUX.h"
#include "AHB_Lite_BDDI.h"
#include "AHB_Lite_BDMMI.h"

SC_MODULE(AHB_Lite)	{
	// Global Clock & Resetn
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	// Master(Cortex-M0DS) Interface
  BD_AHBPort_MS *AHBMaster_M0;

	// Slave Interface
	BD_AHBPort_SM *AHBSlave_S0;
	BD_AHBPort_SM *AHBSlave_S1;
	BD_AHBPort_SM *AHBSlave_S2;
	BD_AHBPort_SM *AHBSlave_S3;
	BD_AHBPort_SM *AHBSlave_S4;
	BD_AHBPort_SM *AHBSlave_S5;
	BD_AHBPort_SM *AHBSlave_S6;
	BD_AHBPort_SM *AHBSlave_S7;
	BD_AHBPort_SM *AHBSlave_S8;
	BD_AHBPort_SM *AHBSlave_S9;

	sc_out<bool>		HSEL_NOMAP;

	sc_signal<UINT32>	MUX_SEL;

	AHBDCD*	BD_AHBDCD;
	AHBMUX* BD_AHBMUX;

	BDDI*						bddi;
	BDMMI*					bdmmi;

	BDDI* GetBDDI();
	BDMMI* GetBDMMI();
	char* GetModuleName();
	void BDInit();

	void do_transfer();
	void assign_signals(BD_AHBPort_SM *Slave, BD_AHBPort_MS *Master);

	SC_CTOR(AHB_Lite)	{

		BDInit();

		// AHBDCD Port Connection
		BD_AHBDCD = new AHBDCD("ahbdcd");
		BD_AHBDCD->HADDR		(AHBMaster_M0->HADDR);
		BD_AHBDCD->HSEL_S0		(AHBSlave_S0->HSEL);
		BD_AHBDCD->HSEL_S1		(AHBSlave_S1->HSEL);
		BD_AHBDCD->HSEL_S2		(AHBSlave_S2->HSEL);
		BD_AHBDCD->HSEL_S3		(AHBSlave_S3->HSEL);
		BD_AHBDCD->HSEL_S4		(AHBSlave_S4->HSEL);
		BD_AHBDCD->HSEL_S5		(AHBSlave_S5->HSEL);
		BD_AHBDCD->HSEL_S6		(AHBSlave_S6->HSEL);
		BD_AHBDCD->HSEL_S7		(AHBSlave_S7->HSEL);
		BD_AHBDCD->HSEL_S8		(AHBSlave_S8->HSEL);
		BD_AHBDCD->HSEL_S9		(AHBSlave_S9->HSEL);
		BD_AHBDCD->HSEL_NOMAP		(HSEL_NOMAP);
		BD_AHBDCD->MUX_SEL		(MUX_SEL);

		// AHBMUX Port Connection
		BD_AHBMUX = new AHBMUX("ahbmux");
		BD_AHBMUX->HCLK			(HCLK);
		BD_AHBMUX->HRESETn		(HRESETn);
		BD_AHBMUX->MUX_SEL		(MUX_SEL);
		BD_AHBMUX->HREADYOUT_S0		(AHBSlave_S0->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S1		(AHBSlave_S1->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S2		(AHBSlave_S2->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S3		(AHBSlave_S3->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S4		(AHBSlave_S4->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S5		(AHBSlave_S5->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S6		(AHBSlave_S6->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S7		(AHBSlave_S7->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S8		(AHBSlave_S8->HREADYOUT);
		BD_AHBMUX->HREADYOUT_S9		(AHBSlave_S9->HREADYOUT);
		BD_AHBMUX->HRDATA_S0		(AHBSlave_S0->HRDATA);
		BD_AHBMUX->HRDATA_S1		(AHBSlave_S1->HRDATA);
		BD_AHBMUX->HRDATA_S2		(AHBSlave_S2->HRDATA);
		BD_AHBMUX->HRDATA_S3		(AHBSlave_S3->HRDATA);
		BD_AHBMUX->HRDATA_S4		(AHBSlave_S4->HRDATA);
		BD_AHBMUX->HRDATA_S5		(AHBSlave_S5->HRDATA);
		BD_AHBMUX->HRDATA_S6		(AHBSlave_S6->HRDATA);
		BD_AHBMUX->HRDATA_S7		(AHBSlave_S7->HRDATA);
		BD_AHBMUX->HRDATA_S8		(AHBSlave_S8->HRDATA);
		BD_AHBMUX->HRDATA_S9		(AHBSlave_S9->HRDATA);
		BD_AHBMUX->HRESP_S0		(AHBSlave_S0->HRESP);
		BD_AHBMUX->HRESP_S1		(AHBSlave_S1->HRESP);
		BD_AHBMUX->HRESP_S2		(AHBSlave_S2->HRESP);
		BD_AHBMUX->HRESP_S3		(AHBSlave_S3->HRESP);
		BD_AHBMUX->HRESP_S4		(AHBSlave_S4->HRESP);
		BD_AHBMUX->HRESP_S5		(AHBSlave_S5->HRESP);
		BD_AHBMUX->HRESP_S6		(AHBSlave_S6->HRESP);
		BD_AHBMUX->HRESP_S7		(AHBSlave_S7->HRESP);
		BD_AHBMUX->HRESP_S8		(AHBSlave_S8->HRESP);
		BD_AHBMUX->HRESP_S9		(AHBSlave_S9->HRESP);
		BD_AHBMUX->HREADY		(AHBMaster_M0->HREADY);
		BD_AHBMUX->HRDATA		(AHBMaster_M0->HRDATA);
		BD_AHBMUX->HRESP		(AHBMaster_M0->HRESP);

		// Test setting memory map
		bdmmi->SetMemoryMap();

		SC_METHOD(do_transfer);
		sensitive << AHBMaster_M0->HADDR;
		sensitive << AHBMaster_M0->HBURST;
		sensitive << AHBMaster_M0->HLOCK;
		sensitive << AHBMaster_M0->HPROT;
		sensitive << AHBMaster_M0->HSIZE;
		sensitive << AHBMaster_M0->HTRANS;
		sensitive << AHBMaster_M0->HWDATA;
		sensitive << AHBMaster_M0->HWRITE;
		sensitive << AHBMaster_M0->HREADY;
	}
};

#endif	// __AHB_LITE_H___
