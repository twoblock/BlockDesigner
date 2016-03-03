//-----------------------------------------------------------------------------
// Design								: Software Loading Manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareLoadingManager.h
// Date	       					: 2016/3/2
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: help tool load software 
// ----------------------------------------------------------------------------

#ifndef __SOFTWARE_LOADING_MANAGER_H 
#define __SOFTWARE_LOADING_MANAGER_H  

#include "TopManagerBase.h"
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

	// ChannelInfo from Platform Manager
	struct CPUInfo 
	{
		string CPUName;
	  vector<string> ConnectedModules;
	};

	// Return type of parsing hex file
	enum ReturnType_Of_Parsing
	{
		End_Of_File,
		Address,
	  Binary	
	};

	/*
	 * class		    : SoftwareLoadingManager 
	 * design	      : load software based on GUI command 
	 */
	class SoftwareLoadingManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			
			void LoadSoftware(char *CPUName, char *SoftwarePath);
			void ProcessLoading(int CPUIndex);
			BDDI* FindTargetMemoryBDDI(int CPUIndex, UINT32 Address);
			BDDI* SearchTargetMemoryInBus(sc_module *SCmodule);
			ReturnType_Of_Parsing ParsingHexFile(FILE *HexFile, UINT32 *Value);

			void AddConnectionInfo(string CPUName, string ConnectedModuleName);
			int FindCPU(string CPUName);
			
			static SoftwareLoadingManager* GetInstance();
			static void DeleteInstance();

		protected:
			SoftwareLoadingManager();
		  virtual ~SoftwareLoadingManager();

		private:
			vector<CPUInfo*> CPUs;
			ModuleListManager *p_ModuleListManager;

			static SoftwareLoadingManager *_SoftwareLoadingManager;
			// mutex for singleton pattern 
			static pthread_mutex_t SoftwareLoadingManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 
