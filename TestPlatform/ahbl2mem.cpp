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
	HSEL.set_port_name("HSEL");
	HREADY.set_port_name("HREADY");
	HADDR.set_port_name("HADDR");
	HBURST.set_port_name("HBURST");
	HPROT.set_port_name("HPROT");
	HTRANS.set_port_name("HTRANS");
	HWRITE.set_port_name("HWRITE");
	HSIZE.set_port_name("HSIZE");
	HWDATA.set_port_name("HWDATA");
	HREADYOUT.set_port_name("HREADYOUT");
	HRDATA.set_port_name("HRDATA");
	HRESP.set_port_name("HRESP");	

	bddi = new AHBL2MEM_BDDI(this);
}

//extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
//{
	//return new AHBL2MEM(ModuleInstanceName);
//}
