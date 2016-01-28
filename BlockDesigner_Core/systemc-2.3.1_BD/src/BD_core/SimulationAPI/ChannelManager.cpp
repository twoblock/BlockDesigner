//-----------------------------------------------------------------------------
// Design								: Channel manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ChannelManager.cpp
// Date	       					: 2016/1/26
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manager all channels to connect sc_module
// ----------------------------------------------------------------------------

#include "ChannelManager.h"

namespace BDapi
{
	/*
	 * function    : AddChannel 
	 * design      : add channel to channel map
	 * param       : char * - channel type 
	 * param       : char * - channel name
	 * param       : char * - data type
	 * caller      :  
	 */
	void ChannelManager::AddChannel(const char *ChannelType, const char *ChannelName, const char *DataType)
	{
		if(strcmp(ChannelType, "sc_signal") == 0)
			AddSCsignal(ChannelName, DataType);
		else if(strcmp(ChannelType, "sc_clock") == 0)
			AddSCclock(ChannelName, DataType);
		else
			return;
	}

	/*
	 * function    : DeleteChannels
	 * design      : release all channel that is allocated 
	 * caller      : 
	 */
	void ChannelManager::DeleteChannels()
	{
		sc_interface *p_SCinterface = NULL;

		std::map<const char*, sc_interface*>::iterator FirstChannel = ChannelMap.begin();
		std::map<const char*, sc_interface*>::iterator LastChannel = ChannelMap.end();
		std::map<const char*, sc_interface*>::iterator IndexOfChannel = FirstChannel;

		for(IndexOfChannel = FirstChannel; IndexOfChannel != LastChannel; ++IndexOfChannel){
			p_SCinterface = IndexOfChannel->second;
			delete p_SCinterface;
		}

	}

	/*
	 * function    : FindChannel 
	 * design      : find channel in map and return it 
	 * param       : char * - channel name
	 * return      : sc_interface * - channel pointer
	 * caller      : 
	 */
	sc_interface* ChannelManager::FindChannel(const char *ChannelName)
	{
		ChannelFinder = ChannelMap.find(ChannelName);

		if( ChannelFinder != ChannelMap.end() )  
			return ChannelFinder->second;
		else
			return NULL;
	}

	/*
	 * function    : add sc_signal 
	 * design      : allocate sc_signal and push it to map
	 * param       : char * - channel name
	 * param       : char * - data type
	 */
	void ChannelManager::AddSCsignal(const char *ChannelName, const char *DataType)
	{
		sc_interface *p_SCinterface = NULL;

		if(strcmp(DataType, "bool") == 0)
			p_SCinterface =	new sc_signal<bool>(ChannelName);
		else if(strcmp(DataType, "UINT32") == 0)
			p_SCinterface =	new sc_signal<unsigned int>(ChannelName);
		else
			return;

		ChannelMap.insert(map<const char*, sc_interface*>::value_type(ChannelName, p_SCinterface));	
	}

	/*
	 * function    : add sc_clock
	 * design      : allocate sc_clock and push it to map
	 * param       : char * - channel name
	 * param       : char * - data type
	 */
	void ChannelManager::AddSCclock(const char *ChannelName, const char *DataType)
	{
		sc_interface *p_SCinterface = NULL;

		//if(strcmp(DataType, "bool") == 0)
			p_SCinterface =	new sc_clock(ChannelName, 10, SC_NS);
		//else
			//return;

		ChannelMap.insert(map<const char*, sc_interface*>::value_type(ChannelName, p_SCinterface));	
	}
}


