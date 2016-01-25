//-----------------------------------------------------------------------------
// Design								: json file generator for sc_module List 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: PMModuleListGenerator.h
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: get sc_module list and make json formate file 
// ----------------------------------------------------------------------------

#ifndef __PM_MODULELIST_GENERATOR_H__
#define __PM_MODULELIST_GENERATOR_H__

#include "systemc.h"
#include <string>
#include <list>

using namespace std;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : PMModuleListGenerator 
	 * design	      : json file generator for sc_module list
	 *                the generated information is used at Platform Manager
	 */
	class PMModuleListGenerator
	{
		public:
			string GenerateJsonFile(list<sc_module*> SCModuleList);

		private:
			string JsonFileOfPMModuleList;
	}; 
}
#endif 

