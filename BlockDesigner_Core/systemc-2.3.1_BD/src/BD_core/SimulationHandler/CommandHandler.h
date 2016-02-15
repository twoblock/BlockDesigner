//-----------------------------------------------------------------------------
// Design								: Block Designer Command Queue 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CommandHandler.h
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide CommandHandler API 
// ----------------------------------------------------------------------------

#ifndef COMMANDHANDLER_H 
#define COMMANDHANDLER_H 

#include "AllSimulationHandler.h"
#include "BD_core/manager/AllManager.h"

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{

	/*
	 * class		    : CommandHandler 
	 * design       : handle command from user interface 
	 */
	class CommandHandler 
	{
		public:
			CommandHandler();
			
			void SetCommand(GUI_COMMAND st_Command);

			int Execute();
			int PutOperation();
			int GetOperation();
			void SetManagerForPutOperation(TopManagerBase *manager);
			void SetManagerForGetOperation(TopManagerBase *manager);

		private:
			GUI_COMMAND st_GUICommand;
			
			// declare all manager instance
			ExecutionManager* CmdExecutionManager;
			BDDIManager* CmdBDDIManager;
			ModuleListManager* CmdModuleListManager;
			BDPMDInitManager* CmdBDPMDInitManager;
		  PMMLGenerationManager* CmdPMMLGenerationManager;
			SignalTraceManager* CmdSignalTraceManager;
	};
} 

#endif 

