//-----------------------------------------------------------------------------
// Design								: Block Designer Execution Manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDDIManager.h
// Date	       					: 2015/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Execution contol API
// ----------------------------------------------------------------------------

#ifndef __BDDI_MANAGER_H__
#define __BDDI_MANAGER_H__

#include "TopManagerBase.h"

// for Debugging BDDI
#include <stdio.h>

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : BDDIManager
	 * design	      : Control BDDI Function
	 * description	: interface parameter, register,
	 *								memory and assembly code by controlling BDDI function
	 */
	class BDDIManager : public TopManagerBase
	{
		public:
			void PutOperationControl(GUI_COMMAND Command);
			void GetOperationControl(GUI_COMMAND Command);
			static BDDIManager* GetInstance();

			~BDDIManager();

		protected:
			BDDIManager();

		private:
			static BDDIManager *_BDDIManager;
	};
} // namespace BDapi 

#endif	// __BDDI_MANAGER_H__
