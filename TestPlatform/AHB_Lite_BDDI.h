#ifndef __AHB_Lite_BDDI_H__
#define __AHB_Lite_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class AHB_Lite;

class AHB_Lite_BDDI : public BDDIBase
{
	public:
		AHB_Lite_BDDI(AHB_Lite *c);
		virtual ~AHB_Lite_BDDI();

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
		AHB_Lite *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __AHB_Lite_BDDI_H__
