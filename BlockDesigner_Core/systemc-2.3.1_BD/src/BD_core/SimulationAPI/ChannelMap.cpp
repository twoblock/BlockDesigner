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
	void ChannelMap::AddChannel(ChannelInfo *st_ChannelInfo)
	{
		if(strcmp(st_ChannelInfo->ChannelType, "sc_signal") == 0)
			AddSCsignal(st_ChannelInfo->ChannelName, st_ChannelInfo->DataType);
		else if(strcmp(st_ChannelInfo->ChannelType, "sc_clock") == 0)
			AddSCclock(st_ChannelInfo->ChannelName, st_ChannelInfo->DataType);
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
		ChannelObject *p_ChannelObject = NULL;
		sc_interface *p_SCinterface = NULL;

		std::map<const char*, ChannelObject*>::iterator FirstChannel = RealChannelMap.begin();
		std::map<const char*, ChannelObject*>::iterator LastChannel = RealChannelMap.end();
		std::map<const char*, ChannelObject*>::iterator IndexOfChannel = FirstChannel;

		for(IndexOfChannel = FirstChannel; IndexOfChannel != LastChannel; ++IndexOfChannel){
			p_ChannelObject	= IndexOfChannel->second;
			p_SCinterface = p_ChannelObject->p_SCinterface;

			delete p_SCinterface;
			p_SCinterface = NULL;

			delete p_ChannelObject;
			p_ChannelObject = NULL;
		}
	}

	/*
	 * function    : FindChannel 
	 * design      : find channel in map and return it 
	 * param       : char * - channel name
	 * return      : ChannelObject* - ChannelObject pointer
	 * caller      : 
	 */
	ChannelObject* ChannelMap::FindChannel(const char *ChannelName)
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
		
		ChannelObject *p_ChannelObject = new ChannelObject();

		// assign datas in ChannelObject
		strcpy(p_ChannelObject->ChannelType, "sc_signal");
		strcpy(p_ChannelObject->DataType, DataType);
		p_ChannelObject->p_SCinterface = p_SCinterface; 

		// insert ChannelObject into map
		RealChannelMap[ChannelName] = p_ChannelObject;
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
		
		ChannelObject *p_ChannelObject = new ChannelObject();

		// assign datas in ChannelObject
		strcpy(p_ChannelObject->ChannelType, "sc_clock");
		strcpy(p_ChannelObject->DataType, DataType);
		p_ChannelObject->p_SCinterface = p_SCinterface; 

		// insert ChannelObject into map
		RealChannelMap[ChannelName] = p_ChannelObject;
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


