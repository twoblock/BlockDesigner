//-----------------------------------------------------------------------------
// Design								: 
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDPMDInitManager.h
// Date	       					: 2016/2/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: 
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
			
			void ConnectModules(const char *FilePath);

			BDPMDReturnStatus ParsingPlatformManagerInformation(const char *FilePath);
			BDPMDReturnStatus ParsingOwnConnectionInformation(unsigned int Index, BindingInfo* BindingObject);
			BDPMDReturnStatus ParsingChannelInformation(unsigned int Index, ChannelInfo* ChannelObject);
			BDPMDReturnStatus ParsingConnectionInformation(unsigned int PIndex, unsigned int CIndex, BindingInfo* BindingObject);

			static BDPMDInitManager* GetInstance();
			static void DeleteInstance();

		protected:
			BDPMDInitManager();
			virtual ~BDPMDInitManager();

		private:
		 	static BDPMDInitManager *_BDPMDInitManager;
			ChannelMap *p_ChannelMap;
			ModuleConnector *p_ModuleConnector;

			Json::Reader InfoReader;
			Json::Value InfoRoot;
			Json::Value InfoChannel;

			char a_TokBuf[BUFFUR_SIZE];

			// mutex for singleton pattern 
			static pthread_mutex_t BDPMDInitManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif	// __BDPMD_INIT_MANAGER_H__
