//-------------------------------------------------------------
// Design	: AHBMUX
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: AHBMUX.h
// Date		: 2015. 11. 20
// Reference	: AHBMUX.v (by Changwon Choi)
//-------------------------------------------------------------
// Copyright (C) 2015 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: Multiplexer of AHB-Lite for processor
//-------------------------------------------------------------

#ifndef __AHBMUX_H__
#define __AHBMUX_H__

#include "systemc.h"
#include "type.h"

SC_MODULE(AHBMUX)	{
	// Global Clock & Reset
	sc_in<bool>		HCLK;
	sc_in<bool>		HRESETn;

	// MUX Select from Address Decoder
	sc_in<UINT32>		MUX_SEL;
	
	// Read Data from All The Slaves
	sc_in<UINT32>		HRDATA_S0;
	sc_in<UINT32>		HRDATA_S1;
	sc_in<UINT32>		HRDATA_S2;
	sc_in<UINT32>		HRDATA_S3;
	sc_in<UINT32>		HRDATA_S4;
	sc_in<UINT32>		HRDATA_S5;
	sc_in<UINT32>		HRDATA_S6;
	sc_in<UINT32>		HRDATA_S7;
	sc_in<UINT32>		HRDATA_S8;
	sc_in<UINT32>		HRDATA_S9;

	// Readyout from All The Slaves
	sc_in<bool>		HREADYOUT_S0;
	sc_in<bool>		HREADYOUT_S1;
	sc_in<bool>		HREADYOUT_S2;
	sc_in<bool>		HREADYOUT_S3;
	sc_in<bool>		HREADYOUT_S4;
	sc_in<bool>		HREADYOUT_S5;
	sc_in<bool>		HREADYOUT_S6;
	sc_in<bool>		HREADYOUT_S7;
	sc_in<bool>		HREADYOUT_S8;
	sc_in<bool>		HREADYOUT_S9;
	
	// Response from All The Slaves
	sc_in<bool>		HRESP_S0;
	sc_in<bool>		HRESP_S1;
	sc_in<bool>		HRESP_S2;
	sc_in<bool>		HRESP_S3;
	sc_in<bool>		HRESP_S4;
	sc_in<bool>		HRESP_S5;
	sc_in<bool>		HRESP_S6;
	sc_in<bool>		HRESP_S7;
	sc_in<bool>		HRESP_S8;
	sc_in<bool>		HRESP_S9;
	
	// Multiplexed HREADY & HRDATA to Master
	sc_out<bool>		HREADY;
	sc_out<UINT32>		HRDATA;
	sc_out<bool>		HRESP;
	
	sc_signal<UINT32>	NEXT_ADDR_PHASE_MUX_SEL;
	sc_signal<UINT32>	REG_ADDR_PHASE_MUX_SEL;
	
	void do_input_mux_signal();
	void do_register_address_phase();
	void do_divide_mux_signal();
	
	SC_CTOR(AHBMUX)		{
		SC_METHOD(do_input_mux_signal);
		sensitive << HREADY;
		sensitive << MUX_SEL;
		sensitive << REG_ADDR_PHASE_MUX_SEL;
	
		SC_THREAD(do_register_address_phase);
		sensitive << HCLK.pos();
		sensitive << HRESETn.neg();

		SC_METHOD(do_divide_mux_signal);
 		sensitive << REG_ADDR_PHASE_MUX_SEL;
		sensitive << HRDATA_S0;
		sensitive << HRDATA_S1;
		sensitive << HRDATA_S2;
		sensitive << HRDATA_S3;
		sensitive << HRDATA_S4;
		sensitive << HRDATA_S5;
		sensitive << HRDATA_S6;
		sensitive << HRDATA_S7;
		sensitive << HRDATA_S8;
		sensitive << HRDATA_S9;
		sensitive << HREADYOUT_S0;
		sensitive << HREADYOUT_S1;
		sensitive << HREADYOUT_S2;
		sensitive << HREADYOUT_S3;
		sensitive << HREADYOUT_S4;
		sensitive << HREADYOUT_S5;
		sensitive << HREADYOUT_S6;
		sensitive << HREADYOUT_S7;
		sensitive << HREADYOUT_S8;
		sensitive << HREADYOUT_S9;
		sensitive << HRESP_S0;
		sensitive << HRESP_S1;
		sensitive << HRESP_S2;
		sensitive << HRESP_S3;
		sensitive << HRESP_S4;
		sensitive << HRESP_S5;
		sensitive << HRESP_S6;
		sensitive << HRESP_S7;
		sensitive << HRESP_S8;
		sensitive << HRESP_S9;
	}
};

#endif // __AHBMUX_H__ 
