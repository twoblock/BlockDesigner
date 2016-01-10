//-----------------------------------------------------------------------------
// Design								: Block Designer Command Queue 
// Autor								: Bryan.Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CommandHandler.cpp
// Date	       					: 2015/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide CommandHandler API 
// ----------------------------------------------------------------------------

#include "BD_core/SimulationHandler/CommandHandler.h"	

namespace BDapi
{	

	void CommandHandler::SetCommand(GUI_COMMAND st_Command){

		st_GUIcommand = st_Command;
	}	

	int CommandHandler::Execute(){

		if( st_GUIcommand.Operation	== PUT ){
			PutOperation();
		}
		else if( st_GUIcommand.Operation	== PUT ){
			//GetOperation();
		}
		else; // Exeception

		// Set Default

		return 0;
	}

	int CommandHandler::PutOperation(){

		if( st_GUIcommand.Command == ExecutionControl ){
			ExcutionControl();
		}

		return 0;
	}

	void CommandHandler::ExcutionControl(){

		unsigned int StepValue = 0;

		if( strcmp( st_GUIcommand.Argu1,"RUN") == 0 ){
			ExecutionManager::SetExecutionFlag(RUN);	
		}	
		else if( strcmp( st_GUIcommand.Argu1,"STEP") == 0 ){
			StepValue  = atoi(st_GUIcommand.Argu2);
			StepValue *= 10;
			ExecutionManager::SetStepValue(StepValue);	
			ExecutionManager::SetExecutionFlag(STEP);	
		}
		else if( strcmp( st_GUIcommand.Argu1,"STOP") == 0 ){
			ExecutionManager::SetExecutionFlag(STOP);	
		}	
		else;// Exeception	

	}

}
