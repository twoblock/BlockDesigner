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
#include "../manager/AllManager.h"
#include "../manager/ModuleConnector.h"
#include "../SimulationAPI/ChannelMap.h"


#define	 SECOND_UNIT(X)		((X)*1000000)
#define	 CYCLE_DISPLAY_UNIT 1371

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

		while(1){
			dw_SimControl = ExecutionManager::GetExecutionFlag();
			dw_SimState = Simulate(dw_SimControl);			

			if(dw_SimState == -1) break; // Simulation End 
		}

    // excepting handling
		// if simulation don't start, nothing was written to named pipe(wave.vcd)
    // so related processed(gtkwave, shmidcat) can't be removed
		if(glw_Cycle == 0){
			// write some value to named pipe(wave.vcd) 
			// to remove gtkwave, shmidcat processes
			popen("echo 1 > wave.vcd", "r");
		}
		fp = popen("rm -rf wave.vcd", "r");

		sc_stop();

		while(sc_is_running() != false);
		ModuleListManager::GetInstance()->DeleteInstance();
		ChannelMap::GetInstance()->DeleteInstance();
		SignalTraceManager::GetInstance()->DeleteInstance();

		sleep(3);

		if(sc_curr_simcontext != NULL){
			delete sc_default_global_context;
			sc_curr_simcontext = NULL;
		}

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
				case    CLOSE: Close();
											 return -1; 
											 break;
											 //case    EXIT : Close(); break;
				default			 :          break;
			}

			if(sc_is_running() == false){
				Stop();
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

		glw_Cycle++;
		CycleCallBack(RUN);
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

			glw_Cycle++;
			CycleCallBack(STEP);

			dw_StepValue -= 10;
			ExecutionManager::SetStepValue(dw_StepValue);
		}
		else{
			Stop();
		}
	}

	/*
	 * function    	: Stop
	 * design	      : pause simulation 
	 * caller		    : Simulate 
	 */
	void Stop()
	{
		StopCallBack();
		CycleCallBack(STOP);
		ExecutionManager::SetExecutionFlag(NOTHING);
	}

	/*
	 * function    	: Close
	 * design	      : stop and close simulation 
	 * caller		    : Simulate 
	 */
	void Close()
	{
		ExecutionManager::SetExecutionFlag(NOTHING);
		glw_Cycle = 0;
		CycleCallBack(STOP);
	}

	void StopCallBack()
	{
		Return = p_CallBackManager->SendBackAllWhenStop();
		if(Return == CallBackError){
			printf("Stop CallBack error\n");		
		}
	}

	void CycleCallBack(int Status)
	{
		bool b_Check = false;

		if(Status == STOP)
			b_Check = true;
		else
			b_Check = ((glw_Cycle % CYCLE_DISPLAY_UNIT) == 0);	

		if(b_Check){
			p_CallBackManager->SendBackLongLong(glw_Cycle, "CycleCallBack");
			if(Return == CallBackError){
				printf("Cycle CallBack error\n");		
			}
		}
	}
}

