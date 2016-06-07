#ifndef __BDSTUB_BDDI_H__
#define __BDSTUB_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class BDSTUB;

class BDSTUB_BDDI : public BDDIBase
{
	public:
		BDSTUB_BDDI(BDSTUB *c);
		virtual ~BDSTUB_BDDI();

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
		BDSTUB *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __BDSTUB_BDDI_H__
