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
#include "../manager/AllManager.h"
#include "../manager/ModuleConnector.h"
#include "../SimulationAPI/ChannelMap.h"

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

	void *MainThreadRoutine( void *arg)
	{
  	pthread_t SimulationHandlerThread;
		pthread_t SimulationThread;

		int dw_HandlerStatus    = 0;
		int dw_SimulationStatus = 0;

		while(1){

			dw_HandlerStatus    = 0;
			dw_SimulationStatus = 0;

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

			pthread_join(SimulationThread, (void**)&dw_SimulationStatus);
			pthread_join(SimulationHandlerThread, (void**)&dw_HandlerStatus);

			sc_stop();

			while(sc_is_running() != false);
			ModuleListManager::GetInstance()->DeleteInstance();
			ChannelMap::GetInstance()->DeleteInstance();
			SignalTraceManager::GetInstance()->DeleteInstance();

			sleep(3);
			delete sc_default_global_context;
			sc_curr_simcontext = NULL;

			BDDIJsonManager::GetInstance()->DeleteInstance();
			BDDIManager::GetInstance()->DeleteInstance();
			BDPMDInitManager::GetInstance()->DeleteInstance();
			PMMLGenerationManager::GetInstance()->DeleteInstance();
			SoftwareManager::GetInstance()->DeleteInstance();
			ModuleConnector::GetInstance()->DeleteInstance();
			//CallBackManager::GetInstance()->DeleteInstance();
			//ExecutionManager::GetInstance()->DeleteInstance();

			ModuleListManager::GetInstance();
			BDDIJsonManager::GetInstance();
			BDDIManager::GetInstance();
			BDPMDInitManager::GetInstance();
			PMMLGenerationManager::GetInstance();
			SignalTraceManager::GetInstance();
			SoftwareManager::GetInstance();
			ModuleConnector::GetInstance();
			CallBackManager::GetInstance()->GetManagers();
			//ExecutionManager::GetInstance();


		}

		return arg;
	}


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
		pthread_t MainThread;
		int dw_MainStatus = 0;

		// create Simulation Thread
		dw_MainStatus = pthread_create(&MainThread, NULL, MainThreadRoutine, NULL);
		if( dw_MainStatus < 0){
			perror("Simulation thread create error:");
			exit(0);
		}

		pthread_detach(MainThread);
	}

}
