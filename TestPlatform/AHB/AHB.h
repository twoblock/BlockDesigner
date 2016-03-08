#ifndef __AHB_H___
#define __AHB_H___ 

#include "BlockDesigner.h"
#include "AHB_Lite.h"

SC_MODULE(AHB)	{

	// Global Clock & Resetn
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	// Master Interface
  BD_AHBPort_MS *AHBMaster_M0;
  BD_AHBPort_MS *AHBMaster_M1;
  BD_AHBPort_MS *AHBMaster_M2;

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

	sc_signal<bool>		HSEL_NOMAP;

	SC_CTOR(AHB)	{

	}
};

#endif	// __AHB_H___ 
