//-------------------------------------------------------------
// Design	: AHBDCD
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: AHBDCD.h
// Date		: 2015. 11. 20
// Reference	: AHBDCD.v (by Changwon Choi)
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: Decoder of AHB-Lite for processor
//-------------------------------------------------------------

#ifndef	__AHBDCD_H__
#define __AHBDCD_H__

#include "systemc.h"
#include "memory_map.h"

SC_MODULE(AHBDCD)	{
	sc_in<UINT32>		HADDR;
	
	sc_out<bool>		HSEL_S0;
	sc_out<bool>		HSEL_S1;
	sc_out<bool>		HSEL_S2;
	sc_out<bool>		HSEL_S3;
	sc_out<bool>		HSEL_S4;
	sc_out<bool>		HSEL_S5;
	sc_out<bool>		HSEL_S6;
	sc_out<bool>		HSEL_S7;
	sc_out<bool>		HSEL_S8;
	sc_out<bool>		HSEL_S9;
	sc_out<bool>		HSEL_NOMAP;
	sc_out<UINT32>		MUX_SEL;
	
	sc_signal<UINT32>	decoder;

	void do_divide();
	void do_decoder();

	SC_CTOR(AHBDCD)		{
		SC_METHOD(do_divide);
		sensitive << decoder;

		SC_METHOD(do_decoder);
		sensitive << HADDR;
	}
};

#endif // __AHBDCD_H__
