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

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ChannelManager;
	class PMModuleListManager;

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

			void BindChannel(
					const char *ModuleName, 
					const char *ModulePortName, 
					const char *ChannelName);

			static ModuleConnectionManager* GetInstance();

		protected:
			ModuleConnectionManager();		
			~ModuleConnectionManager();		

		private:
			ChannelManager *p_ChannelManager;
			PMModuleListManager *p_PMModuleListManager;
			static ModuleConnectionManager *_ModuleConnectionManager;
	};
} // namespace BDapi 

#endif 

