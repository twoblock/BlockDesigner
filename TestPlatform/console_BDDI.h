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
		BDDIReturn BDDIGetParameterValues(unsigned int ParamIndex, unsigned int *OutParam);
		BDDIReturn BDDISetParameterValues(unsigned int ParamIndex, unsigned int SetValue);

	private:
		CONSOLE *target;
};

#endif	// __CONSOLE_BDDI_H__
