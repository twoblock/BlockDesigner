//-----------------------------------------------------------------------------
// Design								: Software Loader
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareLoader.h
// Date	       					: 2016/3/2
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: help tool load software 
// ----------------------------------------------------------------------------

#ifndef __SOFTWARE_LOADER_H__
#define __SOFTWARE_LOADER_H__

#include "BD_core/PlatformAPI/json/json.h"
#include "systemc.h"
#include <pthread.h>
#include <vector>
#include <string>

using namespace std;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ModuleListManager;

	// Return type of parsing hex file
	enum ReturnType_Of_Parsing
	{
		End_Of_File,
		Address,
		Binary	
	};

	/*
	 * class		    : SoftwareLoader 
	 * design	      : load software based on GUI command 
	 */
	class SoftwareLoader
	{
		public:
			void LoadSoftware(int CPUIndex, char *SoftwarePath);
			void ProcessLoading(int CPUIndex);
			sc_module* FindTargetMemoryBDDI(int CPUIndex, UINT32 dw_Address);
			sc_module* SearchTargetMemoryInBus(sc_module *SCmodule, UINT32 dw_Address);
			ReturnType_Of_Parsing ParsingHexFile(FILE *HexFile, UINT32 *Value);

			void PushBinaryToJson(const char *ModuleInstanceName, unsigned int Address, unsigned int Value);
			string GetMemoryViewList();

			SoftwareLoader();
			~SoftwareLoader();

		private:
			// json format entities
			Json::Value Root_MemoryViewList;
			Json::Value MemoryViewList;
			Json::Value MemoryView;
			Json::Value BinaryValueList;
			Json::Value BinaryValue;

			ModuleListManager *p_ModuleListManager;
	};
} // namespace BDapi 

#endif 
