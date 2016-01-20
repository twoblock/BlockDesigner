//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface Type
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDITypes.h
// Date	       					: 2016/1/18
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: define enum and struct for BDDI Type
// ----------------------------------------------------------------------------

#ifndef __BDDITYPES_H__
#define __BDDITYPES_H__

#define BDDI_NAME_SIZE					1024
#define BDDI_DESCRIPTION_SIZE		1024

typedef unsigned char				UINT8;
typedef unsigned short			UINT16;
typedef unsigned int				UINT32;
typedef unsigned long long	UINT64;

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{

	// BDDI Command Status Return Type
	enum BDDIReturn
	{
		BDDIStatusOK,
		BDDIStatusError,
		BDDIStatusCmdNotSupported,
		BDDIStatusEnumMax = 0xFFFFFFFF
	};

	// BDDI Register Type	
	enum BDDIRegType
	{
		BDDIRegTypeHEX,
		BDDIRegTypeUINT,
		BDDIRegTypeBOOL,
		BDDIRegTypeFLOAT,
		BDDIRegTypeSTRING,
		BDDIRegTypePC,
		BDDIRegTypeMax = 0xFFFFFFFF
	};

	// BDDI Parameter Type
	enum BDDIParamType
	{
		BDDIParamTypeUINT,
		BDDIParamTypeBOOL,
		BDDIParamTypeSTRING,
		BDDIParamTypeINT,
		BDDIParamTypeMax = 0xFFFFFFFF
	};

	// BDDI Register Information
	struct BDDIRegInfo
	{
		char Name[BDDI_NAME_SIZE];
		unsigned int Bitswide;
		BDDIRegType Type;
	};

	// BDDI Parameter Information
	struct BDDIParamInfo
	{
		char Name[BDDI_NAME_SIZE];
		unsigned int Bitswide;
		BDDIParamType Type;
	};

	// BDDI Return Value Classification
	struct BDDIRegValue
	{
		bool BoolValue;
		char StringValue[BDDI_DESCRIPTION_SIZE];
		UINT8 Uint8Value;
		UINT16 Uint16Value;
		UINT32 Uint32Value;
		UINT64 Uint64Value;
		
		UINT32 Offset;
	};
	
}

#endif	// __BDDITYPES_H__
