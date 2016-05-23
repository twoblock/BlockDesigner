package com.twoblock.blockdesigner.popup;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

public class BDProgressbar {
	private Shell m_shell;
	protected String Module_Location;
	protected String Selected_core;

	public void show() {
		m_shell.open();
	}

	public BDProgressbar(Display display, String name, int time, int style ) {
		m_shell = new Shell(display , SWT.CLOSE);
		m_shell.setSize(400, 100);
		m_shell.setText(name);
		
		// Move the dialog to the center of the top level shell.
		Rectangle shellBounds = m_shell.getDisplay().getBounds();
		Point dialogSize = m_shell.getSize();

		m_shell.setLocation(shellBounds.x + (shellBounds.width - dialogSize.x) / 2,
				shellBounds.y + (shellBounds.height - dialogSize.y) / 2);
		m_shell.setSize(400, 300);

		try {
			Thread.sleep(time);
			m_shell.close();
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
}
