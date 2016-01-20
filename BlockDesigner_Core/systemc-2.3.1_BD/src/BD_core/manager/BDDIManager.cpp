#include "BDDIManager.h"
#include "systemc.h"

//#define NDEBUG
// for debugging
#include <assert.h>	

// for systemc kernel api
using namespace sc_core;

namespace BDapi
{	
	/*
	 * function    	: PutOperationControl
	 * design	      : 
	 * caller		    : CommandHandler::SetManagerForPutOperation
	 */
	void BDDIManager::PutOperationControl(GUI_COMMAND Command)
	{
		sc_object *p_Object = sc_find_object(Command.Argu1);
		sc_module *p_Module = static_cast<sc_module*>(p_Object);

		if(strcmp(Command.Argu2, "param") == 0)	{
			if(strcmp(Command.Argu3, "write") == 0)	{
				int dw_Index = atoi(Command.Argu4);
				
			}
			else	{
				// Invalid Command : Breakpoint of parameter is not supported.
				assert(0);
			}
		}
		else if(strcmp(Command.Argu2, "reg") == 0)	{

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
	 * design	      : 
	 * caller		    : CommandHandler::SetManagerForGetOperation
	 */
	void BDDIManager::GetOperationControl(GUI_COMMAND Command)
	{
		sc_object *p_Object = sc_find_object(Command.Argu1);
		sc_module *p_Module = static_cast<sc_module*>(p_Object);	

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
	 * design	    : delete execution manager instance
	 */
	BDDIManager::~BDDIManager()
	{
		delete _BDDIManager;
	}
}
