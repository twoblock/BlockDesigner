#ifndef __LITE_TO_AHB_H__
#define __LITE_TO_AHB_H__

#include "BlockDesigner.h"

SC_MODULE(LITETOAHB)	{

	// Global Clock & Resetn
	sc_in<bool>							HCLK;
	sc_in<bool>							HRESETn;

	// AHB Lite Interface
	BD_AHBLitePort_MS *AHBLiteMaster_M0;

	// AHB Interface
	BD_AHBPort_MM *AHBMaster_M0;

	char* GetModuleName();
	void BDInit();

	void do_transfer();
	void assign_signals(BD_AHBPort_MM *Master, BD_AHBLitePort_MS *Slave);

	SC_CTOR(LITETOAHB)	{
		BDInit();

	}

};

#endif	// __LITE_TO_AHB_H__
