package com.twoblock.blockdesigner.command;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.handlers.HandlerUtil;

import com.twoblock.blockdesigner.modulewizard.CW_Wizard;

public class Handler_ModuleWizard extends AbstractHandler {

	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		Display display = HandlerUtil.getActiveShellChecked(event).getDisplay();
		new CW_Wizard().run(display);
		return null;
	}

}