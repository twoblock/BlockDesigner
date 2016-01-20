//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDIBase.h
// Date	       					: 2016/1/18
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This interface provide parameter, register, memory,
//								breakpoint, disassembly API	
// ----------------------------------------------------------------------------

#ifndef __BDDIBASE_H__
#define __BDDIBASE_H__

#include "BDDI.h"

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	class BDDIBase : public BDDI
	{
		public:
			
			virtual BDDIReturn BDDIGetParameterValues(unsigned int ParamIndex, unsigned int *OutParam)
			{
				return BDDIStatusCmdNotSupported;
			}

			virtual BDDIReturn BDDISetParameterValues(unsigned int ParamIndex, unsigned int SetValue)
			{
				return BDDIStatusCmdNotSupported;
			}
	};
}

#endif	// __BDDIBASE_H__
