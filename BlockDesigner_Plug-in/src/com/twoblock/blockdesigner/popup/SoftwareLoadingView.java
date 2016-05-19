package com.twoblock.blockdesigner.popup;


import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;

import com.twoblock.blockdesigner.command.Handler_Command;
import com.twoblock.blockdesigner.view.View_SimulationEnvironment;

public class SoftwareLoadingView {

	private Shell m_shell;
	protected String Module_Location;
	protected String Selected_core;
	private Combo cmb_core;
	private Button btn_sw;

	public void show() {
		m_shell.open();
	}



	public SoftwareLoadingView(Shell shell,String core) {
		m_shell = new Shell(shell.getDisplay(), SWT.CLOSE);
		m_shell.setSize(400, 100);
		m_shell.setText("Software Loading.");
		m_shell.setLayout(new FillLayout(SWT.VERTICAL));
		
		Composite cmp_core = new Composite(m_shell, SWT.NONE);
		cmp_core.setLayout(new FillLayout(SWT.VERTICAL));
		Label lbl_core = new Label(cmp_core, SWT.NONE);
		lbl_core.setText("Please select core");
		
		Selected_core=null;
		cmb_core = new Combo(cmp_core, SWT.NONE);
		core=core.replaceFirst(",", "");
		String[] core_list = core.split(",");
		cmb_core.setItems(core_list);
		
		cmb_core.addSelectionListener( new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				Selected_core=cmb_core.getText();
			}
		});
		
		Label lbl_sep = new Label(m_shell, SWT.SEPARATOR | SWT.HORIZONTAL);
		
		
		Composite cmp_sw = new Composite(m_shell, SWT.NONE);
		cmp_sw.setLayout(new FillLayout(SWT.VERTICAL));
		Label lbl_sw = new Label(cmp_sw, SWT.NONE);
		lbl_sw.setText("software load");
		btn_sw = new Button(cmp_sw, SWT.NONE);
		btn_sw.setText("Load");
		
		
		btn_sw.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				FileDialog file_dlg = new FileDialog(m_shell.getShell() , SWT.OPEN);
				
				file_dlg.setText("Software Loading");
				String[] filterExt={"*.[e|a][l|x]f"};
				String[] filterName={"*.elf , *.axf "};
				file_dlg.setFilterExtensions(filterExt);
				file_dlg.setFilterNames(filterName);
				file_dlg.setFilterPath(System.getProperty("user.home"));
				
				Module_Location = file_dlg.open();
				
				if (Module_Location != null) {
					// File directory = new File(saveTarget);
					Module_Location = Module_Location.replace("\\", "/");
					btn_sw.setText(Module_Location);
				}
			}
		});
		
		
		Label lbl_sep2 = new Label(m_shell, SWT.SEPARATOR | SWT.HORIZONTAL);
		
		Composite cmp_ok = new Composite(m_shell, SWT.NONE);
		cmp_ok.setLayout(new FillLayout(SWT.VERTICAL));
		
		Button btn_ok = new Button(cmp_ok, SWT.NONE);
		btn_ok.setText("OK");
		
		btn_ok.addSelectionListener( new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				View_SimulationEnvironment.SWLoadCheck=true;
				Handler_Command.Command_Func(0, 0, Selected_core , Module_Location, "", "","");
				View_SimulationEnvironment.Selected_core_check=Selected_core;
				m_shell.close();
			}
		});
		
		// Move the dialog to the center of the top level shell.
		Rectangle shellBounds = m_shell.getDisplay().getBounds();
		Point dialogSize = m_shell.getSize();

		m_shell.setLocation(shellBounds.x + (shellBounds.width - dialogSize.x) / 2,
				shellBounds.y + (shellBounds.height - dialogSize.y) / 2);
		m_shell.setSize(400, 300);
	}
}
