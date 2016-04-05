#ifndef __NANDController_BDDI_H__
#define __NANDController_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class NANDController;

class NANDController_BDDI : public BDDIBase
{
	public:
		NANDController_BDDI(NANDController *c);
		virtual ~NANDController_BDDI();

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
		NANDController *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __NANDController_BDDI_H__
