//-----------------------------------------------------------------------------
// Design								: sc_module list Manager
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleListManager.h
// Date	       					: 2016/1/22
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage sc_module list 
// ----------------------------------------------------------------------------

#ifndef __MODULE_LIST_MANAGER_H 
#define __MODULE_LIST_MANAGER_H  

#include "TopManagerBase.h"
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
	class ModuleLoader;

	/*
	 * class		    : ModuleListManager 
	 * design	      : manage sc_module list and                           
	 *                transfer them to json format to deliver GUI thread 
	 */
	class ModuleListManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);

			void AddModule(const char *SoFilePath, const char *ModuleName);
			sc_module* FindModule(const char *ModuleName);

			list<sc_module*> GetModuleList();
			
			static ModuleListManager* GetInstance();
			static void DeleteInstance();

		protected:
			ModuleListManager();
		  virtual ~ModuleListManager();

		private:
			ModuleLoader *p_ModuleLoader;
			list<sc_module*> ModuleList;	
			
			static ModuleListManager *_ModuleListManager;
			// mutex for singleton pattern 
			static pthread_mutex_t ModuleListManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 
