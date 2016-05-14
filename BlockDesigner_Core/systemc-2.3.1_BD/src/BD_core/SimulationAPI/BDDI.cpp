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

			case BDDIRegTypeSTRING: return BDDIStatusCmdNotSupported;
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
	 *								to string data which is set by user input 
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

			case BDDISelectRegBIT8:			sprintf(Value, "%u", ReturnValue->hw_Value);		break;
			case BDDISelectRegBIT16:		sprintf(Value, "%u", ReturnValue->w_Value);			break;
			case BDDISelectRegBIT32:		sprintf(Value, "0x%x", ReturnValue->dw_Value);	break;
			case BDDISelectRegBIT64:		sprintf(Value, "%llu", ReturnValue->lw_Value);	break;
			case BDDISelectRegHEX:			sprintf(Value, "0x%x", ReturnValue->dw_Value);	break;
			case BDDISelectRegFLOAT:		sprintf(Value, "%f", ReturnValue->f_Value);			break;
			case BDDISelectRegDOUBLE:		sprintf(Value, "%f", ReturnValue->df_Value);		break;
			case BDDISelectRegSTRING:		return BDDIStatusCmdNotSupported;
			case BDDISelectRegPC:				return BDDIStatusCmdNotSupported;
			case BDDISelectRegMax:			return BDDIStatusError;
		}
		
		return BDDIStatusOK;
	}

	/*
	 * function			: BDDIConvertStringToParameterValue
	 * design				: Convert String Value to Parameter Value
	 * description	: this function convert string value which is set by  user input to 
	 *								the real value of parameter by checking structure of BDDIParInfo
	 * param				: ReturnValue - this parameter is set the co6nverting value
	 *															by checking structure of BDDIParInfo 
	 *								ParInfo			-	this parameter is the information of parameter in each module
	 *								Value				- this parameter is the string data which is set by user input							
	 * return				: this function return status of success or failure
	 * caller				: BDDISetParameterValues
	 * see					: if you want to know more information
	 *								see enum and structure in BDDITypes.h
	 */
	BDDIReturn BDDI::BDDIConvertStringToParameterValue(BDDIParValue *ReturnValue, BDDIParInfo *ParInfo, const char *Value)
	{
		char hw_TempValue = 0;
		short w_TempValue = 0;
		int dw_TempValue = 0;
		long long lw_TempValue = 0;
		UINT8 hw_TempValueU = 0;
		UINT16 w_TempValueU = 0;
		UINT32 dw_TempValueU = 0;
		UINT64 lw_TempValueU = 0;
		float f_TempValue = 0;
		double df_TempValue = 0; 
		
		switch(ParInfo->Type)
		{

			case BDDIParTypeINT:
				if(ParInfo->Bitswide == 8)	{
					hw_TempValue = (char)strtol(Value, NULL, 10);
					ReturnValue->hw_Value = hw_TempValue;
					ReturnValue->Offset = BDDISelectParBIT8;
				}
				else if(ParInfo->Bitswide == 16)	{
					w_TempValue = (short)strtol(Value, NULL, 10);
					ReturnValue->w_Value = w_TempValue;
					ReturnValue->Offset = BDDISelectParBIT16;
				}
				else if(ParInfo->Bitswide == 32)	{
					dw_TempValue = (int)strtol(Value, NULL, 10);
					ReturnValue->dw_Value = dw_TempValue;
					ReturnValue->Offset = BDDISelectParBIT32;
				}
				else if(ParInfo->Bitswide == 64)	{
					lw_TempValue = strtoll(Value, NULL, 10);
					ReturnValue->lw_Value = lw_TempValue;
					ReturnValue->Offset = BDDISelectParBIT64;
				}
				else	{
					return BDDIStatusError;
				}
							
			break;

			case BDDIParTypeUINT:
				if(Value[0] == '0' &&
					((Value[1] == 'X') ||
						(Value[1] == 'x')))	{
					if(ParInfo->Bitswide == 8)	{
						hw_TempValueU = (UINT8)strtoul(Value, NULL, 16);
						ReturnValue->hw_ValueU = hw_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT8U;
					}
					else if(ParInfo->Bitswide == 16)	{
						w_TempValueU = (UINT16)strtoul(Value, NULL, 16);
						ReturnValue->w_ValueU = w_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT16U;
					}
					else if(ParInfo->Bitswide == 32)	{
						dw_TempValueU = (UINT32)strtoul(Value, NULL, 16);
						ReturnValue->dw_ValueU = dw_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT32U;
					}
					else if(ParInfo->Bitswide == 64)	{
						lw_TempValueU = strtoull(Value, NULL, 16);
						ReturnValue->lw_ValueU = lw_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT64U;
					}
					else	{
						return BDDIStatusError;
					}
				}
				else {
					if(ParInfo->Bitswide == 8)	{
						hw_TempValueU = (UINT8)strtoul(Value, NULL, 10);
						ReturnValue->hw_ValueU = hw_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT8U;
					}
					else if(ParInfo->Bitswide == 16)	{
						w_TempValueU = (UINT16)strtoul(Value, NULL, 10);
						ReturnValue->w_ValueU = w_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT16U;
					}
					else if(ParInfo->Bitswide == 32)	{
						dw_TempValueU = (UINT32)strtoul(Value, NULL, 10);
						ReturnValue->dw_ValueU = dw_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT32U;
					}
					else if(ParInfo->Bitswide == 64)	{
						lw_TempValueU = strtoull(Value, NULL, 10);
						ReturnValue->lw_ValueU = lw_TempValueU;
						ReturnValue->Offset = BDDISelectParBIT64U;
					}
					else	{
						return BDDIStatusError;
					}
				}

				break;

			case BDDIParTypeBOOL:
				if((strcmp(Value, "false") == 0) || (strcmp(Value, "0") == 0))	{
					ReturnValue->b_Value = false;
					ReturnValue->Offset = BDDISelectParBOOL;
				}
				else	{
					ReturnValue->b_Value = true;
					ReturnValue->Offset = BDDISelectParBOOL;
				} 

				break;

			case BDDIParTypeFLOAT:
				if(ParInfo->Bitswide == 32)	{
					f_TempValue = (float)strtod(Value, NULL);
					ReturnValue->f_Value = f_TempValue;
					ReturnValue->Offset = BDDISelectParFLOAT;
				}
				else if(ParInfo->Bitswide == 64)	{
					df_TempValue = strtod(Value, NULL);
					ReturnValue->df_Value = df_TempValue;
					ReturnValue->Offset = BDDISelectParDOUBLE;
				}
				else	{
					return BDDIStatusError;
				}

				break;

			case BDDIParTypeSTRING:	return BDDIStatusCmdNotSupported;
			case BDDIParTypeMax:	return BDDIStatusError;
			default:	return BDDIStatusError;
		}

		return BDDIStatusOK;
	}

	/*
	 * function			: BDDIConvertParameterValueToString
	 * design				: Convert Parameter Value to String Value
	 * description	: this function convert the current value of parameter in each module
	 *								to string data which is set by user input 
	 * param				: ReturnValue - this parameter is set the converting value
	 *															by checking structure of BDDIParInfo 
	 *								ParInfo			-	this parameter is the information of parameter in each module
	 *								Value				- this parameter is the string data which is send to user
	 * return				: this function return status of success or failure
	 * caller				: BDDIGetParameterValues
	 * see					: if you want to know more information
	 *								see enum and structure in BDDITypes.h
	 */
	BDDIReturn BDDI::BDDIConvertParameterValueToString(BDDIParValue *ReturnValue, char *Value)
	{

		switch(ReturnValue->Offset)
		{

			case BDDISelectParBOOL:
				if(ReturnValue->b_Value)	strcpy(Value, "true");
				else											strcpy(Value, "false");

				break;
			
			case BDDISelectParBIT8:			sprintf(Value, "%d", ReturnValue->hw_Value);		break;
			case BDDISelectParBIT16:		sprintf(Value, "%d", ReturnValue->w_Value);			break;
			case BDDISelectParBIT32:		sprintf(Value, "%d", ReturnValue->dw_Value);		break;
			case BDDISelectParBIT64:		sprintf(Value, "%lld", ReturnValue->lw_Value);	break;
			case BDDISelectParBIT8U:		sprintf(Value, "%u", ReturnValue->hw_ValueU);		break;
			case BDDISelectParBIT16U:		sprintf(Value, "%u", ReturnValue->w_ValueU);		break;
			case BDDISelectParBIT32U:		sprintf(Value, "%u", ReturnValue->dw_ValueU);		break;
			case BDDISelectParBIT64U:		sprintf(Value, "%llu", ReturnValue->lw_ValueU);	break;
			case BDDISelectParFLOAT:		sprintf(Value, "%f", ReturnValue->f_Value);			break;
			case BDDISelectParDOUBLE:		sprintf(Value, "%f", ReturnValue->df_Value);		break;
			case BDDISelectParSTRING:		return BDDIStatusCmdNotSupported;
			case BDDISelectParMax:			return BDDIStatusError;
		}

		return BDDIStatusOK;
	}

	void BDDI::BDDIGenerateMemoryViewJsonFile(unsigned int Address, unsigned int Value)
	{
		memset(a_ChangeAddr, 0, sizeof(a_ChangeAddr));
		memset(a_ChangeValue, 0, sizeof(a_ChangeValue));

		sprintf(a_ChangeAddr, "0x%08x", Address);
		sprintf(a_ChangeValue, "0x%08x", Value);

		Change["address"] = a_ChangeAddr;
		Change["value"] = a_ChangeValue;
		ChangeList[dw_JsonIndex++] = Change;

		Change.clear();
	}

	void BDDI::BDDISetModuleInstanceName(const char* Name)
	{
		memset(a_InstanceName, 0, sizeof(a_InstanceName));
		strcpy(a_InstanceName, Name);

		InstanceName["instance_name"] = a_InstanceName;
	}

	BDDI::BDDI()
	{
		InstanceName.clear();
		Change.clear();
		ChangeList.clear();

		dw_JsonIndex = 0;
	}
}
