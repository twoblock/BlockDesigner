//-----------------------------------------------------------------------------
// Design								: test command setting 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: test.cpp
// Date	       					: 20.05/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 20.05-2016 TwoBlockTechinologies Co.
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
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "8");
			strcpy(st_GUICommand.Argu5, "hello Harold Ko!");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "5");
			strcpy(st_GUICommand.Argu5, "FFFF");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "2");
			strcpy(st_GUICommand.Argu5, "0xFFFFFFFF");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "3");
			strcpy(st_GUICommand.Argu5, "0xFFFFFFFFFFFFFFFF");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "4");
			strcpy(st_GUICommand.Argu5, "true");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "8");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "5");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));
			
			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "2");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "3");
			CommandQueue::PushCommand( st_GUICommand );


			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "4");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "4");
			strcpy(st_GUICommand.Argu5, "false");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "7");
			strcpy(st_GUICommand.Argu5, "2016.012219");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "4");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "reg");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "7");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "8");
			strcpy(st_GUICommand.Argu5, "hello Harold Ko!");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "5");
			strcpy(st_GUICommand.Argu5, "0xFFFFFFFF");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "2");
			strcpy(st_GUICommand.Argu5, "-2147483640");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "3");
			strcpy(st_GUICommand.Argu5, "-9223372036854775800");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "4");
			strcpy(st_GUICommand.Argu5, "true");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "8");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "5");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));
			
			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "2");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "3");
			CommandQueue::PushCommand( st_GUICommand );


			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "4");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "4");
			strcpy(st_GUICommand.Argu5, "false");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 0;
			st_GUICommand.Command		= 2;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "write");
			strcpy(st_GUICommand.Argu4, "7");
			strcpy(st_GUICommand.Argu5, "2016.012516");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "4");
			CommandQueue::PushCommand( st_GUICommand );

			usleep(SECOND_UNIT(0.005));

			st_GUICommand.Operation = 1;
			st_GUICommand.Command		= 1;
			strcpy(st_GUICommand.Argu1, "BD_CONSOLE");
			strcpy(st_GUICommand.Argu2, "par");
			strcpy(st_GUICommand.Argu3, "read");
			strcpy(st_GUICommand.Argu4, "7");
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
