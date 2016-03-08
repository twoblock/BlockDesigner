//-------------------------------------------------------------
// Design	: AHB_BDMMI 
// Author	: Bryan Choi 
// Email	: bryan.choi@twoblocktech.com
// File		: AHB_BDMMI.h
// Date		: 2016.2.14
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: manage AHB_Lite memory map
//-------------------------------------------------------------

#ifndef __AHB_BDMMI_H__
#define __AHB_BDMMI_H__

#include "systemc.h"

#define SlaveNumber 10

using namespace BDapi;

class AHB;

class AHB_BDMMI : public BDMMI 
{
	public:
	  // this function set this bus memory map	
		// TODO : user have to implement this function
		void SetMemoryMap();

		// return slave number for generating PMML.json
		unsigned int GetSlaveNumber();

		AHB_BDMMI(AHB *c);
		virtual ~AHB_BDMMI();

	private:
		AHB *p_Target;

	  SlaveMemoryMap ast_BusSlave[SlaveNumber];	
		//unsigned int SlaveNumber;
};

#endif	// __AHB_BDMMI_H__

