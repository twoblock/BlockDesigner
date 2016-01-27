#include "tb_BDDI.h"
#include "tb.h"

BDDIRegInfo ast_TBRegInfo[] = 
{
};

BDDIParInfo ast_TBParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_TBRegInfo) / sizeof(ast_TBRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_TBParInfo) / sizeof(ast_TBParInfo[0]);

TB_BDDI::TB_BDDI(TB *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_TBRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_TBRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_TBRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_TBParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_TBParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_TBParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);

		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

TB_BDDI::~TB_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn TB_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn TB_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn TB_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn TB_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

char* TB_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* TB_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* TB_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int TB_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int TB_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
