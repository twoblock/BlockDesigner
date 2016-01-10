//-----------------------------------------------------------------------------
// Design								: Block Designer Execution Manager 
// Autor								: Bryan.Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ExecutionManager.h
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Execution contol API
// ----------------------------------------------------------------------------

#include "BDSim.h"	

namespace BDapi
{
	long cycle = 0;
	unsigned int ExecutionManager::ExecutionControlFlag;
	unsigned int ExecutionManager::StepValue;

#define	 SECOND_UNIT(X)		((X)*1000000)
	void BD_start()
	{
		unsigned int SimControl;
		int SimState;

		while(1)
		{
			SimControl = ExecutionManager::GetExecutionFlag();

			SimState = Simulate( SimControl );			
			if( SimState == -1 ) // Simulation End 
				break;
		}
	}

	int Simulate(unsigned int SimControl)
	{
		if( SimControl != NOTHING)
		{
			switch( SimControl )
			{
				case    RUN  : Run();	 break;	
				case    STEP : Step(); break;
				case    STOP : Stop(); break;
											 //case    EXIT : Close(); break;
				default			 :         break;
			}

			if( sc_is_running() == false )	{
				ExecutionManager::SetExecutionFlag(NOTHING);
				return -1; // Exit
			}
		}
		return 0; // Running
	}

	void Run()
	{
		sc_start( 10, SC_NS);
		cycle++;
	}

	void Step()
	{
		int StepValue;
		StepValue  = ExecutionManager::GetStepValue();

		if( StepValue != 0 ){
			sc_start( 10, SC_NS );
			cycle++;
			StepValue -= 10;
			ExecutionManager::SetStepValue(StepValue);
		}
		else{
			ExecutionManager::SetExecutionFlag(NOTHING);
		}
	}

	void Stop()
	{
		ExecutionManager::SetExecutionFlag(NOTHING);
	}

}

