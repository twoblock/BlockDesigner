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

#define BDDI_NAME_SIZE			1024
#define BDDI_STRING_SIZE		1024

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

	// BDDI To Select Register Value Information
	enum BDDISelectRegValue
	{
		BDDISelectRegBOOL,
		BDDISelectRegSTRING,
		BDDISelectRegBIT8,
		BDDISelectRegBIT16,
		BDDISelectRegBIT32,
		BDDISelectRegBIT64,
		BDDISelectRegHEX,
		BDDISelectRegFLOAT,
		BDDISelectRegDOUBLE,
		BDDISelectRegPC,
		BDDISelectRegMax = 0xFFFFFFFF
	};	

	// BDDI Return Register Value Classification
	struct BDDIRegValue
	{
		BDDIRegValue(bool b_Par = false,
									UINT8 hw_Par = 0,
									UINT16 w_Par = 0,
									UINT32 dw_Par = 0,
									UINT64 lw_Par = 0,
									float f_Par = 0,
									double df_Par = 0,
									UINT32 pc_Par = 0,
									BDDISelectRegValue e_Par = BDDISelectRegMax) :
			b_Value(b_Par),
			hw_Value(hw_Par),
			w_Value(w_Par),
			dw_Value(dw_Par),
			lw_Value(lw_Par),
			f_Value(f_Par),
			df_Value(df_Par),
			pc_Value(pc_Par),
			Offset(e_Par)
		{
			a_Value[0] = '\0';
		}

		bool b_Value;
		char a_Value[BDDI_STRING_SIZE];
		UINT8 hw_Value;
		UINT16 w_Value;
		UINT32 dw_Value;
		UINT64 lw_Value;
		float f_Value;
		double df_Value;
		UINT32 pc_Value;
		
		BDDISelectRegValue Offset;
	};
	
}

#endif	// __BDDITYPES_H__
