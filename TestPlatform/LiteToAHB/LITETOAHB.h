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
	sc_in<unsigned int>			M_HRDATA;
	sc_in<bool>							M_HREADY;
	sc_in<bool>							M_HRESP;

	char* GetModuleName();
	void BDInit();

	





	SC_CTOR(LITETOAHB)	{

		BDInit();

	}

};

#endif	// __LITE_TO_AHB_H__
