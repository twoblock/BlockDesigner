//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface Manager 
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDIManager.cpp
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provides debugging interface contol API
// ----------------------------------------------------------------------------

#include "BDDIManager.h"
#include "CallBackManager.h"
#include "systemc.h"
#include "BD_core/SimulationAPI/BDDI.h"

//#define NDEBUG
// for debugging
#include <assert.h>	

// for systemc kernel api
using namespace sc_core;

namespace BDapi
{	
	// declare static variable for linker 
	BDDIManager* BDDIManager::_BDDIManager = NULL;
	// initialize mutex 
	pthread_mutex_t BDDIManager::BDDIManagerInstanceMutex = PTHREAD_MUTEX_INITIALIZER;  

	/*
	 * function    	: PutOperationControl
	 * design	      : Transfer Debugging Information by Using BDDIManager
	 * caller		    : CommandHandler::SetManagerForPutOperation
	 */
	void BDDIManager::PutOperationControl(GUI_COMMAND Command)
	{
		sc_object *p_Object = sc_find_object(Command.Argu1);
		sc_module *p_Module = static_cast<sc_module*>(p_Object);

		if(strcmp(Command.Argu2, "par") == 0)	{
			if(strcmp(Command.Argu3, "write") == 0)	{
				unsigned int dw_Index = (unsigned int)strtoul(Command.Argu4, NULL, 10);
				p_Module->GetBDDI()->BDDISetParameterValues(dw_Index, Command.Argu5);
			}
			else	{
				// Invalid Command : Breakpoint of parameter is not supported.
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "reg") == 0)	{
			if(strcmp(Command.Argu3, "write") == 0)	{
				unsigned int dw_Index = (unsigned int)strtoul(Command.Argu4, NULL, 10);
				p_Module->GetBDDI()->BDDISetRegisterValues(dw_Index, Command.Argu5);
			}
			else	{
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "mem") == 0)	{
			if(strcmp(Command.Argu3, "write") == 0)	{
					unsigned int dw_Address = (unsigned int)strtoul(Command.Argu4, NULL, 16);
					unsigned int dw_Value = (unsigned int)strtoul(Command.Argu5, NULL, 16);
					p_Module->GetBDDI()->BDDISetMemoryAddressValue(dw_Address, dw_Value);
			}
		}
		else if(strcmp(Command.Argu2, "assem") == 0)	{

		}
		else	{
			// Invalid Command : This command does not exist.
			assert(0);
		}
	}

	/*
	 * function    	: GetOperationControl
	 * design	      : Receive Debugging Information by Using BDDIManager
	 * caller		    : CommandHandler::SetManagerForGetOperation
	 */
	void BDDIManager::GetOperationControl(GUI_COMMAND Command)
	{
		sc_object *p_Object = sc_find_object(Command.Argu1);
		sc_module *p_Module = static_cast<sc_module*>(p_Object);	

		if(strcmp(Command.Argu2, "par") == 0)	{
			if(strcmp(Command.Argu3, "read") == 0)	{
				unsigned int dw_Index = (unsigned int)strtoul(Command.Argu4, NULL, 10);
				p_Module->GetBDDI()->BDDIGetParameterValues(dw_Index, Command.Argu5);

				//printf("\nget parameter value : %s\n", Command.Argu5);
			}
			else	{
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "reg") == 0)	{
			if(strcmp(Command.Argu3, "read") == 0)	{
				unsigned int dw_Index = (unsigned int)strtoul(Command.Argu4, NULL, 10);
				p_Module->GetBDDI()->BDDIGetRegisterValues(dw_Index, Command.Argu5);

				//printf("\nget register value : %s\n", Command.Argu5);
			}
			else	{
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "mem") == 0)	{
			if(strcmp(Command.Argu3, "read") ==0)	{
				unsigned int dw_Address = (unsigned int)strtoul(Command.Argu4, NULL, 16);

				MemoryViewValue = "";

				cout << MemoryViewValue << endl;

				p_Module->GetBDDI()->BDDIGetMemoryView(dw_Address, MemoryViewValue);

				p_CallBackManager->SendBackJson(MemoryViewValue, "MemoryViewCallBack");
			}
		}
		else if(strcmp(Command.Argu2, "assem") == 0)	{

		}
		else	{
			// Invalid Command : This command does not exist.
			assert(0);
		}
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	BDDIManager* BDDIManager::GetInstance()
	{
		// lock
		pthread_mutex_lock(&BDDIManagerInstanceMutex); 

		if( _BDDIManager == NULL ){
			_BDDIManager = new BDDIManager();
		}
		// unlock
		pthread_mutex_unlock(&BDDIManagerInstanceMutex);

		return _BDDIManager;
	}

	/*
	 * function 	: DeleteInstance 
	 * design	    : Delete BDDIManager instance 
	 */
	void BDDIManager::DeleteInstance()
	{	
		delete _BDDIManager;
		_BDDIManager = NULL;
	}


	/*
	 * function 	: BDDIManager 
	 * design	    : Constructor 
	 */
	BDDIManager::BDDIManager()
	{
		p_CallBackManager = CallBackManager::GetInstance();
		MemoryViewValue = "";
	}

	/*
	 * function 	: ~BDDIManager 
	 * design	    : Destructor 
	 */
	BDDIManager::~BDDIManager()
	{
	}
}
