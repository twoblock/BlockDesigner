package kr.co.twoblocktech.block.designer.handler;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.handlers.HandlerUtil;

import kr.co.twoblocktech.block.designer.module.wizard.CW_Wizard;

public class CW_WizardHandler extends AbstractHandler {

	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		Display display = HandlerUtil.getActiveShellChecked(event).getDisplay();
		new CW_Wizard().run(display);
		return null;
	}

}