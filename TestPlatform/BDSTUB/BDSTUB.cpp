#include "BDSTUB.h"

BDDI* BDSTUB::GetBDDI()
{
	return bddi;
}

char* BDSTUB::GetModuleName()
{
	return (char*)"BDSTUB";
}

void BDSTUB::BDInit()
{
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	AHB_MM = new BD_AHBPort_MM((char*)"MM_M0");

	data_phase = false;
	req_down = 20;
	data_stop = 10;

	// for BDDI
	bddi = new BDSTUB_BDDI(this);
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new BDSTUB(ModuleInstanceName);
}
