#include "VCORTEXM0DS_BDDI.h"
#include "VCORTEXM0DS.h"

BDDIRegInfo ast_VCORTEXM0DSRegInfo[] = 
{
	{"v__DOT__cm0_r00", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r01", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r02", 32, BDDIRegTypeHEX}, 
	{"v__DOT__cm0_r03", 32, BDDIRegTypeHEX}, 
	{"v__DOT__cm0_r04", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r05", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r06", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r07", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r08", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r09", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r10", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r11", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r12", 32, BDDIRegTypeHEX},
	{"v__DOT__cm0_r14", 32, BDDIRegTypeHEX},
	{"v__DOT__vis_msp", 32, BDDIRegTypeHEX},
	{"v__DOT__vis_psp", 32, BDDIRegTypeHEX},
	{"v__DOT__vis_pc", 32, BDDIRegTypeHEX}
};

BDDIParInfo ast_VCORTEXM0DSParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_VCORTEXM0DSRegInfo) / sizeof(ast_VCORTEXM0DSRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_VCORTEXM0DSParInfo) / sizeof(ast_VCORTEXM0DSParInfo[0]);

VCORTEXM0DS_BDDI::VCORTEXM0DS_BDDI(VCORTEXM0DS *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_VCORTEXM0DSRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_VCORTEXM0DSRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_VCORTEXM0DSRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_VCORTEXM0DSParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_VCORTEXM0DSParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_VCORTEXM0DSParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);

		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

VCORTEXM0DS_BDDI::~VCORTEXM0DS_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn VCORTEXM0DS_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	UINT32 h_Temp;

	switch(RegIndex)
	{
		case 0:
			h_Temp = p_Target->v__DOT__cm0_r00;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			h_Temp = p_Target->v__DOT__cm0_r01;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 2:
			h_Temp = p_Target->v__DOT__cm0_r02;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 3:
			h_Temp = p_Target->v__DOT__cm0_r03;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 4:
			h_Temp = p_Target->v__DOT__cm0_r04;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 5:
			h_Temp = p_Target->v__DOT__cm0_r05;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 6:
			h_Temp = p_Target->v__DOT__cm0_r06;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 7:
			h_Temp = p_Target->v__DOT__cm0_r07;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 8:
			h_Temp = p_Target->v__DOT__cm0_r08;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 9:
			h_Temp = p_Target->v__DOT__cm0_r09;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 10:
			h_Temp = p_Target->v__DOT__cm0_r10;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 11:
			h_Temp = p_Target->v__DOT__cm0_r11;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 12:
			h_Temp = p_Target->v__DOT__cm0_r12;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 13:
			h_Temp = p_Target->v__DOT__cm0_r14;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 14:
			h_Temp = p_Target->v__DOT__vis_msp;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 15:
			h_Temp = p_Target->v__DOT__vis_psp;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 16:
			h_Temp = p_Target->v__DOT__vis_pc;
			BDDIPutInRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn VCORTEXM0DS_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	UINT32 h_Temp;

	switch(RegIndex)
	{
		case 0:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r00 = h_Temp;

			break;

		case 1:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r01 = h_Temp;

			break;

		case 2:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r02 = h_Temp;

			break;

		case 3:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r03 = h_Temp;

			break;

		case 4:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r04 = h_Temp;

			break;

		case 5:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r05 = h_Temp;

			break;

		case 6:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r06 = h_Temp;

			break;

		case 7:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r07 = h_Temp;

			break;

		case 8:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r08 = h_Temp;

			break;

		case 9:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r09 = h_Temp;

			break;

		case 10:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r10 = h_Temp;

			break;

		case 11:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r11 = h_Temp;

			break;

		case 12:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r12 = h_Temp;

			break;

		case 13:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__cm0_r14 = h_Temp;

			break;

		case 14:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__vis_msp = h_Temp;

			break;

		case 15:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__vis_psp = h_Temp;

			break;

		case 16:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_VCORTEXM0DSRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->v__DOT__vis_pc = h_Temp;

			break;

		default:	return BDDIStatusError;	

	}	

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn VCORTEXM0DS_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn VCORTEXM0DS_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

char* VCORTEXM0DS_BDDI::BDDIGetModuleType()
{
	return (char*)"cpu";
}

BDDIRegInfo* VCORTEXM0DS_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* VCORTEXM0DS_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int VCORTEXM0DS_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int VCORTEXM0DS_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
