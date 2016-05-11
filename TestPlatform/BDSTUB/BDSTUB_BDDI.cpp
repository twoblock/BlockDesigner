#include "BDSTUB_BDDI.h"
#include "BDSTUB.h"

BDDIRegInfo ast_BDSTUBRegInfo[] = 
{
	{"hw_reg", 8, BDDIRegTypeUINT},
	{"w_reg", 16, BDDIRegTypeUINT},
	{"dw_reg", 32, BDDIRegTypeUINT},
	{"lw_reg", 64, BDDIRegTypeUINT},
	{"b_reg", 8, BDDIRegTypeBOOL},
	{"h_reg", 32, BDDIRegTypeHEX},
	{"f_reg", 32, BDDIRegTypeFLOAT},
	{"df_reg", 64, BDDIRegTypeFLOAT},
	{"a_reg", 8, BDDIRegTypeSTRING}
};

BDDIParInfo ast_BDSTUBParInfo[] = 
{
	{"hw_par", 8, BDDIParTypeINT, ""},
	{"w_par", 16, BDDIParTypeINT, ""},
	{"dw_par", 32, BDDIParTypeINT, ""},
	{"lw_par", 64, BDDIParTypeINT, ""},
	{"b_par", 8, BDDIParTypeBOOL, ""},
	{"dw_paru", 32, BDDIParTypeUINT, ""},
	{"f_par", 32, BDDIParTypeFLOAT, ""},
	{"df_par", 64, BDDIParTypeFLOAT, ""},
	{"a_par", 8, BDDIParTypeSTRING, ""}
};

static const UINT32 dw_RegCnt = sizeof(ast_BDSTUBRegInfo) / sizeof(ast_BDSTUBRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_BDSTUBParInfo) / sizeof(ast_BDSTUBParInfo[0]);

BDSTUB_BDDI::BDSTUB_BDDI(BDSTUB *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_BDSTUBRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_BDSTUBRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_BDSTUBRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_BDSTUBParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_BDSTUBParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_BDSTUBParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);
	
		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

BDSTUB_BDDI::~BDSTUB_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn BDSTUB_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	UINT8 hw_Temp;
	UINT16 w_Temp;
	UINT32 dw_Temp;
	UINT64 lw_Temp;
	bool b_Temp;
	UINT32 h_Temp;
	float f_Temp;
	double df_Temp;
	char a_Temp[128];

	switch(RegIndex)
	{
		case 0:
			hw_Temp = p_Target->hw_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &hw_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			w_Temp = p_Target->w_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &w_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 2:
			dw_Temp = p_Target->dw_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &dw_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 3:
			lw_Temp = p_Target->lw_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &lw_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 4:
			b_Temp = p_Target->b_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &b_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 5:
			h_Temp = p_Target->h_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &h_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 6:
			f_Temp = p_Target->f_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &f_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 7:
			df_Temp = p_Target->df_reg;
			BDDIPutInRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], &df_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		case 8:
			strcpy(a_Temp, p_Target->a_reg);
			strcpy(OutValue, a_Temp);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn BDSTUB_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	UINT8 hw_Temp;
	UINT16 w_Temp;
	UINT32 dw_Temp;
	UINT64 lw_Temp;
	bool b_Temp;
	UINT32 h_Temp;
	float f_Temp;
	double df_Temp;
	char a_Temp[128];

	switch(RegIndex)
	{
		case 0:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &hw_Temp);
			p_Target->hw_reg = hw_Temp;

			break;

		case 1:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &w_Temp);
			p_Target->w_reg = w_Temp;

			break;

		case 2:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &dw_Temp);
			p_Target->dw_reg = dw_Temp;

			break;

		case 3:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &lw_Temp);
			p_Target->lw_reg = lw_Temp;

			break;

		case 4:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &b_Temp);
			p_Target->b_reg = b_Temp;

			break;

		case 5:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &h_Temp);
			p_Target->h_reg = h_Temp;

			break;

		case 6:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &f_Temp);
			p_Target->f_reg = f_Temp;

			break;

		case 7:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BDSTUBRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &df_Temp);
			p_Target->df_reg = df_Temp;

			break;

		case 8:
			strcpy(a_Temp, SetValue);
			strcpy(p_Target->a_reg, a_Temp);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn BDSTUB_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	char hw_Temp;
	short w_Temp;
	int dw_Temp;
	long long lw_Temp;
	bool b_Temp;
	UINT32 dw_TempU;
	float f_Temp;
	double df_Temp;
	char a_Temp[128];

	switch(ParIndex)
	{
		case 0:
			hw_Temp = p_Target->hw_par;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &hw_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 1:
			w_Temp = p_Target->w_par;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &w_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 2:
			dw_Temp = p_Target->dw_par;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &dw_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 3:
			lw_Temp = p_Target->lw_par;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &lw_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 4:
			b_Temp = p_Target->b_par;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &b_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 5:
			dw_TempU = p_Target->dw_paru;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 6:
			f_Temp = p_Target->f_par;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &f_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 7:
			df_Temp = p_Target->df_par;
			BDDIPutInParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], &df_Temp);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		case 8:
			strcpy(a_Temp, p_Target->a_par);
			strcpy(OutValue, a_Temp);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn BDSTUB_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	UINT8 hw_Temp;
	UINT16 w_Temp;
	UINT32 dw_Temp;
	UINT64 lw_Temp;
	bool b_Temp;
	UINT32 dw_TempU;
	float f_Temp;
	double df_Temp;
	char a_Temp[128];

	switch(ParIndex)
	{
		case 0:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &hw_Temp);
			p_Target->hw_par = hw_Temp;

			break;

		case 1:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &w_Temp);
			p_Target->w_par = w_Temp;

			break;

		case 2:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_Temp);
			p_Target->dw_par = dw_Temp;

			break;

		case 3:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &lw_Temp);
			p_Target->lw_par = lw_Temp;

			break;

		case 4:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &b_Temp);
			p_Target->b_par = b_Temp;

			break;

		case 5:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->dw_paru = dw_TempU;

			break;

		case 6:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &f_Temp);
			p_Target->f_par = f_Temp;

			break;

		case 7:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_BDSTUBParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &df_Temp);
			p_Target->df_par = df_Temp;

			break;

		case 8:
			strcpy(a_Temp, SetValue);
			strcpy(p_Target->a_par, a_Temp);

			break;

		default:	return BDDIStatusError;	

	}

	return BDDIStatusOK;
}

char* BDSTUB_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* BDSTUB_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* BDSTUB_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int BDSTUB_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int BDSTUB_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
