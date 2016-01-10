package kr.co.twoblock.component.wizard;

import org.eclipse.swt.SWT;
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
import org.eclipse.swt.widgets.Spinner;
import org.eclipse.swt.widgets.Text;

public class PortInputDialog extends Dialog {
	private static String port_name;
	private static String port_type;
	private static String port_data_type;
	private static String port_count;
	Double value;
	/**
	 * @param parent
	 */
	public PortInputDialog(Shell parent) {
		super(parent);
	}

	/**
	 * @param parent
	 * @param style
	 */
	public PortInputDialog(Shell parent, int style) {
		super(parent, style);
	}

	/**
	 * Makes the dialog visible.
	 * 
	 * @return
	 */
	public Double open() {
		Text name_text;
		Button create_btn;
		Button cancel_btn;
		Spinner count;
		Combo type_cmb;
		Combo data_type_cmb;
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
		shell.setText("Enter Port Information");
		shell.setBounds(400,400,500,500);
		shell.setLayout(new GridLayout(1, true));

		label = new Label(shell, SWT.LEFT);
		label.setText("1. Enter the Port Name");
		label.setLayoutData(gridData);

		name_text = new Text(shell, SWT.SINGLE | SWT.BORDER);
		name_text.setLayoutData(gridData);
		name_text.setText(port_name);
		
		seperator = new Label(shell, SWT.HORIZONTAL | SWT.SEPARATOR);
		seperator.setLayoutData(gridData);
		
		
		label = new Label(shell, SWT.LEFT);
		label.setText("2. Select the Port Type");
		type_cmb= new Combo(shell, SWT.DROP_DOWN |SWT.READ_ONLY );
		type_cmb.setItems(new String[]
				{"sc_in","sc_out","sc_inout","sc_in_rv","sc_out_rv","sc_inout_rv"});
			type_cmb.setText(port_type);
		
		
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
		count.setLayoutData(gridData);
		count.setSelection(1);
		count.setMinimum(1);
			
		
		
		create_btn = new Button(shell, SWT.PUSH);
		create_btn.setText("Ok");
		//create_btn.setText("C&reate@Ctrl+W");
		create_btn.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
		
		cancel_btn = new Button(shell, SWT.PUSH);
		cancel_btn.setText("Cancel");
		cancel_btn.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));

		//check input data.
//		text.addListener(SWT.Modify, new Listener() {
//			public void handleEvent(Event event) {
//				try {
//					value = new Double(text.getText());
//					buttonOK.setEnabled(true);
//				} catch (Exception e) {
//					buttonOK.setEnabled(true);
//				}
//			}
//		});

//		shell.addKeyListener(new KeyAdapter()
//		{	
//			public void keyPressed(KeyEvent e)
//			{
//				if(e.keyCode == SWT.ESC)
//				{
//					System.out.println ("sss");
//				}
//
//			}
//		});
		
		
		create_btn.addListener(SWT.Selection, new Listener() {
			public void handleEvent(Event event) {
				port_name=name_text.getText();
				port_type=type_cmb.getText();
				port_data_type=data_type_cmb.getText();
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
		port_type="sc_in";
		port_name="";
		port_data_type="bool";
		String result;
		Shell shell = new Shell();
		PortInputDialog dialog = new PortInputDialog(shell);
		System.out.println("dialog.open()="+dialog.open());
		result=(port_type+","+port_data_type+","+port_name+","+port_count);
		return result;
		
	}

	public static String main(String name, String p_type, String d_type) {
		// TODO Auto-generated method stub
		port_type=p_type;
		port_name=name;
		port_data_type=d_type;
		String result;
		Shell shell = new Shell();
		PortInputDialog dialog = new PortInputDialog(shell);
		System.out.println("dialog.open()="+dialog.open());
		result=(port_type+","+port_data_type+","+port_name+","+port_count);
		return result;
	}
}
