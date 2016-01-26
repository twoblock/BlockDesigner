//-----------------------------------------------------------------------------
// Design								: Simulation InitThread 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: StartSimulationThreads.cpp
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide api to create essential threads 
// ----------------------------------------------------------------------------

#include "sysc/kernel/sc_cmnhdr.h"
#include "sysc/kernel/sc_externs.h"
#include <pthread.h>
#include "BD_core/gui/test.h"
#include "BD_core/SimulationHandler/SimulationHandler.h"	
#include "StartSimulationThreads.h"	

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */

namespace BDapi
{

	/*
	 * function 	: SimulationHandlerRoutine
	 * design	    : make SimulationHandler thread 
	 */

	void *SimulationHandlerRoutine( void *arg)
	{
		SimulationHandler();
		return arg;
	}

	/*
	 * function 	: SimulationRoutine
	 * design	    : make Simulation thread
	 */
	void *SimulationRoutine( void *arg)
	{
		sc_core::sc_elab_and_sim( 0, NULL );
		return arg;
	}

	/*
	 * function 	: StartSimulationThreads
	 * design	    : make essential threads
	 */
	void StartSimulationThreads()
	{
		pthread_t SimulationHandlerThread;
		pthread_t SimulationThread;

		int dw_HandlerStatus    = 0;
		int dw_SimulationStatus = 0;

		// create Simulation Thread
		dw_SimulationStatus = pthread_create( &SimulationThread, NULL, SimulationRoutine, NULL);
		if( dw_SimulationStatus < 0){
			perror("Simulation thread create error:");
			exit(0);
		}

		// create SimulationHandler Thread
		dw_HandlerStatus    = pthread_create( &SimulationHandlerThread, NULL, SimulationHandlerRoutine, NULL);
		if( dw_HandlerStatus < 0){
			perror("Handler thread create error:");
			exit(0);
		}

	}

}
