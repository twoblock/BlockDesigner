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

#include "BD_core/SimulationHandler/SimulationHandler.h"	

//for strcpy function
using namespace std;

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
			void SetCommand(GUI_COMMAND st_Command);

			int Execute();
			int PutOperation();
			void CmdExecutionControl();

		private:
			GUI_COMMAND st_GUICommand;
	};
} 

#endif 

