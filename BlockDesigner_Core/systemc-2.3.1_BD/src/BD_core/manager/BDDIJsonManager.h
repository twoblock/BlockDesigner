//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface Manager 
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDIJsonManager.h
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provides debugging interface contol API
// ----------------------------------------------------------------------------

#ifndef __BDDI_JSON_MANAGER_H__
#define __BDDI_JSON_MANAGER_H__

#include "TopManagerBase.h"
#include <pthread.h>
#include <list>
#include <string>
#include "BD_core/PlatformAPI/json/json.h"
#include "systemc.h"

// for Debugging BDDIJson
#include <stdio.h>

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ModuleListManager;
	/*
	 * class		    : BDDIJsonManager
	 * design	      : Control BDDIJson Function
	 * description	: interface parameter, register,
	 *								memory and assembly code by controlling BDDIJson function
	 */
	class BDDIJsonManager : public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void GetOperationControl(GUI_COMMAND Command);

			string GenerateBDDIJsonFile();
			string GenerateMemoryViewJsonFile();

			void AddRegisterValueInformation();
			void AddMemoryViewInformation();
			
			static BDDIJsonManager* GetInstance();
			static void DeleteInstance();

		protected:
			BDDIJsonManager();
			virtual ~BDDIJsonManager();

		private:
			// json format entities
			Json::Value Root;
			Json::Value BDDIJsonList;
			Json::Value Module;
			Json::Value Register;
			Json::Value RegisterList;
			Json::Value MemoryViewRoot;
			Json::Value MemoryViewList;

			string JsonFileOfBDDI;
			string JsonFileOfMemoryView;

			ModuleListManager *p_ModuleListManager;
			list<sc_module*> ModuleList;

			char a_TempBuf[128];

		 	static BDDIJsonManager *_BDDIJsonManager;
			// mutex for singleton pattern 
			static pthread_mutex_t BDDIJsonManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif	// __BDDI_JSON_MANAGER_H__
