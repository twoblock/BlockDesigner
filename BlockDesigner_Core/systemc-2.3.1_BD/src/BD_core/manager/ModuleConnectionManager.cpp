//-----------------------------------------------------------------------------
// Design								: Module connection manager 
// Author								: Bryan Choi 
// Email								: bryan.choi@twoblocktech.com 
// File		     					: ModuleConnectionManager.cpp
// Date	       					: 2016/1/27
// Reference            :
// ----------------------------------------------------------------------------
// Copyright (c) 2015-2016 TwoBlock Techinologies Co.
// ----------------------------------------------------------------------------
// Description	: manage channels and modules 
//                connect all modules by using channels
// ----------------------------------------------------------------------------

#include "ModuleConnectionManager.h"
#include "PMModuleListManager.h"
#include "../SimulationAPI/ChannelManager.h"

namespace BDapi
{	
	void ModuleConnectionManager::PutOperationControl(GUI_COMMAND Command)
	{
		p_ChannelManager->AddChannel("sc_clock", "HCLK", "bool");
		p_ChannelManager->AddChannel("sc_signal", "HRESETn", "bool");

		p_ChannelManager->AddChannel("sc_signal", "HBURST_P", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HLOCK_P", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HPROT_P", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HSIZE_P", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HTRANS_P", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HWRITE_P", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADY_P", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_P", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HADDR_P", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HWDATA_P", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_P", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HBURST_S", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HLOCK_S", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HPROT_S", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HSIZE_S", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HTRANS_S", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HWRITE_S", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADY_S", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HADDR_S", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S0", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S0", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S0", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S1", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S1", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S1", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S2", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S2", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S2", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S3", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S3", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S3", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S4", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S4", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S4", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S5", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S5", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S5", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S6", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S6", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S6", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S7", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S7", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S7", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S8", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S8", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S8", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_S9", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HREADYOUT_S9", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HRESP_S9", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HSEL_NOMAP", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "HWDATA_S", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S0", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S1", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S2", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S3", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S4", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S5", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S6", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S7", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S8", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "HRDATA_S9", "UINT32");

		p_ChannelManager->AddChannel("sc_signal", "NMI", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ00", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ01", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ02", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ03", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ04", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ05", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ06", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ07", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ08", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ09", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ10", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ11", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ12", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ13", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ14", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "IRQ15", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "TXEV", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "RXEV", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "LOCKUP", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "SYSRESETREQ", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "SLEEPING", "bool");	 
		p_ChannelManager->AddChannel("sc_signal", "EXTRACT_PC", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "EXTRACT_R3", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "EXTRACT_R4", "UINT32");
		p_ChannelManager->AddChannel("sc_signal", "EXTRACT_R10", "UINT32");

		BindChannel("BD_CORTEXM0DS", "HCLK", "HCLK");
		BindChannel("BD_CORTEXM0DS", "HRESETn", "HRESETn");
		BindChannel("BD_CORTEXM0DS", "HADDR", "HADDR_P");
		BindChannel("BD_CORTEXM0DS", "HBURST", "HBURST_P");
		BindChannel("BD_CORTEXM0DS", "HMASTLOCK", "HLOCK_P");
		BindChannel("BD_CORTEXM0DS", "HPROT", "HPROT_P");
		BindChannel("BD_CORTEXM0DS", "HSIZE", "HSIZE_P");
		BindChannel("BD_CORTEXM0DS", "HTRANS", "HTRANS_P");
		BindChannel("BD_CORTEXM0DS", "HWDATA", "HWDATA_P");
		BindChannel("BD_CORTEXM0DS", "HWRITE", "HWRITE_P");
		BindChannel("BD_CORTEXM0DS", "HRDATA", "HRDATA_P");
		BindChannel("BD_CORTEXM0DS", "HREADY", "HREADY_P");
		BindChannel("BD_CORTEXM0DS", "HRESP", "HRESP_P");
		BindChannel("BD_CORTEXM0DS", "NMI", "NMI");        
		BindChannel("BD_CORTEXM0DS", "IRQ00", "IRQ00");      
		BindChannel("BD_CORTEXM0DS", "IRQ01", "IRQ01");
		BindChannel("BD_CORTEXM0DS", "IRQ02", "IRQ02");
		BindChannel("BD_CORTEXM0DS", "IRQ03", "IRQ03");
		BindChannel("BD_CORTEXM0DS", "IRQ04", "IRQ04");
		BindChannel("BD_CORTEXM0DS", "IRQ05", "IRQ05");
		BindChannel("BD_CORTEXM0DS", "IRQ06", "IRQ06");
		BindChannel("BD_CORTEXM0DS", "IRQ07", "IRQ07");
		BindChannel("BD_CORTEXM0DS", "IRQ08", "IRQ08");
		BindChannel("BD_CORTEXM0DS", "IRQ09", "IRQ09");
		BindChannel("BD_CORTEXM0DS", "IRQ10", "IRQ10");
		BindChannel("BD_CORTEXM0DS", "IRQ11", "IRQ11");
		BindChannel("BD_CORTEXM0DS", "IRQ12", "IRQ12");
		BindChannel("BD_CORTEXM0DS", "IRQ13", "IRQ13");
		BindChannel("BD_CORTEXM0DS", "IRQ14", "IRQ14");
		BindChannel("BD_CORTEXM0DS", "IRQ15", "IRQ15");     
		BindChannel("BD_CORTEXM0DS", "TXEV", "TXEV");       
		BindChannel("BD_CORTEXM0DS", "RXEV", "RXEV");      
		BindChannel("BD_CORTEXM0DS", "LOCKUP", "LOCKUP");     
		BindChannel("BD_CORTEXM0DS", "SYSRESETREQ", "SYSRESETREQ");
		BindChannel("BD_CORTEXM0DS", "SLEEPING", "SLEEPING");   
		BindChannel("BD_CORTEXM0DS", "EXTRACT_PC", "EXTRACT_PC");
		BindChannel("BD_CORTEXM0DS", "EXTRACT_R3", "EXTRACT_R3");
		BindChannel("BD_CORTEXM0DS", "EXTRACT_R4", "EXTRACT_R4");
		BindChannel("BD_CORTEXM0DS", "EXTRACT_R10", "EXTRACT_R10");

		BindChannel("BD_AHB_LITE", "HCLK", "HCLK");
		BindChannel("BD_AHB_LITE", "HRESETn", "HRESETn"); 
		BindChannel("BD_AHB_LITE", "HADDR_M", "HADDR_P");
		BindChannel("BD_AHB_LITE", "HBURST_M", "HBURST_P");
		BindChannel("BD_AHB_LITE", "HLOCK_M", "HLOCK_P");;;
		BindChannel("BD_AHB_LITE", "HPROT_M", "HPROT_P");;
		BindChannel("BD_AHB_LITE", "HSIZE_M", "HSIZE_P");
		BindChannel("BD_AHB_LITE", "HTRANS_M", "HTRANS_P");
		BindChannel("BD_AHB_LITE", "HWDATA_M", "HWDATA_P");
		BindChannel("BD_AHB_LITE", "HWRITE_M", "HWRITE_P");
		BindChannel("BD_AHB_LITE", "HRDATA_M", "HRDATA_P"); 
		BindChannel("BD_AHB_LITE", "HREADY_M", "HREADY_P");
		BindChannel("BD_AHB_LITE", "HRESP_M", "HRESP_P"); 
		BindChannel("BD_AHB_LITE", "HADDR_S", "HADDR_S");
		BindChannel("BD_AHB_LITE", "HBURST_S", "HBURST_S");
		BindChannel("BD_AHB_LITE", "HLOCK_S", "HLOCK_S");
		BindChannel("BD_AHB_LITE", "HPROT_S", "HPROT_S");
		BindChannel("BD_AHB_LITE", "HSIZE_S", "HSIZE_S");
		BindChannel("BD_AHB_LITE", "HTRANS_S", "HTRANS_S");
		BindChannel("BD_AHB_LITE", "HWDATA_S", "HWDATA_S");
		BindChannel("BD_AHB_LITE", "HWRITE_S", "HWRITE_S");
		BindChannel("BD_AHB_LITE", "HREADY_S", "HREADY_S");
		BindChannel("BD_AHB_LITE", "HSEL_S0", "HSEL_S0");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S0", "HREADYOUT_S0");
		BindChannel("BD_AHB_LITE", "HRESP_S0", "HRESP_S0");
		BindChannel("BD_AHB_LITE", "HRDATA_S0", "HRDATA_S0");
		BindChannel("BD_AHB_LITE", "HSEL_S1", "HSEL_S1");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S1", "HREADYOUT_S1");
		BindChannel("BD_AHB_LITE", "HRESP_S1", "HRESP_S1");
		BindChannel("BD_AHB_LITE", "HRDATA_S1", "HRDATA_S1");
		BindChannel("BD_AHB_LITE", "HSEL_S2", "HSEL_S2");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S2", "HREADYOUT_S2");
		BindChannel("BD_AHB_LITE", "HRESP_S2", "HRESP_S2");
		BindChannel("BD_AHB_LITE", "HRDATA_S2", "HRDATA_S2");
		BindChannel("BD_AHB_LITE", "HSEL_S3", "HSEL_S3");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S3", "HREADYOUT_S3");
		BindChannel("BD_AHB_LITE", "HRESP_S3", "HRESP_S3");
		BindChannel("BD_AHB_LITE", "HRDATA_S3", "HRDATA_S3");
		BindChannel("BD_AHB_LITE", "HSEL_S4", "HSEL_S4");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S4", "HREADYOUT_S4");
		BindChannel("BD_AHB_LITE", "HRESP_S4", "HRESP_S4");
		BindChannel("BD_AHB_LITE", "HRDATA_S4", "HRDATA_S4");
		BindChannel("BD_AHB_LITE", "HSEL_S5", "HSEL_S5");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S5", "HREADYOUT_S5");
		BindChannel("BD_AHB_LITE", "HRESP_S5", "HRESP_S5");
		BindChannel("BD_AHB_LITE", "HRDATA_S5", "HRDATA_S5");
		BindChannel("BD_AHB_LITE", "HSEL_S6", "HSEL_S6");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S6", "HREADYOUT_S6");
		BindChannel("BD_AHB_LITE", "HRESP_S6", "HRESP_S6");
		BindChannel("BD_AHB_LITE", "HRDATA_S6", "HRDATA_S6");
		BindChannel("BD_AHB_LITE", "HSEL_S7", "HSEL_S7");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S7", "HREADYOUT_S7");
		BindChannel("BD_AHB_LITE", "HRESP_S7", "HRESP_S7");
		BindChannel("BD_AHB_LITE", "HRDATA_S7", "HRDATA_S7");
		BindChannel("BD_AHB_LITE", "HSEL_S8", "HSEL_S8");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S8", "HREADYOUT_S8");
		BindChannel("BD_AHB_LITE", "HRESP_S8", "HRESP_S8");
		BindChannel("BD_AHB_LITE", "HRDATA_S8", "HRDATA_S8");
		BindChannel("BD_AHB_LITE", "HSEL_S9", "HSEL_S9");
		BindChannel("BD_AHB_LITE", "HREADYOUT_S9", "HREADYOUT_S9");
		BindChannel("BD_AHB_LITE", "HRESP_S9", "HRESP_S9");
		BindChannel("BD_AHB_LITE", "HRDATA_S9", "HRDATA_S9");
		BindChannel("BD_AHB_LITE", "HSEL_NOMAP", "IRQ14");

		BindChannel("BD_ROM", "HCLK", "HCLK");
		BindChannel("BD_ROM", "HRESETn", "HRESETn");
		BindChannel("BD_ROM", "HSEL", "HSEL_S0");
		BindChannel("BD_ROM", "HADDR", "HADDR_S");
		BindChannel("BD_ROM", "HTRANS", "HTRANS_S");
		BindChannel("BD_ROM", "HWRITE", "HWRITE_S");
		BindChannel("BD_ROM", "HSIZE", "HSIZE_S");
		BindChannel("BD_ROM", "HBURST", "HBURST_S");
		BindChannel("BD_ROM", "HWDATA", "HWDATA_S");
		BindChannel("BD_ROM", "HRDATA", "HRDATA_S0");
		BindChannel("BD_ROM", "HRESP", "HRESP_S0");
		BindChannel("BD_ROM", "HREADY", "HREADY_S");
		BindChannel("BD_ROM", "HREADYOUT", "HREADYOUT_S0");
		BindChannel("BD_ROM", "HPROT", "HPROT_S");

		BindChannel("BD_SRAM", "HCLK", "HCLK");
		BindChannel("BD_SRAM", "HRESETn", "HRESETn");
		BindChannel("BD_SRAM", "HSEL", "HSEL_S1");
		BindChannel("BD_SRAM", "HADDR", "HADDR_S");
		BindChannel("BD_SRAM", "HTRANS", "HTRANS_S");
		BindChannel("BD_SRAM", "HWRITE", "HWRITE_S");
		BindChannel("BD_SRAM", "HSIZE", "HSIZE_S");
		BindChannel("BD_SRAM", "HBURST", "HBURST_S");
		BindChannel("BD_SRAM", "HWDATA", "HWDATA_S");
		BindChannel("BD_SRAM", "HRDATA", "HRDATA_S1");
		BindChannel("BD_SRAM", "HRESP", "HRESP_S1");
		BindChannel("BD_SRAM", "HREADY", "HREADY_S");
		BindChannel("BD_SRAM", "HREADYOUT", "HREADYOUT_S1");
		BindChannel("BD_SRAM", "HPROT", "HPROT_S");

		BindChannel("BD_CONSOLE", "HCLK", "HCLK");
		BindChannel("BD_CONSOLE", "HRESETn", "HRESETn");
		BindChannel("BD_CONSOLE", "HSEL", "HSEL_S2");
		BindChannel("BD_CONSOLE", "HADDR", "HADDR_S");
		BindChannel("BD_CONSOLE", "HREADY", "HREADY_S");
		BindChannel("BD_CONSOLE", "HBURST", "HBURST_S");
		BindChannel("BD_CONSOLE", "HPROT", "HPROT_S");
		BindChannel("BD_CONSOLE", "HTRANS", "HTRANS_S");
		BindChannel("BD_CONSOLE", "HWRITE", "HWRITE_S");
		BindChannel("BD_CONSOLE", "HSIZE", "HSIZE_S");
		BindChannel("BD_CONSOLE", "HWDATA", "HWDATA_S");
		BindChannel("BD_CONSOLE", "HREADYOUT", "HREADYOUT_S2");
		BindChannel("BD_CONSOLE", "HRDATA", "HRDATA_S2");
		BindChannel("BD_CONSOLE", "HRESP", "HRESP_S2");

		BindChannel("BD_TB", "HCLK", "HCLK");
		BindChannel("BD_TB", "HRESETn", "HRESETn");
		BindChannel("BD_TB", "EXTRACT_PC", "EXTRACT_PC"); 
	}
	void ModuleConnectionManager::GetOperationControl(GUI_COMMAND Command)
	{

	}
	/*
	 * function    : ConnectModules 
	 * design      : each module port bind this channel, which means to make connection 
	 * param       : char * - First module name 
	 * param       : char * - First module port name 
	 * param       : char * - channel name 
	 * param       : char * - Second module name
	 * param       : char * - Second module port name 
	 * caller      :  
	 */
	void ModuleConnectionManager::ConnectModules(
			const char *FirstModuleName,
			const char *FirstModulePortName, 
			const char *ChannelName,
			const char *SecondModuleName, 
			const char *SecondModulePortName)
	{
		BindChannel(FirstModuleName, FirstModulePortName, ChannelName);
		BindChannel(SecondModuleName, SecondModulePortName, ChannelName);
	}

	/*
	 * function    : BindChannel 
	 * design      : one module port connect this channel 
	 * param       : char * - Module name 
	 * param       : char * - Module port name 
	 * param       : char * - Channel name 
	 * caller      :  
	 */
	void ModuleConnectionManager::BindChannel(
			const char *ModuleName, 
			const char *ModulePortName, 
			const char *ChannelName)
	{
		sc_module *p_SCmodule = NULL;
		p_SCmodule = p_PMModuleListManager->FindModule(ModuleName);

		std::vector<sc_port_base*>* p_PortList = NULL;
		p_PortList = p_SCmodule->get_port_list();	
		
		// find channel
		sc_interface *p_SCinterface = NULL;
		p_SCinterface = p_ChannelManager->FindChannel(ChannelName);

		// find port
		sc_port_base *p_SCportbase = NULL;
		std::vector<sc_port_base*>::iterator FirstPort = p_PortList->begin(); 
		std::vector<sc_port_base*>::iterator LastPort = p_PortList->end(); 
		std::vector<sc_port_base*>::iterator IndexOfPort = FirstPort;

		for(IndexOfPort = FirstPort; IndexOfPort != LastPort; ++IndexOfPort){   
			p_SCportbase = (*IndexOfPort);
			if(strcmp(p_SCportbase->get_port_name(), ModulePortName) == 0){
				// this port bind channel
				p_SCportbase->BDbind(*p_SCinterface);
			}
		} 
	}

	/*
	 * function 	: GetInstance
	 * design	    : singleton design
	 */
	ModuleConnectionManager* ModuleConnectionManager::GetInstance()
	{
		if( _ModuleConnectionManager == NULL ){
			_ModuleConnectionManager = new ModuleConnectionManager();
		}

		return _ModuleConnectionManager;
	}

	/*
	 * function 	: Constructor
	 * design	    : 
	 */
	ModuleConnectionManager::ModuleConnectionManager()
	{
		p_PMModuleListManager = PMModuleListManager::GetInstance();
		p_ChannelManager = new ChannelManager();
	}

	/*
	 * function 	: Destructor
	 * design	    : delete execution manager instance
	 */
	ModuleConnectionManager::~ModuleConnectionManager()
	{
		delete p_ChannelManager;
	}
}
