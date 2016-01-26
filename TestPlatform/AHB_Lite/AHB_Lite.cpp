//-------------------------------------------------------------
// Design	: AHB_Lite
// Author	: Harold Ko
// Email	: harold.ko@twoblock.co
// File		: AHB_Lite.cpp
// Date		: 2015. 11. 20
// Reference	: AHB_Lite.v (by Changwon Choi)
//------------------------------------------------------------
// Copyright (C) 2015 TwoBlock Co.
//-------------------------------------------------------------
// Description	: AHB Lite for processor
//-------------------------------------------------------------

#include "AHB_Lite.h"

void AHB_Lite::do_transfer()	{
	HADDR_S = HADDR_M;
	HBURST_S = HBURST_M;
	HLOCK_S = HLOCK_M;
	HPROT_S = HPROT_M;
	HSIZE_S = HSIZE_M;
	HTRANS_S = HTRANS_M;
	HWDATA_S = HWDATA_M;
	HWRITE_S = HWRITE_M;
	HREADY_S = HREADY_M;
}

sc_module* CreateInstance(const char *ModuleInstanceName)
{
		return new AHB_Lite(ModuleInstanceName);
}
