#ifndef __LITE_TO_AHB_H__
#define __LITE_TO_AHB_H__

#include "BlockDesigner.h"
#include "LITETOAHB_BDDI.h"
#include "LITETOAHB_BDMMI.h"

#define IDLE 0
#define REQ  1
#define GRANTED 2
#define LASTADDRESS 3
#define LASTDATA 4

SC_MODULE(LITETOAHB)	{

	// Global Clock & Resetn
	sc_in<bool>							HCLK;
	sc_in<bool>							HRESETn;

	// AHB Lite Interface
	BD_AHBLitePort_MS *AHBLiteMaster_M0;
	// AHB Interface
	BD_AHBPort_MM *AHBMaster_M0;

	sc_signal<unsigned int> state;
	unsigned int IdleCount;
	unsigned int ReqCount;
	bool First;

	BDDI*						bddi;
	BDMMI*					bdmmi;

	BDDI* GetBDDI();
	BDMMI* GetBDMMI();

	char* GetModuleName();
	void BDInit();

	void do_transfer();
	void FSM();
	void assign_signals(BD_AHBPort_MM *Master, BD_AHBLitePort_MS *Slave);

	SC_CTOR(LITETOAHB)	{
		BDInit();

		state = IDLE;
		IdleCount = 0;
		ReqCount = 0;
		First = false;

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
		 sensitive << state; 

		SC_METHOD(FSM);
		 sensitive << HCLK.pos();
	}
};

#endif	// __LITE_TO_AHB_H__
