//-------------------------------------------------------------
// Design	: AHB_Lite_BDMMI 
// Author	: Bryan Choi 
// Email	: bryan.choi@twoblocktech.com
// File		: AHB_Lite_BDMMI.h
// Date		: 2016.2.14
//-------------------------------------------------------------
// Copyright (C) 2015-2016 TwoBlock Technologies Co.
//-------------------------------------------------------------
// Description	: manage AHB_Lite memory map
//-------------------------------------------------------------

#ifndef __AHB_Lite_BDMMI_H__
#define __AHB_Lite_BDMMI_H__

#include "systemc.h"

#define SlaveNumber 10

using namespace BDapi;

class AHB_Lite;

class AHB_Lite_BDMMI : public BDMMI 
{
	public:
	  // this function set this bus memory map	
		// TODO : user have to implement this function
		void SetMemoryMap();

		// return slave number for generating PMML.json
		unsigned int GetSlaveNumber();

		AHB_Lite_BDMMI(AHB_Lite *c);
		virtual ~AHB_Lite_BDMMI();

	private:
		AHB_Lite *p_Target;

	  SlaveMemoryMap ast_BusSlave[SlaveNumber];	
		//unsigned int SlaveNumber;
};

#endif	// __AHB_Lite_BDMMI_H__

