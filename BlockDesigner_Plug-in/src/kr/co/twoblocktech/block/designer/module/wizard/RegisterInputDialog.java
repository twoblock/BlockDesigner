package kr.co.twoblocktech.block.designer.module.wizard;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

public class RegisterInputDialog extends Dialog {
	private static String reg_name;
	private static String reg_value;
	private static String reg_type;
	Double value;
	/**
	 * @param parent
	 */
	public RegisterInputDialog(Shell parent) {
		super(parent);
	}

	/**
	 * @param parent
	 * @param style
	 */
	public RegisterInputDialog(Shell parent, int style) {
		super(parent, style);
	}

	/**
	 * Makes the dialog visible.
	 * 
	 * @return
	 */
	public Double open() {
		Text name_text;
		Text value_text;
		Button create_btn;
		Button cancel_btn;
		Combo type_cmb;
		Label label;
		Label seperator;
		
		GridData gridData;
		gridData = new GridData();
		gridData.horizontalSpan = 1;
		gridData.horizontalAlignment=GridData.BEGINNING;
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
				{"bool","int","char","bit"});
		type_cmb.setText("bool");
		type_cmb.setLayoutData(gridData);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
				
		label = new Label(shell, SWT.LEFT);
		label.setText("3. Enter the Default Value.        ");
		value_text= new Text(shell, SWT.SINGLE | SWT.BORDER);
		value_text.setText("true");
		value_text.setLayoutData(gridData);
		
		// detect register type.
		type_cmb.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent event){
				if(type_cmb.getSelectionIndex()==0) 		value_text.setText("true");
				else if(type_cmb.getSelectionIndex()==1) 	value_text.setText("0");
				else if(type_cmb.getSelectionIndex()==2) 	value_text.setText("0");
				else if(type_cmb.getSelectionIndex()==3) 	value_text.setText("16");
			}
		});
		
		
		
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

	public static String main(String[] args) {
		
		String result;
		Shell shell = new Shell();
		RegisterInputDialog dialog = new RegisterInputDialog(shell);
		System.out.println("dialog.open()="+dialog.open());
		result=(reg_name+","+reg_value+","+reg_type);
		return result;
		
	}
}
