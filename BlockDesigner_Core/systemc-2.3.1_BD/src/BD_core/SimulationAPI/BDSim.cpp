//-----------------------------------------------------------------------------
// Design								: Simulation Core 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDSim.cpp
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: simulate systemc kernel and conrol it  
// ----------------------------------------------------------------------------

#include "BDSim.h"	

#define	 SECOND_UNIT(X)		((X)*1000000)

namespace BDapi
{

	unsigned int ExecutionManager::dw_ExecutionControlFlag;
	unsigned int ExecutionManager::dw_StepValue;

	long long glw_Cycle = 0;
	sc_trace_file *wtf = NULL;

	/*
	 * function    	: BDStart
	 * design	      : start Block Designer simulation
	 * description	: 
	 * caller		    : sc_main 
	 * callee		    : 
	 */
	void BDStart()
	{
		unsigned int dw_SimControl = NOTHING;
		int dw_SimState = 0;
		FILE *fp = NULL;

		// create fifo wave file.
		fp = popen("rm -rf wave.vcd", "r");
		usleep(SECOND_UNIT(0.5));
		fp = popen("mkfifo wave.vcd", "r");
		usleep(SECOND_UNIT(0.5));

		// Activate GTKWAVE Interactive Mode.
		fp = popen("shmidcat wave.vcd | gtkwave -v -I /home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/wave.gtkw", "r");	
		if(fp == NULL) printf("\n\033[31m Error : Can not open GTKWAVE\033[0m\n");

		while(1){
			dw_SimControl = ExecutionManager::GetExecutionFlag();
			dw_SimState = Simulate(dw_SimControl);			
			
			if(dw_SimState == -1) break; // Simulation End 
		}
	}

	/*
	 * function    	: Simulate 
	 * design	      : control simulation and execute one cycle  
	 * description	: 
	 * caller		    : BDStart 
	 * callee		    : 
	 */
	int Simulate(unsigned int SimControl)
	{
		if(SimControl != NOTHING){
			
			switch(SimControl)
			{
				case    RUN  : Run();	  break;	
				case    STEP : Step();  break;
				case    STOP : Stop();  break;
											 //case    EXIT : Close(); break;
				default			 :          break;
			}

			if(sc_is_running() == false){
				ExecutionManager::SetExecutionFlag(NOTHING);
				sc_close_vcd_trace_file(wtf);
				return -1; // Exit
			}
		}
		return 0; // Running
	}

	/*
	 * function    	: Run 
	 * design	      : execute one cycle  
	 * caller		    : Simulate 
	 */
	void Run()
	{
		sc_start(10, SC_NS);
		glw_Cycle++;
	}

	/*
	 * function    	: Step 
	 * design	      : check step value and decide to execute one cycle  
	 * caller		    : Simulate 
	 */
	void Step()
	{
		int dw_StepValue = 0;
		dw_StepValue = ExecutionManager::GetStepValue();

		if(dw_StepValue != 0){
			sc_start(10, SC_NS);
			glw_Cycle++;
			dw_StepValue -= 10;
			ExecutionManager::SetStepValue(dw_StepValue);
		}
		else{
			ExecutionManager::SetExecutionFlag(NOTHING);
		}
	}

	/*
	 * function    	: Stop
	 * design	      : pause simulation 
	 * caller		    : Simulate 
	 */
	void Stop()
	{
		ExecutionManager::SetExecutionFlag(NOTHING);
	}

}

