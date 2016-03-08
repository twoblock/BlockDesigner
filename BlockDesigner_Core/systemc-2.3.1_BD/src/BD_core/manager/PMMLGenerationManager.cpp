//-----------------------------------------------------------------------------
// Design								: PMML(PlatformManager Module List) generator 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: PMMLGenerationManager.cpp
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: generate PMML.json for Platform Manager
// ----------------------------------------------------------------------------

#include "PMMLGenerationManager.h"
#include "ModuleLoader.h"

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define Size 128

namespace BDapi
{	
	// declare static variable for linker 
	PMMLGenerationManager* PMMLGenerationManager::_PMMLGenerationManager= NULL;
	// initialize mutex 
	pthread_mutex_t PMMLGenerationManager::PMMLGenerationManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      : add sc_module to sc_module list
	 * param	      : GUI_COMMAND - command from user
	 *							  Argu1 - so file path 
	 *							  Argu2 - module name
	 * caller		    : PMCommandHandler::SetManagerForPutOperation
	 */
	void PMMLGenerationManager::PutOperationControl(GUI_COMMAND Command)
	{
		AddModuleToPMML(Command.Argu1, Command.Argu2);
	}

	/*
	 * function    	: AddModule 
	 * design	      : get sc_module instance and push it to sc_module list
	 * param	      : const char * ( so file path )
	 * param	      : const char * ( sc_module instace name)
	 * caller		    : 
	 */
	void PMMLGenerationManager::AddModuleToPMML(const char *SoFilePath, const char *ModuleName)
	{
		sc_module *p_SCmodule = p_ModuleLoader->GetSCmodule(SoFilePath, ModuleName);

		// to add module location(so file path) to PMML 
		PMMLGenerationManager *p_PMMLGenerationManager = NULL;
		p_PMMLGenerationManager = PMMLGenerationManager::GetInstance();
    p_PMMLGenerationManager->AddModuleLocation(p_SCmodule, SoFilePath); 
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : get sc_module list json file 
	 * caller		    : CommandHandler::SetManagerForGetOperation
	 */
	void PMMLGenerationManager::GetOperationControl(GUI_COMMAND Command)
	{
		GeneratePMMLJsonFile();
	}

	/*
	 * function    	: GenerateJsonFile 
	 * design	      : generate PMML(PlatformManager Module List) json file 
	 * caller		    : 
	 */
	string PMMLGenerationManager::GeneratePMMLJsonFile()
	{
		Root["PMML"] = PMModuleList;

		Json::StyledWriter writer;
		JsonFileOfPMModuleList = writer.write(Root);
		cout<< endl << "JSON WriteTest" << endl << JsonFileOfPMModuleList << endl; 

		return JsonFileOfPMModuleList;
	}

	/*
	 * function 	: AddModuleLocation 
	 * design	    : add module location(so file path) to PMML 
	 */
	void PMMLGenerationManager::AddModuleLocation(sc_module *p_SCmodule, const char *SoFilePath)
	{
		// sc_module's port list pointer 
		std::vector<sc_port_base*>* p_PortList = NULL;

		// variable to parse port list
		char a_PortTypeInfo[Size] = {0,};
		const char *p_PortName= NULL;
		const char *p_ScPortType = NULL;
		const char *p_DataType = NULL;

		// variable to parse parameter, register list
		char a_Temp[1024] = {0,};
		unsigned int dw_Index = 0;
		unsigned int dw_ParNum = 0;
		unsigned int dw_RegNum = 0;

		// variable to parse memory map
		char *p_ModuleType = NULL;
		unsigned int dw_MemoryMapNum= 0;

		// for AHB type
		char a_AHBType[3] = {0,};

		char *p_SCmoduleName = NULL;
		p_SCmoduleName = p_SCmodule->GetModuleName();

	  // check duplication
		ModulePathMapFinder = ModulePathMap.find(p_SCmoduleName);
		if(ModulePathMapFinder != ModulePathMap.end())
			return; // exist
		else
			ModulePathMap[p_SCmoduleName] = "insert";

		// Initialize json data
		Module.clear();
		PortList.clear();
		Port.clear();
		ParameterList.clear();
		Parameter.clear();
		RegisterList.clear();
		MemoryMapList.clear();
		MemoryMap.clear();

		// get sc_module's port list
		p_PortList = p_SCmodule->get_port_list();	

		// ready to iterate ports
		std::vector<sc_port_base*>::iterator FirstPort = p_PortList->begin(); 
		std::vector<sc_port_base*>::iterator LastPort = p_PortList->end();
		std::vector<sc_port_base*>::iterator IndexOfPort = FirstPort;  

		/********************************************
		 * Iterate ports in sc_module
		 ********************************************/
		for(IndexOfPort = FirstPort; IndexOfPort != LastPort; ++IndexOfPort){   

			p_PortName = (*IndexOfPort)->get_port_name();

			// handle exception
			if(p_PortName != NULL){

				// case : AHB port
				if(p_PortName[0] == '$'){

					if( p_PortName[1] == 'H' &&
							p_PortName[2] == 'A' &&
							p_PortName[3] == 'D' &&
							p_PortName[4] == 'D' &&
							p_PortName[5] == 'R' 
						){
						// parse port information
						strcpy(a_PortTypeInfo, (*IndexOfPort)->get_port_name());
						strtok(a_PortTypeInfo, "_");
						p_PortName = strtok(NULL," ");


						// add Port to PortList in json format
						if(p_PortName != NULL){
							Port["port_name"] = p_PortName;
							a_AHBType[0] = p_PortName[0];	
							a_AHBType[1] = p_PortName[1];	
							a_AHBType[2] = 0; 
							Port["sc_type"]   = a_AHBType; 
						}
						else{
							Port["port_name"] = "null";
							Port["sc_type"]   = "null"; 
						}

						Port["data_type"] = "AHB";
						PortList.append(Port);	
					}
					else{
						continue;
					}
				}
				// case : other port
				else{
					// parse port information
					strcpy(a_PortTypeInfo, (*IndexOfPort)->kind());
					p_DataType = strtok(a_PortTypeInfo, "\n");
					p_ScPortType = strtok(NULL,"\n");

					// add Port to PortList in json format
					Port["port_name"] = p_PortName;
					Port["sc_type"]   = p_ScPortType; 
					Port["data_type"] = p_DataType;
					PortList.append(Port);	
				}
			}
		}
			/********************************************
			 * Iterate parameter in sc_module
			 ********************************************/
			dw_ParNum = p_SCmodule->GetBDDI()->BDDIGetModuleTotalParNum();		

			for(dw_Index = 0; dw_Index < dw_ParNum; dw_Index++){

				BDDIParInfo *pst_ParInfo = p_SCmodule->GetBDDI()->BDDIGetModuleParInfo(); 
				Parameter["parameter_name"] = pst_ParInfo[dw_Index].Name;	
				sprintf(a_Temp, "%u", pst_ParInfo[dw_Index].Bitswide);
				Parameter["bits_wide"] = a_Temp;
				sprintf(a_Temp, "%d", (int)pst_ParInfo[dw_Index].Type);	
				Parameter["type"] = a_Temp;
				Parameter["value"] = pst_ParInfo[dw_Index].Value;
				ParameterList.append(Parameter);
			}

			/********************************************
			 * Iterate register in sc_module
			 ********************************************/
			dw_RegNum = p_SCmodule->GetBDDI()->BDDIGetModuleTotalRegNum();		

			for(dw_Index = 0; dw_Index < dw_RegNum; dw_Index++){

				BDDIRegInfo *pst_RegInfo = p_SCmodule->GetBDDI()->BDDIGetModuleRegInfo(); 
				Register["register_name"] = pst_RegInfo[dw_Index].Name;	
				sprintf(a_Temp, "%u", pst_RegInfo[dw_Index].Bitswide);
				Register["bits_wide"] = a_Temp;
				sprintf(a_Temp, "%d", (int)pst_RegInfo[dw_Index].Type);	
				Register["type"] = a_Temp;
				RegisterList.append(Register);
			}	

			/********************************************
			 * memory map in sc_module ( only Bus type )
			 ********************************************/
			p_ModuleType = NULL;
			p_ModuleType = p_SCmodule->GetBDDI()->BDDIGetModuleType();

			if(strcmp(p_ModuleType, "bus") == 0)
			{
				dw_MemoryMapNum = p_SCmodule->GetBDMMI()->GetSlaveNumber();	

				for(dw_Index = 0; dw_Index < dw_MemoryMapNum; dw_Index++){

					sprintf(a_Temp, "SM_S%d", dw_Index);	
					MemoryMap["port_name"] = a_Temp;	
					MemoryMapList[dw_Index] = MemoryMap;
				}	

				Module["memory_map"] = MemoryMapList;
			}

			// add Module to PMModuleList in json format
			Module["module_name"] = p_SCmodule->GetModuleName();
			Module["module_type"] = p_SCmodule->GetBDDI()->BDDIGetModuleType();
			Module["module_location"] = SoFilePath;
			Module["port"] = PortList;
			Module["parameter"] = ParameterList;
			Module["register"] = RegisterList;
			PMModuleList.append(Module);
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	PMMLGenerationManager* PMMLGenerationManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&PMMLGenerationManagerInstanceMutex); 

		if( _PMMLGenerationManager == NULL ){
			_PMMLGenerationManager = new PMMLGenerationManager();
		}
		// unlock
		pthread_mutex_unlock(&PMMLGenerationManagerInstanceMutex);

		return _PMMLGenerationManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete PMMLGenerationManager instance 
	 */
	void PMMLGenerationManager::DeleteInstance()
	{	
		delete _PMMLGenerationManager;
		_PMMLGenerationManager = NULL;
	}

	/*
	 * function 	: PMMLGenerationManager 
	 * design	    : Constructor 
	 */
	PMMLGenerationManager::PMMLGenerationManager()
	{
		p_ModuleLoader = new ModuleLoader();
	}

	/*
	 * function 	: ~PMMLGenerationManager
	 * design	    : Destructor
	 */
	PMMLGenerationManager::~PMMLGenerationManager()
	{
		delete p_ModuleLoader;
		p_ModuleLoader = NULL;
	}
}
