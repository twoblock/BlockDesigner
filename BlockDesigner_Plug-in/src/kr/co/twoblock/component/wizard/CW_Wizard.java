package kr.co.twoblock.component.wizard;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.wizard.IWizardPage;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.jface.wizard.WizardDialog;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CCombo;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.DirectoryDialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;

/**
 * This class displays a ComponentWizard using a wizard
 */
public class CW_Wizard {
	static {
		System.setProperty("user.dir", "libBD_core");
//		System.loadLibrary("libBD_core");
		try {
            System.loadLibrary("libBD_core"); //$NON-NLS-1$
        } catch (Exception e) {
            e.printStackTrace();
            MessageDialog.openInformation(null, "HelloWorld", "HelloWorld Catch: " + e.getMessage());
        }
	}

	public native String ComponentCreate(String msg);

	public String component_name;
	public String component_location;
	public int port_count;
	public int reg_count;
	public int para_count;
	public TableItem[] port_item = new TableItem[100];
	public TableItem[] sen_item = new TableItem[100];
	public TableItem[] reg_item = new TableItem[100];
	public TableItem[] para_item = new TableItem[100];
	public Text pro_name;
	public String pro_type = "SC_METHOD";
	public CCombo[] combo = new CCombo[100];
	public boolean sen_checked = false;
	WizardPage page;

	/**
	 * Runs the application
	 */

	public void run(Display display) {
		// Create the parent shell for the dialog, but don't show it
		Shell shell = new Shell(display);
		// Create the dialog
		WizardDialog dlg = new WizardDialog(shell, new ComponentWizard(this));
		dlg.setPageSize(350, 250);

		dlg.open();

		// Dispose the display
//		display.dispose();
	}

	/**
	 * The application entry point
	 * 
	 * @param args
	 *            the command line arguments
	 */
	public static void main(String[] args) {
		//new CW_Wizard().run();

	}
}

/**
 * This class shows a satisfaction survey
 */
class ComponentWizard extends Wizard {
	private CW_Wizard cw;

	public ComponentWizard(CW_Wizard w) {
		cw = w;
		setWindowTitle("Component Wizard");
		setDefaultPageImageDescriptor(ImageDescriptor.createFromFile(this.getClass(), "/images/twoblock_logo.png"));

		// Add the pages
		addPage(new Step1_name(cw));
		addPage(new Step2_port(cw));
		addPage(new Step3_register(cw));
		addPage(new Step4_parameter(cw));
		addPage(new Step5_process(cw));
		addPage(new Step6_sensitivity(cw));
		addPage(new Step7_complete(cw));

	}

	/**
	 * Called when user clicks Finish
	 * 
	 * @return boolean
	 */
	public boolean performFinish() {
		// Dismiss the wizard
		return true;
	}

}

class Step1_name extends WizardPage {
	private String saveTarget;
	private Text name_text;
	private CW_Wizard m_w;

	/**
	 * General constructor
	 */
	public Step1_name(CW_Wizard w) {
		super("General");
		m_w = w;
	}

	/**
	 * Creates the page controls
	 */
	public void createControl(Composite parent) {

		Label label;
		Text location_text;
		Button Location_btn;
		GridData gridData1;
		GridData gridData2;
		GridData gridData3;

		Composite composite = new Composite(parent, SWT.NONE);
		GridLayout layout = new GridLayout();
		layout.numColumns = 2;
		composite.setLayout(layout);

		label = new Label(composite, SWT.LEFT);
		label.setText("Step 1 - Enter Component Name and Location.");
		gridData1 = new GridData();
		gridData2 = new GridData();
		gridData3 = new GridData();
		gridData1.horizontalSpan = 1;
		gridData2.horizontalSpan = 2;
		gridData3.horizontalSpan = 2;
		label = new Label(composite, SWT.HORIZONTAL | SWT.SEPARATOR);
		label.setLayoutData(gridData2);

		label = new Label(composite, SWT.LEFT);
		label.setText("Component name?");
		name_text = new Text(composite, SWT.SINGLE | SWT.BORDER);
		gridData1.horizontalAlignment = GridData.BEGINNING;
		gridData1.horizontalAlignment = GridData.FILL;
		gridData1.grabExcessHorizontalSpace = true;
		gridData2.horizontalAlignment = GridData.FILL;
		gridData2.grabExcessHorizontalSpace = true;

		gridData3.horizontalAlignment = GridData.FILL;
		gridData3.verticalAlignment = GridData.FILL;

		label.setLayoutData(gridData1);
		name_text.setLayoutData(gridData1);

		label = new Label(composite, SWT.LEFT);
		label.setText("Location?");
		location_text = new Text(composite, SWT.SINGLE | SWT.READ_ONLY | SWT.BORDER);

		label.setLayoutData(gridData1);
		location_text.setLayoutData(gridData1);
		Location_btn = new Button(composite, SWT.PUSH);
		Location_btn.setLayoutData(gridData3);
		Location_btn.setText("Location");

		// (When you click the Add button)set save location
		Location_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				DirectoryDialog dialog = new DirectoryDialog(composite.getShell());
				dialog.setMessage("Choose a save directory");
				saveTarget = dialog.open();
				if (saveTarget != null) {
					// File directory = new File(saveTarget);
					location_text.setText(saveTarget);
					saveTarget = saveTarget.replace("\\", "/");
					m_w.component_location = saveTarget;
				}
			}
		});
		// setPageComplete(false);
		setControl(composite);
	}

	public boolean canFlipToNextPage() {
		return true;
	}

	public IWizardPage getNextPage() {
		m_w.component_name = name_text.getText();
		return super.getNextPage();
	}
}

/**
 * This page Port Definition
 */
class Step2_port extends WizardPage {
	protected int index = 0;
	private CW_Wizard m_w;

	/**
	 * Port Definition constructor
	 */
	public Step2_port(CW_Wizard w) {
		super("Port_Definition");
		m_w = w;
	}

	/**
	 * Creates the controls for this page
	 */
	public void createControl(Composite parent) {

		GridData gd_table = new GridData(SWT.FILL, SWT.TOP, true, false, 2, 1);
		Button AddPort_btn;
		Button EditPort_btn;
		Composite composite = new Composite(parent, SWT.NONE);
		composite.setLayout(new GridLayout(1, false));

		new Label(composite, SWT.LEFT).setText("Step 2 - Add Port Definitions");

		Table po_table = new Table(composite, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		gd_table.heightHint = 120;
		po_table.setLayoutData(gd_table);
		TableColumn po_type = new TableColumn(po_table, SWT.CENTER);
		TableColumn po_data_type = new TableColumn(po_table, SWT.CENTER);
		TableColumn po_name = new TableColumn(po_table, SWT.CENTER);
		// TableColumn po_count = new TableColumn(po_table, SWT.CENTER);
		po_type.setWidth(130);
		po_data_type.setWidth(130);
		po_name.setWidth(180);
		// po_count.setWidth(80);
		po_type.setText("Port Type");
		po_data_type.setText("Port Data Type");
		po_name.setText("Port Name");
		// po_count.setText("Count");
		po_table.setHeaderVisible(true);
		po_table.setLinesVisible(false);
		AddPort_btn = new Button(composite, SWT.PUSH);
		AddPort_btn.setText("   Add   ");
		AddPort_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				String str = PortInputDialog.main(null);
				String[] port_info = str.split(",");
				if (Integer.parseInt(port_info[3]) > 1) {
					for (int i = 1; i <= Integer.parseInt(port_info[3]); i++) {
						m_w.port_item[index] = new TableItem(po_table, SWT.NONE);
						m_w.port_item[index]
								.setText(new String[] { port_info[0], port_info[1], port_info[2] + "_" + i });
						index++;
					}
				} else if (!port_info[1].equals("canceled")) {
					m_w.port_item[index] = new TableItem(po_table, SWT.NONE);
					m_w.port_item[index].setText(new String[] { port_info[0], port_info[1], port_info[2] });
					index++;
				}
			}
		});

		// definition of edit button
		po_table.addListener(SWT.MouseDoubleClick, new Listener() {
			@Override
			public void handleEvent(Event arg0) {
				// TODO Auto-generated method stub
				String name = m_w.port_item[po_table.getSelectionIndex()].getText(2);
				String p_type = m_w.port_item[po_table.getSelectionIndex()].getText(0);
				String d_type = m_w.port_item[po_table.getSelectionIndex()].getText(1);
				String str = PortInputDialog.main(name, p_type, d_type);
				String[] port_info = str.split(",");
				m_w.port_item[po_table.getSelectionIndex()]
						.setText(new String[] { port_info[0], port_info[1], port_info[2] });
			}
		});
		EditPort_btn = new Button(composite, SWT.PUSH);
		EditPort_btn.setText("   Edit   ");
		EditPort_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				String name = m_w.port_item[po_table.getSelectionIndex()].getText(2);
				String p_type = m_w.port_item[po_table.getSelectionIndex()].getText(0);
				String d_type = m_w.port_item[po_table.getSelectionIndex()].getText(1);
				String str = PortInputDialog.main(name, p_type, d_type);
				String[] port_info = str.split(",");
				m_w.port_item[po_table.getSelectionIndex()]
						.setText(new String[] { port_info[0], port_info[1], port_info[2] });
			}
		});

		// WizardDialog dialog = new WizardDialog(composite, new parent ) {
		//
		// @Override
		// protected void createButtonsForButtonBar(Composite parent) {
		// super.createButtonsForButtonBar(parent);
		// Button finishButton = getButton(IDialogConstants.FINISH_ID);
		// finishButton.setText(IDialogConstants.OK_LABEL);
		// }
		// };

		po_table.addListener(SWT.SetData, new Listener() {
			@Override
			public void handleEvent(Event event) {
				// TODO Auto-generated method stub
			}
		});

		setControl(composite);
	}

	public IWizardPage getNextPage() {
		m_w.port_count = index;
		return super.getNextPage();
	}

	public WizardPage getPage(int pageIndex) {
		System.out.println("pageIndex=" + pageIndex);
		if (pageIndex < 5)
			setPageComplete(false);

		return null;
	}
}

/**
 * This page Register Definition.
 */
class Step3_register extends WizardPage {
	protected int index = 0;
	private CW_Wizard m_w;

	/**
	 * Parameter Definition constructor
	 */
	public Step3_register(CW_Wizard w) {
		super("Register Definition");
		m_w = w;
	}

	/**
	 * Creates the controls for this page
	 */
	public void createControl(Composite parent) {
		GridData gd_table = new GridData(SWT.FILL, SWT.TOP, true, false, 2, 1);
		Button AddRegister_btn;
		Composite composite = new Composite(parent, SWT.NONE);
		composite.setLayout(new GridLayout(1, false));

		new Label(composite, SWT.LEFT).setText("Step 3 - Add Register Definitions");

		Table reg_table = new Table(composite, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		gd_table.heightHint = 120;
		reg_table.setLayoutData(gd_table);
		TableColumn reg_name = new TableColumn(reg_table, SWT.CENTER);
		TableColumn reg_reg_name = new TableColumn(reg_table, SWT.CENTER);
		TableColumn reg_type = new TableColumn(reg_table, SWT.CENTER);
		TableColumn reg_value = new TableColumn(reg_table, SWT.CENTER);
		reg_name.setWidth(110);
		reg_reg_name.setWidth(130);
		reg_value.setWidth(150);
		reg_type.setWidth(80);

		reg_name.setText("Register Name");
		reg_reg_name.setText("Register Variable");
		reg_value.setText("Default Value");
		reg_type.setText("Type");

		reg_table.setHeaderVisible(true);
		reg_table.setLinesVisible(false);

		AddRegister_btn = new Button(composite, SWT.PUSH);
		AddRegister_btn.setText("   Add   ");
		AddRegister_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				String str = RegisterInputDialog.main(null);
				String[] reg_info = str.split(",");
				if (!reg_info[2].equals("canceled")) {
					m_w.reg_item[index] = new TableItem(reg_table, SWT.NONE);
					m_w.reg_item[index]
							.setText(new String[] { reg_info[0], "r_" + reg_info[0], reg_info[2], reg_info[1] });
					index++;
				}
			}
		});
		setControl(composite);
	}

	public IWizardPage getNextPage() {
		m_w.reg_count = index;
		return super.getNextPage();
	}
}

/**
 * This page Parameter Definition.
 */
class Step4_parameter extends WizardPage {
	protected int index = 0;
	private CW_Wizard m_w;

	/**
	 * Parameter Definition constructor
	 */
	public Step4_parameter(CW_Wizard w) {
		super("Parameter_Definition");
		m_w = w;
	}

	/**
	 * Creates the controls for this page
	 */
	public void createControl(Composite parent) {
		GridData gd_table = new GridData(SWT.FILL, SWT.TOP, true, false, 2, 1);
		Button AddParameter_btn;
		Composite composite = new Composite(parent, SWT.NONE);
		composite.setLayout(new GridLayout(1, false));

		new Label(composite, SWT.LEFT).setText("Step 4 - Add Parameter Definitions");

		Table pa_table = new Table(composite, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		gd_table.heightHint = 120;
		pa_table.setLayoutData(gd_table);
		TableColumn pa_name = new TableColumn(pa_table, SWT.CENTER);
		TableColumn pa_pa_name = new TableColumn(pa_table, SWT.CENTER);
		TableColumn pa_type = new TableColumn(pa_table, SWT.CENTER);
		TableColumn pa_value = new TableColumn(pa_table, SWT.CENTER);
		pa_name.setWidth(110);
		pa_pa_name.setWidth(130);
		pa_value.setWidth(150);
		pa_type.setWidth(80);

		pa_name.setText("Parameter Name");
		pa_pa_name.setText("Parameter Variable");
		pa_value.setText("Default Value");
		pa_type.setText("Type");

		pa_table.setHeaderVisible(true);
		pa_table.setLinesVisible(false);

		AddParameter_btn = new Button(composite, SWT.PUSH);
		AddParameter_btn.setText("   Add   ");
		AddParameter_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				String str = ParameterInputDialog.main(null);
				String[] pa_info = str.split(",");

				if (!pa_info[2].equals("canceled")) {
					m_w.para_item[index] = new TableItem(pa_table, SWT.NONE);
					m_w.para_item[index]
							.setText(new String[] { pa_info[0], "p_" + pa_info[0], pa_info[2], pa_info[1] });
					index++;
				}
			}
		});
		setControl(composite);
	}

	public IWizardPage getNextPage() {
		m_w.para_count = index;
		return super.getNextPage();
	}
}

/**
 * This page Process Definition.
 */
class Step5_process extends WizardPage {
	// private Text pro_name;
	private Combo pro_cmb;
	private CW_Wizard m_w;

	/**
	 * Parameter Definition constructor
	 */
	public Step5_process(CW_Wizard w) {
		super("Process Definition");
		m_w = w;
	}

	/**
	 * Creates the controls for this page
	 */
	public void createControl(Composite parent) {
		Label label;
		Label text_label;
		Label separator;
		GridData gridData1;
		gridData1 = new GridData();
		gridData1.horizontalSpan = 1;
		gridData1.horizontalAlignment = GridData.FILL;
		gridData1.grabExcessHorizontalSpace = true;
		GridData gridData2;
		gridData2 = new GridData();
		gridData2.horizontalSpan = 2;
		gridData2.horizontalAlignment = GridData.FILL;
		gridData2.grabExcessHorizontalSpace = true;

		Composite composite = new Composite(parent, SWT.NONE);
		composite.setLayout(new GridLayout(2, false));

		label = new Label(composite, SWT.LEFT);
		label.setText("Step 5 - Process Definitions");
		separator = new Label(composite, SWT.HORIZONTAL | SWT.SEPARATOR);
		separator.setLayoutData(gridData2);

		label = new Label(composite, SWT.LEFT);
		label.setText("Process");
		label.setLayoutData(gridData2);
		text_label = new Label(composite, SWT.LEFT);
		text_label.setText("Process name?");
		text_label.setLayoutData(gridData1);
		m_w.pro_name = new Text(composite, SWT.SINGLE | SWT.BORDER);
		m_w.pro_name.setLayoutData(gridData1);
		text_label = new Label(composite, SWT.LEFT);
		text_label.setText("Process Type Select");
		text_label.setLayoutData(gridData1);
		pro_cmb = new Combo(composite, SWT.DROP_DOWN | SWT.READ_ONLY);
		pro_cmb.setItems(new String[] { "SC_METHOD", "SC_THREAD", "SC_CTHREAD" });
		pro_cmb.setText("SC_METHOD");
		pro_cmb.setLayoutData(gridData1);
		pro_cmb.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				m_w.pro_type = pro_cmb.getText();
			}
		});
		setControl(composite);
	}

	public IWizardPage getNextPage() {
		return super.getNextPage();
	}
}

/**
 * This page
 */
class Step6_sensitivity extends WizardPage {
	protected int index = 0;
	protected int tb_index = 0;
	private Table sen_table;
	private CW_Wizard m_w;

	/**
	 * ThanksPage constructor
	 */
	public Step6_sensitivity(CW_Wizard w) {
		super("Sensitive Definition");
		m_w = w;
	}

	/**
	 * Creates the controls for this page
	 */
	public void createControl(Composite parent) {
		GridData gd_table = new GridData(SWT.FILL, SWT.TOP, false, false, 2, 1);
		Composite composite = new Composite(parent, SWT.NONE);
		composite.setLayout(new GridLayout(1, false));

		new Label(composite, SWT.LEFT).setText("Step 6 - Sensitivity Definitions");

		sen_table = new Table(composite, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL | SWT.MULTI);
		gd_table.heightHint = 120;
		sen_table.setLayoutData(gd_table);
		TableColumn port_name = new TableColumn(sen_table, SWT.CENTER);
		TableColumn sen_type = new TableColumn(sen_table, SWT.CENTER);
		sen_type.setWidth(150);
		port_name.setWidth(150);
		sen_type.setText("Sensitivity Type");
		port_name.setText("Port Name");

		sen_table.setHeaderVisible(true);
		sen_table.setLinesVisible(true);

		setControl(composite);
	}

	public IWizardPage getNextPage() {

		if (m_w.sen_checked == false) {
			for (int i = 0; i < 100; i++) {
				m_w.sen_item[i] = new TableItem(sen_table, SWT.NONE);
			}
			m_w.sen_checked = true;
		}

		if (m_w.port_count != index) {
			System.out.println("sensitivity make");
			String col_1;
			index = 0;
			TableEditor editor = new TableEditor(sen_table);
			Color white = new Color(null, 255, 255, 255);
			for (int i = 0; i < m_w.port_count; i++) {
				col_1 = m_w.port_item[i].getText(2);
				System.out.println("index=" + index);

				m_w.sen_item[index].setText(new String[] { col_1 });

				m_w.combo[index] = new CCombo(sen_table, SWT.BORDER | SWT.READ_ONLY);
				m_w.combo[index].add("None");
				m_w.combo[index].add("Negative Edge");
				m_w.combo[index].add("Positive Edge");
				m_w.combo[index].add("Evaluation");
				m_w.combo[index].select(0);
				m_w.combo[index].pack();
				m_w.combo[index].setBackground(white);
				editor.grabHorizontal = true;
				editor.horizontalAlignment = SWT.CENTER;
				editor.setEditor(m_w.combo[index], m_w.sen_item[index], 1);
				editor = new TableEditor(sen_table);
				index++;
			}
			// m_w.sen_checked = true;
		}

		return super.getNextPage();
	}
}

/**
 * This page
 */
class Step7_complete extends WizardPage {
	private CW_Wizard m_w;

	/**
	 * ThanksPage constructor
	 */
	public Step7_complete(CW_Wizard w) {
		super("Successfully Created");
		m_w = w;
	}

	/**
	 * Creates the controls for this page
	 */
	public void createControl(Composite parent) {
		Label label = new Label(parent, SWT.CENTER);
		label.setText("Component Successfully Created");
		setControl(label);
	}

	public IWizardPage getNextPage() {

		/// Sending component wizard data by JNI
		String component_info_str;
		int state_temp = 0;
		int sen_count = 0;
		StringBuilder str = new StringBuilder(m_w.component_name + ",");
		str.append(m_w.component_location + ",");
		str.append(m_w.port_count + ",");
		// port info append
		for (int i = 0; i < m_w.port_count; i++) {
			if (m_w.port_item[i].getText(0).equals("sc_in"))
				state_temp = 0;
			else if (m_w.port_item[i].getText(0).equals("sc_out"))
				state_temp = 1;
			else if (m_w.port_item[i].getText(0).equals("sc_inout"))
				state_temp = 2;
			else if (m_w.port_item[i].getText(0).equals("sc_in_rv"))
				state_temp = 3;
			else if (m_w.port_item[i].getText(0).equals("sc_out_rv"))
				state_temp = 4;
			else if (m_w.port_item[i].getText(0).equals("sc_inout_rv"))
				state_temp = 5;
			str.append(m_w.port_item[i].getText(2) + "," + state_temp + "," + m_w.port_item[i].getText(1) + ",");
		}
		// register info append
		str.append(m_w.reg_count + ",");
		for (int i = 0; i < m_w.reg_count; i++) {
			str.append(m_w.reg_item[i].getText(0) + "," + m_w.reg_item[i].getText(2) + "," + m_w.reg_item[i].getText(3)
					+ ",");
		}
		// parameter info append
		str.append(m_w.para_count + ",");
		for (int i = 0; i < m_w.para_count; i++) {
			str.append(m_w.para_item[i].getText(0) + "," + m_w.para_item[i].getText(2) + ","
					+ m_w.para_item[i].getText(3) + ",");
		}
		if (m_w.pro_type.equals("SC_METHOD"))
			state_temp = 0;
		else if (m_w.pro_type.equals("SC_THREAD"))
			state_temp = 1;
		else if (m_w.pro_type.equals("SC_CTHREAD"))
			state_temp = 2;
		str.append(m_w.pro_name.getText() + ",");
		str.append(state_temp + ",");
		// sensitivity info append
		for (int i = 0; i < m_w.port_count; i++) {
			if (m_w.combo[i].getSelectionIndex() != 0)
				sen_count++;
		}
		str.append(sen_count + ",");
		for (int i = 0; i < m_w.port_count; i++) {
			state_temp = m_w.combo[i].getSelectionIndex();
			if (state_temp != 0)
				str.append(m_w.sen_item[i].getText(0) + "," + state_temp + ",");
		}
		component_info_str = str.toString();
		System.out.println(component_info_str);
		m_w.ComponentCreate(component_info_str);
		return super.getNextPage();
	}
}
