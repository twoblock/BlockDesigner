#ifndef __LITETOAHB_BDDI_H__
#define __LITETOAHB_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class LITETOAHB;

class LITETOAHB_BDDI : public BDDIBase
{
	public:
		LITETOAHB_BDDI(LITETOAHB *c);
		virtual ~LITETOAHB_BDDI();

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
		LITETOAHB *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __LITETOAHB_BDDI_H__
