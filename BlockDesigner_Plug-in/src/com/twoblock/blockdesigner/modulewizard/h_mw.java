package com.twoblock.blockdesigner.modulewizard;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.handlers.HandlerUtil;


public class h_mw extends AbstractHandler {

	private Display display;
	private ExecutionEvent E_event;

	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		E_event = event;
		display = HandlerUtil.getActiveShellChecked(E_event).getDisplay();
		new CW_Wizard().run(display);
		return null;
	}

}