//-----------------------------------------------------------------------------
// Design								: User command parser 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: test.h
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This Thread provide user command test 
// ----------------------------------------------------------------------------

#ifndef GUITHREAD_H 
#define GUITHREAD_H 

#include "BD_core/SimulationHandler/SimulationHandler_type.h"	
#include "BD_core/SimulationHandler/CommandQueue.h"	
#include "BD_core/manager/ExecutionManager.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define	 SECOND_UNIT(X)		((X)*1000000)
#define	 SIZE 256 
#define	 NO_OPERATION -1
#define	 NO_COMMAND -1
#define	 NO_ARGUMENT 0

/*
 * namespace   	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */

namespace BDapi
{
	// Script line Return Type
	enum ScriptReturn
	{
		_NO_COMMAND,
		_COMMAND,	
		_SLEEP
	};

	extern void GUIThread();
	void PushCommand(char *p_UserCommand);
	void Sleep(char *p_UserCommand);
	void InitializeCommand(GUI_COMMAND &Command);
	ScriptReturn CheckScriptLine(char *p_UserCommand);
}

#endif 

