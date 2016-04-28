#include "MemoryUtility_BDDI.h"
#include "MemoryUtility.h"

BDDIRegInfo ast_ConsoleRegInfo[] = 
{
	{"MU_SRC_ADDR", 32, BDDIRegTypeUINT},
	{"MU_DST_ADDR", 32, BDDIRegTypeUINT},
	{"MU_VALUE", 32, BDDIRegTypeUINT},
	{"MU_SIZE", 32, BDDIRegTypeUINT},
	{"MU_RESULT", 32, BDDIRegTypeUINT},
	{"MU_CMD", 32, BDDIRegTypeUINT},
	{"MU_UNITSTEP", 32, BDDIRegTypeUINT}
};

BDDIParInfo ast_ConsoleParInfo[] = 
{
	{"p_Base_Addr", 32, BDDIParTypeINT, ""},
	{"p_Addr_Size", 32, BDDIParTypeINT, ""}
};

static const UINT32 dw_RegCnt = sizeof(ast_ConsoleRegInfo) / sizeof(ast_ConsoleRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_ConsoleParInfo) / sizeof(ast_ConsoleParInfo[0]);

MemoryUtility_BDDI::MemoryUtility_BDDI(MemoryUtility *c) : p_Target(c)
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

MemoryUtility_BDDI::~MemoryUtility_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn MemoryUtility_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	uint32_t r_MU_SRC_ADDR_temp;
	uint32_t r_MU_DST_ADDR_temp;
	uint32_t r_MU_VALUE_temp;
	uint32_t r_MU_SIZE_temp;
	uint32_t r_MU_RESULT_temp;
	uint32_t r_MU_CMD_temp;
	uint32_t r_MU_UNITSTEP_temp;

	switch(RegIndex)
	{
		case 0:
			r_MU_SRC_ADDR_temp = p_Target->r_MU_SRC_ADDR;
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &r_MU_SRC_ADDR_temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			r_MU_DST_ADDR_temp = p_Target->r_MU_DST_ADDR;
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &r_MU_DST_ADDR_temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 2:
			r_MU_VALUE_temp = p_Target->r_MU_VALUE;
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &r_MU_VALUE_temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 3:
			r_MU_SIZE_temp = p_Target->r_MU_SIZE;
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &r_MU_SIZE_temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 4:
			r_MU_RESULT_temp = p_Target->r_MU_RESULT;
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &r_MU_RESULT_temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 5:
			r_MU_CMD_temp = p_Target->r_MU_CMD;
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &r_MU_CMD_temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 6:
			r_MU_UNITSTEP_temp = p_Target->r_MU_UNITSTEP;
			BDDIPutInRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], &r_MU_UNITSTEP_temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn MemoryUtility_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	uint32_t r_MU_SRC_ADDR_temp;
	uint32_t r_MU_DST_ADDR_temp;
	uint32_t r_MU_VALUE_temp;
	uint32_t r_MU_SIZE_temp;
	uint32_t r_MU_RESULT_temp;
	uint32_t r_MU_CMD_temp;
	uint32_t r_MU_UNITSTEP_temp;

	switch(RegIndex)
	{
		case 0:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &r_MU_SRC_ADDR_temp);
			p_Target->r_MU_SRC_ADDR = r_MU_SRC_ADDR_temp;

			break;

		case 1:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &r_MU_DST_ADDR_temp);
			p_Target->r_MU_DST_ADDR = r_MU_DST_ADDR_temp;

			break;

		case 2:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &r_MU_VALUE_temp);
			p_Target->r_MU_VALUE = r_MU_VALUE_temp;

			break;
		case 3:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &r_MU_SIZE_temp);
			p_Target->r_MU_SIZE = r_MU_SIZE_temp;

			break;
		case 4:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &r_MU_RESULT_temp);
			p_Target->r_MU_RESULT = r_MU_RESULT_temp;

			break;
		case 5:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &r_MU_CMD_temp);
			p_Target->r_MU_CMD = r_MU_CMD_temp;

			break;
		case 6:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_ConsoleRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &r_MU_UNITSTEP_temp);
			p_Target->r_MU_UNITSTEP = r_MU_UNITSTEP_temp;

			break;

		default:	return BDDIStatusError;	
	}
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn MemoryUtility_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	uint32_t p_Base_Addr_temp;
	uint32_t p_Addr_Size_temp;

	switch(ParIndex)
	{
		case 0:
			p_Base_Addr_temp = p_Target->p_Base_Addr;
			BDDIPutInParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], &p_Base_Addr_temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			p_Addr_Size_temp = p_Target->p_Addr_Size;
			BDDIPutInParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], &p_Addr_Size_temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	
	}
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn MemoryUtility_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	uint32_t p_Base_Addr_temp;
	uint32_t p_Addr_Size_temp;

	switch(ParIndex)
	{
		case 0:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &p_Base_Addr_temp);
			p_Target->p_Base_Addr = p_Base_Addr_temp;

			break;

		case 1:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_ConsoleParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &p_Addr_Size_temp);
			p_Target->p_Addr_Size = p_Addr_Size_temp;

			break;

		default:	return BDDIStatusError;	
	}
	return BDDIStatusOK;
}

char* MemoryUtility_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* MemoryUtility_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* MemoryUtility_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int MemoryUtility_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int MemoryUtility_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
