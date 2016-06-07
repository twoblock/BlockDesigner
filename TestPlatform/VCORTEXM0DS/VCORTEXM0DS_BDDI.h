#ifndef __VCORTEXM0DS_BDDI_H__
#define __VCORTEXM0DS_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class VCORTEXM0DS;

class VCORTEXM0DS_BDDI : public BDDIBase
{
	public:
		VCORTEXM0DS_BDDI(VCORTEXM0DS *c);
		virtual ~VCORTEXM0DS_BDDI();

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

		unsigned int BDDIGetPCValue();

	private:
		VCORTEXM0DS *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __VCORTEXM0DS_BDDI_H__
