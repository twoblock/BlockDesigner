//-----------------------------------------------------------------------------
// Design								: test command setting 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: test.h
// Date	       					: 2016/1/3
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide gui test API
// ----------------------------------------------------------------------------

#ifndef GUITHREAD_H 
#define GUITHREAD_H 

#include "BD_core/SimulationHandler/SimulationHandler_type.h"	
#include "BD_core/SimulationHandler/CommandQueue.h"	
#include "BD_core/manager/ExecutionManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * namespace   	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */

namespace BDapi
{
	extern void GUIThread();
}

#endif 

