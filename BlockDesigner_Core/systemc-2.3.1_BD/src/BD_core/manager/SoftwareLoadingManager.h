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
	// ChannelInfo from Platform Manager
	struct CPUInfo 
	{
		string CPUName;
	  vector<string> ConnectedModules;
	};

	/*
	 * class		    : SoftwareLoadingManager 
	 * design	      : load software based on GUI command 
	 */
	class SoftwareLoadingManager: public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			
			void AddConnectionInfo(string CPUName, string ConnectedModuleName);
			int FindCPU(string CPUName);
			
			static SoftwareLoadingManager* GetInstance();
			static void DeleteInstance();

		protected:
			SoftwareLoadingManager();
		  virtual ~SoftwareLoadingManager();

		private:
			vector<CPUInfo*> CPUs;
		
			static SoftwareLoadingManager *_SoftwareLoadingManager;
			// mutex for singleton pattern 
			static pthread_mutex_t SoftwareLoadingManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif 
