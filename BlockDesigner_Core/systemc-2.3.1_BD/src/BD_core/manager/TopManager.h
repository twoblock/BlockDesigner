//----------------------------------------------------------------------------- 
// Design								: Block Designer Top Manager 
// Author								: Harold Ko 
// Email								: harold.ko@twoblocktech.com 
// File		     					: TopManager.h
// Date	       					: 2016/1/15
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide to manage all Block Desginer Manager
// ----------------------------------------------------------------------------

#ifndef __TOPMANAGER_H__
#define __TOPMANAGER_H__

#include "BD_core/SimulationHandler/SimulationHandler_type.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	 * class		    : ExecutionManager 
	 * design	      : Control Execution of simulation 
	 * description	: Give Execution Control flag to Simulation thread, Simulation Handler thread 
	 */
	class TopManager
	{
		public:
			virtual void PutOperationControl(GUI_COMMAND Command) = 0;
			virtual void GetOperationControl(GUI_COMMAND Command) = 0; 
	};
} // namespace BDapi 

#endif 

