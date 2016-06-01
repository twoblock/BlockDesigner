//-----------------------------------------------------------------------------
// Design								: Simulation Core 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDSim.h
// Date	       					: 2016/1/3
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: simulate systemc kernel and conrol it  
// ----------------------------------------------------------------------------

#ifndef BDSIM_H 
#define BDSIM_H 

#include "systemc.h"
#include "../manager/ExecutionManager.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// for systemc kernel api
using namespace sc_core;

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	extern void BDStart();

	int Simulate(unsigned int SimControl);

	void Run();
	void Step();
	void Stop();
	void Close();

	void StartCallBack();
	void StopCallBack();
	void CycleCallBack(int Status);

	extern long long glw_Cycle;
} 

#endif 

