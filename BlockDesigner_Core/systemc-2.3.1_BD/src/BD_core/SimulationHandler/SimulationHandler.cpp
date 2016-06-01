//-----------------------------------------------------------------------------
// Design								: Block Designer Simulation Handler 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SimulationHandler.cpp
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This function is used for Simulator Handler thread
// ----------------------------------------------------------------------------

#include "BD_core/SimulationAPI/BDSim.h"	
#include "SimulationHandler.h"	

namespace BDapi
{
	/*
	 * function    	: SimulationHandler 
	 * design	      : Thread for command handler and response handler
	 * description	: 
	 * caller		    : StartSimulationThreads 
	 * callee		    : 
	 */
	void SimulationHandler()
	{
		/*
			 new CallBackHandler ( CycleListener )
			 new CallBackHandler 
			 new CallBackHandler
			 new CallBackHandler
			 new CallBackHandler

			 new CommandHander    --> 
			 new ResponseHander   <-- 
			 */

		GUI_COMMAND st_Command;

		CommandQueue *p_CommandQueue = NULL;
		p_CommandQueue = CommandQueue::GetInstance();

		CommandHandler *p_CommandHandler = NULL;
		p_CommandHandler = new CommandHandler();

		while(1){
			if(p_CommandQueue->IsEmpty() == false){

				st_Command = p_CommandQueue->PopCommand();
				p_CommandHandler->SetCommand(st_Command);
				p_CommandHandler->Execute();

				if(strcmp(st_Command.Argu1, "CLOSE") == 0)
					break;
			}
		}
	delete p_CommandHandler;
	}
}
