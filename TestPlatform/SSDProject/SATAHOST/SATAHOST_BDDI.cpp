#include "SATAHOST_BDDI.h"
#include "SATAHOST.h"

BDDIRegInfo ast_SataHostRegInfo[] = 
{
};

BDDIParInfo ast_SataHostParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_SataHostRegInfo) / sizeof(ast_SataHostRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_SataHostParInfo) / sizeof(ast_SataHostParInfo[0]);

SATAHOST_BDDI::SATAHOST_BDDI(SATAHOST *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_SataHostRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_SataHostRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_SataHostRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_SataHostParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_SataHostParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_SataHostParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);
	
		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

SATAHOST_BDDI::~SATAHOST_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn SATAHOST_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;
	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn SATAHOST_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn SATAHOST_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn SATAHOST_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;
	return BDDIStatusOK;
}

char* SATAHOST_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* SATAHOST_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* SATAHOST_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int SATAHOST_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int SATAHOST_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
