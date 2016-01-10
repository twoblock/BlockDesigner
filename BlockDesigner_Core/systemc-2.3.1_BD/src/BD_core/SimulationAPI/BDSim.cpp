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

#include "BDSim.h"	

namespace BDapi
{

#define	 SECOND_UNIT(X)		((X)*1000000)
void BD_start()
	{

		FILE *fp;
		bool first_open_gtk = false;

		int state;
		int a = 0;
		int _exec_cycles = 0;
		int status = 0;

		pid_t pid;

		signal(SIGUSR1, sig_handler);
		signal(SIGUSR2, sig_handler);
		signal(SIGCONT, sig_handler);
		signal(SIGINT , sig_handler);
		signal(SIGTERM, sig_handler);

		pid = fork();

		if(pid == -1)	{	// Error Phase
			printf("\n\033[31m Error : Can not fork\033[0m\n");
			exit(0);
		}

		if(pid == 0)	{	// Simulation Phase (Child Process)
			fp = popen("shmidcat wave.vcd | gtkwave -v -I wave.gtkw", "r");				// Activate GTKWAVE Interactive Mode.
			if(fp == NULL)		printf("\n\033[31m Error : Can not open GTKWAVE\033[0m\n");

			while(1)
			{
				if( Control_Flag == PAUSE )
				{
					Control_Flag = NOTHING;
					// nothing
				}
				else if( Control_Flag == STEP )
				{
					printf(" \033[34mStep Number (Input) : \033[0m");
					scanf("%d", &_exec_cycles);
					printf("\n");
					_exec_cycles *= 10;
					Control_Flag = NOTHING;


					sc_start( _exec_cycles, SC_NS );
					if( sc_is_running() == false )	{
						sc_stop();

						if(first_open_gtk)	{
							fp = popen("gtkwave wave.vcd wave.gtkw", "r");
							if(fp == NULL)		printf("\n\033[31m Error : Can not open GTKWAVE\033[0m\n");

							first_open_gtk = false;	
						}

						break;
					}


					kill(getppid(), SIGUSR1);
					if(first_open_gtk)	{						
						fp = popen("gtkwave wave.vcd wave.gtkw", "r");
						if(fp == NULL)		printf("\n\033[31m Error : Can not open GTKWAVE\033[0m\n");

						first_open_gtk = false;
					}				
					// Input Cycle
					// number
					// Run and pause	
				}
				else if( Control_Flag == STOP )
				{
					sc_stop(); 
					break;
				}
				else if( Control_Flag == RUN )
				{
					sc_start( 10, SC_NS);

					if( sc_is_running() == false )	{
						sc_stop();

						if(first_open_gtk)	{
							fp = popen("gtkwave wave.vcd wave.gtkw", "r");
							if(fp == NULL)		printf("\n\033[31m Error : Can not open GTKWAVE\033[0m\n");

							first_open_gtk = false;
						}

						break;
					}
				}
			}


			if(Control_Flag == RUN || Control_Flag == STEP)	{
				printf("\n\n \033[34m----------------------------------------------------- End of Simulation -----------------------------------------------------\033[0m \n");
				printf(" \033[34m-------------------------------------- Please Enter 4 for Block Designer Termination ----------------------------------------\033[0m \n\n");
			}
		}
		else {		// Waiting Input Phase (Parent Process)
			printf("\n\n \033[34mBlock Desginer Simulation Environment Ver.1\n");
			printf(" Copyright (c) 2015 by TwoBlock,\n");
			printf(" ALL RIGHTS RESERVED\033[0m \n");

			while(1)
			{
				usleep(SECOND_UNIT(0.5));			// Required to prevent the print output overlap.

				if(Control_Flag != STEP)	{
					printf("\n\n \033[34mOPTION MENU \n");
					printf(" 1. Step  \n");
					printf(" 2. Run   \n");
					printf(" 3. Pause \n");
					printf(" 4. Stop  \n\n");
					printf(" 5. Breakpoint enable/disable \n\n");
					printf(" Input Option (Must Input Number) : \033[0m");
					scanf("%d", &a);

					if( !(a <= 4 && a >= 1) )	printf("\n\033[31m Invalid Option Number, Please check the option again. \033[0m");
					printf("\n");

					if(a == 1)	{		// Step.
						kill(pid, SIGUSR2);
						a = 0;
						Control_Flag = STEP; 
					}
					if(a == 2)	{		// Run.
						kill(pid, SIGCONT);
						a = 0;
					}
					if(a == 3)	{		// Pause.
						kill(pid, SIGTERM);
						a = 0;
					}
					if(a == 4)	{		// Stop.
						kill(pid, SIGINT);
						break;
					}
				}
			}
			waitpid(pid, &status, 0);

			printf("\n\n \033[34mClosing Block Designer");

			for(int wait_closed=0; wait_closed<10; wait_closed++)	{
				usleep(SECOND_UNIT(0.4));
				printf(".");
				fflush(stdout);
			}	

			printf("\n Block Designer Shut Down! \033[0m\n\n");
		}

	}

}
