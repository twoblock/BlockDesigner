//-----------------------------------------------------------------------------
// Design								: sc_module list Manager
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: CallBackManager.h
// Date	       					: 2016/1/22
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage sc_module list 
// ----------------------------------------------------------------------------

#ifndef __CALLBACK_MANAGER_H__
#define __CALLBACK_MANAGER_H__ 

#include "TopManagerBase.h"
#include "../../../../JNI_Interface/jdk_h/jni.h"
#include "../../../../JNI_Interface/jdk_h/jni_md.h"
#include "systemc.h"
#include <pthread.h>
#include <list> 

using namespace sc_core;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : CallBackManager 
	 * design	      : manage sc_module list and                           
	 *                transfer them to json format to deliver GUI thread 
	 */
	class CallBackManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);

			void AddJaveCallBackClass(jobject Jobject,JNIEnv* jenv, jmethodID jmid);
			void AddModule(const char *SoFilePath, const char *ModuleName);
	
			jobject GetObject();
			jmethodID GetMID();
			JNIEnv* GetEnv();

			static CallBackManager* GetInstance();
			static void DeleteInstance();

		protected:
			CallBackManager();
		  virtual ~CallBackManager();

		private:
			JNIEnv *m_Env;
			jobject m_Jobject;
			jmethodID m_MethodID;

			static CallBackManager *_CallBackManager;
			// mutex for singleton pattern 
			static pthread_mutex_t CallBackManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 
