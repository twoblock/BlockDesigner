package com.twoblock.blockdesigner.modulewizard;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
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
import org.eclipse.swt.widgets.Spinner;
import org.eclipse.swt.widgets.Text;

public class Dialog_PortInput extends Dialog {
	private static String port_name;
	private static String port_type;
	private static String port_data_type;
	private static String port_count;
	Double value;
	private Text rv_bit;
	private Combo data_type_cmb;
	/**
	 * @param parent
	 */
	public Dialog_PortInput(Shell parent) {
		super(parent);
	}

	/**
	 * @param parent
	 * @param style
	 */
	public Dialog_PortInput(Shell parent, int style) {
		super(parent, style);
	}

	/**
	 * Makes the dialog visible.
	 * 
	 * @return
	 */
	public Double open() {
		final Text name_text;
		Button create_btn;
		Button cancel_btn;
		final Spinner count;
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

		GridData gridDataHoFILL= new GridData();
		gridDataHoFILL.horizontalSpan = 1;
		gridDataHoFILL.horizontalAlignment=GridData.FILL;
		gridDataHoFILL.grabExcessHorizontalSpace=true;
		
		Shell parent = getParent();
		final Shell shell = new Shell(parent, SWT.TITLE | SWT.BORDER | SWT.APPLICATION_MODAL);
		shell.setText("Enter Port Information");
		shell.setBounds(400,400,500,700);
		shell.setLayout(new GridLayout(1, true));

		label = new Label(shell, SWT.LEFT);
		label.setText("1. Enter the Port Name");
//		label.setLayoutData(gridData);

		name_text = new Text(shell, SWT.FILL | SWT.BORDER);
		name_text.setLayoutData(gridDataHoFILL);
		name_text.setText(port_name);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		
		label = new Label(shell, SWT.LEFT);
		label.setText("2. Select the Port Type");
		type_cmb= new Combo(shell, SWT.DROP_DOWN |SWT.READ_ONLY );
		type_cmb.setItems(new String[] 
				{ "sc_in", "sc_out", "sc_inout", "sc_in_rv", "sc_out_rv", "sc_inout_rv"
				,"BD_AHBPort_MM","BD_AHBPort_MS","BD_AHBPort_SM","BD_AHBPort_SS"
				,"BD_AHBLitePort_MM","BD_AHBLitePort_MS","BD_AHBLitePort_SM","BD_AHBLitePort_SS"});
		type_cmb.setText(port_type);
		type_cmb.addSelectionListener(new SelectionListener() {
			
			@Override
			public void widgetSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				String seleted = type_cmb.getText();
				if (seleted.equals("sc_in_rv") || seleted.equals("sc_out_rv") || seleted.equals("sc_inout_rv")) {
					rv_bit.setEnabled(true);
					data_type_cmb.removeAll();
					data_type_cmb.setEnabled(false);
				}else if (seleted.equals("sc_in") || seleted.equals("sc_out") || seleted.equals("sc_inout")) {
					data_type_cmb.setItems(new String[]
							{"bool","int","char","bit"});
					data_type_cmb.setEnabled(true);
					rv_bit.setEnabled(false);
				}else if(seleted.equals("BD_AHBPort_MM") || seleted.equals("BD_AHBPort_MS") || seleted.equals("BD_AHBPort_SM")||
						seleted.equals("BD_AHBPort_SS") || seleted.equals("BD_AHBLitePort_MM") || seleted.equals("BD_AHBLitePort_MS")||
						seleted.equals("BD_AHBLitePort_SM") || seleted.equals("BD_AHBLitePort_SS")){
					if(seleted.contains("MM") || seleted.contains("MS")){
						data_type_cmb.removeAll();
						data_type_cmb.add("Master");
						data_type_cmb.select(0);
						data_type_cmb.setText("Master");
					}else if(seleted.contains("SM") || seleted.contains("SS")){
						data_type_cmb.removeAll();
						data_type_cmb.add("Slave");
						data_type_cmb.select(0);
						data_type_cmb.setText("Slave");
					}
					rv_bit.setEnabled(false);
				}
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				
			}
		});
		
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		label = new Label(shell, SWT.LEFT);
		label.setText("3. Select the Data Type");
		data_type_cmb= new Combo(shell, SWT.DROP_DOWN |SWT.READ_ONLY );
		data_type_cmb.setItems(new String[]
				{"bool","int","char","bit"});
		data_type_cmb.setText(port_data_type);
		
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		label = new Label(shell, SWT.LEFT);
		label.setText("4. Enter the number of Ports of this unique port type.");
		count= new Spinner(shell, SWT.NULL);
		count.setLayoutData(gridDataHoFILL);
		count.setSelection(1);
		count.setMinimum(1);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		label = new Label(shell, SWT.LEFT);
		label.setText("5. If you select 'rv' Type.(Bit size)");
		rv_bit = new Text(shell, SWT.BORDER);
		rv_bit.setLayoutData(gridDataHoFILL);
		rv_bit.setEnabled(false);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		create_btn = new Button(shell, SWT.PUSH);
		create_btn.setText("Ok");
		//create_btn.setText("C&reate@Ctrl+W");
		create_btn.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
		
		cancel_btn = new Button(shell, SWT.PUSH);
		cancel_btn.setText("Cancel");
		cancel_btn.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));	
		
		create_btn.addListener(SWT.Selection, new Listener() {
			public void handleEvent(Event event) {
				port_name=name_text.getText();
				port_type=type_cmb.getText();
				if(data_type_cmb.getEnabled()==true){
					port_data_type=data_type_cmb.getText();
				}
				if(!rv_bit.getText().equals("")){
					port_data_type=rv_bit.getText();
				}
				port_count=count.getText();
				shell.dispose();
			}
		});

		cancel_btn.addListener(SWT.Selection, new Listener() {
			public void handleEvent(Event event) {
				port_data_type="canceled";
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

		shell.getShell().pack();
		Shell shellopen = shell.getShell();
		shellopen.open();

		Display display = parent.getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}

		return value;
	}

	
	public static String main(String[] args, Composite parent) {
		port_type="sc_in";
		port_name="";
		port_data_type="bool";
		String result;
		Shell shell = parent.getShell();
		Dialog_PortInput dialog = new Dialog_PortInput(shell);
		dialog.open();
		result=(port_type+","+port_data_type+","+port_name+","+port_count);
		return result;
	}
	// for edit.
	public static String main(String name, String p_type, String d_type, Composite parent) {
		// TODO Auto-generated method stub
		port_type=p_type;
		port_name=name;
		port_data_type=d_type;
		String result;
		Shell shell = parent.getShell();
		Dialog_PortInput dialog = new Dialog_PortInput(shell);
		System.out.println("dialog.open()="+dialog.open());
		result=(port_type+","+port_data_type+","+port_name+","+port_count);
		return result;
	}
}
