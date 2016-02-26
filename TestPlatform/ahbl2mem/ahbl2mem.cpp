#include "ahbl2mem.h"

BDDI* AHBL2MEM::GetBDDI()
{
	return bddi;
}

char* AHBL2MEM::GetModuleName()
{
	return (char*)"AHBL2MEM";
}

void AHBL2MEM::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	AHB_SS = new BD_AHBPort_SS((char*)"S0");

	bddi = new AHBL2MEM_BDDI(this);
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new AHBL2MEM(ModuleInstanceName);
}
