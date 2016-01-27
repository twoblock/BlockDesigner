#include "AHB_Lite_BDDI.h"
#include "AHB_Lite.h"

BDDIRegInfo ast_AHB_LiteRegInfo[] = 
{
};

BDDIParInfo ast_AHB_LiteParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_AHB_LiteRegInfo) / sizeof(ast_AHB_LiteRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_AHB_LiteParInfo) / sizeof(ast_AHB_LiteParInfo[0]);

AHB_Lite_BDDI::AHB_Lite_BDDI(AHB_Lite *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_AHB_LiteRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_AHB_LiteRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_AHB_LiteRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_AHB_LiteParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_AHB_LiteParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_AHB_LiteParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);

		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

AHB_Lite_BDDI::~AHB_Lite_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn AHB_Lite_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn AHB_Lite_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn AHB_Lite_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn AHB_Lite_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

char* AHB_Lite_BDDI::BDDIGetModuleType()
{
	return (char*)"bus";
}

BDDIRegInfo* AHB_Lite_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* AHB_Lite_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int AHB_Lite_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int AHB_Lite_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
