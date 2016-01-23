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
		char p_PortTypeInfo[128];
		const char *p_ScPortType;
		const char *p_DataType;
		printf("1");	
		
		sc_module *p_SCmodule =	p_ModuleLoader->GetSCmodule(Command.Argu1,"AHB_Lite");
/*
		printf("1");	
		// one module
		// get portlist from sc_module
		std::vector<sc_port_base*>* TestPortList = NULL;
		TestPortList = p_SCmodule->get_port_list();	

		printf("2");	
		// make iterator to get all port information
		std::vector<sc_port_base*>::const_iterator
		it  = TestPortList->begin(), end = TestPortList->end();

		printf("3");	
		for( ; it != end; ++it  ){   
		// parse port information
		strcpy(p_PortTypeInfo, (*it)->kind());
		p_DataType = (strtok(p_PortTypeInfo, "\n"));
		printf("%s\n",p_DataType);
		p_ScPortType = strtok(NULL,"\n");
		printf("%s\n",p_ScPortType);
		}   
*/
		printf("4");	
  	//ModuleList->push_front(p_SCmodule);		
	  //p_PMModuleListGenerator->GenerateJsonFile(ModuleList);
		//ModuleList->push_front(*p_SCmodule);		
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : 
	 * caller		    : PMCommandHandler::SetManagerForGetOperation
	 */
	void PMModuleListManager::GetOperationControl(GUI_COMMAND Command)
	{
	  //p_PMModuleListGenerator->GenerateJsonFile(ModuleList);
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
