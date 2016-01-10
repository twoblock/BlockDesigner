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

#include"BD_core/manager/ExecutionManager.h"

namespace BDapi
{	

	
	void ExecutionManager::SetExecutionFlag(unsigned int Flag)
	{
		ExecutionControlFlag = Flag;
	}
	unsigned int ExecutionManager::GetExecutionFlag()
	{
		return ExecutionControlFlag;
	}
	void ExecutionManager::SetStepValue(unsigned int Value)
	{
		StepValue = Value;
	}
	unsigned int ExecutionManager::GetStepValue()
	{
		return StepValue;
	}

}
