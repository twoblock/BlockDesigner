//-------------------------------------------------------------
// Design	: LITETOAHB_BDMMI 
// Author	: Bryan Choi 
// Email	: bryan.choi@twoblocktech.com
// File		: LITETOAHB_BDMMI.h
// Date		: 2016.2.14
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: manage LITETOAHB memory map
//-------------------------------------------------------------

#ifndef __LITETOAHB_BDMMI_H__
#define __LITETOAHB_BDMMI_H__

#include "systemc.h"

#define SlaveNumber 1

using namespace BDapi;

class LITETOAHB;

class LITETOAHB_BDMMI : public BDMMI 
{
	public:
	  // this function set this bus memory map	
		// TODO : user have to implement this function
		void SetMemoryMap();

		// return slave number for generating PMML.json
		unsigned int GetSlaveNumber();

		LITETOAHB_BDMMI(LITETOAHB *c);
		virtual ~LITETOAHB_BDMMI();

	private:
		LITETOAHB *p_Target;

	  SlaveMemoryMap ast_BusSlave[SlaveNumber];	
		//unsigned int SlaveNumber;
};

#endif	// __LITETOAHB_BDMMI_H__

