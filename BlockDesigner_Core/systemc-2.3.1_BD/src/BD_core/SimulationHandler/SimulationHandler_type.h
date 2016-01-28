//-----------------------------------------------------------------------------
// Design								: define srtuct enum for SimulationHandler
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SimulationHandler_type.h
// Date	       					: 2016/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: These struct, enum is used for Simulator Handler thread
// ----------------------------------------------------------------------------

#ifndef SIMULATIONHANDLER_TYPE_H
#define SIMULATIONHANDLER_TYPE_H

// Operation way
#define PUT 0 
#define GET 1

// Put Command
#define SoftwareLoad       0
#define ExecutionControl   1 
#define PutDebugInterface  2
#define PutMemoryMap       3 
#define WireTraceControl   4 
#define RegisterCallBack   5 
#define LoadModule         6 
#define ModuleConnection   7

// Get Command
#define ModuleInfo         0
#define GetDebugInterface  1 
#define GetMemoryMap       2

#define ArgumentSize        128

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	typedef struct GUI_commnad{
		int Operation;
		int Command;
		char Argu1[ArgumentSize];
		char Argu2[ArgumentSize];
		char Argu3[ArgumentSize];
		char Argu4[ArgumentSize];
		char Argu5[ArgumentSize];
	}GUI_COMMAND;
}

#endif 

