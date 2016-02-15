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

	p_Target->BD_AHBDCD->S0_BASE_ADDR = BDMMIMemoryMap[0].StartAddress;
	p_Target->BD_AHBDCD->S1_BASE_ADDR = BDMMIMemoryMap[1].StartAddress;
	p_Target->BD_AHBDCD->S2_BASE_ADDR = BDMMIMemoryMap[2].StartAddress;

	p_Target->BD_AHBDCD->S0_END_ADDR = BDMMIMemoryMap[0].StartAddress + BDMMIMemoryMap[0].Size - 1;
	p_Target->BD_AHBDCD->S1_END_ADDR = BDMMIMemoryMap[1].StartAddress + BDMMIMemoryMap[1].Size - 1;
	p_Target->BD_AHBDCD->S2_END_ADDR = BDMMIMemoryMap[2].StartAddress + BDMMIMemoryMap[2].Size - 1;
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
	// initialize Slave Number
	//SlaveNumber = 10;

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

	/////////////////// Test //////////////////////////

	SlaveMemoryMap st_SlaveMemoryMap;	

	// set S0 slave
	strcpy(st_SlaveMemoryMap.SlaveModule, "ahbl2mem");
	strcpy(st_SlaveMemoryMap.SlavePort, "S0");
	st_SlaveMemoryMap.StartAddress = 0x00000000;
	st_SlaveMemoryMap.Size = 0x00100000;

	ModifyMemoryMap(0, st_SlaveMemoryMap);

	// set S0 slave
	strcpy(st_SlaveMemoryMap.SlaveModule, "ahbl2mem_1");
	strcpy(st_SlaveMemoryMap.SlavePort, "S1");
	st_SlaveMemoryMap.StartAddress = 0x20000000;
	st_SlaveMemoryMap.Size = 0x00100000;

	ModifyMemoryMap(1, st_SlaveMemoryMap);

	// set S0 slave
	strcpy(st_SlaveMemoryMap.SlaveModule, "console");
	strcpy(st_SlaveMemoryMap.SlavePort, "S2");
	st_SlaveMemoryMap.StartAddress = 0x25000000;
	st_SlaveMemoryMap.Size = 0x00100000;

	ModifyMemoryMap(2, st_SlaveMemoryMap);
}

/*  
 * function    : ~AHB_Lite_BDMMI 
 * design      : Destructor 
 */
AHB_Lite_BDMMI::~AHB_Lite_BDMMI()
{
}


