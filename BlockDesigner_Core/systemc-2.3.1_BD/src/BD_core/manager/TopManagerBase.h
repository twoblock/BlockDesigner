//----------------------------------------------------------------------------- 
// Design								: Block Designer Top Manager Base
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: TopManagerBase.h
// Date	       					: 2016/1/15
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide to manage all Block Desginer Manager
// ----------------------------------------------------------------------------

#ifndef __TOPMANAGERBASE_H__
#define __TOPMANAGERBASE_H__

#include "TopManager.h"

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
	class TopManagerBase : public TopManager
	{
		public:
			virtual void PutOperationControl(GUI_COMMAND Command) {};
			virtual void GetOperationControl(GUI_COMMAND Command) {};
	};
} // namespace BDapi 

#endif 

