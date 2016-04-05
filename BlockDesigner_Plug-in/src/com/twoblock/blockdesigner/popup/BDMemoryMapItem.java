package com.twoblock.blockdesigner.popup;

public class BDMemoryMapItem {
	public String SlaveName;
	public String SlavePort;
	public long StartAddr;
	public long Size;
	public long EndAddr;

	public BDMemoryMapItem(String moduleName, String portName, long sAddr, long size, long eAddr) {
		this.SlaveName = moduleName;
		this.SlavePort = portName;
		this.StartAddr = sAddr;
		this.Size = size;
		this.EndAddr = eAddr;
	}
}
