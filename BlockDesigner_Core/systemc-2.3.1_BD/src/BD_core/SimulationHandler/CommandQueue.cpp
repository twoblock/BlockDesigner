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
	// initialize mutex 
	pthread_mutex_t CommandQueue::InstanceMutex = PTHREAD_MUTEX_INITIALIZER;  
	
	/*
	 * function    	: PushCommand 
	 * design	      : push command into command queue 
	 */
	void CommandQueue::PushCommand(GUI_COMMAND Command){
		// lock
		pthread_mutex_lock(&CommandQueueMutex); 
		// push command 
		RealCommandQueue.push(Command);
		// unlock
		pthread_mutex_unlock(&CommandQueueMutex); 
	}	

	/*
	 * function    	: IsEmpty 
	 * design	      : check that queue is empty 
	 */
	bool CommandQueue::IsEmpty(){
		
		bool IsEmpty;
		// lock
		pthread_mutex_lock(&CommandQueueMutex); 
		// Check Queue is empty
		IsEmpty = RealCommandQueue.empty();	
		// unlock
		pthread_mutex_unlock(&CommandQueueMutex);
	
		return IsEmpty; 
	}

	/*
	 * function    	: PopCommand 
	 * design	      : Pop command from command queue 
	 */
	GUI_COMMAND CommandQueue::PopCommand(){
		// lock
		pthread_mutex_lock(&CommandQueueMutex); 
		// pop command 
		GUI_COMMAND st_Command = RealCommandQueue.front();
		RealCommandQueue.pop();
		// unlock
		pthread_mutex_unlock(&CommandQueueMutex);

		return st_Command;
	}	

	/*
	 * function 	: GetInstance
	 * design	    : Allocate CommandQueue instance and return it
	 */
	CommandQueue* CommandQueue::GetInstance()
	{
		// lock
		pthread_mutex_lock(&InstanceMutex); 
	  	
		if( _CommandQueue == NULL ){
			_CommandQueue = new CommandQueue();
		}
		// unlock
		pthread_mutex_unlock(&InstanceMutex);
		
		return _CommandQueue;
	}

	/*
	 * function 	: GetInstance
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
		pthread_mutex_init(&CommandQueueMutex, NULL);
	}

}
