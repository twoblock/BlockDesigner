#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stack>
#include <vector>

using namespace std;

class Software_Profiler
{
	
	public:

		typedef struct M_SYM_TABLE_ELEMENT {
			unsigned long Start_Addr;
			unsigned long End_Addr;
			char          Function_Name[50];
			unsigned long Call_Num;
			unsigned long Duration;
			unsigned long Self_Duration;
			unsigned long Partial_Start_Duration;
			bool          Is_it_Called_Now;
		}m_sym_table_element;

		// Table 
		unsigned int Table_element_num;
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

		Software_Profiler( char* Elf_File_Path);
		~Software_Profiler( );
		
		void PC_Analyzer( unsigned long pc );
		void Summary_Display();
		void Stop_And_Calculate_Duration();

		int Function_Search( unsigned long pc );
		unsigned int Cal_Num_Of_Table_Elements(const char* Elf_File_Path);
		int Make_Table( const char* Elf_File_Path );
		void swap( m_sym_table_element* a, m_sym_table_element* b ); 


};
