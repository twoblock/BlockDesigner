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
#define BDDI_STRING_SIZE				1024
#define BDDI_MEMORYVIEW_SIZE		256

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
	enum BDDIParType
	{
		BDDIParTypeUINT,
		BDDIParTypeBOOL,
		BDDIParTypeFLOAT,
		BDDIParTypeSTRING,
		BDDIParTypeINT,
		BDDIParTypeMax = 0xFFFFFFFF
	};

	// BDDI Register Information
	struct BDDIRegInfo
	{
		char Name[BDDI_NAME_SIZE];
		unsigned int Bitswide;
		BDDIRegType Type;
	};

	// BDDI Parameter Information
	struct BDDIParInfo
	{
		char Name[BDDI_NAME_SIZE];
		unsigned int Bitswide;
		BDDIParType Type;
		char Value[BDDI_STRING_SIZE];
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

	// BDDI To Select Parameter Value Information
	enum BDDISelectParValue
	{
		BDDISelectParBOOL,
		BDDISelectParSTRING,
		BDDISelectParBIT8,
		BDDISelectParBIT16,
		BDDISelectParBIT32,
		BDDISelectParBIT64,
		BDDISelectParBIT8U,
		BDDISelectParBIT16U,
		BDDISelectParBIT32U,
		BDDISelectParBIT64U,
		BDDISelectParFLOAT,
		BDDISelectParDOUBLE,
		BDDISelectParMax = 0xFFFFFFFF
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

	// BDDI Return Parameter Value Classification
	struct BDDIParValue
	{
		BDDIParValue(bool b_Par = false,
				char hw_Par = 0,
				short w_Par = 0,
				int dw_Par = 0,
				long long lw_Par = 0,
				UINT8 hw_ParU = 0,
				UINT16 w_ParU = 0,
				UINT32 dw_ParU = 0,
				UINT64 lw_ParU = 0,
				float f_Par = 0,
				double df_Par = 0,
				BDDISelectParValue e_Par = BDDISelectParMax) :
			b_Value(b_Par),
			hw_Value(hw_Par),
			w_Value(w_Par),
			dw_Value(dw_Par),
			lw_Value(lw_Par),
			hw_ValueU(hw_ParU),
			w_ValueU(w_ParU),
			dw_ValueU(dw_ParU),
			lw_ValueU(lw_ParU),
			f_Value(f_Par),
			df_Value(df_Par),
			Offset(e_Par)
		{
			a_Value[0] = '\0';
		}

		bool b_Value;
		char a_Value[BDDI_STRING_SIZE];
		char hw_Value;
		short w_Value;
		int dw_Value;
		long long lw_Value;
		UINT8 hw_ValueU;
		UINT16 w_ValueU;
		UINT32 dw_ValueU;
		UINT64 lw_ValueU;
		float f_Value;
		double df_Value;

		BDDISelectParValue Offset;
	};
}

#endif	// __BDDITYPES_H__
