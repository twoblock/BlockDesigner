//-----------------------------------------------------------------------------
// Design								: Block Designer Command Queue 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CommandQueue.cpp
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Command queue 
// ----------------------------------------------------------------------------

#include "CommandQueue.h"	

namespace BDapi
{
	/*
	 * function    	: PushCommand 
	 * design	      : push command into command queue 
	 */
	void CommandQueue::PushCommand(GUI_COMMAND Command){
		_CommandQueue.push(Command);
	}	

	/*
	 * function    	: IsEmpty 
	 * design	      : check that queue is empty 
	 */
	bool CommandQueue::IsEmpty(){
		return _CommandQueue.empty();
	}

	/*
	 * function    	: PopCommand 
	 * design	      : Pop command from command queue 
	 */
	GUI_COMMAND CommandQueue::PopCommand(){
		GUI_COMMAND st_Command = _CommandQueue.front();
		_CommandQueue.pop();

		return st_Command;
	}	

}
