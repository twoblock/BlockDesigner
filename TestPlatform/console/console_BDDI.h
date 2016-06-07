#ifndef __CONSOLE_BDDI_H__
#define __CONSOLE_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class CONSOLE;

class CONSOLE_BDDI : public BDDIBase
{
	public:
		CONSOLE_BDDI(CONSOLE *c);
		virtual ~CONSOLE_BDDI();

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
		CONSOLE *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __CONSOLE_BDDI_H__
