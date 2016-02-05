//-----------------------------------------------------------------------------
// Design								: give module connection api 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleConnector.h
// Date	       					: 2016/1/27
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage channels and modules 
//                connect all modules by using channels
// ----------------------------------------------------------------------------

#ifndef __MODULE_CONNECTION_MANAGER_H__
#define __MODULE_CONNECTION_MANAGER_H__

#include "TopManagerBase.h"
#include <pthread.h>

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ChannelMap;
	class ModuleListManager;

	struct BindingInfo
	{
		const char *ModuleName;
		const char *ModulePortName;
		const char *ChannelName;
	};

	/*
	 * class		    : 
	 * design	      :
	 * description	: 
	 */
	class ModuleConnector 
	{
		public:
			void ConnectModules(
					const char *FirstModuleName,
					const char *FirstModulePortName, 
					const char *ChannelName,
					const char *SecondModuleName, 
					const char *SecondModulePortName);

			void BindChannel(BindingInfo *BindingObject);

			static ModuleConnector* GetInstance();
			static void DeleteInstance();

		protected:
			ModuleConnector();		
			virtual ~ModuleConnector();		

		private:
			ChannelMap *p_ChannelMap;
			ModuleListManager *p_ModuleListManager;

			static ModuleConnector *_ModuleConnector;
			// mutex for singleton pattern 
			static pthread_mutex_t ModuleConnectorInstanceMutex;   
	};
} // namespace BDapi 

#endif 

