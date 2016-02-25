#include "ahbl2mem_1.h"

BDDI* AHBL2MEM_1::GetBDDI()
{
	return bddi;
}

char* AHBL2MEM_1::GetModuleName()
{
	return (char*)"AHBL2MEM_1";
}

void AHBL2MEM_1::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	AHB_SS = new BD_AHBPort_SS(NULL);

	bddi = new AHBL2MEM_1_BDDI(this);
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new AHBL2MEM_1(ModuleInstanceName);
}
