//-----------------------------------------------------------------------------
// Design								: Module connection manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleConnectionManager.cpp
// Date	       					: 2016/1/27
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage channels and modules 
//                connect all modules by using channels
// ----------------------------------------------------------------------------

#include "ModuleConnectionManager.h"
#include "PMModuleListManager.h"
#include "../SimulationAPI/ChannelManager.h"
#include "../PlatformAPI/PMInfoJsonParser.h"

namespace BDapi
{	
	// declare static variable for linker 
	ModuleConnectionManager* ModuleConnectionManager::_ModuleConnectionManager= NULL;
	// initialize mutex 
	pthread_mutex_t ModuleConnectionManager::ModuleConnectionManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	void ModuleConnectionManager::PutOperationControl(GUI_COMMAND Command)
	{
		ChannelInfo st_ChannelInfo = {NULL, NULL, NULL};
		BindingInfo st_BindingInfo = {NULL, NULL, NULL};

		p_PMInfoJsonParser->ParsingPlatformManagerInformation("/home/harold/BDPMD.json");

		for(unsigned int dw_PIndex = 0; ; dw_PIndex++)	{
			if(p_PMInfoJsonParser->ParsingChannelInformation(dw_PIndex, &st_ChannelInfo) == PMInfoReturnStatusError)	break;
			else	{
				p_ChannelManager->AddChannel(&st_ChannelInfo);

				p_PMInfoJsonParser->ParsingOwnConnectionInformation(dw_PIndex, &st_BindingInfo);
				BindChannel(&st_BindingInfo);

				for(unsigned int dw_CIndex = 0; ; dw_CIndex++)	{
					if(p_PMInfoJsonParser->ParsingConnectionInformation(dw_PIndex, dw_CIndex, &st_BindingInfo) == PMInfoReturnStatusError)	break;
					else	{
						BindChannel(&st_BindingInfo);
					}
				}
			}
		}
	}
	void ModuleConnectionManager::GetOperationControl(GUI_COMMAND Command)
	{

	}
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
	void ModuleConnectionManager::ConnectModules(
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
	void ModuleConnectionManager::BindChannel(BindingInfo *BindingObject)
	{
		sc_module *p_SCmodule = NULL;
		p_SCmodule = p_PMModuleListManager->FindModule(BindingObject->ModuleName);

		std::vector<sc_port_base*>* p_PortList = NULL;
		p_PortList = p_SCmodule->get_port_list();	

		// find channel
		sc_interface *p_SCinterface = NULL;
		p_SCinterface = p_ChannelManager->FindChannel(BindingObject->ChannelName);

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
	ModuleConnectionManager* ModuleConnectionManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&ModuleConnectionManagerInstanceMutex); 

		if( _ModuleConnectionManager == NULL ){
			_ModuleConnectionManager = new ModuleConnectionManager();
		}
		// unlock
		pthread_mutex_unlock(&ModuleConnectionManagerInstanceMutex);

		return _ModuleConnectionManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete ModuleConnectionManager instance 
	 */
	void ModuleConnectionManager::DeleteInstance()
	{	
		delete _ModuleConnectionManager;
		_ModuleConnectionManager = NULL;
	}

	/*
	 * function 	: ModuleConnectionManager 
	 * design	    : Constructor 
	 */
	ModuleConnectionManager::ModuleConnectionManager()
	{
		p_PMModuleListManager = PMModuleListManager::GetInstance();
		p_ChannelManager = new ChannelManager();
		p_PMInfoJsonParser = new PMInfoJsonParser();
	}

	/*
	 * function 	: ~ModuleConnectionManager 
	 * design	    : Destructor
	 */
	ModuleConnectionManager::~ModuleConnectionManager()
	{
		delete p_ChannelManager;
		p_ChannelManager = NULL;

		delete p_PMInfoJsonParser;
		p_PMInfoJsonParser = NULL;
	}
}
