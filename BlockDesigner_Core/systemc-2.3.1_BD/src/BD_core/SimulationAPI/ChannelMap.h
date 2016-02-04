//-----------------------------------------------------------------------------
// Design								: Channel Map to manager channels 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ChannelMap.h
// Date	       					: 2016/1/26
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage channels and give  channel information to other manager 
// ----------------------------------------------------------------------------

#ifndef __CHANNEL_MAP_H__
#define __CHANNEL_MAP_H__

#include "systemc.h"
#include "string.h"
#include <map>
#include <pthread.h>

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	struct ChannelInfo
	{
		const char *ChannelType;
		const char *ChannelName;
		const char *DataType;
	};

	/*
	 * class		    : 
	 * design	      :
	 * description	: 
	 */
	class ChannelMap
	{
		public:
		  void AddChannel(ChannelInfo *ChannelObject);
			void DeleteChannels();
		  sc_interface* FindChannel(const char *ChannelName);
		
			static ChannelMap* GetInstance();
			static void DeleteInstance();
		
		protected:
			ChannelMap();
	
		private:
		  void AddSCsignal(const char *ChannelName, const char *DataType);
		  void AddSCclock(const char *ChannelName, const char *DataType);
			
			std::map<const char*, sc_interface*> RealChannelMap;
			std::map<const char*, sc_interface*>::iterator ChannelFinder; 
			
			static ChannelMap *_ChannelMap; 
			// mutex for singleton pattern 
			static pthread_mutex_t ChannelMapInstanceMutex;   
	};
} // namespace BDapi 

#endif 

