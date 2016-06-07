#ifndef __AHBL2MEM_BDDI_H__
#define __AHBL2MEM_BDDI_H__

#include "systemc.h"
#include <string>

using namespace BDapi;

class AHBL2MEM;

class AHBL2MEM_BDDI : public BDDIBase
{
	public:
		AHBL2MEM_BDDI(AHBL2MEM *c);
		virtual ~AHBL2MEM_BDDI();

	public:
		BDDIReturn BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue);
		BDDIReturn BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue);
		BDDIReturn BDDIGetParameterValues(unsigned int ParIndex, char *OutValue);
		BDDIReturn BDDISetParameterValues(unsigned int ParIndex, const char *SetValue);

		char* BDDIGetModuleType();

		BDDIRegInfo* BDDIGetModuleRegInfo();
		BDDIParInfo* BDDIGetModuleParInfo();

		unsigned int BDDIGetModuleTotalRegNum();
		unsigned int BDDIGetModuleTotalParNum();

		BDDIReturn BDDIGetMemoryAddressValue(unsigned int Address, unsigned int *Value);
		BDDIReturn BDDISetMemoryAddressValue(unsigned int Address, unsigned int Value);

		BDDIReturn BDDIGetMemoryView(unsigned int Address, string &OutValue);

		unsigned int BDDIGetMemoryBaseAddress();
		unsigned int BDDIGetMemoryAddressSize();

	private:
		AHBL2MEM *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
		sc_module* p_Module;
};

#endif	// __AHBL2MEM_BDDI_H__
