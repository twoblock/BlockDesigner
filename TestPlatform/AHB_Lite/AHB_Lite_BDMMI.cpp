//-------------------------------------------------------------
// Design	: AHB_Lite_BDMMI 
// Author	: Bryan Choi 
// Email	: bryan.choi@twoblocktech.com
// File		: AHB_Lite_BDMMI.cpp
// Date		: 2016.2.14
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: manage AHB_Lite memory map
//-------------------------------------------------------------

#include "AHB_Lite_BDMMI.h"
#include "AHB_Lite.h"

/*  
 * function    : SetMemoryMap 
 * design      : set this bus memory map by using BDMMI
 */
void AHB_Lite_BDMMI::SetMemoryMap()
{
	// TODO : user have to implement this area 
	
	unsigned int Index = 0;

	for(Index = 0; Index < SlaveNumber; Index++){
		p_Target->BD_AHBDCD->BASE_ADDR[Index] = BDMMIMemoryMap[Index].StartAddress;
	}
	for(Index = 0; Index < SlaveNumber; Index++){
		p_Target->BD_AHBDCD->END_ADDR[Index] = BDMMIMemoryMap[Index].StartAddress + BDMMIMemoryMap[Index].Size - 1;
	}
}

/*  
 * function    : GetSlaveNumber 
 * design      : return slave numberh 
 * return      : unsigned int - SlaveNumber 
 */
unsigned int AHB_Lite_BDMMI::GetSlaveNumber()
{
	return SlaveNumber;	
}

/*  
 * function    : AHB_Lite_BDMMI 
 * design      : Constructor 
 */
AHB_Lite_BDMMI::AHB_Lite_BDMMI(AHB_Lite *c) : p_Target(c)
{
	// initialize this bus memory map
	for(int SlaveIndex = 0; SlaveIndex < SlaveNumber; SlaveIndex++){

		// initialize a slave memory map
		memset(ast_BusSlave[SlaveIndex].SlaveModule, 0, sizeof(ast_BusSlave[SlaveIndex].SlaveModule));
		memset(ast_BusSlave[SlaveIndex].SlavePort, 0, sizeof(ast_BusSlave[SlaveIndex].SlavePort));
		ast_BusSlave[SlaveIndex].StartAddress = 0x0;
		ast_BusSlave[SlaveIndex].Size = 0x0;

		// push each slave memory map to bus memory map
		BDMMIMemoryMap.push_back(ast_BusSlave[SlaveIndex]); 
	}
}

/*  
 * function    : ~AHB_Lite_BDMMI 
 * design      : Destructor 
 */
AHB_Lite_BDMMI::~AHB_Lite_BDMMI()
{
}


