package com.twoblock.blockdesigner.modulewizard;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

public class Dialog_RegisterInput extends Dialog {
	private static String reg_name;
	private static String reg_value;
	private static String reg_type;
	private static String bits_wide;
	Double value;
	/**
	 * @param parent
	 */
	public Dialog_RegisterInput(Shell parent) {
		super(parent);
	}

	/**
	 * @param parent
	 * @param style
	 */
	public Dialog_RegisterInput(Shell parent, int style) {
		super(parent, style);
	}

	/**
	 * Makes the dialog visible.
	 * 
	 * @return
	 */
	public Double open() {
		final Text name_text;
		final Text value_text;
		Button create_btn;
		Button cancel_btn;
		final Combo type_cmb;
		Label label;
		Label seperator;
		
		GridData gridData;
		gridData = new GridData();
		gridData.horizontalSpan = 1;
		gridData.horizontalAlignment=GridData.FILL;
		gridData.verticalAlignment=GridData.FILL;
		gridData.grabExcessHorizontalSpace=true;
		gridData.grabExcessVerticalSpace=true;

		Shell parent = getParent();
		final Shell shell = new Shell(parent, SWT.TITLE | SWT.BORDER | SWT.APPLICATION_MODAL);
		shell.setText("Enter Register Information");
		shell.setLayout(new GridLayout(1, true));
		shell.setBounds(400, 400, 400, 400);
		
		label = new Label(shell, SWT.LEFT);
		label.setText("1. Enter the Register Name.        ");
		label.setLayoutData(gridData);


		name_text = new Text(shell, SWT.SINGLE | SWT.BORDER);
		name_text.setLayoutData(gridData);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		label = new Label(shell, SWT.LEFT);
		label.setText("2. Select the Register Type.        ");
		type_cmb= new Combo(shell, SWT.DROP_DOWN |SWT.READ_ONLY );
		type_cmb.setItems(new String[]
				{"HEX","UINT","BOOL","FLOAT"});
		type_cmb.setText("UINT");
		type_cmb.setLayoutData(gridData);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
				
		label = new Label(shell, SWT.LEFT);
		label.setText("3. Enter the Default Value.        ");
		value_text= new Text(shell, SWT.SINGLE | SWT.BORDER);
		value_text.setText("0");
		value_text.setLayoutData(gridData);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		label = new Label(shell, SWT.LEFT);
		label.setText("4. Enter the size of Bits wide.");
		final Combo cmb_Bits_wide = new Combo(shell, SWT.SINGLE | SWT.BORDER|SWT.READ_ONLY);
		cmb_Bits_wide.setLayoutData(gridData);
		cmb_Bits_wide.setItems(new String[]{"8","16","32","64"});
		cmb_Bits_wide.select(0);
		
		// detect register type.
		type_cmb.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent event) {
				if (type_cmb.getSelectionIndex() == 0){//HEX
					value_text.setText("0");
					cmb_Bits_wide.removeAll();
					cmb_Bits_wide.setItems(new String[]{"32"});
					cmb_Bits_wide.select(0);
				}
				else if (type_cmb.getSelectionIndex() == 1){//UINT
					value_text.setText("0");
					cmb_Bits_wide.removeAll();
					cmb_Bits_wide.setItems(new String[]{"8","16","32","64"});
					cmb_Bits_wide.select(0);
				}
				else if (type_cmb.getSelectionIndex() == 2){//BOOL
				 	value_text.setText("true");
					cmb_Bits_wide.removeAll();
					cmb_Bits_wide.setItems(new String[]{"8"});
					cmb_Bits_wide.select(0);
				}
				else if (type_cmb.getSelectionIndex() == 3){//FLOAT
					value_text.setText("0");
					cmb_Bits_wide.removeAll();
					cmb_Bits_wide.setItems(new String[]{"32","64"});
					cmb_Bits_wide.select(0);
				}
			}
		});
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		create_btn = new Button(shell, SWT.PUSH);
		create_btn.setText("Ok");
		create_btn.setLayoutData(gridData);
		
		cancel_btn = new Button(shell, SWT.PUSH);
		cancel_btn.setText("Cancel");
		cancel_btn.setLayoutData(gridData);

		create_btn.addListener(SWT.Selection, new Listener() {
			public void handleEvent(Event event) {
				reg_name=name_text.getText();
				reg_value=value_text.getText();
				reg_type=type_cmb.getText();
				bits_wide=cmb_Bits_wide.getText();
				shell.dispose();
			}
		});

		cancel_btn.addListener(SWT.Selection, new Listener() {
			public void handleEvent(Event event) {
				reg_type="canceled";
				//value = null;
				shell.dispose();
			}
		});

		shell.addListener(SWT.Traverse, new Listener() {
			public void handleEvent(Event event) {
				if (event.detail == SWT.TRAVERSE_ESCAPE)
					event.doit = false;
			}
		});

		
		shell.pack();
		shell.open();

		Display display = parent.getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}

		return value;
	}

	public static String main(String[] args, Composite parent) {
		
		String result;
		Shell shell = parent.getShell();
		Dialog_RegisterInput dialog = new Dialog_RegisterInput(shell);
		dialog.open();
		result=(reg_name+","+reg_value+","+reg_type+","+bits_wide);
		return result;
		
	}
}
