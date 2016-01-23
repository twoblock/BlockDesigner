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
// Description	: 
// ----------------------------------------------------------------------------

#include "PMModuleListManager.h"
#include "../PlatformAPI/PMModuleListGenerator.h"

namespace BDapi
{	
	/*
	 * function    	: PutOperationControl
	 * design	      : 
	 * caller		    : PMCommandHandler::SetManagerForPutOperation
	 */
	void PMModuleListManager::PutOperationControl(GUI_COMMAND Command)
	{
		sc_module *p_SCmodule = p_ModuleLoader->GetSCmodule(Command.Argu1,"AHB_Lite");
  	ModuleList.push_front(p_SCmodule);		
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : 
	 * caller		    : PMCommandHandler::SetManagerForGetOperation
	 */
	void PMModuleListManager::GetOperationControl(GUI_COMMAND Command)
	{
	  p_PMModuleListGenerator->GenerateJsonFile(ModuleList);
	}

	/*
	 * function    	: AddModule 
	 * design	      : 
	 * caller		    : 
	 */
	void PMModuleListManager::AddModule()
	{


	}

	/*
	 * function    	: GetJsonFile 
	 * design	      : 
	 * caller		    : 
	 */
	void PMModuleListManager::GetJsonFile()
	{


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
