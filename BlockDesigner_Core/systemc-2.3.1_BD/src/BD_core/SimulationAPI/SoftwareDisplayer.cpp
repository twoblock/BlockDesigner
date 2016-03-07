//-----------------------------------------------------------------------------
// Design								: Software Displayer 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareDisplayer.h
// Date	       					: 2016/3/7
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: this class help display assembly code 
// ----------------------------------------------------------------------------

#include "SoftwareDisplayer.h"

namespace BDapi
{
	/*
	 * function    	: DisplayAssemblyCode 
	 * design	      : display assembly code based on pc 
	 * param	      : PC - program counter 
	 */
	void SoftwareDisplayer::DisplayAssemblyCode(unsigned int PC)
	{
		unsigned int dw_PC = 0;

		for(dw_PC = (PC-10); dw_PC < (PC+10); dw_PC+=2){
			AssemblyCodeFinder = AssemblyCode.find(dw_PC);
			if(AssemblyCodeFinder != AssemblyCode.end()){
				if(dw_PC == PC){
					printf("\033[31m%x : %s \n\033[0m", dw_PC, AssemblyCodeFinder->second.c_str());
				}
				else{
					printf("%x : %s \n", dw_PC, AssemblyCodeFinder->second.c_str());
				}	
			}
		}
	}

 	/*
	 * function    	: StoreAssemblyCode
	 * design	      : store assembly code to AssemblyCode map
	 * param	      : PC - program counter 
	 */
	void SoftwareDisplayer::StoreAssemblyCode(char *SoftwarePath)
	{
		FILE* Command = NULL;
		char a_Command[1024] = {0,};

		char a_Buffer[256] = {0,};
		char a_AssemblyCode[256] = {0,};
		unsigned int dw_HexValue = 0;

		// get assembly code from elf file( SoftwarePath )
		sprintf(a_Command, "arm-linux-gnueabi-objdump -d %s", SoftwarePath);
		Command = popen(a_Command , "r");

		// exception handling 
		if(Command == NULL){
			perror("fail to execute popen function in SoftwareDisplayer");
			return;
		}
		else{
			while(fgets(a_Buffer, 256, Command)){
				if(a_Buffer[0] == 'D') break;
			}

			while(fgets(a_Buffer, 256, Command)){
				GetAssemblyCodeFromBuffer(a_Buffer, a_AssemblyCode);
				if(a_AssemblyCode[0] == 0) continue;
				else{
					dw_HexValue = strtoul(a_Buffer, NULL, 16);
					AssemblyCode[dw_HexValue] = a_AssemblyCode;
				}	
				memset(a_AssemblyCode, 0, sizeof(a_AssemblyCode));
				memset(a_Buffer, 0, sizeof(a_Buffer));
			}
			fclose(Command);
		}
	}

	/*
	 * function    	: GetAssemblyCodeFromBuffer 
	 * design	      : check if buffer is assembly code or not
   *                if - it is assembly code, parse it from buffer 
										else - return with not storing AssemblyCode
	 * param	      : PC - program counter 
	 */
	void SoftwareDisplayer::GetAssemblyCodeFromBuffer(char *Buffer, char *AssemblyCode)
	{
		// Initialize AssemblyCode
		AssemblyCode[0] = 0;

		int ColonIndex = 0;
		int SemicolonIndex = 0;
		int AssemblyCodeIndex = 0;

		bool Assem = false;

		// find colon
		for(ColonIndex = 0; ColonIndex < 256; ColonIndex++){
			if(Buffer[ColonIndex] == ':') break;
		}
		if(ColonIndex == 256) return;
		else ColonIndex++; 

		// find semicolon
		for(SemicolonIndex = ColonIndex; SemicolonIndex < 256; SemicolonIndex++){
			// find any character
			if(Buffer[SemicolonIndex] != '\n' && Buffer[SemicolonIndex] != ' ') 
				Assem = true;
			if(Buffer[SemicolonIndex] == '\n') break;
			if(Buffer[SemicolonIndex] == ';') break;
		}
	
		// check if this buffer is assembly code
		if(SemicolonIndex == 256 || Assem == false){
			return;
		}

		// assembly code
		for(; ColonIndex < SemicolonIndex; ColonIndex++){
			AssemblyCode[AssemblyCodeIndex] = Buffer[ColonIndex];
			AssemblyCodeIndex++;
		}
		AssemblyCode[AssemblyCodeIndex] = 0;
	}


	/*
	 * function 	: SoftwareDisplayer 
	 * design	    : Constructor 
	 */
	SoftwareDisplayer::SoftwareDisplayer()
	{
	}

	/*
	 * function 	: ~SoftwareDisplayer
	 * design	    : Destructor
	 */
	SoftwareDisplayer::~SoftwareDisplayer()
	{
	}
}
