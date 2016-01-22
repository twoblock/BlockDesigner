//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDIBase.h
// Date	       					: 2016/1/18
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This interface provide parameter, register, memory,
//								breakpoint, disassembly API	
// ----------------------------------------------------------------------------

#ifndef __BDDIBASE_H__
#define __BDDIBASE_H__

#include "BDDI.h"

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : BDDIBase
	 * design	      : Provide Block Designer Debugging Interface Function
	 * description	: this class provides to access parameter, register
	 *								memory, assembly code by using BDDI function
	 */
	class BDDIBase : public BDDI
	{
		public:

			/*
			 * function			: BDDIGetRegisterValues
			 * design				: Get Register Value from Each Module 
			 * description	: this function bring the current value of register value in each module
			 *								to transfer the value to user
			 * param				: RegIndex		- this parameter is	the real number of the register group
			 *								OutValue		-	this parameter is the current value of register value in each module
			 * return				: this function return status of success or failure
			 * caller				: BDDIManager::GetOperationControl
			 */
			virtual BDDIReturn BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
			{
				return BDDIStatusCmdNotSupported;
			}

			/*
			 * function			: BDDISetRegisterValues
			 * design				: Set Register Value to Each Module 
			 * description	: this function set the value which is set by user to register in module
			 * param				: RegIndex		- this parameter is	the real number of the register group
			 *								SetValue		-	this parameter is set by user 
			 * return				: this function return status of success or failure
			 * caller				: BDDIManager::PutOperationControl
			 */
			virtual BDDIReturn BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
			{
				return BDDIStatusCmdNotSupported;
			}
	};

}

#endif	// __BDDIBASE_H__
