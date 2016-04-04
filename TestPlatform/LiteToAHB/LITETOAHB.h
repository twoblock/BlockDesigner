#ifndef __LITE_TO_AHB_H__
#define __LITE_TO_AHB_H__

#include "BlockDesigner.h"
#include "LITETOAHB_BDDI.h"
#include "LITETOAHB_BDMMI.h"

SC_MODULE(LITETOAHB)	{

	// Global Clock & Resetn
	sc_in<bool>							HCLK;
	sc_in<bool>							HRESETn;

	// AHB Lite Interface
	BD_AHBLitePort_MS *AHBLiteMaster_M0;
	// AHB Interface
	BD_AHBPort_MM *AHBMaster_M0;

	BDDI*						bddi;
	BDMMI*					bdmmi;

	BDDI* GetBDDI();
	BDMMI* GetBDMMI();

	char* GetModuleName();
	void BDInit();

	void do_transfer();
	void assign_signals(BD_AHBPort_MM *Master, BD_AHBLitePort_MS *Slave);

	SC_CTOR(LITETOAHB)	{
		BDInit();

		SC_METHOD(do_transfer);
		 sensitive << AHBLiteMaster_M0->HADDR;
		 sensitive << AHBLiteMaster_M0->HBURST;
		 sensitive << AHBLiteMaster_M0->HPROT;
		 sensitive << AHBLiteMaster_M0->HSIZE;
		 sensitive << AHBLiteMaster_M0->HTRANS;
		 sensitive << AHBLiteMaster_M0->HWDATA;
		 sensitive << AHBLiteMaster_M0->HWRITE;
		 sensitive << AHBLiteMaster_M0->HLOCK;

		 sensitive << AHBMaster_M0->HREADY;
		 sensitive << AHBMaster_M0->HRESP;
		 sensitive << AHBMaster_M0->HRDATA;
	}
};

#endif	// __LITE_TO_AHB_H__
