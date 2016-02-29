//-------------------------------------------------------------
// Design	: AHBDCD
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: AHBDCD.cpp
// Date		: 2015. 11. 20
// Reference	: AHBDCD.v (by Changwon Choi)
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: Decoder of AHB-Lite for processor
//-------------------------------------------------------------

#include "AHBDCD.h"

void AHBDCD::do_divide()	{
	HSEL_S0 = decoder & 0x1;
	HSEL_S1 = decoder & 0x2;
	HSEL_S2 = decoder & 0x4;
	HSEL_S3 = decoder & 0x8;
	HSEL_S4 = decoder & 0x10;
	HSEL_S5 = decoder & 0x20;
	HSEL_S6 = decoder & 0x40;
	HSEL_S7 = decoder & 0x80;
	HSEL_S8 = decoder & 0x100;
	HSEL_S9 = decoder & 0x200;

	HSEL_NOMAP = decoder & 0x0;
}

void AHBDCD::do_decoder()	{
	if( (HADDR >= BASE_ADDR[0]) && (HADDR <= END_ADDR[0]) )		{
		decoder = 0x1;	
		MUX_SEL = 0;
	}
	else if( (HADDR >= BASE_ADDR[1]) && (HADDR <= END_ADDR[1]) )	{
		decoder = 0x2;
		MUX_SEL = 1;
	}
	else if( (HADDR >= BASE_ADDR[2]) && (HADDR <= END_ADDR[2]) )	{
		decoder = 0x4;
		MUX_SEL = 2;
	}
	else if( (HADDR >= BASE_ADDR[3]) && (HADDR <= END_ADDR[3]) )	{
		decoder = 0x8;
		MUX_SEL = 3;
	}
	else if( (HADDR >= BASE_ADDR[4]) && (HADDR <= END_ADDR[4]) )	{
		decoder = 0x10;
		MUX_SEL = 4;
	}
	else if( (HADDR >= BASE_ADDR[5]) && (HADDR <= END_ADDR[5]) )	{
		decoder = 0x20;
		MUX_SEL = 5;
	}
	else if( (HADDR >= BASE_ADDR[6]) && (HADDR <= END_ADDR[6]) )	{
		decoder = 0x40;
		MUX_SEL = 6;
	}
	else if( (HADDR >= BASE_ADDR[7]) && (HADDR <= END_ADDR[7]) )	{
		decoder = 0x80;
		MUX_SEL = 7;
	}
	else if( (HADDR >= BASE_ADDR[8]) && (HADDR <= END_ADDR[8]) )	{
		decoder = 0x100;
		MUX_SEL = 8;
	}
	else if( (HADDR >= BASE_ADDR[9]) && (HADDR <= END_ADDR[9]) )	{
		decoder = 0x200;
		MUX_SEL = 9;
	}
	else	{
		decoder = 0x0;
		MUX_SEL = 10;
	}
}	
