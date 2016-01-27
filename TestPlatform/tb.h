//-------------------------------------------------------------
// Design	: Test Bench
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: tb.h
// Date		: 2015. 12. 29
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: Test Bench for Test System v.1.0.0
//-------------------------------------------------------------

#include "systemc.h"
#include "type.h"
#include "Software_Profiler.h"

SC_MODULE(TB)	{
	sc_in<bool>		HCLK;
	sc_out<bool>		HRESETn;

	sc_in<UINT32>		EXTRACT_PC;

	Software_Profiler *SP;

	void do_test() {
		HRESETn.write(0);
		wait(10);
		HRESETn.write(1);

		while(true){
			SP->PC_Analyzer(EXTRACT_PC);
			wait();
		}
	}

	SC_CTOR(TB)	{
		SP = new Software_Profiler( (char *)("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/CM0DS.elf") );
		//SP = new Software_Profiler( (char *)("../CM0DS.elf") );

		SC_CTHREAD(do_test, HCLK.pos());
	}
};
