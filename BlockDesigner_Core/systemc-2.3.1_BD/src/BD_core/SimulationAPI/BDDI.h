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

// for converting string to return value
#include <stdlib.h>
#include <string.h>

// for converting return value to string
#include <stdio.h>

/*
 * namespace	: BDapi 
 * design	    : Block Designer API 
 * description	: support analyzing ESL platform based on systemc
 */
namespace BDapi
{
	/*
	 * class		    : BDDI
	 * design	      : Provide Block Designer Debugging Interface Function
	 * description	: this class provides to access parameter, register
	 *								memory, assembly code by using BDDI function
	 */
	class BDDI
	{
		public:

			virtual BDDIReturn BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue) = 0;
			virtual BDDIReturn BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue) = 0;

			BDDIReturn BDDIConvertStringToRegisterValue(BDDIRegValue *ReturnValue, BDDIRegInfo *RegInfo, const char *Value);
			BDDIReturn BDDIConvertRegisterValueToString(BDDIRegValue *ReturnValue, char *Value);

			/*
			 * function			: BDDIExtractRegisterValue
			 * design				: Extract Register Value from Structure of BDDIRegValue
			 * description	: this function extract register value from structure of BDDIRegValue
			 *								by checking offset in structure of BDDIRegValue
			 * param				: ReturnValue - this parameter is already set register value and offset
			 *															by BDDIConvertStringToRegisterValue function
			 *								TempBuf			-	this parameter is template type to deal with standard types
			 *															and this include the real value of register
			 * return				: this function return status of success or failure
			 * caller				: BDDISetRegisterValues
			 * see					: if you want to know more information
			 *								see enum and structure in BDDITypes.h
			 */
			template <typename T>
			BDDIReturn BDDIExtractRegisterValue(BDDIRegValue *ReturnValue, T *TempBuf)
			{

				switch(ReturnValue->Offset)
				{
					case BDDISelectRegBOOL:		*TempBuf = ReturnValue->b_Value;		break;
					//case BDDISelectRegSTRING: return BDDIStatusCmdNotSupported;
					case BDDISelectRegBIT8:		*TempBuf = ReturnValue->hw_Value;		break;
					case BDDISelectRegBIT16:	*TempBuf = ReturnValue->w_Value;		break;
					case BDDISelectRegBIT32:	*TempBuf = ReturnValue->dw_Value;		break;
					case BDDISelectRegBIT64:	*TempBuf = ReturnValue->lw_Value;		break;
					case BDDISelectRegHEX:		*TempBuf = ReturnValue->dw_Value;		break;
					case BDDISelectRegFLOAT:	*TempBuf = ReturnValue->f_Value;		break;
					case BDDISelectRegDOUBLE:	*TempBuf = ReturnValue->df_Value;		break;
					case BDDISelectRegPC:			return BDDIStatusCmdNotSupported;
					case BDDISelectRegMax:		return BDDIStatusError;
					default:									return BDDIStatusError;
				}

				return BDDIStatusOK;
			}

			/*
			 * function			: BDDIPutInRegisterValue
			 * design				: Put into Register Value to Structure of BDDIRegValue
			 * description	: this function put into register value to structure of BDDIRegValue
			 *								by checking register information in structure of BDDIRegInfo
			 * param				: ReturnValue - this parameter is set register value and offset
			 *															for preparing to transfer parameter's value	from module to user
			 *								TempBuf			-	this parameter is template type to deal with standard types
			 *															and this include the current value of register in each module
			 * return				: this function return status of success or failure
			 * caller				: BDDIGetRegisterValues
			 * see					: if you want to know more information
			 *								see enum and structure in BDDITypes.h
			 */
			template <typename T>
			BDDIReturn BDDIPutInRegisterValue(BDDIRegValue *ReturnValue, BDDIRegInfo *RegInfo, T *TempBuf)
			{
				switch(RegInfo->Type)
				{

					case BDDIRegTypeHEX:
						ReturnValue->dw_Value = *TempBuf;
						ReturnValue->Offset = BDDISelectRegHEX;

						break;

					case BDDIRegTypeUINT:
						if(RegInfo->Bitswide == 8)	{
							ReturnValue->hw_Value = *TempBuf;
							ReturnValue->Offset = BDDISelectRegBIT8;
						}
						else if(RegInfo->Bitswide == 16)	{
							ReturnValue->w_Value = *TempBuf;
							ReturnValue->Offset = BDDISelectRegBIT16;
						}
						else if(RegInfo->Bitswide == 32)	{
							ReturnValue->dw_Value = *TempBuf;
							ReturnValue->Offset = BDDISelectRegBIT32;
						}
						else if(RegInfo->Bitswide == 64)	{
							ReturnValue->lw_Value = *TempBuf;
							ReturnValue->Offset = BDDISelectRegBIT64;
						}
						else	{
							return BDDIStatusError;
						}

						break;

					case BDDIRegTypeBOOL:
						ReturnValue->b_Value = *TempBuf;
						ReturnValue->Offset = BDDISelectRegBOOL;

						break;

					case BDDIRegTypeFLOAT:
						if(RegInfo->Bitswide == 32)	{
							ReturnValue->f_Value = *TempBuf;
							ReturnValue->Offset = BDDISelectRegFLOAT;
						}
						else if(RegInfo->Bitswide == 64)	{
							ReturnValue->df_Value = *TempBuf;
							ReturnValue->Offset = BDDISelectRegDOUBLE;
						}
						else	{
							return BDDIStatusError;
						}

						break;

					//case BDDIRegTypeSTRING: return BDDIStatusCmdNotSupported;
					case BDDIRegTypePC:	return BDDIStatusCmdNotSupported;
					case BDDIRegTypeMax:	return BDDIStatusError;
					default:	return BDDIStatusError;
				}

				return BDDIStatusOK;
			}

	};

}

#endif	// __BDDI_H__
