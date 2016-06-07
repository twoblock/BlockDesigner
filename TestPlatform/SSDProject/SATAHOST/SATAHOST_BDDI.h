#ifndef __SATAHOST_BDDI_H__
#define __SATAHOST_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class SATAHOST;

class SATAHOST_BDDI : public BDDIBase
{
	public:
		SATAHOST_BDDI(SATAHOST *c);
		virtual ~SATAHOST_BDDI();

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
		SATAHOST *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __SATAHOST_BDDI_H__
