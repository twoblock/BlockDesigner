//-----------------------------------------------------------------------------
// Design								: Simulation Core 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDSim.h
// Date	       					: 2016/1/3
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: simulate systemc kernel and conrol it  
// ----------------------------------------------------------------------------

#ifndef __BDPLATFORM_H__
#define __BDPLATFORM_H__

#include "systemc.h"
#include <string>
#include <list>

using namespace std;
using namespace sc_core;

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class PMModuleListGenerator{

		public:
			string GenerateJsonFile(list<sc_module*>* SCModuleList);

		private:
			string JsonFileOfPMModuleList;
	}; 
}
#endif 

