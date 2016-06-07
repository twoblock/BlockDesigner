#include "BufferManager_BDDI.h"
#include "BufferManager.h"

BDDIRegInfo ast_BufferManagerRegInfo[] = 
{
	{"r_BM_WRITE_LIMIT", 32, BDDIRegTypeUINT}	
};

BDDIParInfo ast_BufferManagerParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_BufferManagerRegInfo) / sizeof(ast_BufferManagerRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_BufferManagerParInfo) / sizeof(ast_BufferManagerParInfo[0]);

BufferManager_BDDI::BufferManager_BDDI(BufferManager *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_BufferManagerRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_BufferManagerRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_BufferManagerRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_BufferManagerParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_BufferManagerParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_BufferManagerParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);
	
		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

BufferManager_BDDI::~BufferManager_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn BufferManager_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;

	UINT32 dw_Temp;

	switch(RegIndex)
	{
		case 0:
			dw_Temp = p_Target->r_BM_WRITE_LIMIT;
			BDDIPutInRegisterValue(&st_Temp, &ast_BufferManagerRegInfo[RegIndex], &dw_Temp);
			BDDIConvertRegisterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;	

	}
	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn BufferManager_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;

	UINT32 dw_Temp;

	switch(RegIndex)
	{
		case 0:
			BDDIConvertStringToRegisterValue(&st_Temp, &ast_BufferManagerRegInfo[RegIndex], SetValue);
			BDDIExtractRegisterValue(&st_Temp, &dw_Temp);
			p_Target->r_BM_WRITE_LIMIT = dw_Temp;

			break;

		default:	return BDDIStatusError;	

	}
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn BufferManager_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn BufferManager_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;
	return BDDIStatusOK;
}

char* BufferManager_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* BufferManager_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* BufferManager_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int BufferManager_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int BufferManager_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
