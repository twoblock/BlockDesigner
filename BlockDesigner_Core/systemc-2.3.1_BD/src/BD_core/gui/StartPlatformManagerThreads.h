//-----------------------------------------------------------------------------
// Design								: Platform Manager InitThread 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: StartPlatformManageThreads.h
// Date	       					: 2015/1/19
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide api to create essential threads 
//								for platform manager
// ----------------------------------------------------------------------------

#ifndef __START_PLATFORM_MANAGER_THREADS_H__
#define __START_PLATFORM_MANAGER_THREADS_H__

/*
 * namespace  	: BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	void *PlatformManagerHandlerRoutine( void *arg);
	void *PlatformManagerRoutine( void *arg);
	extern void StartPlatformManagerThreads();
} 

#endif 

