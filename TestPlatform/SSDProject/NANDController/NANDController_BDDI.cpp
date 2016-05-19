#include "NANDController_BDDI.h"
#include "NANDController.h"

BDDIRegInfo ast_ConsoleRegInfo[] = 
{
	{"r_MON_CHABANKIDLE", 32, BDDIRegTypeUINT}
};

BDDIParInfo ast_ConsoleParInfo[] = 
{
	{"p_addr_base", 32, BDDIParTypeUINT, ""},
	{"p_addr_size", 32, BDDIParTypeUINT, ""},
	{"p_Data_Bit_Width", 32, BDDIParTypeINT, ""},
};

static const UINT32 dw_RegCnt = sizeof(ast_ConsoleRegInfo) / sizeof(ast_ConsoleRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_ConsoleParInfo) / sizeof(ast_ConsoleParInfo[0]);

NANDController_BDDI::NANDController_BDDI(NANDController *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_ConsoleRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_ConsoleRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_ConsoleRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_ConsoleParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_ConsoleParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_ConsoleParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);

		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

NANDController_BDDI::~NANDController_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn NANDController_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	UINT32 dw_Temp;

	switch(RegIndex)
	{
		case 0:
			dw_Temp = p_Target->m_regs[0x7A4/4];
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &dw_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	

	}
	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn NANDController_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	UINT32 dw_Temp;

	switch(RegIndex)
	{
		case 0:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &dw_Temp);
			p_Target->m_regs[0x7A4/4] = dw_Temp;

			break;

		default:	return BDDIStatusError;	

	}
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn NANDController_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	int dw_Temp;
	UINT32 dw_TempU;

	switch(ParIndex)
	{
		case 0:
			dw_TempU = p_Target->p_addr_base;
			BDDIPutInParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			dw_TempU = p_Target->p_addr_size;
			BDDIPutInParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 2:
			dw_Temp = p_Target->p_Data_Bit_Width;
			BDDIPutInParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], &dw_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn NANDController_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	int dw_Temp;
	UINT32 dw_TempU;

	switch(ParIndex)
	{
		case 0:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_addr_base = dw_TempU;

			break;

		case 1:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->p_addr_size = dw_TempU;

			break;

		case 2:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_Temp);
			p_Target->p_Data_Bit_Width = dw_Temp;

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

char* NANDController_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* NANDController_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* NANDController_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int NANDController_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int NANDController_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
