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
#include "BD_core/PlatformAPI/BDPlatform.h"	
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
	 * function 	: PlatformManagerRoutine
	 * design	    : make PlatformManager thread
	 * desciption : load module( so file ) and give informations to load manager 
	 */
	void *PlatformManagerRoutine( void *arg)
	{
	  PlatformManagerCore();
		return arg;
	}

	/*
	 * function 	: StartPlatformManagerThreads
	 * design	    : make essential threads for platform manager
	 */
	void StartPlatformManagerThreads()
	{
		pthread_t SimulationHandlerThread;
		pthread_t PlatfotmManagerThread;

		int dw_HandlerStatus    = 0;
		int dw_SimulationStatus = 0;

		// create Simulation Thread
		dw_SimulationStatus = pthread_create( &PlatfotmManagerThread, NULL, PlatformManagerRoutine, NULL);
		if( dw_SimulationStatus < 0){
			perror("Platform Manager thread create error:");
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
