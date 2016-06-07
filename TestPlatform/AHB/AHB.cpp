#include "AHB.h"

BDDI* AHB::GetBDDI()
{
	return bddi;
}

BDMMI* AHB::GetBDMMI()
{
	return bdmmi;
}

char* AHB::GetModuleName()
{
	return (char*)"AHB";
}

void AHB::BDInit()
{
	// Global Clock & Resetn
	HCLK.set_port_name("HCLK");
	HRESETn.set_port_name("HRESETn");

	AHBMaster_M0 = new BD_AHBPort_MS((char*)"MS_M0");
	AHBMaster_M1 = new BD_AHBPort_MS((char*)"MS_M1");
	AHBMaster_M2 = new BD_AHBPort_MS((char*)"MS_M2");

	// Slave 0 Interface
	AHBSlave_S0 = new BD_AHBPort_SM((char*)"SM_S0");
	AHBSlave_S1 = new BD_AHBPort_SM((char*)"SM_S1");
	AHBSlave_S2 = new BD_AHBPort_SM((char*)"SM_S2");
	AHBSlave_S3 = new BD_AHBPort_SM((char*)"SM_S3");
	AHBSlave_S4 = new BD_AHBPort_SM((char*)"SM_S4");
	AHBSlave_S5 = new BD_AHBPort_SM((char*)"SM_S5");
	AHBSlave_S6 = new BD_AHBPort_SM((char*)"SM_S6");
	AHBSlave_S7 = new BD_AHBPort_SM((char*)"SM_S7");
	AHBSlave_S8 = new BD_AHBPort_SM((char*)"SM_S8");
	AHBSlave_S9 = new BD_AHBPort_SM((char*)"SM_S9");

	bddi = new AHB_BDDI(this);
	bdmmi = new AHB_BDMMI(this);
}

AHB::~AHB()
{
	delete AHBMaster_M0;
	delete AHBMaster_M1;
	delete AHBMaster_M2;
	delete AHBSlave_S0;
	delete AHBSlave_S1;
	delete AHBSlave_S2;
	delete AHBSlave_S3;
	delete AHBSlave_S4;
	delete AHBSlave_S5;
	delete AHBSlave_S6;
	delete AHBSlave_S7;
	delete AHBSlave_S8;
	delete AHBSlave_S9;

	delete bddi;            
	delete bdmmi;
}

extern "C" sc_module* CreateInstance(const char *ModuleInstanceName)
{
	return new AHB(ModuleInstanceName);
}
