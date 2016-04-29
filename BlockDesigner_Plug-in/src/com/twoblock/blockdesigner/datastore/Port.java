package com.twoblock.blockdesigner.datastore;

import org.eclipse.swt.custom.CCombo;

public class Port {
		
	public Port clone(Module Parent){
		Port port = new Port();
		
		port.port_name = this.port_name;
		port.sc_type = this.sc_type;
		port.data_type = this.data_type;
 		port.Parent = Parent;
		
		port.SM_Index = this.SM_Index;
		port.startAddr = this.startAddr;
		port.addrSize = this.addrSize;
		port.Dest_Port=null;
		port.cmb_dPort=null;
		
		return port;	
	}
	
	public String port_name;
	public String sc_type;
	public String data_type;
	public Module Parent;
	
	public int SM_Index;
	public String startAddr;
	public String addrSize;
	public Port Dest_Port;
	public CCombo cmb_dPort;
}
