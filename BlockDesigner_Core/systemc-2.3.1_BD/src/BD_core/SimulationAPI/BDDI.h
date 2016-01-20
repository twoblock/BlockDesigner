//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDI.h
// Date	       					: 2016/1/18
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This interface provide parameter, register, memory,
//								breakpoint, disassembly API	
// ----------------------------------------------------------------------------


#ifndef __BDDI_H__
#define __BDDI_H__

#include "BDDITypes.h"	

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class BDDI
	{
		public:
			
			virtual BDDIReturn BDDIGetParameterValues(unsigned int ParamIndex, unsigned int *OutParam) = 0;
			virtual BDDIReturn BDDISetParameterValues(unsigned int ParamIndex, unsigned int SetValue) = 0;

	};
}

#endif	// __BDDI_H__
