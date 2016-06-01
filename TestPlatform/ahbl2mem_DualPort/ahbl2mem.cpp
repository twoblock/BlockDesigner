#include "ahbl2mem.h"

BDDI* AHBL2MEM::GetBDDI()
{
	return bddi;
}

char* AHBL2MEM::GetModuleName()
{
	return (char*)"AHBL2MEM_DUAL_PORT";
}

void AHBL2MEM::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	AHB_S0 = new BD_AHBPort_SS((char*)"SS_S0");
	AHB_S1 = new BD_AHBPort_SS((char*)"SS_S1");

	base_addr = 0;
	addr_size = 0x10000000;

	memory = (unsigned int*)malloc(sizeof(unsigned int)*MEM_ADDR_100MB_WIDTH);
	memset(memory, 0, sizeof(memory));

	bddi = new AHBL2MEM_BDDI(this);
}

AHBL2MEM::~AHBL2MEM()
{
	free(memory);
	//delete AHB_S0;
	//delete AHB_S1;
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new AHBL2MEM(ModuleInstanceName);
}
