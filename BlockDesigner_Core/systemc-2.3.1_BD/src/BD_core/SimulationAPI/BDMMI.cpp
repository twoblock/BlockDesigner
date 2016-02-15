//-----------------------------------------------------------------------------
// Design								: Block Designer Memory Map Interface 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDMMI.cpp
// Date	       					: 2016/2/11
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: Memory Map Interface data structure
// ----------------------------------------------------------------------------

#include "BDMMI.h"

namespace BDapi 
{
	/*
	 * function    : AddMemoryMap 
	 * design      : add one slave memory map to bus memory map
	 * param       : SlaveMemoryMap Map - Slave memory map information 
	 */
	void BDMMI::AddMemoryMap(SlaveMemoryMap Map)
	{
		BDMMIMemoryMap.push_back(Map);
	}

	/*
	 * function    : ModifyMemoryMap 
	 * design      : modify one slave memory map in bus memory map 
	 * param       : int Index - chose slave memory map 
	 * param       : SlaveMemoryMap Map - Slave memory map information 
	 */
	void BDMMI::ModifyMemoryMap(int Index, SlaveMemoryMap Map)
	{
		strcpy(BDMMIMemoryMap[Index].SlaveModule, Map.SlaveModule);
		strcpy(BDMMIMemoryMap[Index].SlavePort, Map.SlavePort);
		BDMMIMemoryMap[Index].StartAddress = Map.StartAddress;
		BDMMIMemoryMap[Index].Size = Map.Size;
	}

	/*
	 * function    : SetMemoryMap 
	 * design      : user have to implement this function in a drived class 
	 */
	void BDMMI::SetMemoryMap()
	{
		return;
	}

	/*
	 * function    : GetSlaveNumber 
	 * design      : return SlaveNumber at a drived class 
	 * return      : unsigned int - SlaveNumber 
	 */
	unsigned int BDMMI::GetSlaveNumber()
	{
		return 0;
	}
}

