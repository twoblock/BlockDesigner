//-----------------------------------------------------------------------------
// Design								: Simulation InitThread 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: StartSimulationThreads.h
// Date	       					: 2016/1/3
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide api to create essential threads 
// ----------------------------------------------------------------------------

#ifndef SIMULATION_INIT_THREAD_H 
#define SIMULATION_INIT_THREAD_H

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */

namespace BDapi
{
	void *SimulationHandlerRoutine( void *arg);
	void *SimulationRoutine( void *arg);
	extern void StartSimulationThreads();
} 

#endif 

