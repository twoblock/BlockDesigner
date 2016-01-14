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

#include"BD_core/manager/ExecutionManager.h"

namespace BDapi
{	
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

}
