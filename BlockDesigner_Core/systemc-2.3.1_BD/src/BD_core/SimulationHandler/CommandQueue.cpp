//-----------------------------------------------------------------------------
// Design								: Block Designer Command Queue 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CommandQueue.cpp
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Command queue 
// ----------------------------------------------------------------------------

#include "CommandQueue.h"	

namespace BDapi
{
	// declare static variable for linker 
	CommandQueue* CommandQueue::_CommandQueue = NULL;
	// initialize mutex 
	pthread_mutex_t CommandQueue::CommandQueueInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  
	
	/*
	 * function    	: PushCommand 
	 * design	      : push command into command queue 
	 */
	void CommandQueue::PushCommand(GUI_COMMAND Command){
		// lock
		pthread_mutex_lock(&RealCommandQueueMutex); 
		// push command 
		RealCommandQueue.push(Command);
		// unlock
		pthread_mutex_unlock(&RealCommandQueueMutex); 
	}	

	/*
	 * function    	: IsEmpty 
	 * design	      : check that queue is empty 
	 */
	bool CommandQueue::IsEmpty(){
		
		bool IsEmpty;
		// lock
		pthread_mutex_lock(&RealCommandQueueMutex); 
		// Check Queue is empty
		IsEmpty = RealCommandQueue.empty();	
		// unlock
		pthread_mutex_unlock(&RealCommandQueueMutex);
	
		return IsEmpty; 
	}

	/*
	 * function    	: PopCommand 
	 * design	      : Pop command from command queue 
	 */
	GUI_COMMAND CommandQueue::PopCommand(){
		// lock
		pthread_mutex_lock(&RealCommandQueueMutex); 
		// pop command 
		GUI_COMMAND st_Command = RealCommandQueue.front();
		RealCommandQueue.pop();
		// unlock
		pthread_mutex_unlock(&RealCommandQueueMutex);

		return st_Command;
	}	

	/*
	 * function 	: GetInstance
	 * design	    : Allocate CommandQueue instance and return it
	 */
	CommandQueue* CommandQueue::GetInstance()
	{
		// lock
		pthread_mutex_lock(&CommandQueueInstanceMutex); 
	  	
		if( _CommandQueue == NULL ){
			_CommandQueue = new CommandQueue();
		}
		// unlock
		pthread_mutex_unlock(&CommandQueueInstanceMutex);
		
		return _CommandQueue;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete CommandQueue instance 
	 */
	void CommandQueue::DeleteInstance()
	{
		delete _CommandQueue;
		_CommandQueue = NULL;
	}

	/*
	 * function 	: CommandQueue 
	 * design	    : Constructor 
	 */
	CommandQueue::CommandQueue()
	{
		// initialize mutex 
		pthread_mutex_init(&RealCommandQueueMutex, NULL);
	}

}
