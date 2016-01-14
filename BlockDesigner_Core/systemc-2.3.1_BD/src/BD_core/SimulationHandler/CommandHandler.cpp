//-----------------------------------------------------------------------------
// Design								: Block Designer Command Queue 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CommandHandler.cpp
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide CommandHandler API 
// ----------------------------------------------------------------------------

#include "BD_core/SimulationHandler/CommandHandler.h"	

namespace BDapi
{	
	/*
	 * function    	: SetCommand 
	 * design	      : set command
	 * caller		    : SimulationHandler 
	 */
	void CommandHandler::SetCommand(GUI_COMMAND Command)
	{
		st_GUICommand = Command;
	}	

	/*
	 * function    	: Execute 
	 * design	      : check Operation( PUT or GET ) 
	 * caller		    : SimulationHandler 
	 * callee       : PutOperation, GetOperation 
	 */
	int CommandHandler::Execute()
	{
		if(st_GUICommand.Operation == PUT){
			PutOperation();
		}
		else if(st_GUICommand.Operation	== GET){
			//GetOperation();
		}
		else; // Exeception

		return 0;
	}

	/*
	 * function    	: PutOperation 
	 * design	      : check command and perform command
	 * description  : 
	 * caller		    : Execute 
	 * callee       : 
	 */
	int CommandHandler::PutOperation()
	{
		if(st_GUICommand.Command == ExecutionControl){
			CmdExecutionControl();
		}
		return 0;
	}
	
	/*
	 * function    	: ExecutionControl
	 * design	      : Set execution flag by using ExecutionManager 
	 * caller		    : PutOperation 
	 */
	void CommandHandler::CmdExecutionControl(){

		unsigned int dw_StepValue = 0;

		if(strcmp(st_GUICommand.Argu1,"RUN") == 0 ){
			ExecutionManager::SetExecutionFlag(RUN);	
		}	
		else if(strcmp(st_GUICommand.Argu1,"STEP") == 0 ){
			dw_StepValue  = atoi(st_GUICommand.Argu2);
			dw_StepValue *= 10;
			ExecutionManager::SetStepValue(dw_StepValue);	
			ExecutionManager::SetExecutionFlag(STEP);	
		}
		else if(strcmp(st_GUICommand.Argu1,"STOP") == 0 ){
			ExecutionManager::SetExecutionFlag(STOP);	
		}	
		else;// Exeception	
	}
}
