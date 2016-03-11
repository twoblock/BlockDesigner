//-----------------------------------------------------------------------------
// Design								: Software Displayer 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareDisplayer.h
// Date	       					: 2016/3/7
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: this class help display assembly code 
// ----------------------------------------------------------------------------

#ifndef __SOFTWARE_DISPLAYER_H__
#define __SOFTWARE_DISPLAYER_H__

#include "../PlatformAPI/json/json.h"
#include "systemc.h"
#include <pthread.h>
#include <string>
#include <map>

using namespace std;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ModuleListManager;

	/*
	 * class		    : SoftwareDisplayer 
	 * design	      : display assembly code
	 */
	class SoftwareDisplayer
	{
		public:
			void DisplayAssemblyCode(unsigned int PC);
			void StoreAssemblyCode(char *SoftwarePath);
			void GetAssemblyCodeFromBuffer(char *Buffer, char *SourceCode);
			
			string GetJsonOfSourceCode();

			SoftwareDisplayer();
		  ~SoftwareDisplayer();

		private:
			// json format entities
			Json::Value Root_SourceCodeList;
			Json::Value SourceCodeList;
			Json::Value SourceCode;

			map<unsigned int, string> AssemblyCode;
			map<unsigned int, string>::iterator AssemblyCodeFinder; 
	};
} // namespace BDapi 

#endif 
