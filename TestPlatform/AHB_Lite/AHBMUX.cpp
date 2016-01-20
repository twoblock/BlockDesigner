//-------------------------------------------------------------
// Design	: AHBMUX
// Author	: Harold Ko
// Email	: harold.ko@twoblock.co
// File		: AHBMUX.cpp
// Date		: 2015. 11. 20
// Reference	: AHBMUX.v (by Changwon Choi)
//-------------------------------------------------------------
// Copyright (C) 2015 TwoBlock Co.
//-------------------------------------------------------------
// Description	: Multiplexer of AHB-Lite for processor
//-------------------------------------------------------------

#include "AHBMUX.h"

void AHBMUX::do_input_mux_signal()	{
	if(HREADY)	NEXT_ADDR_PHASE_MUX_SEL = MUX_SEL;
	else		NEXT_ADDR_PHASE_MUX_SEL = REG_ADDR_PHASE_MUX_SEL;
}

void AHBMUX::do_register_address_phase()	{
	while(1)	{
		if(!HRESETn)	REG_ADDR_PHASE_MUX_SEL = 0;
		else		REG_ADDR_PHASE_MUX_SEL = NEXT_ADDR_PHASE_MUX_SEL;
		wait();
	}
}

void AHBMUX::do_divide_mux_signal()	{
	switch(REG_ADDR_PHASE_MUX_SEL)	{
		case 0 :
			HRDATA = HRDATA_S0;
			HREADY = HREADYOUT_S0;
			HRESP = HRESP_S0;
			break;
		case 1 :
			HRDATA = HRDATA_S1;
			HREADY = HREADYOUT_S1;
			HRESP = HRESP_S1;
			break;
		case 2 :
			HRDATA = HRDATA_S2;
			HREADY = HREADYOUT_S2;
			HRESP = HRESP_S2;
			break;
		case 3 :
			HRDATA = HRDATA_S3;
			HREADY = HREADYOUT_S3;
			HRESP = HRESP_S3;
			break;
		case 4 :
			HRDATA = HRDATA_S4;
			HREADY = HREADYOUT_S4;
			HRESP = HRESP_S4;
			break;
		case 5 :
			HRDATA = HRDATA_S5;
			HREADY = HREADYOUT_S5;
			HRESP = HRESP_S5;
			break;
		case 6 :
			HRDATA = HRDATA_S6;
			HREADY = HREADYOUT_S6;
			HRESP = HRESP_S6;
			break;
		case 7 :
			HRDATA = HRDATA_S7;
			HREADY = HREADYOUT_S7;
			HRESP = HRESP_S7;
			break;
		case 8 :
			HRDATA = HRDATA_S8;
			HREADY = HREADYOUT_S8;
			HRESP = HRESP_S8;
			break;
		case 9 :
			HRDATA = HRDATA_S9;
			HREADY = HREADYOUT_S9;
			HRESP = HRESP_S9;
			break;
		default :
			HRDATA = 0xF0F0F0F0;
			HREADY = 0x00000001;
			HRESP = 0x00000000;
			break;
	}
}

