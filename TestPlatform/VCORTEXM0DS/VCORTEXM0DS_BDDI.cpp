#include "VCORTEXM0DS_BDDI.h"
#include "VCORTEXM0DS.h"

BDDIRegInfo ast_VCORTEXM0DSRegInfo[] = 
{
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

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn VCORTEXM0DS_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

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
