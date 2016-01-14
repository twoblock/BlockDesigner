//-----------------------------------------------------------------------------
// Design								: test command setting 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: test.cpp
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide gui test API
// ----------------------------------------------------------------------------

#include "test.h"	

#define	 SECOND_UNIT(X)		((X)*1000000)
#define	 ArraySize 256 

namespace BDapi{

	// declare static variable
	std::queue<GUI_COMMAND> CommandQueue::_CommandQueue;

	/*
	 * function   	: GUIThread 
	 * design     	: DIY for test command
	 * caller		    : StartSimulationThreads
	 */
	void GUIThread(){

		GUI_COMMAND st_GUICommand;

		while(1){

			st_GUICommand.Operation = 0;
			st_GUICommand.Command   = 1;
			strcpy( st_GUICommand.Argu1, "STEP");
			strcpy( st_GUICommand.Argu2, "1000");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(1));		

			st_GUICommand.Operation = 0;
			st_GUICommand.Command   = 1;
			strcpy( st_GUICommand.Argu1, "STEP");
			strcpy( st_GUICommand.Argu2, "1000");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(1));		

			st_GUICommand.Operation = 0;
			st_GUICommand.Command   = 1;
			strcpy( st_GUICommand.Argu1, "STEP");
			strcpy( st_GUICommand.Argu2, "1000");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(1));		

			st_GUICommand.Operation = 0;
			st_GUICommand.Command   = 1;
			strcpy( st_GUICommand.Argu1, "STEP");
			strcpy( st_GUICommand.Argu2, "1000");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(1));		

			st_GUICommand.Operation = 0;
			st_GUICommand.Command   = 1;
			strcpy( st_GUICommand.Argu1, "STEP");
			strcpy( st_GUICommand.Argu2, "1000");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(1));		

			st_GUICommand.Operation = 0;
			st_GUICommand.Command   = 1;
			strcpy( st_GUICommand.Argu1, "STEP");
			strcpy( st_GUICommand.Argu2, "1000");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(1));		

			st_GUICommand.Operation = 0;
			st_GUICommand.Command   = 1;
			strcpy( st_GUICommand.Argu1, "STEP");
			strcpy( st_GUICommand.Argu2, "1000");
			CommandQueue::PushCommand( st_GUICommand );

			// protect input command
			while(1);	
		}
	}
}
