#include "SATADevice_BDDI.h"
#include "SATADevice.h"

BDDIRegInfo ast_SataDeviceRegInfo[] = 
{
};

BDDIParInfo ast_SataDeviceParInfo[] = 
{
};

static const UINT32 dw_RegCnt = sizeof(ast_SataDeviceRegInfo) / sizeof(ast_SataDeviceRegInfo[0]);
static const UINT32 dw_ParCnt = sizeof(ast_SataDeviceParInfo) / sizeof(ast_SataDeviceParInfo[0]);

SATADevice_BDDI::SATADevice_BDDI(SATADevice *c) : p_Target(c)
{
	UINT32 dw_Index = 0;
	char a_Temp[BDDI_STRING_SIZE];

	pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];
	pst_OutParInfo = new BDDIParInfo[dw_ParCnt];

	for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++)	{
		strcpy(pst_OutRegInfo[dw_Index].Name,					ast_SataDeviceRegInfo[dw_Index].Name);
		pst_OutRegInfo[dw_Index].Bitswide						= ast_SataDeviceRegInfo[dw_Index].Bitswide;
		pst_OutRegInfo[dw_Index].Type								= ast_SataDeviceRegInfo[dw_Index].Type;
	}

	for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++)	{
		strcpy(pst_OutParInfo[dw_Index].Name,					ast_SataDeviceParInfo[dw_Index].Name);
		pst_OutParInfo[dw_Index].Bitswide						= ast_SataDeviceParInfo[dw_Index].Bitswide;
		pst_OutParInfo[dw_Index].Type								= ast_SataDeviceParInfo[dw_Index].Type;

		BDDIGetParameterValues(dw_Index, a_Temp);
	
		strcpy(pst_OutParInfo[dw_Index].Value,				a_Temp);
	}
}

SATADevice_BDDI::~SATADevice_BDDI()
{
	if(pst_OutRegInfo)	delete [] pst_OutRegInfo;
	if(pst_OutParInfo)	delete [] pst_OutParInfo;
}

// regsiter access function
BDDIReturn SATADevice_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)
{
	BDDIRegValue st_Temp;
	return BDDIStatusOK;
}

// regsiter access function
BDDIReturn SATADevice_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)
{
	BDDIRegValue st_Temp;
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn SATADevice_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)
{
	BDDIParValue st_Temp;
	return BDDIStatusOK;
}

// parameter access function
BDDIReturn SATADevice_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;
	return BDDIStatusOK;
}

char* SATADevice_BDDI::BDDIGetModuleType()
{
	return (char*)"other";
}

BDDIRegInfo* SATADevice_BDDI::BDDIGetModuleRegInfo()
{
	return pst_OutRegInfo;
}

BDDIParInfo* SATADevice_BDDI::BDDIGetModuleParInfo()
{
	return pst_OutParInfo;
}

unsigned int SATADevice_BDDI::BDDIGetModuleTotalRegNum()
{
	return dw_RegCnt;
}

unsigned int SATADevice_BDDI::BDDIGetModuleTotalParNum()
{
	return dw_ParCnt;
}
