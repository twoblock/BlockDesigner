#include "ahbl2mem_BDDI.h"
#include "ahbl2mem.h"

BDDIRegInfo ast_AHBL2MEMRegInfo[] = 
{
};

BDDIParInfo ast_AHBL2MEMParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_AHBL2MEMRegInfo) / sizeof(ast_AHBL2MEMRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_AHBL2MEMParInfo) / sizeof(ast_AHBL2MEMParInfo[0]);

AHBL2MEM_BDDI::AHBL2MEM_BDDI(AHBL2MEM *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_AHBL2MEMRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_AHBL2MEMRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_AHBL2MEMRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_AHBL2MEMParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_AHBL2MEMParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_AHBL2MEMParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);

		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

AHBL2MEM_BDDI::~AHBL2MEM_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn AHBL2MEM_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn AHBL2MEM_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn AHBL2MEM_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn AHBL2MEM_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	return BDDIStatusOK;
}

char* AHBL2MEM_BDDI::BDDIGetModuleType()
{
	return (char*)"mem";
}

BDDIRegInfo* AHBL2MEM_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* AHBL2MEM_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int AHBL2MEM_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int AHBL2MEM_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
