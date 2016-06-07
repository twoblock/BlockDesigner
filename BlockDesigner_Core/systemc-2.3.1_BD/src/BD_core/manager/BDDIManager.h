//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface Manager 
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDIManager.h
// Date	       					: 2016/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provides debugging interface contol API
// ----------------------------------------------------------------------------

#ifndef __BDDI_MANAGER_H__
#define __BDDI_MANAGER_H__

#include "TopManagerBase.h"
#include <pthread.h>

// for Debugging BDDI
#include <stdio.h>
#include <string>

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class CallBackManager;
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
			static void DeleteInstance();

		protected:
			BDDIManager();
			virtual ~BDDIManager();

		private:
			string MemoryViewValue;

			CallBackManager *p_CallBackManager;

		 	static BDDIManager *_BDDIManager;
			// mutex for singleton pattern 
			static pthread_mutex_t BDDIManagerInstanceMutex;   
	};
} // namespace BDapi 

#endif	// __BDDI_MANAGER_H__
