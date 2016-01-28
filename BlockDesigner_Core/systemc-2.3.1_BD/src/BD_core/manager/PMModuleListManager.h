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
// Description	: manage sc_module list and
//                transfer them to json format to deliver GUI thread 
// ----------------------------------------------------------------------------

#ifndef __PM_MODULE_LIST_MANAGER_H 
#define __PM_MODULE_LIST_MANAGER_H  

#include "TopManagerBase.h"
#include <list> 

namespace sc_core
{	class sc_module; }
using sc_core::sc_module;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class PMModuleListGenerator;
	class ModuleLoader;

	/*
	 * class		    : PMModuleListManager 
	 * design	      : manage sc_module list and                           
	 *                transfer them to json format to deliver GUI thread 
	 */
	class PMModuleListManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void GetOperationControl(GUI_COMMAND Command);
			void AddModule(const char *SoFilePath, const char *ModuleName);
			sc_module* FindModule(const char *ModuleName);
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
