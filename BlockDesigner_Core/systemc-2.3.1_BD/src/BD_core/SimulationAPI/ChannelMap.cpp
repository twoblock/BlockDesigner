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
		else if(strcmp(st_ChannelInfo->ChannelType, "AHB") == 0)
			AddAHBSignal(st_ChannelInfo->ChannelName, st_ChannelInfo->DataType);
		else if(strcmp(st_ChannelInfo->ChannelType, "AHBLITE") == 0)
			AddAHBLiteSignal(st_ChannelInfo->ChannelName, st_ChannelInfo->DataType);
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

		std::map<std::string, ChannelObject*>::iterator FirstChannel = RealChannelMap.begin();
		std::map<std::string, ChannelObject*>::iterator LastChannel = RealChannelMap.end();
		std::map<std::string, ChannelObject*>::iterator IndexOfChannel = FirstChannel;

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
		std::string TempString(ChannelName);

		ChannelFinder = RealChannelMap.find(TempString);

		if( ChannelFinder != RealChannelMap.end() )  
			return ChannelFinder->second;
		else	return NULL;
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
		std::string TempString(ChannelName);
	
		RealChannelMap[TempString] = p_ChannelObject;
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
		std::string TempString(ChannelName);
	
		RealChannelMap[TempString] = p_ChannelObject;
	}

	/*
	 * function    : add sc_signal 
	 * design      : allocate sc_signal and push it to map
	 * param       : char * - channel name
	 * param       : char * - data type
	 */
	void ChannelMap::AddAHBSignal(const char *ChannelName, const char *DataType)
	{
		sc_interface *p_SCinterface = NULL;
		char a_NameTemp[256] = {0,};

		if(strcmp(DataType, "Master") == 0)	{
			char a_UINTTemp[7][256] = { "$AHBHADDR_", "$AHBHBURST_", "$AHBHRDATA_",
															 		"$AHBHSIZE_", "$AHBHTRANS_", "$AHBHWDATA_", "$AHBHPROT_" };

			char a_BOOLTemp[6][256] = { "$AHBHLOCK_", "$AHBHWRITE_", "$AHBHREADY_",
																	"$AHBHRESP_", "$AHBHBUSREQ_", "$AHBHGRANT_" };

			for(int UINTIndex = 0; UINTIndex < 7; UINTIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_UINTTemp[UINTIndex]);	

				p_SCinterface = new sc_signal<unsigned int>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();
				
				strcpy(p_ChannelObject->ChannelType, "AHB");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}

			for(int BOOLIndex = 0; BOOLIndex < 6; BOOLIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_BOOLTemp[BOOLIndex]);

				p_SCinterface = new sc_signal<bool>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();

				strcpy(p_ChannelObject->ChannelType, "AHB");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}
		}
		else if(strcmp(DataType, "Slave") == 0)	{
			char a_UINTTemp[7][256] = { "$AHBHADDR_", "$AHBHBURST_", "$AHBHRDATA_",
																	"$AHBHPROT_", "$AHBHTRANS_", "$AHBHWDATA_", "$AHBHSIZE_" };

			char a_BOOLTemp[6][256] = { "$AHBHLOCK_", "$AHBHWRITE_", "$AHBHREADY_", 
																	"$AHBHSEL_", "$AHBHREADYOUT_", "$AHBHRESP_" };

			for(int UINTIndex = 0; UINTIndex < 7; UINTIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_UINTTemp[UINTIndex]);

				p_SCinterface = new sc_signal<unsigned int>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();
				
				strcpy(p_ChannelObject->ChannelType, "AHB");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}

			for(int BOOLIndex = 0; BOOLIndex < 6; BOOLIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_BOOLTemp[BOOLIndex]);

				p_SCinterface = new sc_signal<bool>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();

				strcpy(p_ChannelObject->ChannelType, "AHB");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}
		}
		else
			return;
	}

	/*
	 * function    : add sc_signal 
	 * design      : allocate sc_signal and push it to map
	 * param       : char * - channel name
	 * param       : char * - data type
	 */
	void ChannelMap::AddAHBLiteSignal(const char *ChannelName, const char *DataType)
	{
		sc_interface *p_SCinterface = NULL;
		char a_NameTemp[256] = {0,};

		if(strcmp(DataType, "Master") == 0)	{
			char a_UINTTemp[7][256] = { "$HADDR_", "$HBURST_", "$HRDATA_",
															 		"$HSIZE_", "$HTRANS_", "$HWDATA_", "$HPROT_" };

			char a_BOOLTemp[4][256] = { "$HLOCK_", "$HWRITE_", "$HREADY_", "$HRESP_" };

			for(int UINTIndex = 0; UINTIndex < 7; UINTIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_UINTTemp[UINTIndex]);	

				p_SCinterface = new sc_signal<unsigned int>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();
				
				strcpy(p_ChannelObject->ChannelType, "AHBLITE");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}

			for(int BOOLIndex = 0; BOOLIndex < 4; BOOLIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_BOOLTemp[BOOLIndex]);

				p_SCinterface = new sc_signal<bool>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();

				strcpy(p_ChannelObject->ChannelType, "AHBLITE");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}
		}
		else if(strcmp(DataType, "Slave") == 0)	{
			char a_UINTTemp[7][256] = { "$HADDR_", "$HBURST_", "$HRDATA_",
																	"$HPROT_", "$HTRANS_", "$HWDATA_", "$HSIZE_" };

			char a_BOOLTemp[6][256] = { "$HLOCK_", "$HWRITE_", "$HREADY_", 
																	"$HSEL_", "$HREADYOUT_", "$HRESP_" };

			for(int UINTIndex = 0; UINTIndex < 7; UINTIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_UINTTemp[UINTIndex]);

				p_SCinterface = new sc_signal<unsigned int>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();
				
				strcpy(p_ChannelObject->ChannelType, "AHBLITE");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}

			for(int BOOLIndex = 0; BOOLIndex < 6; BOOLIndex++)	{
				strcpy(a_NameTemp, ChannelName);
				strcat(a_NameTemp, a_BOOLTemp[BOOLIndex]);

				p_SCinterface = new sc_signal<bool>(a_NameTemp);

				ChannelObject *p_ChannelObject = new ChannelObject();

				strcpy(p_ChannelObject->ChannelType, "AHBLITE");
				strcpy(p_ChannelObject->DataType, DataType);
				p_ChannelObject->p_SCinterface = p_SCinterface;

				std::string TempString(a_NameTemp);

				RealChannelMap[TempString] = p_ChannelObject;
			}
		}
		else
			return;
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

	/*
	 * function 	: ~ChannelMap 
	 * design	    : Destructor 
	 */
	ChannelMap::~ChannelMap()
	{
		DeleteChannels();
	}
}


