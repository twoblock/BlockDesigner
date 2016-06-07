package com.twoblock.blockdesigner.popup;

import java.util.ArrayList;

public interface IBDMemoryMapEditorListener {
	public void onOk(ArrayList<BDMemoryMapItem> items);
	void onCancel();
}
