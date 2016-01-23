//-----------------------------------------------------------------------------
// Design								: Platform Manager InitThread 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: StartPlatformManageThreads.cpp
// Date	       					: 2015/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide api to create essential threads 
//								for platform manager
// ----------------------------------------------------------------------------

#include "sysc/kernel/sc_cmnhdr.h"
#include "sysc/kernel/sc_externs.h"
#include <pthread.h>
#include "BD_core/SimulationHandler/SimulationHandler.h"	
#include "StartPlatformManagerThreads.h"	

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

	void *PlatformManagerHandlerRoutine( void *arg)
	{
		SimulationHandler();
		return arg;
	}

	/*
	 * function 	: StartPlatformManagerThreads
	 * design	    : make essential threads for platform manager
	 */
	void StartPlatformManagerThreads()
	{
		pthread_t SimulationHandlerThread;

		int dw_HandlerStatus    = 0;

		// create SimulationHandler Thread
		dw_HandlerStatus    = pthread_create( &SimulationHandlerThread, NULL, PlatformManagerHandlerRoutine, NULL);
		if( dw_HandlerStatus < 0){
			perror("Handler thread create error:");
			exit(0);
		}

	}

}
