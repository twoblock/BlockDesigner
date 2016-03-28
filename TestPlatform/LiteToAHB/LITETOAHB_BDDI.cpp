#include "LITETOAHB_BDDI.h"
#include "LITETOAHB.h"

BDDIRegInfo ast_AHBRegInfo[] = 
{
};

BDDIParInfo ast_AHBParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_AHBRegInfo) / sizeof(ast_AHBRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_AHBParInfo) / sizeof(ast_AHBParInfo[0]);

LITETOAHB_BDDI::LITETOAHB_BDDI(LITETOAHB *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_AHBRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_AHBRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_AHBRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_AHBParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_AHBParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_AHBParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);

		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

LITETOAHB_BDDI::~LITETOAHB_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn LITETOAHB_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn LITETOAHB_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn LITETOAHB_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn LITETOAHB_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

char* LITETOAHB_BDDI::BDDIGetModuleType()
{
	return (char*)"bus";
}

BDDIRegInfo* LITETOAHB_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* LITETOAHB_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int LITETOAHB_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int LITETOAHB_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
