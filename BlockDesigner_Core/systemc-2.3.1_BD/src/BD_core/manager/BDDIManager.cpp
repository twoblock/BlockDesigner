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
#include "systemc.h"
#include "BD_core/SimulationAPI/BDDI.h"

//#define NDEBUG
// for debugging
#include <assert.h>	

// for systemc kernel api
using namespace sc_core;

namespace BDapi
{	
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
				p_Module->bddi->BDDISetParameterValues(dw_Index, Command.Argu5);
			}
			else	{
				// Invalid Command : Breakpoint of parameter is not supported.
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "reg") == 0)	{
			if(strcmp(Command.Argu3, "write") == 0)	{
				unsigned int dw_Index = (unsigned int)strtoul(Command.Argu4, NULL, 10);
				p_Module->bddi->BDDISetRegisterValues(dw_Index, Command.Argu5);
			}
			else	{
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "mem") == 0)	{
		
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
				p_Module->bddi->BDDIGetParameterValues(dw_Index, Command.Argu5);

				printf("\nget parameter value : %s\n", Command.Argu5);
			}
			else	{
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "reg") == 0)	{
			if(strcmp(Command.Argu3, "read") == 0)	{
				unsigned int dw_Index = (unsigned int)strtoul(Command.Argu4, NULL, 10);
				p_Module->bddi->BDDIGetRegisterValues(dw_Index, Command.Argu5);

				printf("\nget register value : %s\n", Command.Argu5);
			}
			else	{
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "mem") == 0)	{
		
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
		if( _BDDIManager == NULL ){
			_BDDIManager = new BDDIManager();
		}

		return _BDDIManager;
	}

	/*
	 * function 	: Constructor
	 * design	    : 
	 */
	BDDIManager::BDDIManager()
	{
	}

	/*
	 * function 	: Destructor
	 * design	    : delete BDDI manager instance
	 */
	BDDIManager::~BDDIManager()
	{
		delete _BDDIManager;
	}
}
