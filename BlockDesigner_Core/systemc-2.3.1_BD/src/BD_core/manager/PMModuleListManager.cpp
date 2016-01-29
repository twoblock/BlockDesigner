//-----------------------------------------------------------------------------
// Design								: Block Designer Platform Manager module list Manager
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: PMModuleListManager.cpp
// Date	       					: 2016/1/22
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage sc_module list and
//                transfer them to json format to deliver GUI thread 
// ----------------------------------------------------------------------------

#include "PMModuleListManager.h"
#include "../PlatformAPI/PMModuleListGenerator.h"
#include "ModuleLoader.h"

namespace BDapi
{	
	/*
	 * function    	: PutOperationControl
	 * design	      : add sc_module to sc_module list
	 * param	      : GUI_COMMAND - command from user
	 *							  Argu1 - so file path 
	 *							  Argu2 - module name
	 * caller		    : PMCommandHandler::SetManagerForPutOperation
	 */
	void PMModuleListManager::PutOperationControl(GUI_COMMAND Command)
	{
		AddModule(Command.Argu1, Command.Argu2);
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : get sc_module list json file 
	 * caller		    : PMCommandHandler::SetManagerForGetOperation
	 */
	void PMModuleListManager::GetOperationControl(GUI_COMMAND Command)
	{
		GetJsonFile();
	}

	/*
	 * function    	: AddModule 
	 * design	      : get sc_module instance and push it to sc_module list
	 * param	      : const char * ( so file path )
	 * param	      : const char * ( sc_module instace name)
	 * caller		    : 
	 */
	void PMModuleListManager::AddModule(const char *SoFilePath, const char *ModuleName)
	{
		sc_module *p_SCmodule = p_ModuleLoader->GetSCmodule(SoFilePath, ModuleName);
		ModuleList.push_front(p_SCmodule);		
	}

	/*
	 * function    	: FindModule 
	 * design	      : find module in sc_module list 
	 * param        : const char * - Module name
	 * return       : sc_module * - module pointer 
	 * caller		    : 
	 */
	sc_module* PMModuleListManager::FindModule(const char *ModuleName)
	{
		sc_module *p_SCmodule;

		list<sc_module*>::iterator FirstModule = ModuleList.begin();
		list<sc_module*>::iterator LastModule = ModuleList.end();
		list<sc_module*>::iterator IndexOfModule = FirstModule;

		/********************************************
		 * Iterate sc_modules in sc_module list
		 ********************************************/
		for(IndexOfModule = FirstModule; IndexOfModule != LastModule; ++IndexOfModule){  		
			// compare name 
			if(strcmp((*IndexOfModule)->name(), ModuleName) == 0){
				p_SCmodule = (*IndexOfModule);
				return p_SCmodule;
			}
		}
		return NULL;
	}


	/*
	 * function    	: GetJsonFile 
	 * design	      : generate sc_module list json file 
	 * caller		    : 
	 */
	void PMModuleListManager::GetJsonFile()
	{
		p_PMModuleListGenerator->GenerateJsonFile(ModuleList);
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	PMModuleListManager* PMModuleListManager::GetInstance()
	{
		if( _PMModuleListManager == NULL ){
			_PMModuleListManager = new PMModuleListManager();
		}

		return _PMModuleListManager;
	}

	/*
	 * function 	: Constructor
	 * design	    : 
	 */
	PMModuleListManager::PMModuleListManager()
	{
		p_PMModuleListGenerator = new PMModuleListGenerator();
		p_ModuleLoader = new ModuleLoader();
	}

	/*
	 * function 	: Destructor
	 * design	    : delete execution manager instance
	 */
	PMModuleListManager::~PMModuleListManager()
	{
		delete p_PMModuleListGenerator;
		delete p_ModuleLoader;
		delete _PMModuleListManager;
	}
}
