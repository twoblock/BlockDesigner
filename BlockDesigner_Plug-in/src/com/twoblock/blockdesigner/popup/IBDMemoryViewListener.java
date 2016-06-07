package com.twoblock.blockdesigner.popup;

public interface IBDMemoryViewListener {
	public void onChangeData(long addr, long data);
	public void onDataLoad(BDMemoryView view, long startAddr, long size);
}
