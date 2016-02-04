//-----------------------------------------------------------------------------
// Design								: Channel manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ChannelMap.cpp
// Date	       					: 2016/1/26
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manager all channels to connect sc_module
// ----------------------------------------------------------------------------

#include "ChannelMap.h"

namespace BDapi
{
	// declare static variable for linker 
	ChannelMap* ChannelMap::_ChannelMap = NULL;
	// initialize mutex 
	pthread_mutex_t ChannelMap::ChannelMapInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  
	
	/*
	 * function    : AddChannel 
	 * design      : add channel to channel map
	 * param       : char * - channel type 
	 * param       : char * - channel name
	 * param       : char * - data type
	 * caller      :  
	 */
	void ChannelMap::AddChannel(ChannelInfo *ChannelObject)
	{
		if(strcmp(ChannelObject->ChannelType, "sc_signal") == 0)
			AddSCsignal(ChannelObject->ChannelName, ChannelObject->DataType);
		else if(strcmp(ChannelObject->ChannelType, "sc_clock") == 0)
			AddSCclock(ChannelObject->ChannelName, ChannelObject->DataType);
		else
			return;
	}

	/*
	 * function    : DeleteChannels
	 * design      : release all channel that is allocated 
	 * caller      : 
	 */
	void ChannelMap::DeleteChannels()
	{
		sc_interface *p_SCinterface = NULL;

		std::map<const char*, sc_interface*>::iterator FirstChannel = RealChannelMap.begin();
		std::map<const char*, sc_interface*>::iterator LastChannel = RealChannelMap.end();
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
	sc_interface* ChannelMap::FindChannel(const char *ChannelName)
	{
		ChannelFinder = RealChannelMap.find(ChannelName);

		if( ChannelFinder != RealChannelMap.end() )  
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
	void ChannelMap::AddSCsignal(const char *ChannelName, const char *DataType)
	{
		sc_interface *p_SCinterface = NULL;

		if(strcmp(DataType, "bool") == 0)
			p_SCinterface =	new sc_signal<bool>(ChannelName);
		else if(strcmp(DataType, "UINT32") == 0)
			p_SCinterface =	new sc_signal<unsigned int>(ChannelName);
		else
			return;

		RealChannelMap.insert(map<const char*, sc_interface*>::value_type(ChannelName, p_SCinterface));	
	}

	/*
	 * function    : add sc_clock
	 * design      : allocate sc_clock and push it to map
	 * param       : char * - channel name
	 * param       : char * - data type
	 */
	void ChannelMap::AddSCclock(const char *ChannelName, const char *DataType)
	{
		sc_interface *p_SCinterface = NULL;

		p_SCinterface =	new sc_clock(ChannelName, 10, SC_NS);

		RealChannelMap.insert(map<const char*, sc_interface*>::value_type(ChannelName, p_SCinterface));	
	}
	
  /*
	 * function 	: GetInstance
	 * design	    : Allocate ChannelMap instance and return it
	 */
	ChannelMap* ChannelMap::GetInstance()
	{
		// lock
		pthread_mutex_lock(&ChannelMapInstanceMutex); 
	  	
		if( _ChannelMap == NULL ){
			_ChannelMap = new ChannelMap();
		}
		// unlock
		pthread_mutex_unlock(&ChannelMapInstanceMutex);
		
		return _ChannelMap;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete ChannelMap instance 
	 */
	void ChannelMap::DeleteInstance()
	{
		delete _ChannelMap;
		_ChannelMap = NULL;
	}

	/*
	 * function 	: ChannelMap 
	 * design	    : Constructor 
	 */
	ChannelMap::ChannelMap()
	{
	}
}


