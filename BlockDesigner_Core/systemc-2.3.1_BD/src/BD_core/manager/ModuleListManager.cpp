//-----------------------------------------------------------------------------
// Design								: sc_module list Manager
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleListManager.cpp
// Date	       					: 2016/1/22
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage sc_module list 
// ----------------------------------------------------------------------------

#include "ModuleListManager.h"
#include "ModuleLoader.h"

namespace BDapi
{	
	// declare static variable for linker 
	ModuleListManager* ModuleListManager::_ModuleListManager= NULL;
	// initialize mutex 
	pthread_mutex_t ModuleListManager::ModuleListManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      : add sc_module to sc_module list
	 * param	      : GUI_COMMAND - command from user
	 *							  Argu1 - so file path 
	 *							  Argu2 - module name
	 * caller		    : PMCommandHandler::SetManagerForPutOperation
	 */
	void ModuleListManager::PutOperationControl(GUI_COMMAND Command)
	{
		//AddModule(Command.Argu1, Command.Argu2);
	}

	/*
	 * function    	: AddModule 
	 * design	      : get sc_module instance and push it to sc_module list
	 * param	      : const char * ( so file path )
	 * param	      : const char * ( sc_module instace name)
	 * caller		    : 
	 */
	void ModuleListManager::AddModule(const char *SoFilePath, const char *ModuleName)
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
	sc_module* ModuleListManager::FindModule(const char *ModuleName)
	{
		sc_module *p_SCmodule;

		list<sc_module*>::iterator FirstModule = ModuleList.begin();
		list<sc_module*>::iterator LastModule = ModuleList.end();
		list<sc_module*>::iterator IndexOfModule = FirstModule;

		if(ModuleName == NULL)
			return NULL;

		/********************************************
		 * Iterate sc_modules in sc_module list
		 ********************************************/
		for(IndexOfModule = FirstModule; IndexOfModule != LastModule; ++IndexOfModule){  		

			if(strcmp((*IndexOfModule)->name(), ModuleName) == 0){
				p_SCmodule = (*IndexOfModule);
				return p_SCmodule;
			}
		}
		return NULL;
	}

	/*
	 * function    	: GetModuleList 
	 * design	      : get sc_module list
	 * return       : list<sc_module*>
	 */
	list<sc_module*> ModuleListManager::GetModuleList()
	{
		return ModuleList;
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	ModuleListManager* ModuleListManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&ModuleListManagerInstanceMutex); 

		if( _ModuleListManager == NULL ){
			_ModuleListManager = new ModuleListManager();
		}
		// unlock
		pthread_mutex_unlock(&ModuleListManagerInstanceMutex);

		return _ModuleListManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete ModuleListManager instance 
	 */
	void ModuleListManager::DeleteInstance()
	{	
		delete _ModuleListManager;
		_ModuleListManager = NULL;
	}

	/*
	 * function 	: ModuleListManager 
	 * design	    : Constructor 
	 */
	ModuleListManager::ModuleListManager()
	{
		p_ModuleLoader = new ModuleLoader();
	}

	/*
	 * function 	: ~ModuleListManager
	 * design	    : Destructor
	 */
	ModuleListManager::~ModuleListManager()
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
			p_SCmodule = (*IndexOfModule);
			if(p_SCmodule)
				delete p_SCmodule;
		}
		
		delete p_ModuleLoader;
		p_ModuleLoader = NULL;
	}
}
