//-----------------------------------------------------------------------------
// Design								: User command parser 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: test.cpp
// Date	       					: 2015/12/29
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlockTechinologies Co.
// ----------------------------------------------------------------------------
// Description	: This Thread provide user command test 
// ----------------------------------------------------------------------------

#include "test.h"	

using namespace std;

namespace BDapi{

	// declare static variable
	std::queue<GUI_COMMAND> CommandQueue::_CommandQueue;

	/*
	 * function   	: GUIThread 
	 * design     	: DIY for test command
	 * caller		    : StartSimulationThreads
	 */
	void GUIThread()
	{
		ifstream CommandFile;
		CommandFile.open("bd_command_script.sh");

		char UserCommand[SIZE] = {0,};
		ScriptReturn ScriptLine;	

		while(CommandFile.getline(UserCommand, SIZE) != NULL){		
			ScriptLine =	CheckScriptLine(UserCommand);

			if(ScriptLine == _NO_COMMAND)
				continue;
			else if(ScriptLine == _SLEEP)
				Sleep(UserCommand);
			else
				PushCommand(UserCommand);	
		}

		while(1);
	}

	/*
	 * function   	: PushCommand 
	 * design     	: Parse user command and push command
	 * param        : const char* one line of bd_command_script.sh
	 * caller		    : GUIThread 
	 */
	void PushCommand(char *p_UserCommand)
	{	
		char UserCommand[SIZE] = {0,}; 
		char *p_CommnadToken = NULL; 

		strcpy(UserCommand,p_UserCommand);

		GUI_COMMAND st_Command;
		InitializeCommand(st_Command);

		// Operation
		p_CommnadToken = strtok(UserCommand, " ");				
		if(p_CommnadToken == NULL) 
			return;
		else{
			if(strcmp(p_CommnadToken,"PUT") == 0 || p_CommnadToken[0] == '0'){
				st_Command.Operation = PUT;

				// Command 
				p_CommnadToken = strtok(NULL, " ");					
				if(p_CommnadToken == NULL) 
					return;	
				else{
					if(strcmp(p_CommnadToken,"SoftwareLoad") == 0 || p_CommnadToken[0] == '0')
						st_Command.Command = SoftwareLoad; 
					else if(strcmp(p_CommnadToken,"ExecutionControl") == 0 || p_CommnadToken[0] == '1')
						st_Command.Command = ExecutionControl; 
					else if(strcmp(p_CommnadToken,"PutDebugInterface") == 0 || p_CommnadToken[0] == '2')
						st_Command.Command = PutDebugInterface; 
					else if(strcmp(p_CommnadToken,"PutMemoryMap") == 0 || p_CommnadToken[0] == '3')
						st_Command.Command = PutMemoryMap; 
					else if(strcmp(p_CommnadToken,"WireTraceControl") == 0 || p_CommnadToken[0] == '4')
						st_Command.Command = WireTraceControl; 
					else if(strcmp(p_CommnadToken,"RegisterCallBack") == 0 || p_CommnadToken[0] == '5')
						st_Command.Command = RegisterCallBack; 
					else if(strcmp(p_CommnadToken,"LoadModule") == 0 || p_CommnadToken[0] == '6')
						st_Command.Command = LoadModule; 
					else if(strcmp(p_CommnadToken,"ModuleConnection") == 0 || p_CommnadToken[0] == '7')
						st_Command.Command = ModuleConnection; 
					else 
						return;
				}
			}
			else if(strcmp(p_CommnadToken,"GET") == 0 || p_CommnadToken[0] == '1'){
				st_Command.Operation = GET;

				// Command 
				p_CommnadToken = strtok(NULL, " ");					
				if(p_CommnadToken == NULL) 
					return;	
				else{
					if(strcmp(p_CommnadToken,"ModuleInfo") == 0 || p_CommnadToken[0] == '0')
						st_Command.Command = ModuleInfo; 
					else if(strcmp(p_CommnadToken,"GetDebugInterface") == 0 || p_CommnadToken[0] == '1')
						st_Command.Command = GetDebugInterface; 
					else if(strcmp(p_CommnadToken,"GetMemoryMap") == 0 || p_CommnadToken[0] == '2')
						st_Command.Command = GetMemoryMap; 
					else 
						return;
				}
			}
			else
				return;

			// Argument 1 
			p_CommnadToken = strtok(NULL, " ");
			if(p_CommnadToken == NULL){ 
				CommandQueue::PushCommand( st_Command );
				return;	
			}
			else
				strcpy(st_Command.Argu1, p_CommnadToken);

			// Argument 2
			p_CommnadToken = strtok(NULL, " ");
			if(p_CommnadToken == NULL){ 
				CommandQueue::PushCommand( st_Command );
				return;	
			}
			else
				strcpy(st_Command.Argu2, p_CommnadToken);

			// Argument 3
			p_CommnadToken = strtok(NULL, " ");
			if(p_CommnadToken == NULL){ 
				CommandQueue::PushCommand( st_Command );
				return;	
			}
			else
				strcpy(st_Command.Argu3, p_CommnadToken);

			// Argument 4
			p_CommnadToken = strtok(NULL, " ");
			if(p_CommnadToken == NULL){ 
				CommandQueue::PushCommand( st_Command );
				return;	
			}
			else
				strcpy(st_Command.Argu4, p_CommnadToken);

			// Argument 5
			p_CommnadToken = strtok(NULL, " ");
			if(p_CommnadToken == NULL){ 
				CommandQueue::PushCommand( st_Command );
				return;	
			}
			else
				strcpy(st_Command.Argu5, p_CommnadToken);

			CommandQueue::PushCommand( st_Command );
		}
	}

	/*
	 * function   	: Sleep 
	 * design       : sleep command 
	 */
	void Sleep(char *p_UserCommand)
	{
		char UserCommand[SIZE] = {0,}; 
		char *p_CommnadToken = NULL; 
		double time = 0; 

		GUI_COMMAND st_Command;
		strcpy(UserCommand,p_UserCommand);

		InitializeCommand(st_Command);

		// sleep 
		p_CommnadToken = strtok(UserCommand, " ");				
		if(p_CommnadToken == NULL) 
			return;

		// time 
		p_CommnadToken = strtok(NULL, " ");					
		if(p_CommnadToken == NULL) 
			return;	
		time = atof(p_CommnadToken);

		usleep(SECOND_UNIT(time));
	}

	/*
	 * function   	: InitializeCommand 
	 * design       : Initialize command struct
	 */
	void InitializeCommand(GUI_COMMAND &Command)
	{
		Command.Operation = NO_OPERATION;
		Command.Command = NO_COMMAND;
		Command.Argu1[0] = NO_ARGUMENT;
		Command.Argu2[0] = NO_ARGUMENT;
		Command.Argu3[0] = NO_ARGUMENT;
		Command.Argu4[0] = NO_ARGUMENT;
		Command.Argu5[0] = NO_ARGUMENT;
	}

	/*
	 * function   	: CheckScriptLine 
	 * design     	: check if it is command or not
	 */
	ScriptReturn CheckScriptLine(char *p_UserCommand)
	{
		//  0  : blanck
		// '#' : comment
		if(p_UserCommand[0] == 0 || p_UserCommand[0] == '#')
			return _NO_COMMAND;
		else if(p_UserCommand[0] == 's')
			return _SLEEP;
		else
			return _COMMAND;
	}
}
