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
#include <pthread.h>

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
			void PushCommand(GUI_COMMAND Command);	
			bool IsEmpty();	
			GUI_COMMAND PopCommand();	

			static CommandQueue* GetInstance();
			static void DeleteInstance();

		protected:
			CommandQueue();

		private:
			static CommandQueue *_CommandQueue; 
			// c++ STL queue 
			queue<GUI_COMMAND> RealCommandQueue; 
			// mutex for singleton pattern 
			static pthread_mutex_t CommandQueueInstanceMutex;   
			// command queue mutex to synchronize threads( GUI thread and SimulationHandler thread )
			pthread_mutex_t RealCommandQueueMutex;   
	};
}

#endif 

