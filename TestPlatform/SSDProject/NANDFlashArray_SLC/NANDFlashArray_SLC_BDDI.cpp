#include "NANDFlashArray_SLC_BDDI.h"
#include "NANDFlashArray_SLC.h"

BDDIRegInfo ast_NANDFlashArray_SLCRegInfo[] = 
{
	{"r_DataReg", 16, BDDIRegTypeUINT},
	{"r_CmdReg", 16, BDDIRegTypeUINT},
	{"r_C_AddrReg", 16, BDDIRegTypeUINT},
	{"r_P_AddrReg", 16, BDDIRegTypeUINT},
	{"r_B_AddrReg", 16, BDDIRegTypeUINT},
	{"r_StatusReg", 16, BDDIRegTypeUINT}
};

BDDIParInfo ast_NANDFlashArray_SLCParInfo[] = 
{
	{"p_ALE", 32, BDDIParTypeUINT, ""},
	{"p_CEn", 32, BDDIParTypeUINT, ""},
	{"p_CLE", 32, BDDIParTypeUINT, ""},
	{"p_RBn", 32, BDDIParTypeUINT, ""},
	{"p_REn", 32, BDDIParTypeUINT, ""},
	{"p_WEn", 32, BDDIParTypeUINT, ""},
	{"p_WPn", 32, BDDIParTypeUINT, ""},
	{"p_tADL", 32, BDDIParTypeUINT, ""},
	{"p_tBERS", 32, BDDIParTypeUINT, ""},
	{"p_tPROG", 32, BDDIParTypeUINT, ""},
	{"p_tR", 32, BDDIParTypeUINT, ""},
	{"p_tRC", 32, BDDIParTypeUINT, ""},
	{"p_tRR", 32, BDDIParTypeUINT, ""},
	{"p_tWB", 32, BDDIParTypeUINT, ""},
	{"p_tWC", 32, BDDIParTypeUINT, ""}
};

static const UINT32 dw_RegCnt = sizeof(ast_NANDFlashArray_SLCRegInfo) / sizeof(ast_NANDFlashArray_SLCRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_NANDFlashArray_SLCParInfo) / sizeof(ast_NANDFlashArray_SLCParInfo[0]);

NANDFlashArray_SLC_BDDI::NANDFlashArray_SLC_BDDI(NANDFlashArray_SLC *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_NANDFlashArray_SLCRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_NANDFlashArray_SLCRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_NANDFlashArray_SLCRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_NANDFlashArray_SLCParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_NANDFlashArray_SLCParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_NANDFlashArray_SLCParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);

		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

NANDFlashArray_SLC_BDDI::~NANDFlashArray_SLC_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn NANDFlashArray_SLC_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	UINT16 w_Temp;

	switch(RegIndex)
	{
		case 0:
			w_Temp = p_Target->r_DataReg;
			BDDIPutInRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], &w_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			w_Temp = p_Target->r_CmdReg;
			BDDIPutInRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], &w_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 2:
			w_Temp = p_Target->r_C_AddrReg;
			BDDIPutInRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], &w_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 3:
			w_Temp = p_Target->r_P_AddrReg;
			BDDIPutInRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], &w_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 4:
			w_Temp = p_Target->r_B_AddrReg;
			BDDIPutInRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], &w_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 5:
			w_Temp = p_Target->r_StatusReg;
			BDDIPutInRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], &w_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn NANDFlashArray_SLC_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	UINT16 w_Temp;

	switch(RegIndex)
	{
		case 0:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &w_Temp);
			p_Target->r_DataReg = w_Temp;

			break;

		case 1:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &w_Temp);
			p_Target->r_CmdReg = w_Temp;

			break;

		case 2:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &w_Temp);
			p_Target->r_C_AddrReg = w_Temp;

			break;

		case 3:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &w_Temp);
			p_Target->r_P_AddrReg = w_Temp;

			break;

		case 4:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &w_Temp);
			p_Target->r_B_AddrReg = w_Temp;

			break;

		case 5:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_NANDFlashArray_SLCRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &w_Temp);
			p_Target->r_StatusReg = w_Temp;

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn NANDFlashArray_SLC_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	UINT32 dw_TempU;

	switch(ParIndex)
	{
		case 0:
			dw_TempU = p_Target->p_ALE;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			dw_TempU = p_Target->p_CEn;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 2:
			dw_TempU = p_Target->p_CLE;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 3:
			dw_TempU = p_Target->p_RBn;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 4:
			dw_TempU = p_Target->p_REn;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 5:
			dw_TempU = p_Target->p_WEn;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 6:
			dw_TempU = p_Target->p_WPn;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 7:
			dw_TempU = p_Target->p_tADL;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 8:
			dw_TempU = p_Target->p_tBERS;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 9:
			dw_TempU = p_Target->p_tPROG;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 10:
			dw_TempU = p_Target->p_tR;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 11:
			dw_TempU = p_Target->p_tRC;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 12:
			dw_TempU = p_Target->p_tRR;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 13:
			dw_TempU = p_Target->p_tWB;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 14:
			dw_TempU = p_Target->p_tWC;
			BDDIPutInParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn NANDFlashArray_SLC_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	UINT32 dw_TempU;

	switch(ParIndex)
	{
		case 0:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_ALE = dw_TempU;

			break;

		case 1:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_CEn = dw_TempU;

			break;

		case 2:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_CLE = dw_TempU;

			break;

		case 3:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_RBn = dw_TempU;

			break;

		case 4:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_REn = dw_TempU;

			break;

		case 5:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_WEn = dw_TempU;

			break;

		case 6:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_WPn = dw_TempU;

			break;

		case 7:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tADL = dw_TempU;

			break;

		case 8:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tBERS = dw_TempU;

			break;

		case 9:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tPROG = dw_TempU;

			break;

		case 10:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tR = dw_TempU;

			break;

		case 11:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tRC = dw_TempU;

			break;

		case 12:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tRR = dw_TempU;

			break;

		case 13:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tWB = dw_TempU;

			break;

		case 14:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_NANDFlashArray_SLCParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_tWC = dw_TempU;

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

char* NANDFlashArray_SLC_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* NANDFlashArray_SLC_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* NANDFlashArray_SLC_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int NANDFlashArray_SLC_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int NANDFlashArray_SLC_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
