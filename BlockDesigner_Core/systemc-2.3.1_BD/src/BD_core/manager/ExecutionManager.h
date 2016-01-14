//-----------------------------------------------------------------------------
// Design								: Block Designer Execution Manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ExecutionManager.h
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Execution contol API
// ----------------------------------------------------------------------------

#ifndef EXECUTIONMANAGER_H 
#define EXECUTIONMANAGER_H 

#define NOTHING 0
#define RUN   	1
#define STEP  	2
#define STOP  	3

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : ExecutionManager 
	 * design	      : Control Execution of simulation 
	 * description	: Give Execution Control flag to Simulation thread, Simulation Handler thread 
	 */
	class ExecutionManager
	{
		public:
			static void SetExecutionFlag(unsigned int Flag);
			static unsigned int GetExecutionFlag();	

			static void SetStepValue(unsigned int Value);
			static unsigned int GetStepValue();

		private:
			static unsigned int dw_ExecutionControlFlag;
			static unsigned int dw_StepValue;
	};
} // namespace BDapi 

#endif 


