//-----------------------------------------------------------------------------
// Design								: PMML(PlatformManager Module List) generator 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: PMMLGenerationManager.h
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: generate PMML.json for Platform Manager
// ----------------------------------------------------------------------------

#ifndef __PMML_GENERATION_MANAGER_H__
#define __PMML_GENERATION_MANAGER_H__

#include "systemc.h"
#include "TopManagerBase.h"
#include <pthread.h>
#include <string>
#include <list>
#include "BD_core/PlatformAPI/json/json.h"

using namespace std;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ModuleLoader;

	/*
	 * class		    : PMMLGenerationManager 
	 * design	      : PMML(PlatformManager Module List) json file generator for sc_module list
	 *                the generated information is used at Platform Manager
	 */
	class PMMLGenerationManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void AddModuleToPMML(const char *SoFilePath, const char *ModuleName);

			void GetOperationControl(GUI_COMMAND Command);
			string GeneratePMMLJsonFile();

			void AddModuleLocation(sc_module *p_SCmodule, const char *SoFilePath);
			
			static PMMLGenerationManager* GetInstance();
			static void DeleteInstance();

		protected:
			PMMLGenerationManager();
		  virtual ~PMMLGenerationManager();

		private:
			// json format entities
			Json::Value Root;
			Json::Value PMModuleList;
			Json::Value Module;
			Json::Value PortList;
			Json::Value Port;
			Json::Value ParameterList;
			Json::Value Parameter;
			Json::Value RegisterList;
			Json::Value Register;
			Json::Value MemoryMapList;
			Json::Value MemoryMap;

			// json string for GUI
			// this is returned 
			string JsonFileOfPMModuleList;

			// map to manager so file path about each module
			map<string, string> ModulePathMap;
			map<string, string>::iterator ModulePathMapFinder; 
			
			ModuleLoader *p_ModuleLoader;

			// json string for GUI
			static PMMLGenerationManager *_PMMLGenerationManager;
			// mutex for singleton pattern 
			static pthread_mutex_t PMMLGenerationManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 
