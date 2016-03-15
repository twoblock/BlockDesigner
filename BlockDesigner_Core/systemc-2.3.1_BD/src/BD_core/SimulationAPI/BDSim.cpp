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
#include "../manager/CallBackManager.h"
#include "../manager/SoftwareManager.h"

#define	 SECOND_UNIT(X)		((X)*1000000)

namespace BDapi
{
	SoftwareManager *p_SoftwareManager = NULL;
	CallBackManager *p_CallBackManager = NULL;
	CallBackReturn Return = CallBackOK;
	long long glw_Cycle = 0;

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

		p_SoftwareManager = SoftwareManager::GetInstance();	
		p_CallBackManager = CallBackManager::GetInstance();

		//Return = p_CallBackManager->SendBackAllWhenStart();
		//if(Return == CallBackError){
		//printf("Start CallBack error\n");		
		//}	

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
				Return = p_CallBackManager->SendBackAllWhenStop();
				if(Return == CallBackError){
					printf("Stop CallBack error\n");		
				}	
				ExecutionManager::SetExecutionFlag(NOTHING);

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
		// Get pc value
		p_SoftwareManager->PCAnalyzer();	

		// cycle
		glw_Cycle++;
		p_CallBackManager->SendBackLongLong(glw_Cycle, "CycleCallBack");
		if(Return == CallBackError){
			printf("Cycle CallBack error\n");		
		}
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
			// Get pc value
			p_SoftwareManager->PCAnalyzer();	

			// cycle
			glw_Cycle++;
			p_CallBackManager->SendBackLongLong(glw_Cycle, "CycleCallBack");
			if(Return == CallBackError){
				printf("Cycle CallBack error\n");		
			}
			dw_StepValue -= 10;
			ExecutionManager::SetStepValue(dw_StepValue);
		}
		else{
			Return = p_CallBackManager->SendBackAllWhenStop();
			if(Return == CallBackError){
				printf("Stop CallBack error\n");		
			}

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
		Return = p_CallBackManager->SendBackAllWhenStop();
		if(Return == CallBackError){
			printf("Stop CallBack error\n");		
		}	

		ExecutionManager::SetExecutionFlag(NOTHING);
	}
}

