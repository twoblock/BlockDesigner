//-----------------------------------------------------------------------------
// Design								: Platform Manager Core 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDSim.cpp
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: load module and give that information to load manager
// ----------------------------------------------------------------------------

#include "BDPlatform.h"
#include "systemc.h"

// dynamic link so file
#include <dlfcn.h> 

// json
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "json/json.h"

#define Size 128

using namespace std;

typedef void (*Function)(const char*);

namespace BDapi
{
	/*
	 * function    	: PlatformManagerCore 
	 * design	      : load module and give that information to load manager 
	 * description	: 
	 * caller		    : 
	 * callee		    : 
	 */
	void PlatformManagerCore()
	{
		char p_PortTypeInfo[Size];
		const char *p_ScPortType;
		const char *p_DataType;
		
		while(1){

			// load module so file
			void* pHandle = dlopen("/home/tom/workspace/DebugforParsing/TestPlatform/AHB_Lite/libAHB_Lite.so", RTLD_NOW);
			if(!pHandle){ 
				printf("fail to dlopen, %s\n", dlerror());
			}

			// find function symbol
			Function CreateInstance = (Function)dlsym(pHandle,"CreateInstance");
			if ( dlerror() != NULL ){
				printf("fail to dlsym, %s\n", dlerror());
			}

			// Insantiate module ( new module )
			CreateInstance("AHB_Lite");

			// find module in kernel
			sc_module *p_Module;
			p_Module = static_cast<sc_module*>(sc_find_object("AHB_Lite"));

			// get portlist from module
			std::vector<sc_port_base*>* TestPortList = NULL;
			TestPortList = p_Module->get_port_list();	

			Json::Value root;
			Json::Value PMML;
			Json::Value Module;
			Json::Value Friends;
			Json::Value FREN;

			Json::Value ModuleName;

			// print port information
			std::vector<sc_port_base*>::const_iterator
				it  = TestPortList->begin(), end = TestPortList->end();

			for( ; it != end; ++it  ){   
			  strcpy(p_PortTypeInfo, (*it)->kind());
				p_DataType = (strtok(p_PortTypeInfo, "\n"));
				p_ScPortType = strtok(NULL,"\n");

				FREN["port_name"] = (*it)->get_port_name();
				FREN["sc_type"]   = p_ScPortType; 
				FREN["data_type"] = p_DataType;

				Friends.append(FREN);	
			}   

			//PMML.append(Module);
			Module["module_name"] = "AHB_Lite";
			Module["module_type"] = "bus";
			Module["port"] = Friends;

			PMML.append(Module);
			root["PMML"] = PMML;

			Json::StyledWriter writer;
			string strJSON = writer.write(root);

			cout<< endl << "JSON WriteTest" << endl << strJSON << endl;

			dlclose(pHandle);

			while(1);
		}
	}
}
