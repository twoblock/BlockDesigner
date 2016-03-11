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

#include "AllManager.h"

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

	CallBackReturn CallBackManager::SendBackAllWhenStart()
	{
		SoftwareProfiler *p_SoftwareProfiler = NULL;
		p_SoftwareProfiler = p_SoftwarwManager->GetSoftwareProfiler();
		p_SoftwareProfiler->GetJsonOfSymbolTable();	

		SoftwareDisplayer *p_SoftwareDisplayer = NULL;
		p_SoftwareDisplayer = p_SoftwarwManager->GetSoftwareDisplayer();
		p_SoftwareDisplayer->GetJsonOfSourceCode();	

		return CallBackOK;
	}

	CallBackReturn CallBackManager::SendBackAllWhenStop()
	{
		SoftwareProfiler *p_SoftwareProfiler = NULL;
		p_SoftwareProfiler = p_SoftwarwManager->GetSoftwareProfiler();

		p_SoftwareProfiler->GetJsonOfProfilingTable();	
		p_SoftwareProfiler->GetJsonOfFunctionFlowGragh();	

		return CallBackOK;
	}

	CallBackReturn CallBackManager::SendBackPMML(string PMML)
	{
		JNIEnv *p_Env = NULL;

		int getEnvStat = m_JVM->GetEnv((void **)&p_Env, JNI_VERSION_1_6);
		if (getEnvStat == JNI_EDETACHED) {
			printf("GetEnv: not attached\n");
			if (m_JVM->AttachCurrentThread((void **) &p_Env, NULL) != 0) {
				printf("Failed to attach\n");
				return CallBackError;
			}
		} else if (getEnvStat == JNI_OK) {
			//
		} else if (getEnvStat == JNI_EVERSION) {
			printf("GetEnv: version not supported\n");
			return CallBackError;
		}

		jstring string = p_Env->NewStringUTF(PMML.c_str());
		p_Env->CallIntMethod(m_Jobject, m_MethodID, string);

		if (p_Env->ExceptionCheck()) {
			p_Env->ExceptionDescribe();
		}

		m_JVM->DetachCurrentThread();

		return CallBackOK;
	}

	void CallBackManager::SetJVM(JavaVM* JVM)
	{
		m_JVM = JVM;
	}

	JavaVM* CallBackManager::GetJVM()
	{
		return m_JVM;
	}

	void CallBackManager::SetObject(jobject Jobject)
	{
		m_Jobject = Jobject;
	}

	jobject CallBackManager::GetObject() {
		return m_Jobject;
	}

	void CallBackManager::SetMID(jmethodID MethodID)
	{
		m_MethodID = MethodID;
	}

	jmethodID CallBackManager::GetMID() 
	{
		return m_MethodID;
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
		p_SoftwarwManager = SoftwareManager::GetInstance();
	}

	/*
	 * function 	: ~CallBackManager
	 * design	    : Destructor
	 */
	CallBackManager::~CallBackManager()
	{
	}
}
