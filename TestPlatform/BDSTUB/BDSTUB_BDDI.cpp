#include "BDSTUB_BDDI.h"
#include "BDSTUB.h"

BDDIRegInfo ast_BDSTUBRegInfo[] = 
{
};

BDDIParInfo ast_BDSTUBParInfo[] = 
{
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
	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn BDSTUB_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn BDSTUB_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn BDSTUB_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
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
