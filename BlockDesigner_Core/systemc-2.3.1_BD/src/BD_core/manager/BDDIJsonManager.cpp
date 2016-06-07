//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface Manager 
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDIJsonManager.cpp
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provides debugging interface contol API
// ----------------------------------------------------------------------------

#include "BDDIJsonManager.h"
#include "ModuleListManager.h"

// for systemc kernel api
using namespace sc_core;

namespace BDapi
{	
	// declare static variable for linker 
	BDDIJsonManager* BDDIJsonManager::_BDDIJsonManager = NULL;
	// initialize mutex 
	pthread_mutex_t BDDIJsonManager::BDDIJsonManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      : Transfer Debugging Information by Using BDDIJsonManager
	 * caller		    : CommandHandler::SetManagerForPutOperation
	 */
	void BDDIJsonManager::PutOperationControl(GUI_COMMAND Command)
	{
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : Receive Debugging Information by Using BDDIJsonManager
	 * caller		    : CommandHandler::SetManagerForGetOperation
	 */
	void BDDIJsonManager::GetOperationControl(GUI_COMMAND Command)
	{
	}

	string BDDIJsonManager::GenerateBDDIJsonFile()
	{
		Root.clear();
		BDDIJsonList.clear();

		AddRegisterValueInformation();

		Root["SIM_Result"] = BDDIJsonList;

		Json::StyledWriter writer;
		JsonFileOfBDDI = writer.write(Root);
		//cout<< endl << "JSON WriteTest" << endl << JsonFileOfBDDI << endl; 

		return JsonFileOfBDDI;
	}

	string BDDIJsonManager::GenerateMemoryViewJsonFile()
	{
		MemoryViewRoot.clear();
		MemoryViewList.clear();

		AddMemoryViewInformation();

		MemoryViewRoot["MemoryView"] = MemoryViewList;

		Json::StyledWriter writer;
		JsonFileOfMemoryView = writer.write(MemoryViewRoot);
		//cout<< endl << "MemoryView WriteTest" << endl << JsonFileOfMemoryView << endl; 

		return JsonFileOfMemoryView;
	}

	void BDDIJsonManager::AddRegisterValueInformation()
	{
		ModuleList = p_ModuleListManager->GetModuleList();

		sc_module *p_SCmodule;

		unsigned int dw_Index = 0;
		unsigned int dw_RegNum = 0;

		list<sc_module*>::iterator FirstModule = ModuleList.begin();
		list<sc_module*>::iterator LastModule = ModuleList.end();
		list<sc_module*>::iterator IndexOfModule = FirstModule;

		/********************************************
		 * Iterate sc_modules in sc_module list
		 ********************************************/
		for(IndexOfModule = FirstModule; IndexOfModule != LastModule; ++IndexOfModule)	{  		
			p_SCmodule = (*IndexOfModule);

			dw_RegNum = p_SCmodule->GetBDDI()->BDDIGetModuleTotalRegNum();		

			for(dw_Index = 0; dw_Index < dw_RegNum; dw_Index++)	{
				memset(a_TempBuf, 0, sizeof(a_TempBuf));				

				p_SCmodule->GetBDDI()->BDDIGetRegisterValues(dw_Index, a_TempBuf);
				Register["value"] = a_TempBuf;
				RegisterList[dw_Index] = Register;

				Register.clear();
			}

			if(dw_RegNum != 0)	{
				Module["instance_name"] = (*IndexOfModule)->name();
				Module["register_value"] = RegisterList;
				BDDIJsonList.append(Module);

				RegisterList.clear();
				Module.clear();
			}
		}
	}

	void BDDIJsonManager::AddMemoryViewInformation()
	{
		ModuleList = p_ModuleListManager->GetModuleList();

		sc_module *p_SCmodule;

		char *p_ModuleType = NULL;
		unsigned int dw_MemoryNum = 0;

		list<sc_module*>::iterator FirstModule = ModuleList.begin();
		list<sc_module*>::iterator LastModule = ModuleList.end();
		list<sc_module*>::iterator IndexOfModule = FirstModule;

		/********************************************
		 * Iterate sc_modules in sc_module list
		 ********************************************/
		for(IndexOfModule = FirstModule; IndexOfModule != LastModule; ++IndexOfModule)	{  		
			p_SCmodule = (*IndexOfModule);
			p_ModuleType = p_SCmodule->GetBDDI()->BDDIGetModuleType();

			if(strcmp(p_ModuleType, "mem") == 0)	{
				MemoryViewList[dw_MemoryNum] = p_SCmodule->GetBDDI()->InstanceName;
				MemoryViewList[dw_MemoryNum]["change_value"] = p_SCmodule->GetBDDI()->ChangeList;

				p_SCmodule->GetBDDI()->ChangeList.clear();
				p_SCmodule->GetBDDI()->dw_JsonIndex = 0;

				dw_MemoryNum++;
			}
		}
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	BDDIJsonManager* BDDIJsonManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&BDDIJsonManagerInstanceMutex); 

		if( _BDDIJsonManager == NULL ){
			_BDDIJsonManager = new BDDIJsonManager();
		}
		// unlock
		pthread_mutex_unlock(&BDDIJsonManagerInstanceMutex);

		return _BDDIJsonManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete BDDIJsonManager instance 
	 */
	void BDDIJsonManager::DeleteInstance()
	{	
		delete _BDDIJsonManager;
		_BDDIJsonManager = NULL;
	}


	/*
	 * function 	: BDDIJsonManager 
	 * design	    : Constructor 
	 */
	BDDIJsonManager::BDDIJsonManager()
	{
		p_ModuleListManager = ModuleListManager::GetInstance();

		Root.clear();
		BDDIJsonList.clear();
		Module.clear();
		Register.clear();
		RegisterList.clear();
		MemoryViewRoot.clear();
		MemoryViewList.clear();
	}

	/*
	 * function 	: ~BDDIJsonManager 
	 * design	    : Destructor 
	 */
	BDDIJsonManager::~BDDIJsonManager()
	{
	}
}
