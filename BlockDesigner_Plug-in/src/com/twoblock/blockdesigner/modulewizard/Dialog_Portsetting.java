package com.twoblock.blockdesigner.modulewizard;

import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Shell;

public class Dialog_Portsetting extends Dialog{

	public Dialog_Portsetting(Shell parentShell) {
		
		super(parentShell);
	  }

	  @Override
	  protected Control createDialogArea(Composite parent) {
		 
	    Composite container = (Composite) super.createDialogArea(parent);
	    Button button = new Button(container, SWT.PUSH);
	    button.setLayoutData(new GridData(SWT.BEGINNING, SWT.CENTER, false,
	        false));
	    button.setText("Press me");
	    button.addSelectionListener(new SelectionAdapter() {
	      @Override
	      public void widgetSelected(SelectionEvent e) {
	        System.out.println("Pressed");
	      }
	    });

	    return container;
	  }

	  // overriding this methods allows you to set the
	  // title of the custom dialog
	  @Override
	  protected void configureShell(Shell newShell) {
	    super.configureShell(newShell);
	    newShell.setText("Selection dialog");
	  }

	  @Override
	  protected Point getInitialSize() {
	    return new Point(450, 300);
	  }
	  
		public static String main(String[] args) {
			Shell shell = new Shell();
			Dialog_Portsetting dialog = new Dialog_Portsetting(shell);
			dialog.open();
			return null;
		}
	  

	} 