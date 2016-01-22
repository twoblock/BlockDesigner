//-----------------------------------------------------------------------------
// Design								: Block Designer Debugging Interface
// Author								: Harold Ko
// Email								: harold.ko@twoblocktech.com 
// File		     					: BDDI.cpp
// Date	       					: 2016/1/20
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: This interface provide parameter, register, memory,
//								breakpoint, disassembly API	
// ----------------------------------------------------------------------------

#include "BDDI.h"

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * function			: BDDIConvertStringToRegisterValue
	 * design				: Convert String Value to Register Value
	 * description	: this function convert string value which is set by  user input to 
	 *								the real value of register by checking structure of BDDIRegInfo
	 * param				: ReturnValue - this parameter is set the converting value
	 *															by checking structure of BDDIRegInfo 
	 *								RegInfo			-	this parameter is the information of register in each module
	 *								Value				- this parameter is the string data which is set by user input							
	 * return				: this function return status of success or failure
	 * caller				: BDDISetRegisterValues
	 * see					: if you want to know more information
	 *								see enum and structure in BDDITypes.h
	 */
	BDDIReturn BDDI::BDDIConvertStringToRegisterValue(BDDIRegValue *ReturnValue, BDDIRegInfo *RegInfo, const char *Value)
	{
		UINT8 hw_TempValue = 0;
		UINT16 w_TempValue = 0;
		UINT32 dw_TempValue = 0;
		UINT64 lw_TempValue = 0;
		float f_TempValue = 0;
		double df_TempValue = 0; 
		
		switch(RegInfo->Type)
		{

			case BDDIRegTypeHEX:
				dw_TempValue = (UINT32)strtoul(Value, NULL, 16);
				ReturnValue->dw_Value = dw_TempValue;
				ReturnValue->Offset = BDDISelectRegHEX;

				break;

			case BDDIRegTypeUINT:
				if(Value[0] == '0' &&
					((Value[1] == 'X') ||
						(Value[1] == 'x')))	{
					if(RegInfo->Bitswide == 8)	{
						hw_TempValue = (UINT8)strtoul(Value, NULL, 16);
						ReturnValue->hw_Value = hw_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT8;
					}
					else if(RegInfo->Bitswide == 16)	{
						w_TempValue = (UINT16)strtoul(Value, NULL, 16);
						ReturnValue->w_Value = w_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT16;
					}
					else if(RegInfo->Bitswide == 32)	{
						dw_TempValue = (UINT32)strtoul(Value, NULL, 16);
						ReturnValue->dw_Value = dw_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT32;
					}
					else if(RegInfo->Bitswide == 64)	{
						lw_TempValue = strtoull(Value, NULL, 16);
						ReturnValue->lw_Value = lw_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT64;
					}
					else	{
						return BDDIStatusError;
					}
				}
				else {
					if(RegInfo->Bitswide == 8)	{
						hw_TempValue = (UINT8)strtoul(Value, NULL, 10);
						ReturnValue->hw_Value = hw_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT8;
					}
					else if(RegInfo->Bitswide == 16)	{
						w_TempValue = (UINT16)strtoul(Value, NULL, 10);
						ReturnValue->w_Value = w_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT16;
					}
					else if(RegInfo->Bitswide == 32)	{
						dw_TempValue = (UINT32)strtoul(Value, NULL, 10);
						ReturnValue->dw_Value = dw_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT32;
					}
					else if(RegInfo->Bitswide == 64)	{
						lw_TempValue = strtoull(Value, NULL, 10);
						ReturnValue->lw_Value = lw_TempValue;
						ReturnValue->Offset = BDDISelectRegBIT64;
					}
					else	{
						return BDDIStatusError;
					}
				}

				break;

			case BDDIRegTypeBOOL:
				if((strcmp(Value, "false") == 0) || (strcmp(Value, "0") == 0))	{
					ReturnValue->b_Value = false;
					ReturnValue->Offset = BDDISelectRegBOOL;
				}
				else	{
					ReturnValue->b_Value = true;
					ReturnValue->Offset = BDDISelectRegBOOL;
				} 

				break;

			case BDDIRegTypeFLOAT:
				if(RegInfo->Bitswide == 32)	{
					f_TempValue = (float)strtod(Value, NULL);
					ReturnValue->f_Value = f_TempValue;
					ReturnValue->Offset = BDDISelectRegFLOAT;
				}
				else if(RegInfo->Bitswide == 64)	{
					df_TempValue = strtod(Value, NULL);
					ReturnValue->df_Value = df_TempValue;
					ReturnValue->Offset = BDDISelectRegDOUBLE;
				}
				else	{
					return BDDIStatusError;
				}

				break;

			case BDDIRegTypeSTRING:
				strcpy(ReturnValue->a_Value, Value);
				ReturnValue->Offset = BDDISelectRegSTRING;

				break;

			case BDDIRegTypePC:	return BDDIStatusCmdNotSupported;
			case BDDIRegTypeMax:	return BDDIStatusError;
			default:	return BDDIStatusError;
		}

		return BDDIStatusOK;
	}

	/*
	 * function			: BDDIConvertRegisterValueToString
	 * design				: Convert Register Value to String Value
	 * description	: this function convert the current value of register in each module
	 *								to string data whici is set by user input 
	 * param				: ReturnValue - this parameter is set the converting value
	 *															by checking structure of BDDIRegInfo 
	 *								RegInfo			-	this parameter is the information of register in each module
	 *								Value				- this parameter is the string data which is send to user
	 * return				: this function return status of success or failure
	 * caller				: BDDIGetRegisterValues
	 * see					: if you want to know more information
	 *								see enum and structure in BDDITypes.h
	 */
	BDDIReturn BDDI::BDDIConvertRegisterValueToString(BDDIRegValue *ReturnValue, char *Value)
	{
		switch(ReturnValue->Offset)
		{

			case BDDISelectRegBOOL:
				if(ReturnValue->b_Value)	strcpy(Value, "true");
				else											strcpy(Value, "false");

				break;

			case BDDISelectRegSTRING:		return BDDIStatusCmdNotSupported;
			case BDDISelectRegBIT8:			sprintf(Value, "%u", ReturnValue->hw_Value);		break;
			case BDDISelectRegBIT16:		sprintf(Value, "%u", ReturnValue->w_Value);			break;
			case BDDISelectRegBIT32:		sprintf(Value, "%u", ReturnValue->dw_Value);		break;
			case BDDISelectRegBIT64:		sprintf(Value, "%llu", ReturnValue->lw_Value);	break;
			case BDDISelectRegHEX:			sprintf(Value, "0x%x", ReturnValue->dw_Value);	break;
			case BDDISelectRegFLOAT:		sprintf(Value, "%f", ReturnValue->f_Value);			break;
			case BDDISelectRegDOUBLE:		sprintf(Value, "%f", ReturnValue->df_Value);		break;
			case BDDISelectRegPC:				return BDDIStatusCmdNotSupported;
			case BDDISelectRegMax:			return BDDIStatusError;
		}
		
		return BDDIStatusOK;
	}

	/*
	 * function			: BDDIExtractRegisterValue
	 * see					: if you want to know more information
	 *								see BDDIExtractRegisterValue function in BDDI.h
	 */
	template <>
	BDDIReturn BDDI::BDDIExtractRegisterValue(BDDIRegValue *ReturnValue, char *TempBuf)
	{

		switch(ReturnValue->Offset)
		{
			case BDDISelectRegSTRING: strcpy(TempBuf, ReturnValue->a_Value);	break;
			default:									return BDDIStatusError;
		}

		return BDDIStatusOK;
	}

	/*
	 * function			: BDDIPutInRegisterValue
	 * see					: if you want to know more information
	 *								see BDDIPutInRegisterValue function in BDDI.h
	 */
	template <>
	BDDIReturn BDDI::BDDIPutInRegisterValue(BDDIRegValue *ReturnValue, BDDIRegInfo *RegInfo, char *TempBuf)
	{
		switch(RegInfo->Type)
		{

			case BDDIRegTypeSTRING:
				strcpy(ReturnValue->a_Value, TempBuf);
				ReturnValue->Offset = BDDISelectRegSTRING;

				break;
				
			default:	return BDDIStatusError;
		}

		return BDDIStatusOK;
	}

}
