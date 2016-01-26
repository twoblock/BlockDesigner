//-----------------------------------------------------------------------------
// Design								: Block Designer Simulation Handler 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SimulationHandler.h
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This function is used for Simulator Handler thread
// ----------------------------------------------------------------------------

#ifndef SIMULATION_HANDLER_H
#define SIMULATION_HANDLER_H

#include "AllSimulationHandler.h"

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	extern void SimulationHandler();
}

#endif 

