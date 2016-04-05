#ifndef __NANDFlashArray_SLC_BDDI_H__
#define __NANDFlashArray_SLC_BDDI_H__

#include "systemc.h"

using namespace BDapi;

class NANDFlashArray_SLC;

class NANDFlashArray_SLC_BDDI : public BDDIBase
{
	public:
		NANDFlashArray_SLC_BDDI(NANDFlashArray_SLC *c);
		virtual ~NANDFlashArray_SLC_BDDI();

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
		NANDFlashArray_SLC *p_Target;
		BDDIRegInfo *pst_OutRegInfo;
		BDDIParInfo *pst_OutParInfo;
};

#endif	// __NANDFlashArray_SLC_BDDI_H__
