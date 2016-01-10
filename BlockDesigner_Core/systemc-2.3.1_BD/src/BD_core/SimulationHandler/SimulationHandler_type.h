//-----------------------------------------------------------------------------
// Design								: define srtuct enum for SimulationHandler
// Autor								: Bryan.Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SimulationHandler_type.h
// Date	       					: 2015/1/4
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: These struct, enum is used for Simulator Handler thread
// ----------------------------------------------------------------------------

#ifndef SIMULATIONHANDLER_TYPE_H
#define SIMULATIONHANDLER_TYPE_H

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */

namespace BDapi
{
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

// Get Command
#define ModuleInfo         0
#define GetDebugInterface  1 
#define GetMemoryMap       2

#define ArumentSize        128

	typedef struct GUI_commnad{
		int Operation;
		int Command;
		char Argu1[ArumentSize];
		char Argu2[ArumentSize];
		char Argu3[ArumentSize];
		char Argu4[ArumentSize];
		char Argu5[ArumentSize];
	}GUI_COMMAND;

} // namespace BDapi 

#endif 

