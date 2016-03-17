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
#include "ModuleListManager.h"
#include "../SimulationAPI/ChannelMap.h"

namespace BDapi
{	
	// declare static variable for linker 
	ModuleConnector* ModuleConnector::_ModuleConnector= NULL;
	// initialize mutex 
	pthread_mutex_t ModuleConnector::ModuleConnectorInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    : BindChannel 
	 * design      : one module port connect this channel 
	 * param       : char * - Module name 
	 * param       : char * - Module port name 
	 * param       : char * - Channel name 
	 * caller      :  
	 */
	void ModuleConnector::BindChannel(BindingInfo *BindingObject, ChannelInfo *ChannelMatching)
	{
		sc_module *p_SCmodule = NULL;
		p_SCmodule = p_ModuleListManager->FindModule(BindingObject->ModuleName);

		std::vector<sc_port_base*>* p_PortList = NULL;
		p_PortList = p_SCmodule->get_port_list();

		if(strcmp(ChannelMatching->ChannelType, "AHB") == 0)	{
			char a_TempChannelName[256] = {0,};

			if(strcmp(ChannelMatching->DataType, "Master") == 0)	{
				char a_MasterTemp[13][256] = { "$AHBHADDR_", "$AHBHBURST_", "$AHBHRDATA_",
					"$AHBHSIZE_", "$AHBHTRANS_", "$AHBHWDATA_", "$AHBHPROT_", 
					"$AHBHLOCK_", "$AHBHWRITE_", "$AHBHREADY_", "$AHBHRESP_", "$AHBHBUSREQ_", "$AHBHGRANT_" };

				for(int MasterIndex = 0; MasterIndex < 13; MasterIndex++)	{
					strcpy(a_TempChannelName, BindingObject->ChannelName);
					strcat(a_TempChannelName, a_MasterTemp[MasterIndex]);

					ChannelObject *p_ChannelObject = NULL;
					p_ChannelObject = p_ChannelMap->FindChannel(a_TempChannelName);

					sc_interface *p_SCinterface = NULL;
					p_SCinterface = p_ChannelObject->p_SCinterface;

					sc_port_base *p_SCportbase = NULL;
					std::vector<sc_port_base*>::iterator FirstPort = p_PortList->begin(); 
					std::vector<sc_port_base*>::iterator LastPort = p_PortList->end(); 
					std::vector<sc_port_base*>::iterator IndexOfPort = FirstPort;

					char a_TempPortName[256] = {0,};

					strcpy(a_TempPortName, a_MasterTemp[MasterIndex]);
					strcat(a_TempPortName, BindingObject->ModulePortName);

					for(IndexOfPort = FirstPort; IndexOfPort != LastPort; ++IndexOfPort){   
						p_SCportbase = (*IndexOfPort);
						if(strcmp(p_SCportbase->get_port_name(), a_TempPortName) == 0){
							p_SCportbase->BDbind(*p_SCinterface);
						}
					}				
				}
			}
			else if(strcmp(ChannelMatching->DataType, "Slave") == 0)	{
				char a_SlaveTemp[13][256] = { "$AHBHADDR_", "$AHBHBURST_", "$AHBHRDATA_",
																			"$AHBHPROT_", "$AHBHTRANS_", "$AHBHWDATA_", 
																			"$AHBHSIZE_", "$AHBHLOCK_", "$AHBHWRITE_", 
																			"$AHBHREADY_", "$AHBHSEL_", "$AHBHREADYOUT_", "$AHBHRESP_" };

				for(int SlaveIndex = 0; SlaveIndex < 13; SlaveIndex++)	{
					strcpy(a_TempChannelName, BindingObject->ChannelName);
					strcat(a_TempChannelName, a_SlaveTemp[SlaveIndex]);

					ChannelObject *p_ChannelObject = NULL;
					p_ChannelObject = p_ChannelMap->FindChannel(a_TempChannelName);

					sc_interface *p_SCinterface = NULL;
					p_SCinterface = p_ChannelObject->p_SCinterface;

					sc_port_base *p_SCportbase = NULL;
					std::vector<sc_port_base*>::iterator FirstPort = p_PortList->begin(); 
					std::vector<sc_port_base*>::iterator LastPort = p_PortList->end(); 
					std::vector<sc_port_base*>::iterator IndexOfPort = FirstPort;

					char a_TempPortName[256] = {0,};

					strcpy(a_TempPortName, a_SlaveTemp[SlaveIndex]);
					strcat(a_TempPortName, BindingObject->ModulePortName);

					for(IndexOfPort = FirstPort; IndexOfPort != LastPort; ++IndexOfPort){   
						p_SCportbase = (*IndexOfPort);
						if(strcmp(p_SCportbase->get_port_name(), a_TempPortName) == 0){
							p_SCportbase->BDbind(*p_SCinterface);
						}
					}				
				}
			}
			else
				return;
		}
		else if(strcmp(ChannelMatching->ChannelType, "AHBLITE") == 0)	{
			char a_TempChannelName[256] = {0,};

			if(strcmp(ChannelMatching->DataType, "Master") == 0)	{
				char a_MasterTemp[11][256] = { "$HADDR_", "$HBURST_", "$HRDATA_",
					"$HSIZE_", "$HTRANS_", "$HWDATA_", "$HPROT_", 
					"$HLOCK_", "$HWRITE_", "$HREADY_", "$HRESP_" };

				for(int MasterIndex = 0; MasterIndex < 11; MasterIndex++)	{
					strcpy(a_TempChannelName, BindingObject->ChannelName);
					strcat(a_TempChannelName, a_MasterTemp[MasterIndex]);

					ChannelObject *p_ChannelObject = NULL;
					p_ChannelObject = p_ChannelMap->FindChannel(a_TempChannelName);

					sc_interface *p_SCinterface = NULL;
					p_SCinterface = p_ChannelObject->p_SCinterface;

					sc_port_base *p_SCportbase = NULL;
					std::vector<sc_port_base*>::iterator FirstPort = p_PortList->begin(); 
					std::vector<sc_port_base*>::iterator LastPort = p_PortList->end(); 
					std::vector<sc_port_base*>::iterator IndexOfPort = FirstPort;

					char a_TempPortName[256] = {0,};

					strcpy(a_TempPortName, a_MasterTemp[MasterIndex]);
					strcat(a_TempPortName, BindingObject->ModulePortName);

					for(IndexOfPort = FirstPort; IndexOfPort != LastPort; ++IndexOfPort){   
						p_SCportbase = (*IndexOfPort);
						if(strcmp(p_SCportbase->get_port_name(), a_TempPortName) == 0){
							p_SCportbase->BDbind(*p_SCinterface);
						}
					}				
				}
			}
			else if(strcmp(ChannelMatching->DataType, "Slave") == 0)	{
				char a_SlaveTemp[13][256] = { "$HADDR_", "$HBURST_", "$HRDATA_",
																			"$HPROT_", "$HTRANS_", "$HWDATA_", 
																			"$HSIZE_", "$HLOCK_", "$HWRITE_", 
																			"$HREADY_", "$HSEL_", "$HREADYOUT_", "$HRESP_" };

				for(int SlaveIndex = 0; SlaveIndex < 13; SlaveIndex++)	{
					strcpy(a_TempChannelName, BindingObject->ChannelName);
					strcat(a_TempChannelName, a_SlaveTemp[SlaveIndex]);

					ChannelObject *p_ChannelObject = NULL;
					p_ChannelObject = p_ChannelMap->FindChannel(a_TempChannelName);

					sc_interface *p_SCinterface = NULL;
					p_SCinterface = p_ChannelObject->p_SCinterface;

					sc_port_base *p_SCportbase = NULL;
					std::vector<sc_port_base*>::iterator FirstPort = p_PortList->begin(); 
					std::vector<sc_port_base*>::iterator LastPort = p_PortList->end(); 
					std::vector<sc_port_base*>::iterator IndexOfPort = FirstPort;

					char a_TempPortName[256] = {0,};

					strcpy(a_TempPortName, a_SlaveTemp[SlaveIndex]);
					strcat(a_TempPortName, BindingObject->ModulePortName);

					for(IndexOfPort = FirstPort; IndexOfPort != LastPort; ++IndexOfPort){   
						p_SCportbase = (*IndexOfPort);
						if(strcmp(p_SCportbase->get_port_name(), a_TempPortName) == 0){
							p_SCportbase->BDbind(*p_SCinterface);
						}
					}				
				}
			}
			else
				return;
		}
		else	{
			// find channel
			ChannelObject *p_ChannelObject = NULL;
			p_ChannelObject = p_ChannelMap->FindChannel(BindingObject->ChannelName);

			sc_interface *p_SCinterface = NULL;
			p_SCinterface = p_ChannelObject->p_SCinterface;

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
		p_ModuleListManager = ModuleListManager::GetInstance();
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
