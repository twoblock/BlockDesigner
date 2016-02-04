//-----------------------------------------------------------------------------
// Design								: Module connection manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleConnector.cpp
// Date	       					: 2016/1/27
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage channels and modules 
//                connect all modules by using channels
// ----------------------------------------------------------------------------

#include "ModuleConnector.h"
#include "PMModuleListManager.h"
#include "../SimulationAPI/ChannelMap.h"

namespace BDapi
{	
	// declare static variable for linker 
	ModuleConnector* ModuleConnector::_ModuleConnector= NULL;
	// initialize mutex 
	pthread_mutex_t ModuleConnector::ModuleConnectorInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    : ConnectModules 
	 * design      : each module port bind this channel, which means to make connection 
	 * param       : char * - First module name 
	 * param       : char * - First module port name 
	 * param       : char * - channel name 
	 * param       : char * - Second module name
	 * param       : char * - Second module port name 
	 * caller      :  
	 */
	void ModuleConnector::ConnectModules(
			const char *FirstModuleName,
			const char *FirstModulePortName, 
			const char *ChannelName,
			const char *SecondModuleName, 
			const char *SecondModulePortName)
	{
		BindingInfo st_FirstBindingInfo;
		BindingInfo st_SecondBindingInfo;

		st_FirstBindingInfo.ModuleName = FirstModuleName;
		st_FirstBindingInfo.ModulePortName = FirstModulePortName;
		st_FirstBindingInfo.ChannelName = ChannelName;

		st_SecondBindingInfo.ModuleName = SecondModuleName;
		st_SecondBindingInfo.ModulePortName = SecondModulePortName;
		st_SecondBindingInfo.ChannelName = ChannelName;

		BindChannel(&st_FirstBindingInfo);
		BindChannel(&st_SecondBindingInfo);
	}

	/*
	 * function    : BindChannel 
	 * design      : one module port connect this channel 
	 * param       : char * - Module name 
	 * param       : char * - Module port name 
	 * param       : char * - Channel name 
	 * caller      :  
	 */
	void ModuleConnector::BindChannel(BindingInfo *BindingObject)
	{
		sc_module *p_SCmodule = NULL;
		p_SCmodule = p_PMModuleListManager->FindModule(BindingObject->ModuleName);

		std::vector<sc_port_base*>* p_PortList = NULL;
		p_PortList = p_SCmodule->get_port_list();	

		// find channel
		sc_interface *p_SCinterface = NULL;
		p_SCinterface = p_ChannelMap->FindChannel(BindingObject->ChannelName);

		// find port
		sc_port_base *p_SCportbase = NULL;
		std::vector<sc_port_base*>::iterator FirstPort = p_PortList->begin(); 
		std::vector<sc_port_base*>::iterator LastPort = p_PortList->end(); 
		std::vector<sc_port_base*>::iterator IndexOfPort = FirstPort;

		for(IndexOfPort = FirstPort; IndexOfPort != LastPort; ++IndexOfPort){   
			p_SCportbase = (*IndexOfPort);
			if(strcmp(p_SCportbase->get_port_name(), BindingObject->ModulePortName) == 0){
				// this port bind channel
				p_SCportbase->BDbind(*p_SCinterface);
			}
		} 
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	ModuleConnector* ModuleConnector::GetInstance()
	{
		// lock
		pthread_mutex_lock(&ModuleConnectorInstanceMutex); 

		if( _ModuleConnector == NULL ){
			_ModuleConnector = new ModuleConnector();
		}
		// unlock
		pthread_mutex_unlock(&ModuleConnectorInstanceMutex);

		return _ModuleConnector;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete ModuleConnector instance 
	 */
	void ModuleConnector::DeleteInstance()
	{	
		delete _ModuleConnector;
		_ModuleConnector = NULL;
	}

	/*
	 * function 	: ModuleConnector 
	 * design	    : Constructor 
	 */
	ModuleConnector::ModuleConnector()
	{
		p_PMModuleListManager = PMModuleListManager::GetInstance();
		p_ChannelMap = ChannelMap::GetInstance();
	}

	/*
	 * function 	: ~ModuleConnector 
	 * design	    : Destructor
	 */
	ModuleConnector::~ModuleConnector()
	{
	}
}
