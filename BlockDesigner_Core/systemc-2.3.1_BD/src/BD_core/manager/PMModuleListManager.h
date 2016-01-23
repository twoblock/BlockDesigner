//-----------------------------------------------------------------------------
// Design								: Block Designer Platform Manager module list Manager
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: PMModuleListManager.h
// Date	       					: 2016/1/22
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: 
// ----------------------------------------------------------------------------

#ifndef __PM_MODULE_LIST_MANAGER_H 
#define __PM_MODULE_LIST_MANAGER_H  

#include "TopManagerBase.h"
#include "ModuleLoader.h"
#include "systemc.h"
#include <list> 

class PMModuleListGenerator;

using namespace sc_core;

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : 
	 * design	      : 
	 * description	: 
	 */
	class PMModuleListManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void GetOperationControl(GUI_COMMAND Command);
			void AddModule();
			void GetJsonFile();
			
			static PMModuleListManager* GetInstance();

		protected:
			PMModuleListManager();
		  ~PMModuleListManager();

		private:
			PMModuleListGenerator *p_PMModuleListGenerator;
			ModuleLoader *p_ModuleLoader;
			list<sc_module*> ModuleList;	
			
			static PMModuleListManager *_PMModuleListManager;
	};
} // namespace BDapi 

#endif 


