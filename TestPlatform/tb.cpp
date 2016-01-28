#include "tb.h"

BDDI* TB::GetBDDI()
{
	return bddi;
}

char* TB::GetModuleName()
{
	return (char*)"TB";
}

void TB::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");
	EXTRACT_PC.set_port_name("EXTRACT_PC");

	bddi = new TB_BDDI(this);
}

//extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
//{
	//return new TB(ModuleInstanceName);
//}
