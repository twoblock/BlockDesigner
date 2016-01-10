//-----------------------------------------------------------------------------
// Design								: Block Designer Execution Manager 
// Autor								: Bryan.Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ExecutionManager.h
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This class provide Execution contol API
// ----------------------------------------------------------------------------

#include "test.h"	

namespace BDapi{

#define	 SECOND_UNIT(X)		((X)*1000000)
#define	 ArraySize 256 

	std::queue<GUI_COMMAND> CommandQueue::_CommandQueue;

	void GUIThread(){
    
		GUI_COMMAND GUI_commnad;

		while(1){
			usleep(SECOND_UNIT(0.5));			// Required to prevent the print output overlap.

			// Get Command
			printf("\n\n \033[34mOPTION MENU \n");
			printf(" 0. Put \n");
			printf("  1. ExecutionControl \n");
			printf("   RUN \n");
			printf("   STOP \n");
			printf("   STEP with Cycle  \n\n");
			printf(" Input Command : \033[0m");

			//scanf("Input %d \n", Operation);
			//scanf("Input %d \n", Command);
			//scanf("Input %s\n", Argu1);
			//scanf("Input %s\n", Argu2);

			//GUI_commnad.Operation = Operation;
			//GUI_commnad.Command   = Command;
			//strcpy( GUI_commnad.Argu1, Argu1 );
			//strcpy( GUI_commnad.Argu2, Argu2);
			//strcpy( GUI_commnad.Argu3, strtok(NULL," ") );
			//strcpy( GUI_commnad.Argu4, strtok(NULL," ") );
			//strcpy( GUI_commnad.Argu5, strtok(NULL," ") );

			GUI_commnad.Operation = 0;
			GUI_commnad.Command   = 1;
			strcpy( GUI_commnad.Argu1, "STEP");
			strcpy( GUI_commnad.Argu2, "1000");
			CommandQueue::PushCommand( GUI_commnad );
			usleep(SECOND_UNIT(2));		

			GUI_commnad.Operation = 0;
			GUI_commnad.Command   = 1;
			strcpy( GUI_commnad.Argu1, "STEP");
			strcpy( GUI_commnad.Argu2, "1000");
			CommandQueue::PushCommand( GUI_commnad );
			usleep(SECOND_UNIT(2));		


			GUI_commnad.Operation = 0;
			GUI_commnad.Command   = 1;
			strcpy( GUI_commnad.Argu1, "STEP");
			strcpy( GUI_commnad.Argu2, "1000");
			CommandQueue::PushCommand( GUI_commnad );
			usleep(SECOND_UNIT(2));		



			GUI_commnad.Operation = 0;
			GUI_commnad.Command   = 1;
			strcpy( GUI_commnad.Argu1, "STEP");
			strcpy( GUI_commnad.Argu2, "1000");
			CommandQueue::PushCommand( GUI_commnad );
			usleep(SECOND_UNIT(2));		



			GUI_commnad.Operation = 0;
			GUI_commnad.Command   = 1;
			strcpy( GUI_commnad.Argu1, "STEP");
			strcpy( GUI_commnad.Argu2, "1000");
			CommandQueue::PushCommand( GUI_commnad );
			usleep(SECOND_UNIT(2));		

			GUI_commnad.Operation = 0;
			GUI_commnad.Command   = 1;
			strcpy( GUI_commnad.Argu1, "STEP");
			strcpy( GUI_commnad.Argu2, "1000");
			CommandQueue::PushCommand( GUI_commnad );
			usleep(SECOND_UNIT(2));		

/*			GUI_commnad.Operation = 0;
			GUI_commnad.Command   = 1;
			strcpy( GUI_commnad.Argu1, "RUN");
			CommandQueue::PushCommand( GUI_commnad );
			usleep(SECOND_UNIT(0.5));		

*/



			while(1);	
		}
	}
}
