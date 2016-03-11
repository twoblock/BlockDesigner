//-----------------------------------------------------------------------------
// Design								: Software Profiler 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareProfiler.h
// Date	       					: 2016/3/8
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: provide apis to profile software flow data and display them
// ----------------------------------------------------------------------------

#ifndef __SOFTWARE_PROFILER_H__
#define __SOFTWARE_PROFILER_H__

#include "BD_core/PlatformAPI/json/json.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stack>
#include <vector>

using namespace std;

/*
 * namespace	  : BDapi 
 * design	      : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : SoftwareProfiler
	 * design	      : profile software flow by using symbol table and pc value
	 */
	class SoftwareProfiler
	{

		public:

			// symbol table
			typedef struct M_SYM_TABLE_ELEMENT {
				unsigned long Start_Addr;
				unsigned long End_Addr;
				char          Function_Name[50];
				unsigned long Call_Num;
				unsigned long Duration;
				unsigned long Self_Duration;
				unsigned long Partial_Start_Duration;
				bool          Is_it_Called_Now;
				bool          Is_Profilied;
			}m_sym_table_element;

			SoftwareProfiler( char* Elf_File_Path);
			~SoftwareProfiler( );

			// apis to analyze datas
			void PC_Analyzer( unsigned long pc );
			int Function_Search( unsigned long pc );

			// apis to display datas
			void Summary_Display();
			void Stop_And_Calculate_Duration();

			// apis to make symbol table
			unsigned int Cal_Num_Of_Table_Elements(const char* Elf_File_Path);
			int Make_Table( const char* Elf_File_Path );
			void swap( m_sym_table_element* a, m_sym_table_element* b ); 

			// apis to make symbol table
			void PushOneFunctionFlow();

			// apis fir call back
			string GetJsonOfSymbolTable();
			string GetJsonOfFunctionFlowGragh();
			string GetJsonOfProfilingTable();

			// Table 
			int Table_element_num;
			m_sym_table_element * m_Symbol_Table; 

			unsigned long Pre_pc;
			unsigned long Global_Time; 
			char * Error;

			// Summary Local Variable
			// Stack
			stack<unsigned int> Call_Stack;
			unsigned int Top_1;
			unsigned int Top_2;
			int Function_Index;

			// this time is used for function flow gragh
			unsigned long OneFunctionFlowTime; 
			int IndexOfFunctionFlow;

			// json format entities
			Json::Value Root_SymbolTable;
			Json::Value SymbolTable;
			Json::Value Symbol;

			Json::Value Root_ProfilingTable;
			Json::Value ProfilingTable;
			Json::Value FunctionPT;

			Json::Value Root_FunctionFlowGragh;
			Json::Value FunctionFlowGragh;
			Json::Value FunctionFG;
	};
}

#endif 
