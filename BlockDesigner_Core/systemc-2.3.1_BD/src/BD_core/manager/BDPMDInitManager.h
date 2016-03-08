//-----------------------------------------------------------------------------
// Design								: Block Designer Platform Module List Initialization
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDPMDInitManager.h
// Date	       					: 2016/2/4
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: Extract the information from BDPMD json file to initialize
//								Block Designer environment
// ----------------------------------------------------------------------------

#ifndef __BDPMD_INIT_MANAGER_H__
#define __BDPMD_INIT_MANAGER_H__

#include "TopManagerBase.h"
#include <pthread.h>
#include <iostream>
#include <fstream>
#include "../PlatformAPI/json/json.h"

#define BUFFUR_SIZE				128

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class ModuleConnector;
	class ModuleListManager;
	class ChannelMap;

	struct BindingInfo;
	struct ChannelInfo;

	enum BDPMDReturnStatus
	{
		BDPMDReturnStatusOk,
		BDPMDReturnStatusDisable,
		BDPMDReturnStatusError
	};

	/*
	 * class		    : BDPMDInitManager
	 * design	      : 
	 * description	: 
	 */
	class BDPMDInitManager : public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void GetOperationControl(GUI_COMMAND Command);
			
			BDPMDReturnStatus ParsingPlatformManagerInformation(const char *FilePath);
			
			void LoadModules();
			void ConnectModules();

			BDPMDReturnStatus ParsingOwnConnectionInformation(unsigned int Index, BindingInfo* BindingObject);
			BDPMDReturnStatus ParsingChannelInformation(unsigned int Index, ChannelInfo* ChannelObject);
			BDPMDReturnStatus ParsingConnectionInformation(unsigned int PIndex, unsigned int CIndex, BindingInfo* BindingObject);

			void SetMemoryMap();
			void SetCPUInfo();

			static BDPMDInitManager* GetInstance();
			static void DeleteInstance();

		protected:
			BDPMDInitManager();
			virtual ~BDPMDInitManager();

		private:
			static BDPMDInitManager *_BDPMDInitManager;

			ChannelMap *p_ChannelMap;
			ModuleConnector *p_ModuleConnector;
			ModuleListManager *p_ModuleListManager;

			Json::Reader InfoReader;
			Json::Value InfoRoot;
			Json::Value InfoChannel;
			Json::Value InfoModule;
			Json::Value InfoMemoryMap;
			Json::Value InfoSlave;

			char a_TokBuf[BUFFUR_SIZE];

			// mutex for singleton pattern 
			static pthread_mutex_t BDPMDInitManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif	// __BDPMD_INIT_MANAGER_H__
