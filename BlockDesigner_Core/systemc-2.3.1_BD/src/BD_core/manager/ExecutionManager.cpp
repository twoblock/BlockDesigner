//-----------------------------------------------------------------------------
// Design								: Block Designer Execution Manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ExecutionManager.cpp
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Execution contol API
// ----------------------------------------------------------------------------

#include "ExecutionManager.h"

namespace BDapi
{	
	/*
	 * function    	: PutOperationControl
	 * design	      : Set execution flag by using ExecutionManager 
	 * caller		    : CommandHandler::SetManagerForPutOperation
	 */
	void ExecutionManager::PutOperationControl(GUI_COMMAND Command){
		unsigned int dw_StepValue = 0;

		if(strcmp(Command.Argu1,"RUN") == 0 ){
			SetExecutionFlag(RUN);	
		}	
		else if(strcmp(Command.Argu1,"STEP") == 0 ){
			dw_StepValue  = atoi(Command.Argu2);
			dw_StepValue *= 10;
			SetStepValue(dw_StepValue);	
			SetExecutionFlag(STEP);	
		}
		else if(strcmp(Command.Argu1,"STOP") == 0 ){
			SetExecutionFlag(STOP);	
		}	
		else;// Exeception	
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : 
	 * caller		    : CommandHandler::SetManagerForGetOperation
	 */
	void ExecutionManager::GetOperationControl(GUI_COMMAND Command){

	}

	/*
	 * function 	: SetExecutionFlag 
	 * design	    : set Execution flag
	 */
	void ExecutionManager::SetExecutionFlag(unsigned int Flag)
	{
		dw_ExecutionControlFlag = Flag;
	}

	/*
	 * function 	: GetExecutionFlag 
	 * design	    : get Execution flag 
	 */
	unsigned int ExecutionManager::GetExecutionFlag()
	{
		return dw_ExecutionControlFlag;
	}

	/*
	 * function 	: SetStepValue
	 * design	    : set step value 
	 */
	void ExecutionManager::SetStepValue(unsigned int Value)
	{
		dw_StepValue = Value;
	}

	/*
	 * function 	: GetStepValue
	 * design	    : get step value 
	 */
	unsigned int ExecutionManager::GetStepValue()
	{
		return dw_StepValue;
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	ExecutionManager* ExecutionManager::GetInstance()
	{
		if( _ExecutionManager == NULL ){
			_ExecutionManager = new ExecutionManager();
		}

		return _ExecutionManager;
	}

	/*
	 * function 	: Destructor
	 * design	    : delete execution manager instance
	 */
	ExecutionManager::~ExecutionManager()
	{
		delete _ExecutionManager;
	}
}
