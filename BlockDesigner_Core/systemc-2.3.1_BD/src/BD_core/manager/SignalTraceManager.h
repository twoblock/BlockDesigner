//-----------------------------------------------------------------------------
// Design								: 
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: SignalTraceManager.h
// Date	       					: 2016/2/11
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: 
// ----------------------------------------------------------------------------

#ifndef __SIGNAL_TRACE_MANAGER_H__
#define __SIGNAL_TRACE_MANAGER_H__

#include "TopManagerBase.h"
#include "systemc.h"
#include <pthread.h>

using namespace sc_core;

#define ENABLE_TRACE			"0"
#define DISABLE_TRACE			"1"

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ChannelMap;

	struct ChannelObject;

	/*
	 * class		    : SignalTraceManager
	 * design	      : 
	 * description	: 
	 */
	class SignalTraceManager : public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void GetOperationControl(GUI_COMMAND Command);

			void AddTrace(const char *ChannelName, const char *ChannelType);

			static SignalTraceManager* GetInstance();
			static void DeleteInstance();

		protected:
			SignalTraceManager();
			virtual ~SignalTraceManager();

		private:
		 	static SignalTraceManager *_SignalTraceManager;
			ChannelMap *p_ChannelMap;

			sc_trace_file *tf;

			char a_TempBuf[1024];

			char *p_CatBuf1;
			char *p_CatBuf2;

			// mutex for singleton pattern 
			static pthread_mutex_t SignalTraceManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif	//	__SIGNAL_TRACE_MANAGER_H__
