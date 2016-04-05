package com.twoblock.blockdesigner.popup;
import java.util.ArrayList;

public class BDSWProfilingItemArray extends ArrayList<BDSWProfilingItem> {

	public boolean add(String funcName, long call, long durCycle, float durPer, long selfDurCycle, float selfDurPer) {
		BDSWProfilingItem item = new BDSWProfilingItem(funcName, call, durCycle, durPer, selfDurCycle, selfDurPer);
		return super.add(item);
	}
	
	public BDSWProfilingItem get(String funcName) {
		for(BDSWProfilingItem item : this) {
			if(item.funcName.equals(funcName))
				return item;
		}
		
		return null;
	}
}
