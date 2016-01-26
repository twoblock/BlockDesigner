//-----------------------------------------------------------------------------
// Design								: Channel manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ChannelManager.h
// Date	       					: 2016/1/26
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manager all channels to connect sc_module
// ----------------------------------------------------------------------------

#ifndef __CHANNEL_MANAGER_H__
#define __CHANNEL_MANAGER_H__

#include "systemc.h"
#include "string.h"
#include <map>

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : 
	 * design	      :
	 * description	: 
	 */
	class ChannelManager
	{
		public:
		  void AddChannel(const char *ChannelType, const char *ChannelName, const char *DataType);
			void DeleteChannels();
		  sc_interface* FindChannel(const char *ChannelName);
			
		private:
		  void AddSCsignal(const char *ChannelName, const char *DataType);
		  void AddSCclock(const char *ChannelName, const char *DataType);
			
			std::map<const char*, sc_interface*> ChannelMap;
			std::map<const char*, sc_interface*>::iterator ChannelFinder; 
	};
} // namespace BDapi 

#endif 

