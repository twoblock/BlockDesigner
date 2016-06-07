package com.twoblock.blockdesigner.popup;

public class BDSWProfilingItem {
	public String funcName;
	public long call;
	public long durCycle;
	public float durPer;
	public long selfDurCycle;
	public float selfDurPer;
	
	
	public BDSWProfilingItem(String funcName, long call, long durCycle, float durPer, long selfDurCycle, float selfDurPer) {
		super();
		this.funcName = funcName;
		this.call = call;
		this.durCycle = durCycle;
		this.durPer = durPer;
		this.selfDurCycle = selfDurCycle;
		this.selfDurPer = selfDurPer;
	}
}
