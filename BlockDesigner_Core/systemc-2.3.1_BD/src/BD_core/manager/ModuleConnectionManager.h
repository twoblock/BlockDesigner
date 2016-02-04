//-----------------------------------------------------------------------------
// Design								: Module connection manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleConnectionManager.h
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
	class ChannelManager;
	class PMModuleListManager;
	class PMInfoJsonParser;

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
	class ModuleConnectionManager : public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void GetOperationControl(GUI_COMMAND Command);

			void ConnectModules(
					const char *FirstModuleName,
					const char *FirstModulePortName, 
					const char *ChannelName,
					const char *SecondModuleName, 
					const char *SecondModulePortName);

			void BindChannel(BindingInfo *BindingObject);

			static ModuleConnectionManager* GetInstance();
			static void DeleteInstance();

		protected:
			ModuleConnectionManager();		
			virtual ~ModuleConnectionManager();		

		private:
			ChannelManager *p_ChannelManager;
			PMModuleListManager *p_PMModuleListManager;
			PMInfoJsonParser *p_PMInfoJsonParser;

			static ModuleConnectionManager *_ModuleConnectionManager;
			// mutex for singleton pattern 
			static pthread_mutex_t ModuleConnectionManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 

