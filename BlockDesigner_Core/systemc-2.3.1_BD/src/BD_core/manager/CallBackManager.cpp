//-----------------------------------------------------------------------------
// Design								: sc_module list Manager
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CallBackManager.cpp
// Date	       					: 2016/1/22
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage sc_module list 
// ----------------------------------------------------------------------------

#include "CallBackManager.h"

namespace BDapi
{	
	// declare static variable for linker 
	CallBackManager* CallBackManager::_CallBackManager= NULL;
	// initialize mutex 
	pthread_mutex_t CallBackManager::CallBackManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      : add sc_module to sc_module list
	 * param	      : GUI_COMMAND - command from user
	 *							  Argu1 - so file path 
	 *							  Argu2 - module name
	 * caller		    : PMCommandHandler::SetManagerForPutOperation
	 */
	void CallBackManager::PutOperationControl(GUI_COMMAND Command)
	{
		//AddModule(Command.Argu1, Command.Argu2);
	}

	/*
	 * function    	: AddModule 
	 * design	      : get sc_module instance and push it to sc_module list
	 * param	      : const char * ( so file path )
	 * param	      : const char * ( sc_module instace name)
	 * caller		    : 
	 */
	void CallBackManager::AddJaveCallBackClass(jobject Jobject,JNIEnv* jenv, jmethodID jmid)
	{
		m_Jobject = Jobject;
		m_Env = jenv;
		m_MethodID = jmid;
	}

	/*
	 * function    	: GetModuleList 
	 * design	      : get sc_module list
	 * return       : list<sc_module*>
	 */


	jobject CallBackManager::GetObject() {
		return m_Jobject;
	}

	jmethodID CallBackManager::GetMID() {
		return m_MethodID;
	}

	JNIEnv* CallBackManager::GetEnv()
	{
		return m_Env;
	}
	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	CallBackManager* CallBackManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&CallBackManagerInstanceMutex); 

		if( _CallBackManager == NULL ){
			_CallBackManager = new CallBackManager();
		}
		// unlock
		pthread_mutex_unlock(&CallBackManagerInstanceMutex);

		return _CallBackManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete CallBackManager instance 
	 */
	void CallBackManager::DeleteInstance()
	{	
		delete _CallBackManager;
		_CallBackManager = NULL;
	}

	/*
	 * function 	: CallBackManager 
	 * design	    : Constructor 
	 */
	CallBackManager::CallBackManager()
	{
	}

	/*
	 * function 	: ~CallBackManager
	 * design	    : Destructor
	 */
	CallBackManager::~CallBackManager()
	{
	}
}
