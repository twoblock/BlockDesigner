#ifndef __MemoryUtility_BDDI_H__
#define __MemoryUtility_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class MemoryUtility;

class MemoryUtility_BDDI : public BDDIBase
{
	public:
		MemoryUtility_BDDI(MemoryUtility *c);
		virtual ~MemoryUtility_BDDI();

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

	private:
		MemoryUtility *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __MemoryUtility_BDDI_H__
