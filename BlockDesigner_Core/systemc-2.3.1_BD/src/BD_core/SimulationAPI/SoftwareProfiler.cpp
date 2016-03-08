#include "SoftwareProfiler.h" 

SoftwareProfiler::SoftwareProfiler(char* Elf_File_Path )
{
	// Table Initialize
		Table_element_num = 0;
		m_Symbol_Table = NULL; 

		Error = NULL;
		Pre_pc = 0;

		// Time Initialize
		Global_Time = 0; 

		// Stack_Variable
		Top_1 = -1;
		Top_2 = -2;

		//Stack Initialize
		Call_Stack.push(-1);
		Call_Stack.push(-1);
		Call_Stack.push(-1);

		////////////////////////////////////////////////
		//             Make Table                     //
		////////////////////////////////////////////////

		Table_element_num = Cal_Num_Of_Table_Elements(Elf_File_Path );
		Make_Table( Elf_File_Path);
		Function_Index      = Table_element_num ;
}

SoftwareProfiler::~SoftwareProfiler( )
{
}

void SoftwareProfiler::PC_Analyzer( unsigned long pc )
{
	Global_Time++;
	m_Symbol_Table[Function_Index].Self_Duration++;

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
		}
		else
		{
			if( m_Symbol_Table[Table_element_num].Is_it_Called_Now == false )
			{
				m_Symbol_Table[Table_element_num].Is_it_Called_Now = true;
				m_Symbol_Table[Table_element_num].Call_Num++;
			}
			Function_Index = Table_element_num;
		}
	}
	Pre_pc = pc;	

}

////////////////////////////////////////////////
//             Summary Display                //
////////////////////////////////////////////////
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

	return 0;
}

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

