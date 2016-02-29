//-----------------------------------------------------------------------------
// Design								: 
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: SignalTraceManager.cpp
// Date	       					: 2016/2/11
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: 
// ----------------------------------------------------------------------------

#include "SignalTraceManager.h"
#include "../SimulationAPI/ChannelMap.h"

namespace BDapi
{	
	// declare static variable for linker 
	SignalTraceManager* SignalTraceManager::_SignalTraceManager = NULL;
	// initialize mutex 
	pthread_mutex_t SignalTraceManager::SignalTraceManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      :
	 * caller		    : CommandHandler::SetManagerForPutOperation
	 */
	void SignalTraceManager::PutOperationControl(GUI_COMMAND Command)
	{
		if(strcmp(Command.Argu1, ENABLE_TRACE) == 0)	AddTrace(Command.Argu2, Command.Argu3);
		else if(strcmp(Command.Argu1, DISABLE_TRACE) == 0)
		{
		}
		else
		{
		}
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : 
	 * caller		    : CommandHandler::SetManagerForGetOperation
	 */
	void SignalTraceManager::GetOperationControl(GUI_COMMAND Command)
	{

	}

	void SignalTraceManager::AddTrace(const char *ChannelName, const char *ChannelType)
	{
		ChannelObject *pst_ChannelObject = NULL;

		if(strcmp(ChannelType, "AHB") == 0)	{
			char a_UINTTemp[7][256] = { "$HADDR_", "$HBURST_", "$HRDATA_",
															 		"$HSIZE_", "$HTRANS_", "$HWDATA_", "$HPROT_" };

			char a_BOOLTemp[4][256] = { "$HLOCK_", "$HWRITE_", "$HREADY_", "$HRESP_" };

			char a_TempChannelName[256] = {0,};

			for(int UINTIndex = 0; UINTIndex < 7; UINTIndex++)	{
				strcpy(a_TempChannelName, ChannelName);
				strcat(a_TempChannelName, a_UINTTemp[UINTIndex]);

				pst_ChannelObject = p_ChannelMap->FindChannel(a_TempChannelName);

				sc_trace(tf, *(dynamic_cast<sc_signal<unsigned int>*>(pst_ChannelObject->p_SCinterface)), a_TempChannelName);
			}

			for(int BOOLIndex = 0; BOOLIndex < 4; BOOLIndex++)	{
				strcpy(a_TempChannelName, ChannelName);
				strcat(a_TempChannelName, a_BOOLTemp[BOOLIndex]);

				pst_ChannelObject = p_ChannelMap->FindChannel(a_TempChannelName);

				sc_trace(tf, *(dynamic_cast<sc_signal<bool>*>(pst_ChannelObject->p_SCinterface)), a_TempChannelName);
			}

			if(strcmp(pst_ChannelObject->DataType, "Slave") == 0)	{
				char a_RestTemp[2][256] = { "$HSEL_", "$HREADYOUT_" };

				for(int RestIndex = 0; RestIndex < 2; RestIndex++)	{
					strcpy(a_TempChannelName, ChannelName);
					strcat(a_TempChannelName, a_RestTemp[RestIndex]);

					pst_ChannelObject = p_ChannelMap->FindChannel(a_TempChannelName);

					sc_trace(tf, *(dynamic_cast<sc_signal<bool>*>(pst_ChannelObject->p_SCinterface)), a_TempChannelName);
				}
			}
		}
		else	{
			pst_ChannelObject = p_ChannelMap->FindChannel(ChannelName);

			if(strcmp(pst_ChannelObject->ChannelType, "sc_clock") == 0)	{
				sc_trace(tf, *(dynamic_cast<sc_clock*>(pst_ChannelObject->p_SCinterface)), ChannelName);
			}
			else if(strcmp(pst_ChannelObject->ChannelType, "sc_signal") == 0)	{
				if(strcmp(pst_ChannelObject->DataType, "bool") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<bool>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "UINT32") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<unsigned int>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "unsigned int") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<unsigned int>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "unsigned char") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<unsigned char>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "unsigned short") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<unsigned short>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "unsigned long long") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<unsigned long long>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "int") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<int>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "char") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<char>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "short") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<short>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "long long") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<long long>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "float") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<float>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
				else if(strcmp(pst_ChannelObject->DataType, "double") == 0)	{
					sc_trace(tf, *(dynamic_cast<sc_signal<double>*>(pst_ChannelObject->p_SCinterface)), ChannelName);
				}
			}
		}
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	SignalTraceManager* SignalTraceManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&SignalTraceManagerInstanceMutex); 

		if( _SignalTraceManager == NULL ){
			_SignalTraceManager = new SignalTraceManager();
		}
		// unlock
		pthread_mutex_unlock(&SignalTraceManagerInstanceMutex);

		return _SignalTraceManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete SignalTraceManager instance 
	 */
	void SignalTraceManager::DeleteInstance()
	{	
		delete _SignalTraceManager;
		_SignalTraceManager = NULL;
	}

	/*
	 * function 	: SignalTraceManager 
	 * design	    : Constructor 
	 */
	SignalTraceManager::SignalTraceManager()
	{
		p_ChannelMap = ChannelMap::GetInstance();
		tf = sc_create_vcd_trace_file("wave");
	}

	/*
	 * function 	: ~SignalTraceManager 
	 * design	    : Destructor 
	 */
	SignalTraceManager::~SignalTraceManager()
	{
		sc_close_vcd_trace_file(tf);
	}
}
