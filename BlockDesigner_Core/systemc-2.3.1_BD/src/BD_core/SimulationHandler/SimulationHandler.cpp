//-----------------------------------------------------------------------------
// Design								: Block Designer Simulation Handler 
// Autor								: Bryan.Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SimulationHandler.cpp
// Date	       					: 2015/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This function is used for Simulator Handler thread
// ----------------------------------------------------------------------------

#include "BD_core/SimulationAPI/BDSim.h"	
#include "SimulationHandler.h"	

namespace BDapi
{
	void SimulationHandler()
	{

		GUI_COMMAND st_Command;
		CommandHandler *p_CommandHandler;
		p_CommandHandler = new CommandHandler();
		/*
			 new CallBackHandler ( CycleListener )
			 new CallBackHandler 
			 new CallBackHandler
			 new CallBackHandler
			 new CallBackHandler

			 new CommandHander    --> 
			 new ResponseHander   <-- 
			 */

		while(1)
		{
			if( CommandQueue::IsEmpty() == false ){
			
				st_Command = CommandQueue::PopCommand();
			
				p_CommandHandler->SetCommand( st_Command );
				p_CommandHandler->Execute();
			}
			
			if( cycle%100 == 0 )	
			printf("cycle : %d\n",cycle);
	
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
