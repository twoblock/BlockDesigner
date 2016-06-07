//-----------------------------------------------------------------------------
// Design								: Block Designer Memory Map Interface 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: BDMMI.h
// Date	       					: 2016/2/11
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: Memory Map Interface data structure
// ----------------------------------------------------------------------------

#ifndef __BDMMI_H__ 
#define __BDMMI_H__ 

#include <vector>
#include <string.h>

using namespace std;

namespace BDapi 
{
	// store one slave memory map for a bus
	struct SlaveMemoryMap
	{
		char SlaveModule[256];    
		char SlavePort[256];
		unsigned int StartAddress;          
		unsigned int Size;        
	};

	/*
	 * class		    : BDMMI
	 * design	      : provide bus memory map 
	 * description	: two feature
	 *							  1. This is used for bus decoder to select a slave.
	 *                2. This is used for loading software.
	 *                   when each cpu find a memory,they reference this interface.
	 */
	class BDMMI 
	{
		public:
			void AddMemoryMap(SlaveMemoryMap Map);
			void ModifyMemoryMap(int Index, SlaveMemoryMap Map);

			vector<SlaveMemoryMap>* GetMemoryMap();

			virtual void SetMemoryMap();
			virtual unsigned int GetSlaveNumber();

		protected:
			vector<SlaveMemoryMap> BDMMIMemoryMap;
	};
}

#endif
