//-----------------------------------------------------------------------------
// Design								: Simulation InitThread 
// Autor								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: StartSimulationThreads.h
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Execution contol API
// ----------------------------------------------------------------------------

#include "sysc/kernel/sc_cmnhdr.h"
#include "sysc/kernel/sc_externs.h"
#include <pthread.h>
#include "BD_core/gui/test.h"
#include "BD_core/SimulationHandler/SimulationHandler.h"	

namespace BDapi
{

	void *Simulation_Handler_routine( void *arg)
	{
		SimulationHandler();
		return arg;
	}

	void *Simulation_routine( void *arg)
	{
		sc_core::sc_elab_and_sim( NULL, NULL );
		return arg;
	}

	void StartSimulationThreads()
	{
		pthread_t SimulationHandler_Thread;
		pthread_t Simulation_Thread;

		int Handlerstatus;
		int Simulationstatus;

		Simulationstatus = pthread_create( &Simulation_Thread, NULL, Simulation_routine, NULL);
		Handlerstatus    = pthread_create( &SimulationHandler_Thread, NULL, Simulation_Handler_routine, NULL);

		// 쓰레드가 종료되기를 기다린후 
		// 쓰레드의 리턴값을 출력한다. 
		//pthread_join(SimulationHandler_Thread, (void **)&Handlerstatus);
		//pthread_join(Simulation_Thread, (void **)&Simulationstatus);

	}

}
