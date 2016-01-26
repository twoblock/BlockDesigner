//-----------------------------------------------------------------------------
// Design								: Block Designer Command Queue 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CommandQueue.h
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Command queue 
// ----------------------------------------------------------------------------

#ifndef COMMANDQUEUE_H 
#define COMMANDQUEUE_H 

#include "AllSimulationHandler.h"	
#include <queue> 

// for debugging
#include <stdio.h>

// for c++ STL queue
using namespace std;

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{

	/*
	 * class	    	: CommandQueue 
	 * design 			: management of command queue 
	 */
	class CommandQueue 
	{
		public:
			static void PushCommand(GUI_COMMAND Command);	
			static bool IsEmpty();	
			static GUI_COMMAND PopCommand();	

		private:
			static queue<GUI_COMMAND> _CommandQueue; // c++ STL queue 
	};
}

#endif 

