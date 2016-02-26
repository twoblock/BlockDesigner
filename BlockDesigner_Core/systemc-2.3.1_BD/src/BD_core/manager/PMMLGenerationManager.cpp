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
#include "ModuleListManager.h"
#include "systemc.h"

#include "BD_core/PlatformAPI/json/json.h"
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
		// Get ModuleListManager
		ModuleListManager *p_ModuleListManager = NULL;
		p_ModuleListManager = ModuleListManager::GetInstance();	

		list<sc_module*> SCModuleList	= p_ModuleListManager->GetModuleList();

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

		// ready to iterate sc_modules 
		list<sc_module*>::iterator FirstModule = SCModuleList.begin();
		list<sc_module*>::iterator LastModule = SCModuleList.end();
		list<sc_module*>::iterator IndexOfModule = FirstModule;

		/********************************************
		 * Iterate sc_modules in sc_module list
		 ********************************************/
		for(IndexOfModule = FirstModule; IndexOfModule != LastModule; ++IndexOfModule){   

			// Initialize json data
			PortList.clear();
			ParameterList.clear();
			RegisterList.clear();

			// get sc_module's port list
			p_PortList = (*IndexOfModule)->get_port_list();	

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
							p_ScPortType = strtok(NULL,"_");
							p_PortName = strtok(NULL," ");



							// add Port to PortList in json format
							if(p_PortName != NULL){
							Port["port_name"] = p_PortName;
							}
							else{
							Port["port_name"] = "null";
							}
							Port["sc_type"]   = p_ScPortType; 
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
			dw_ParNum = (*IndexOfModule)->GetBDDI()->BDDIGetModuleTotalParNum();		

			for(dw_Index = 0; dw_Index < dw_ParNum; dw_Index++){

				BDDIParInfo *pst_ParInfo = (*IndexOfModule)->GetBDDI()->BDDIGetModuleParInfo(); 
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
			dw_RegNum = (*IndexOfModule)->GetBDDI()->BDDIGetModuleTotalRegNum();		

			for(dw_Index = 0; dw_Index < dw_RegNum; dw_Index++){

				BDDIRegInfo *pst_RegInfo = (*IndexOfModule)->GetBDDI()->BDDIGetModuleRegInfo(); 
				Register["register_name"] = pst_RegInfo[dw_Index].Name;	
				sprintf(a_Temp, "%u", pst_RegInfo[dw_Index].Bitswide);
				Register["bits_wide"] = a_Temp;
				sprintf(a_Temp, "%d", (int)pst_RegInfo[dw_Index].Type);	
				Register["type"] = a_Temp;
				RegisterList.append(Register);
			}	

			// add Module to PMModuleList in json format
			Module["module_name"] = (*IndexOfModule)->GetModuleName();
			Module["module_type"] = (*IndexOfModule)->GetBDDI()->BDDIGetModuleType();
			Module["port"] = PortList;
			Module["parameter"] = ParameterList;
			Module["register"] = RegisterList;
			PMModuleList.append(Module);
		}

		Root["PMML"] = PMModuleList;

		Json::StyledWriter writer;
		JsonFileOfPMModuleList = writer.write(Root);
		cout<< endl << "JSON WriteTest" << endl << JsonFileOfPMModuleList << endl; 

		return JsonFileOfPMModuleList;
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
	}

	/*
	 * function 	: ~PMMLGenerationManager
	 * design	    : Destructor
	 */
	PMMLGenerationManager::~PMMLGenerationManager()
	{
	}
}
