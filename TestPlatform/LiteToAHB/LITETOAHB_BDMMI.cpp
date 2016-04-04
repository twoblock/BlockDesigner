//-------------------------------------------------------------
// Design	: LITETOAHB_BDMMI 
// Author	: Bryan Choi 
// Email	: bryan.choi@twoblocktech.com
// File		: LITETOAHB_BDMMI.cpp
// Date		: 2016.2.14
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: manage LITETOAHB memory map
//-------------------------------------------------------------

#include "LITETOAHB_BDMMI.h"
#include "LITETOAHB.h"

/*  
 * function    : SetMemoryMap 
 * design      : set this bus memory map by using BDMMI
 */
void LITETOAHB_BDMMI::SetMemoryMap()
{
	// TODO : user have to implement this area 
}

/*  
 * function    : GetSlaveNumber 
 * design      : return slave numberh 
 * return      : unsigned int - SlaveNumber 
 */
unsigned int LITETOAHB_BDMMI::GetSlaveNumber()
{
	return SlaveNumber;	
}

/*  
 * function    : LITETOAHB_BDMMI 
 * design      : Constructor 
 */
LITETOAHB_BDMMI::LITETOAHB_BDMMI(LITETOAHB *c) : p_Target(c)
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
 * function    : ~LITETOAHB_BDMMI 
 * design      : Destructor 
 */
LITETOAHB_BDMMI::~LITETOAHB_BDMMI()
{
}


