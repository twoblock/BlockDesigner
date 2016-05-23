//-----------------------------------------------------------------------------
// Design								: Software Loading Manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareManager.h
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
#include "../SimulationAPI/SoftwareLoader.h"
#include "../SimulationAPI/SoftwareDisplayer.h"
#include "../SimulationAPI/SoftwareProfiler.h"
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
	  SoftwareDisplayer *p_SoftwareDisplayer;
	  SoftwareProfiler *p_SoftwareProfiler;
	};

	/*
	 * class		    : SoftwareManager 
	 * design	      : manager software information for each cpu 
	 */
	class SoftwareManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			
			void LoadSoftware(int CPUIndex, char *SoftwarePath);
			void SetSoftwareDisplayer(int CPUIndex, char *SoftwarePath);
			void DisplayAssemblyCode();
	
			void SetSoftwareProfiler(int CPUIndex, char *SoftwarePath);
			void PCAnalyzer();
			string GetPC();
			void DisplayProfilingData();

			string GetInitialMemoryView();
			SoftwareProfiler* GetSoftwareProfiler();
			SoftwareDisplayer* GetSoftwareDisplayer();

			void AddConnectionInfo(string CPUName, string ConnectedModuleName);
			int FindCPU(string CPUName);
			vector<CPUInfo*>* GetCPUInfo();

			void SetExistenceOfCPU(bool IsThereCPU);
			bool GetExistenceOfCPU();
			
			static SoftwareManager* GetInstance();
			static void DeleteInstance();

		protected:
			SoftwareManager();
		  virtual ~SoftwareManager();

		private:
			bool ExistenceOfCPU;
			vector<CPUInfo*> CPUs;

			SoftwareLoader *p_SoftwareLoader;
			string InitialMemoryView;

			static SoftwareManager *_SoftwareManager;
			// mutex for singleton pattern 
			static pthread_mutex_t SoftwareManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 
