//-----------------------------------------------------------------------------
// Design								: Software Profiler 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: SoftwareProfiler.cpp
// Date	       					: 2016/3/8
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: provide apis to profile software flow data and display them
// ----------------------------------------------------------------------------

#include "SoftwareProfiler.h" 

namespace BDapi
{

	/*
	 * function 	: SoftwareLoader 
	 * design	    : Constructor 
	 */
	SoftwareProfiler::SoftwareProfiler(char* Elf_File_Path )
	{
		// Table Initialize
		Table_element_num = 0;
		m_Symbol_Table = NULL; 

		Error = NULL;
		Pre_pc = 0;

		// Time Initialize
		Global_Time = 0; 
		OneFunctionFlowTime = 0;

		// Stack_Variable
		Top_1 = -1;
		Top_2 = -2;

		//Stack Initialize
		Call_Stack.push(-1);
		Call_Stack.push(-1);
		Call_Stack.push(-1);

		SymbolTable.clear();
		ProfilingTable.clear();
		FunctionFlowGragh.clear();

		////////////////////////////////////////////////
		//             Make Table                     //
		////////////////////////////////////////////////

		Table_element_num = Cal_Num_Of_Table_Elements(Elf_File_Path );
		Make_Table( Elf_File_Path);
		Function_Index      = Table_element_num;
		IndexOfFunctionFlow = Table_element_num;
	}

	/*
	 * function 	: ~SoftwareLoader
	 * design	    : Destructor
	 */
	SoftwareProfiler::~SoftwareProfiler( )
	{
	}

	/*
	 * function 	: PC_Analyzer 
	 * design	    : analyze pc and store data 
	 */
	void SoftwareProfiler::PC_Analyzer( unsigned long pc )
	{
		Global_Time++;
		m_Symbol_Table[Function_Index].Self_Duration++;

		// to profile function flow gragh
		OneFunctionFlowTime++;

		if( pc == Pre_pc )
			return;

		if( m_Symbol_Table[Function_Index].Start_Addr <= pc && pc <= m_Symbol_Table[Function_Index].End_Addr )
		{
		}
		else 
		{
			// Find Function
			if(( Function_Index = Function_Search( pc ) ) != -1)
			{
				if( m_Symbol_Table[Function_Index].Start_Addr == pc ) // Call // 
				{
					m_Symbol_Table[Function_Index].Partial_Start_Duration = Global_Time;
					m_Symbol_Table[Function_Index].Call_Num++;
					m_Symbol_Table[Function_Index].Is_it_Called_Now = true;
					m_Symbol_Table[Function_Index].Is_Profilied = true;
				}

				Top_1 = Function_Index;

				if( Top_1 == Call_Stack.top() ) // Return //
				{
					m_Symbol_Table[Top_2].Duration += ( Global_Time - m_Symbol_Table[Top_2].Partial_Start_Duration );
					m_Symbol_Table[Top_2].Is_it_Called_Now = false;
					Top_2 = Call_Stack.top(); 
					Call_Stack.pop(); 
				}
				else                           // No Call No Return 
				{
					Call_Stack.push(Top_2);
					Top_2 = Function_Index;
				}
				m_Symbol_Table[Table_element_num].Is_it_Called_Now = false;

				// to profile function flow gragh
				PushOneFunctionFlow();
			}
			else
			{
				m_Symbol_Table[Table_element_num].Is_Profilied = true;

				if( m_Symbol_Table[Table_element_num].Is_it_Called_Now == false )
				{
					m_Symbol_Table[Table_element_num].Is_it_Called_Now = true;
					m_Symbol_Table[Table_element_num].Call_Num++;

					// to profile function flow gragh
					PushOneFunctionFlow();
				}
				Function_Index = Table_element_num;
			}
		}
		Pre_pc = pc;	
	}

	/*
	 * function 	: Summary_Display
	 * design	    : find function based on pc 
	 */
	int SoftwareProfiler::Function_Search( unsigned long pc )
	{
		int i  = 0;

		for( i = 0; i < Table_element_num ; i++ )
		{
			if( m_Symbol_Table[i].Start_Addr <= pc && pc <= m_Symbol_Table[i].End_Addr )
			{
				return i;
			}
		}
		return -1;
	}

	/*
	 * function 	: Summary_Display
	 * design	    : display software profiling table 
	 */
	void SoftwareProfiler::Summary_Display()
	{
		// For Profiling
		unsigned long Sum_Of_SelfDuration_Cycle= 0;
		unsigned long Sum_Of_Call = 0;
		float self_duration_Per = 0;
		float Sum_Of_self_duration_Per = 0;
		float duration_Per = 0;
		int k;

		Stop_And_Calculate_Duration();

		if(m_Symbol_Table != NULL)
		{
			for( k = 0; k < Table_element_num + 1; k++ )
			{
				Sum_Of_SelfDuration_Cycle += m_Symbol_Table[k].Self_Duration; 
				Sum_Of_Call               += m_Symbol_Table[k].Call_Num; 
			}

			printf("\n\n\033[44m Function Name                    Call   Duration(Cycles)   Duration(Percent)   Self Duration(Cycles)   Self Duration(Percent) \033[0m\n");

			// Normal Function Diaplay
			for( k = 0; k < Table_element_num + 1 ; k++ )
			{
				self_duration_Per =  (float)m_Symbol_Table[k].Self_Duration/(float)Sum_Of_SelfDuration_Cycle ;
				duration_Per      =  (float)m_Symbol_Table[k].Duration/(float)Global_Time ;
				Sum_Of_self_duration_Per += self_duration_Per;

				printf("\033[7m %-25s %10lu %12lu %20.5f %20lu %25.5f         \033[0m\n",  m_Symbol_Table[k].Function_Name,  m_Symbol_Table[k].Call_Num,   m_Symbol_Table[k].Duration, duration_Per*100,  m_Symbol_Table[k].Self_Duration, self_duration_Per*100 );
			}
			// Summary Function Diaplay
			printf("\033[7m Summary %28lu %12lu %20.5f %20lu %25.5f         \033[0m\n",  Sum_Of_Call ,   Global_Time  , 100.0 ,  Sum_Of_SelfDuration_Cycle , Sum_Of_self_duration_Per*100);
		}
	}

	/*
	 * function 	: Stop_And_Calculate_Duration 
	 * design	    : help calculate duration at last 
	 */
	void SoftwareProfiler::Stop_And_Calculate_Duration()
	{
		int k;

		for( k = 0; k < Table_element_num ; k++ )
		{
			if( m_Symbol_Table[k].Is_it_Called_Now == true )
			{
				m_Symbol_Table[k].Duration += ( Global_Time - m_Symbol_Table[k].Partial_Start_Duration );
				m_Symbol_Table[k].Partial_Start_Duration = Global_Time;
			}
		}
		m_Symbol_Table[Table_element_num].Duration = m_Symbol_Table[Table_element_num].Self_Duration;
	}

	/*
	 * function 	: Cal_Num_Of_Table_Elements 
	 * design	    : calculate element number of symbol table   
	 */
	unsigned int SoftwareProfiler::Cal_Num_Of_Table_Elements(const char* Elf_File_Path)
	{
		char buff[1024];
		//char * Error = NULL;
		char * p_Size;
		char * p_Sym_Type;
		char Command[1024];

		FILE* fp;

		sprintf( Command, "readelf -s %s", Elf_File_Path );
		fp = popen( Command , "r");

		if ( NULL == fp)
		{
			perror( "popen() 실패");
			return -1;
		}
		else
		{
			while( fgets( buff, 1024, fp) )
			{
				strtok( buff," ");     // Line number
				strtok( NULL," "); // Start_Addr
				p_Size       = strtok( NULL," "); // Size

				if( p_Size != NULL) 
				{
					if( strcmp("0",p_Size) != 0) // if Size != 0
					{
						p_Sym_Type = strtok( NULL," ");// Sym_Type
						if( p_Sym_Type != NULL)
						{
							if( strcmp("FUNC",p_Sym_Type) == 0) // if Type is FUNC
							{
								Table_element_num++; // caculate elements to make table.
							}
						}
					}
				}
			}

			pclose( fp);
			return Table_element_num;
		}
	}

	/*
	 * function 	: Make_Table 
	 * design	    : make symbol table based on elf file
	 */
	int SoftwareProfiler::Make_Table( const char* Elf_File_Path)
	{
		char buff[1024];
		char * p_Start_Addr;
		char * p_Size;
		char * p_Function_Name;
		char * p_Sym_Type;
		char * Error = NULL;
		int k;

		unsigned long Index = 0;
		//unsigned long pc = 0;
		FILE* fp;

		char Command[1024];

		sprintf( Command, "readelf -s %s", Elf_File_Path );
		fp = popen( Command , "r");

		if ( NULL == fp)
		{
			perror( "popen() 실패");
			return -1;
		}

		m_Symbol_Table = ( m_sym_table_element * )malloc( ( Table_element_num + 1 ) * sizeof( m_sym_table_element ) );

		/////////////////
		//  Make table 
		/////////////////
		while( fgets( buff, 1024, fp) )
		{
			strtok( buff," ");     // Line number
			p_Start_Addr = strtok( NULL," "); // Start_Addr
			p_Size       = strtok( NULL," "); // Size

			if( p_Size != NULL) 
			{
				if( strcmp("0",p_Size) != 0) // if Size != 0
				{
					p_Sym_Type = strtok( NULL," ");// Sym_Type
					if( p_Sym_Type != NULL)
					{
						if( strcmp("FUNC",p_Sym_Type) == 0) // if Type is FUNC
						{
							strtok( NULL," "); // Bind
							strtok( NULL," "); // vis
							strtok( NULL," "); // Ndx

							p_Function_Name = strtok( NULL,"\n"); // Function Name

							m_Symbol_Table[Index].Start_Addr    = strtoul( p_Start_Addr , &Error, 16) -1 ;
							m_Symbol_Table[Index].End_Addr      = m_Symbol_Table[Index].Start_Addr + strtoul( p_Size, &Error, 10) - 2;
							if( p_Function_Name != NULL)
								strcpy(m_Symbol_Table[Index].Function_Name , p_Function_Name);

							m_Symbol_Table[Index].Call_Num = 0;
							m_Symbol_Table[Index].Duration = 0;
							m_Symbol_Table[Index].Self_Duration= 0;
							m_Symbol_Table[Index].Is_it_Called_Now = false;
							m_Symbol_Table[Index].Is_Profilied= false;

							Index++;
						}
					}
				}
			}
		}
		pclose( fp);

		/////////////////
		//  Sort table 
		/////////////////

		int i = 0;
		k = 0;
		int table_index_min = 0;

		for( i = 0; i < Table_element_num - 1 ; i++ )
		{
			table_index_min = i; 
			for( k = i + 1; k < Table_element_num; k++)
			{
				if( m_Symbol_Table[table_index_min].Start_Addr > m_Symbol_Table[k].Start_Addr )
				{
					table_index_min = k; 
				}
			}
			swap( &m_Symbol_Table[i], &m_Symbol_Table[table_index_min]);
		}
		m_Symbol_Table[Table_element_num].Start_Addr    = 0;
		m_Symbol_Table[Table_element_num].End_Addr      = 1;
		strcpy(m_Symbol_Table[Table_element_num].Function_Name ,"Unknown");
		m_Symbol_Table[Table_element_num].Call_Num = 1;
		m_Symbol_Table[Table_element_num].Duration = 0;
		m_Symbol_Table[Table_element_num].Self_Duration= 0;
		m_Symbol_Table[Table_element_num].Is_it_Called_Now = true;
		m_Symbol_Table[Table_element_num].Is_Profilied= false;

		Symbol.clear();
		Symbol["function_name"] = "Summary"; 
		SymbolTable[0] = Symbol;

		// Normal Function Diaplay
		for( i = 0; i < Table_element_num + 1 ; i++ ){
			Symbol.clear();
			Symbol["function_name"] = m_Symbol_Table[i].Function_Name;
			SymbolTable[i+1] = Symbol;
		}

		Root_SymbolTable["SymbolTable"] = SymbolTable;

		return 0;
	}

	/*
	 * function 	: swap 
	 * design	    : swap table element to sort them 
	 */
	void SoftwareProfiler::swap( m_sym_table_element* a, m_sym_table_element* b )
	{
		m_sym_table_element swap_temp;

		swap_temp.Start_Addr     = a->Start_Addr;
		swap_temp.End_Addr       = a->End_Addr;
		strcpy( swap_temp.Function_Name , a->Function_Name );

		a->Start_Addr     = b->Start_Addr;
		a->End_Addr       = b->End_Addr;
		strcpy(	a->Function_Name , b->Function_Name);

		b->Start_Addr     = swap_temp.Start_Addr;
		b->End_Addr       = swap_temp.End_Addr;
		strcpy(	b->Function_Name , swap_temp.Function_Name);
	}

	/*
	 * function 	: PushOneFunctionFlow 
	 * design	    : push function flow into FunctionFlowGragh json
	 */
	void SoftwareProfiler::PushOneFunctionFlow()
	{
		char a_Buffer[128];
		memset(a_Buffer, 0, sizeof(a_Buffer));

		IndexOfFunctionFlow = Function_Search(Pre_pc);
		if(IndexOfFunctionFlow == -1){
			sprintf(a_Buffer, "%d", Table_element_num+1);
			FunctionFG["function_index"] = a_Buffer;
			//FunctionFG["function_name"] = m_Symbol_Table[Table_element_num].Function_Name;
		}
		else{
			sprintf(a_Buffer, "%d", IndexOfFunctionFlow+1);
			FunctionFG["function_index"] = a_Buffer;
			//FunctionFG["function_name"] = m_Symbol_Table[IndexOfFunctionFlow].Function_Name;
		}
		memset(a_Buffer, 0, sizeof(a_Buffer));
		sprintf(a_Buffer, "%lu", OneFunctionFlowTime);
		FunctionFG["function_cycle"] = a_Buffer;
		FunctionFlowGragh.append(FunctionFG);

		OneFunctionFlowTime = 0;
	}

	string SoftwareProfiler::GetJsonOfSymbolTable()
	{
		Json::StyledWriter SymbolTable;
		string StringSymbolTable= SymbolTable.write(Root_SymbolTable);
		//printf("%s \n", StringSymbolTable.c_str()); 

		return StringSymbolTable; 
	}

	string SoftwareProfiler::GetJsonOfFunctionFlowGragh()
	{
		// to profile function flow gragh
		PushOneFunctionFlow();

		int Gragh[Table_element_num];	
		int i = 0;
		int size = 0;
		size = FunctionFlowGragh.size();

		for( i = 0; i < Table_element_num + 1 ; i++ ){

			Gragh[i] = 0;

			for(int IndexOfFG = 0; IndexOfFG < size; IndexOfFG++){
				if(atoi(FunctionFlowGragh[IndexOfFG]["function_index"].asCString()) == i){
					Gragh[i] += atoi(FunctionFlowGragh[IndexOfFG]["function_cycle"].asCString());
				}
			}
		}
		Root_FunctionFlowGragh["FunctionFlowGragh"] = FunctionFlowGragh;

		Json::StyledWriter GraghWriter;
		string StringFunctionFlowGragh = GraghWriter.write(Root_FunctionFlowGragh);
		//printf("%s \n", StringFunctionFlowGragh.c_str()); 

		FunctionFlowGragh.clear();

		return StringFunctionFlowGragh; 
	}

	string SoftwareProfiler::GetJsonOfProfilingTable()
	{
		int i = 0;
		char a_Buffer[128] = {0,};

		// For Profiling
		unsigned long Sum_Of_SelfDuration_Cycle= 0;
		unsigned long Sum_Of_Call = 0;
		float self_duration_Per = 0;
		float Sum_Of_self_duration_Per = 0;
		float duration_Per = 0;
		int k;

		for( k = 0; k < Table_element_num + 1; k++ )
		{
			Sum_Of_SelfDuration_Cycle += m_Symbol_Table[k].Self_Duration; 
			Sum_Of_Call               += m_Symbol_Table[k].Call_Num; 
		}

		// Normal Function Diaplay
		for( i = 0; i < Table_element_num + 1 ; i++ ){

			self_duration_Per =  (float)m_Symbol_Table[i].Self_Duration/(float)Sum_Of_SelfDuration_Cycle ;
			duration_Per      =  (float)m_Symbol_Table[i].Duration/(float)Global_Time ;
			Sum_Of_self_duration_Per += self_duration_Per;

			FunctionPT.clear();
			//if(m_Symbol_Table[i].Is_Profilied == true){
				sprintf(a_Buffer, "%d", i+1);
				FunctionPT["function_index"] = a_Buffer;
				memset(a_Buffer, 0, sizeof(a_Buffer));
				sprintf(a_Buffer, "%lu", m_Symbol_Table[i].Call_Num);
				FunctionPT["function_call"] = a_Buffer;
				memset(a_Buffer, 0, sizeof(a_Buffer));
				sprintf(a_Buffer, "%lu", m_Symbol_Table[i].Duration);
				FunctionPT["function_duration"] = a_Buffer;
				memset(a_Buffer, 0, sizeof(a_Buffer));
				sprintf(a_Buffer, "%f", duration_Per*100);
				FunctionPT["function_duration_per"] = a_Buffer;
				memset(a_Buffer, 0, sizeof(a_Buffer));
				sprintf(a_Buffer, "%lu", m_Symbol_Table[i].Self_Duration);
				FunctionPT["function_selfduration"] = a_Buffer;
				memset(a_Buffer, 0, sizeof(a_Buffer));
				sprintf(a_Buffer, "%f", self_duration_Per*100);
				FunctionPT["function_selfduration_per"] = a_Buffer;

				memset(a_Buffer, 0, sizeof(a_Buffer));

				ProfilingTable.append(FunctionPT);

				//if(m_Symbol_Table[i].Is_it_Called_Now == false)
					//m_Symbol_Table[i].Is_Profilied = false;
			//}
		}

		FunctionPT["function_index"] = "0";
		memset(a_Buffer, 0, sizeof(a_Buffer));
		sprintf(a_Buffer, "%lu", Sum_Of_Call);
		FunctionPT["function_call"] = a_Buffer;
		memset(a_Buffer, 0, sizeof(a_Buffer));
		sprintf(a_Buffer, "%lu", Global_Time);
		FunctionPT["function_duration"] = a_Buffer;
		FunctionPT["function_duration_per"] = "100.000000";
		memset(a_Buffer, 0, sizeof(a_Buffer));
		sprintf(a_Buffer, "%lu", Sum_Of_SelfDuration_Cycle); 
		FunctionPT["function_selfduration"] = a_Buffer;
		FunctionPT["function_selfduration_per"] = "100.000000";

		ProfilingTable.append(FunctionPT);

		Root_ProfilingTable["ProfilingTable"] = ProfilingTable;

		Json::StyledWriter writer;
		string StringProfilingTable= writer.write(Root_ProfilingTable);
		//printf("%s \n", StringProfilingTable.c_str()); 
		
		ProfilingTable.clear();

		return StringProfilingTable;
	}
}
