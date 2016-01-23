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

#include "PMModuleListGenerator.h"

#include <string.h>

#include <iostream>
#include <vector>
#include <list>
#include "json/json.h"

#define Size 128

namespace BDapi
{
	/*
	 * function    	: 
	 * design	      : 
	 * description	: 
	 * caller		    : 
	 * callee		    : 
	 */
	string PMModuleListGenerator::GenerateJsonFile(list<sc_module*>* SCModuleList)
	{
		Json::Value Root;
		Json::Value PMModuleList;
		Json::Value Module;
		Json::Value PortList;
		Json::Value Port;

		char p_PortTypeInfo[Size];
		const char *p_ScPortType;
		const char *p_DataType;

		list<sc_module*>::iterator First = SCModuleList->begin();
		list<sc_module*>::iterator End = SCModuleList->end();
		////////////////////////////////////////////////////////////////

		// one module
		// get portlist from sc_module
		std::vector<sc_port_base*>* TestPortList = NULL;
		TestPortList = (*First)->get_port_list();	

		// make iterator to get all port information
		std::vector<sc_port_base*>::const_iterator
		it  = TestPortList->begin(), end = TestPortList->end();

		for( ; it != end; ++it  ){   
		// parse port information
		strcpy(p_PortTypeInfo, (*it)->kind());
		p_DataType = (strtok(p_PortTypeInfo, "\n"));
		p_ScPortType = strtok(NULL,"\n");

		// add port to port list
		Port["port_name"] = (*it)->get_port_name();
		Port["sc_type"]   = p_ScPortType; 
		Port["data_type"] = p_DataType;
		PortList.append(Port);	
		}   

		// make module info
		Module["module_name"] = "AHB_Lite";
		Module["module_type"] = "bus";
		Module["port"] = PortList;

		// add module to Platform Manager Module List
		PMModuleList.append(Module);

		//////////////////////////////////////////////////////////


		Root["PMML"] = PMModuleList;

		Json::StyledWriter writer;
		string strJSON = writer.write(Root);

		cout<< endl << "JSON WriteTest" << endl << strJSON << endl; 

		return strJSON;

		return JsonFileOfPMModuleList;
	}
}
