//-------------------------------------------------------------
// Design	: sc_main
// Author	: Harold Ko
// Email	: harold.ko@twoblocktech.com
// File		: sc_main.cpp
// Date		: 2016. 1. 5
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: sc_main for Test System v.1.0.1
//-------------------------------------------------------------

#include "systemc.h"

using namespace BDapi;

int sc_main(int argc, char **argv) 
{
	sc_set_time_resolution(1, SC_NS);
	BDStart();
	return 0;
}
