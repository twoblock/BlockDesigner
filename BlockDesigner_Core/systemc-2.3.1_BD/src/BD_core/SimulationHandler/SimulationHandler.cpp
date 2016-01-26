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
		CommandHandler *p_CommandHandler;
		p_CommandHandler = new CommandHandler();

		while(1){
			if(CommandQueue::IsEmpty() == false){
				st_Command = CommandQueue::PopCommand();
				p_CommandHandler->SetCommand(st_Command);
				p_CommandHandler->Execute();
			}

			/*
				 if( ResponseQueue->IsEmpty() )
				 Response = ResponseQueue->GetResponse(); 
				 ResponseHandler->Excute( Response );

				 ================== cycle variable ================
				 ================== set, get function =============

				 CycleListener->CallBackHandler( Cycle->GetCycle() );
				 */
		}
	}
}
