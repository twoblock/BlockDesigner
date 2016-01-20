#include "console_BDDI.h"
#include "console.h"

CONSOLE_BDDI::CONSOLE_BDDI(CONSOLE *c) : target(c)
{

}

CONSOLE_BDDI::~CONSOLE_BDDI()
{

}

BDDIReturn CONSOLE_BDDI::BDDIGetParameterValues(unsigned int ParamIndex, unsigned int *OutParam)
{
	*OutParam = target->dw_LocalParam;
	return BDDIStatusOK;
}

BDDIReturn CONSOLE_BDDI::BDDISetParameterValues(unsigned int ParamIndex, unsigned int SetValue)
{
	target->dw_LocalParam = SetValue;
	return BDDIStatusOK;
}
