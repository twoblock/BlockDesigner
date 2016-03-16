#include "ahbl2mem_BDDI.h"
#include "ahbl2mem.h"

BDDIRegInfo ast_AHBL2MEMRegInfo[] = 
{
};

BDDIParInfo ast_AHBL2MEMParInfo[] = 
{
	{"base_addr", 32, BDDIParTypeUINT, ""}
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

	p_Module = static_cast<sc_module*>(p_Target);

	BDDISetModuleInstanceName(p_Module->name());
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
	
	UINT32 dw_TempU;

	switch(ParIndex)
	{
		case 0:
			dw_TempU = p_Target->base_addr;
			BDDIPutInParameterValue(&st_Temp, &ast_AHBL2MEMParInfo[ParIndex], &dw_TempU);
			BDDIConvertParameterValueToString(&st_Temp, OutValue);

			break;

		default:	return BDDIStatusError;

	}

	return BDDIStatusOK;
}

// parameter access function
BDDIReturn AHBL2MEM_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)
{
	BDDIParValue st_Temp;

	UINT32 dw_TempU;

	switch(ParIndex)
	{
		case 0:
			BDDIConvertStringToParameterValue(&st_Temp, &ast_AHBL2MEMParInfo[ParIndex], SetValue);
			BDDIExtractParameterValue(&st_Temp, &dw_TempU);
			p_Target->base_addr = dw_TempU;

			break;

		default:	return BDDIStatusError;

	}

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

BDDIReturn AHBL2MEM_BDDI::BDDIGetMemoryAddressValue(unsigned int Address, unsigned int *Value)
{
	if( (Address >= p_Target->base_addr) && (Address < (p_Target->base_addr + p_Target->addr_size)) )	{
		UINT32 dw_TempAddr = ( (Address - p_Target->base_addr) >> 2) & 0x3FFFFFFF;

		*Value = p_Target->memory[dw_TempAddr];

		return BDDIStatusOK;
	}
	else	return BDDIStatusError;
}

BDDIReturn AHBL2MEM_BDDI::BDDISetMemoryAddressValue(unsigned int Address, unsigned int Value)
{
	if( (Address >= p_Target->base_addr) && (Address < (p_Target->base_addr + p_Target->addr_size)) )	{
		UINT32 dw_TempAddr = ( (Address - p_Target->base_addr) >> 2) & 0x3FFFFFFF;

		p_Target->memory[dw_TempAddr] = Value;

		return BDDIStatusOK;
	}
	else	return BDDIStatusError;

}

unsigned int AHBL2MEM_BDDI::BDDIGetMemoryBaseAddress()
{
	return p_Target->base_addr;
}

unsigned int AHBL2MEM_BDDI::BDDIGetMemoryAddressSize()
{
	return p_Target->addr_size;
}
