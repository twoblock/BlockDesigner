//-----------------------------------------------------------------------------
// Design								: Block Designer Command Queue 
// Autor								: Bryan.Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CommandQueue.cpp
// Date	       					: 2015/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide user interface 
// ----------------------------------------------------------------------------

#include "BD_core/SimulationHandler/CommandQueue.h"	

namespace BDapi
{	

	void CommandQueue::PushCommand(GUI_COMMAND Command){
		_CommandQueue.push(Command);
		printf("After Push Command\n");
	}	

	bool CommandQueue::IsEmpty(){
		//printf("Is Empty?\n");
		return _CommandQueue.empty();
	}

	GUI_COMMAND CommandQueue::PopCommand(){
		GUI_COMMAND st_Command = _CommandQueue.front();
		_CommandQueue.pop();
		printf("Pop!\n");
		printf("CMD Q!! Output %d %d %s %s\n", st_Command.Operation, st_Command.Command, st_Command.Argu1, st_Command.Argu2);
			

		return st_Command;
	}	

}
