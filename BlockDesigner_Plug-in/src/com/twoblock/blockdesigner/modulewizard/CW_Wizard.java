package com.twoblock.blockdesigner.modulewizard;

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
import org.eclipse.swt.events.SelectionListener;
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
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import com.twoblock.blockdesigner.command.Handler_ModuleWizard;

/**
 * This class displays a ComponentWizard using a wizard
 */
public class CW_Wizard extends Handler_ModuleWizard {
	
	static {
		try{
			System.load("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/libBD_core.so");
		}catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load(MD_Wizard)");
		}
	}
	public native String ComponentCreate(String msg);
	public String component_name;
	public String component_location;
	public String Module_Type="CPU";
	public int port_count;
	public int reg_count;
	public int para_count;
	public int sens_state=1;
	public int sens_count=0;
	public TableItem[] port_item = new TableItem[100];
	public TableItem[] sen_item = new TableItem[100];
	public TableItem[] reg_item = new TableItem[100];
	public TableItem[] para_item = new TableItem[100];
	public Text pro_name;
	public String pro_type = "SC_METHOD";
	public CCombo[] combo = new CCombo[100];
	public boolean sen_checked = false;
	WizardPage page;

	public JSONObject obj_JSON = new JSONObject();
	public JSONObject obj_ModuleWizard = new JSONObject();
	public JSONObject obj_Port = new JSONObject();
	public JSONObject obj_Register = new JSONObject();
	public JSONObject obj_Parameter = new JSONObject();
	public JSONObject obj_Sensitivity = new JSONObject();
	public JSONArray arr_Port_List = new JSONArray();
	public JSONArray arr_Register_List = new JSONArray();
	public JSONArray arr_Parameter_List = new JSONArray();
	public JSONArray arr_Sensitivity_List = new JSONArray();
	
	/**
	 * Runs the application
	 */
	public void run(Display display) {
		// Create the parent shell for the dialog, but don't show it
		Shell shell = new Shell(display);
		// Create the dialog
		WizardDialog dlg = new WizardDialog(shell, new ComponentWizard(this));
		WizardDialog dlg2 = new WizardDialog(dlg.getShell(), new ComponentWizard(this));
		dlg.setTitle("");
		dlg.setPageSize(350, 250);
		
		dlg2.open();
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
		final Text location_text;
		Button Location_btn;
		GridData gridData1;
		GridData gridData2;
		GridData gridData3;

		final Composite composite = new Composite(parent, SWT.NONE);
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
		label = new Label(composite, SWT.HORIZONTAL | SWT.SEPARATOR);
		label.setLayoutData(gridData2);
		label = new Label(composite, SWT.LEFT);
		label.setText("Select Module Type?");
		
		Combo cmb_ModuleType = new Combo(composite, SWT.READ_ONLY);
		cmb_ModuleType.setLayoutData(gridData2);
		cmb_ModuleType.setItems(new String[] {"CPU","BUS","MEM","OTHERS"});
		cmb_ModuleType.select(0);
		cmb_ModuleType.addSelectionListener(new SelectionListener() {
			
			@Override
			public void widgetSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				m_w.Module_Type = cmb_ModuleType.getText();
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				
			}
		});
		
		
		setControl(composite);
	}

	public boolean canFlipToNextPage() {
		return true;
	}

	@SuppressWarnings("unchecked")
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

		final Table po_table = new Table(composite, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
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
		AddPort_btn.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		AddPort_btn.addSelectionListener(new SelectionAdapter() {
			@SuppressWarnings("unchecked")
			public void widgetSelected(SelectionEvent e) {
				String str = Dialog_PortInput.main(null,parent);
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
				String str = Dialog_PortInput.main(name, p_type, d_type,parent);
				String[] port_info = str.split(",");
				m_w.port_item[po_table.getSelectionIndex()]
						.setText(new String[] { port_info[0], port_info[1], port_info[2] });
			}
		});
		EditPort_btn = new Button(composite, SWT.PUSH);
		EditPort_btn.setText("   Edit   ");
		EditPort_btn.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		EditPort_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				String name = m_w.port_item[po_table.getSelectionIndex()].getText(2);
				String p_type = m_w.port_item[po_table.getSelectionIndex()].getText(0);
				String d_type = m_w.port_item[po_table.getSelectionIndex()].getText(1);
				String str = Dialog_PortInput.main(name, p_type, d_type, parent);
				String[] port_info = str.split(",");
				m_w.port_item[po_table.getSelectionIndex()]
						.setText(new String[] { port_info[0], port_info[1], port_info[2] });
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

		final Table reg_table = new Table(composite, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		gd_table.heightHint = 120;
		reg_table.setLayoutData(gd_table);
		TableColumn reg_name = new TableColumn(reg_table, SWT.CENTER);
		TableColumn reg_reg_name = new TableColumn(reg_table, SWT.CENTER);
		TableColumn reg_type = new TableColumn(reg_table, SWT.CENTER);
		TableColumn reg_value = new TableColumn(reg_table, SWT.CENTER);
		TableColumn reg_bits_wide = new TableColumn(reg_table, SWT.CENTER);
		reg_name.setWidth(110);
		reg_reg_name.setWidth(130);
		reg_type.setWidth(80);
		reg_value.setWidth(110);
		reg_bits_wide.setWidth(40);
		

		reg_name.setText("Register Name");
		reg_reg_name.setText("Register Variable");
		reg_value.setText("Default Value");
		reg_bits_wide.setText("Bits Wide");
		reg_type.setText("Type");

		reg_table.setHeaderVisible(true);
		reg_table.setLinesVisible(false);

		AddRegister_btn = new Button(composite, SWT.PUSH);
		AddRegister_btn.setText("   Add   ");
		AddRegister_btn.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
		AddRegister_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				String str = Dialog_RegisterInput.main(null,parent);
				String[] reg_info = str.split(",");
				if (!reg_info[2].equals("canceled")) {
					m_w.reg_item[index] = new TableItem(reg_table, SWT.NONE);
					m_w.reg_item[index]
							.setText(new String[] { reg_info[0], "r_" + reg_info[0], reg_info[2], reg_info[1],reg_info[3] });
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

		final Table pa_table = new Table(composite, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		gd_table.heightHint = 120;
		pa_table.setLayoutData(gd_table);
		TableColumn pa_name = new TableColumn(pa_table, SWT.CENTER);
		TableColumn pa_pa_name = new TableColumn(pa_table, SWT.CENTER);
		TableColumn pa_type = new TableColumn(pa_table, SWT.CENTER);
		TableColumn pa_value = new TableColumn(pa_table, SWT.CENTER);
		TableColumn pa_bits_wide = new TableColumn(pa_table, SWT.CENTER);
		pa_name.setWidth(110);
		pa_pa_name.setWidth(130);
		pa_value.setWidth(110);
		pa_bits_wide.setWidth(40);
		pa_type.setWidth(80);

		pa_name.setText("Parameter Name");
		pa_pa_name.setText("Parameter Variable");
		pa_value.setText("Default Value");
		pa_type.setText("Type");
		pa_bits_wide.setText("Bits Wide");

		pa_table.setHeaderVisible(true);
		pa_table.setLinesVisible(false);

		AddParameter_btn = new Button(composite, SWT.PUSH);
		AddParameter_btn.setText("   Add   ");
		AddParameter_btn.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
		AddParameter_btn.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				String str = Dialog_ParameterInput.main(null,parent);
				String[] pa_info = str.split(",");

				if (!pa_info[2].equals("canceled")) {
					m_w.para_item[index] = new TableItem(pa_table, SWT.NONE);
					m_w.para_item[index]
							.setText(new String[] { pa_info[0], "p_" + pa_info[0], pa_info[2], pa_info[1], pa_info[3] });
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
		GridData gd_table = new GridData(SWT.FILL, SWT.TOP, true, true, 2, 1);
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
		if(m_w.sens_state == 1){
			
			if (m_w.sen_checked == false) {
				for (int i = 0; i < 100; i++) {
					m_w.sen_item[i] = new TableItem(sen_table, SWT.NONE);
				}
				m_w.sen_checked = true;
			}

			if (m_w.port_count != index) {
				String col_1 = null;
				index = 0;
				TableEditor editor = new TableEditor(sen_table);
				Color white = new Color(null, 255, 255, 255);
				for (int i = 0; i < m_w.port_count; i++) {
						if(!m_w.port_item[i].getText(0).contains("AHB")){
							System.err.println(m_w.port_item[i].getText(0)+"/i="+i+"/index="+index);
							col_1 = m_w.port_item[i].getText(2);
							m_w.sen_item[index].setText(new String[] { col_1 });
							m_w.combo[index] = new CCombo(sen_table, SWT.BORDER | SWT.READ_ONLY);
							m_w.combo[index].add("None");
							m_w.combo[index].add("Negative Edge");
							m_w.combo[index].add("Positive Edge");
							m_w.combo[index].add("Evaluation");
							m_w.combo[index].select(0);
							m_w.combo[index].pack();
							m_w.combo[index].setBackground(white);
							m_w.combo[index].addSelectionListener(new SelectionListener() {
								final int cmb_index=index;
								@Override
								public void widgetSelected(SelectionEvent arg0) {
									// TODO Auto-generated method stub
									String temp = m_w.combo[cmb_index].getText();
									m_w.combo[cmb_index].setText(temp);
									System.err.println("m_w.combo["+cmb_index+"]"+" = "+m_w.combo[cmb_index].getText());
								}
								
								@Override
								public void widgetDefaultSelected(SelectionEvent arg0) {
									// TODO Auto-generated method stub
									
								}
							});
							editor.grabHorizontal = true;
							editor.horizontalAlignment = SWT.CENTER;
							editor.setEditor(m_w.combo[index], m_w.sen_item[index], 1);
							editor = new TableEditor(sen_table);
							index++;
						}
					
				}
				m_w.sens_count=index;
			}
			
			m_w.sens_state =0;
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
//			if (m_w.port_item[i].getText(0).equals("sc_in"))
//				state_temp = 0;
//			else if (m_w.port_item[i].getText(0).equals("sc_out"))
//				state_temp = 1;
//			else if (m_w.port_item[i].getText(0).equals("sc_inout"))
//				state_temp = 2;
//			else if (m_w.port_item[i].getText(0).equals("sc_in_rv"))
//				state_temp = 3;
//			else if (m_w.port_item[i].getText(0).equals("sc_out_rv"))
//				state_temp = 4;
//			else if (m_w.port_item[i].getText(0).equals("sc_inout_rv"))
//				state_temp = 5;
			str.append(m_w.port_item[i].getText(2) + "," + m_w.port_item[i].getText(0) + "," + m_w.port_item[i].getText(1) + ",");
		}
		// register info append
		str.append(m_w.reg_count + ",");
		for (int i = 0; i < m_w.reg_count; i++) {
			str.append(m_w.reg_item[i].getText(0) + "," + m_w.reg_item[i].getText(2) + "," 
					+ m_w.reg_item[i].getText(3) + "," + m_w.reg_item[i].getText(4) + ",");
		}
		// parameter info append
		str.append(m_w.para_count + ",");
		for (int i = 0; i < m_w.para_count; i++) {
			str.append(m_w.para_item[i].getText(0) + "," + m_w.para_item[i].getText(2) + ","
					+ m_w.para_item[i].getText(3) + "," + m_w.para_item[i].getText(4) + ",");
		}
//		if (m_w.pro_type.equals("SC_METHOD"))
//			state_temp = 0;
//		else if (m_w.pro_type.equals("SC_THREAD"))
//			state_temp = 1;
//		else if (m_w.pro_type.equals("SC_CTHREAD"))
//			state_temp = 2;
		str.append(m_w.pro_name.getText() + ",");
		str.append(m_w.pro_type + ",");
		// sensitivity info append
		for (int i = 0; i < m_w.sens_count; i++) {
			if (m_w.combo[i].getSelectionIndex() != 0 )
				sen_count++;
		}
		str.append(sen_count + ",");
		for (int i = 0; i < m_w.sens_count; i++) {
			state_temp = m_w.combo[i].getSelectionIndex();
			if (state_temp != 0)
				str.append(m_w.sen_item[i].getText(0) + "," + m_w.combo[i].getText() + ",");
		}
		component_info_str = str.toString();
		StringToJSON(component_info_str);
		System.err.println(m_w.obj_JSON.toJSONString());
		
		m_w.ComponentCreate(m_w.obj_JSON.toJSONString());
		return super.getNextPage();
	}
	
	@SuppressWarnings("unchecked")
	void StringToJSON(String component_info_str){
		String[] modulewizardinfo = component_info_str.split(",");
		m_w.obj_ModuleWizard.put("module_name", modulewizardinfo[0]);
		m_w.obj_ModuleWizard.put("module_location", modulewizardinfo[1]);
		m_w.obj_ModuleWizard.put("module_type", m_w.Module_Type);
		int ptr_index=0;
		if(modulewizardinfo[2].equals("0")){
			ptr_index=2;
		}
		else {
			for (int port_index=0; port_index< Integer.parseInt(modulewizardinfo[2]); port_index++) {
				m_w.obj_Port = new JSONObject();
				m_w.obj_Port.put("port_name",modulewizardinfo[port_index*3+3]);
				m_w.obj_Port.put("sc_type",modulewizardinfo[port_index*3+4]);
				m_w.obj_Port.put("data_type",modulewizardinfo[port_index*3+5]);
				
				m_w.arr_Port_List.add(port_index,m_w.obj_Port);
				
				ptr_index=port_index*3+5;
			}
		}
		
		// port_index*3+5 = 11
		int reg_ptr = ptr_index;
		if(modulewizardinfo[reg_ptr+1].equals("0")){
			ptr_index++;
		}
		else{
			for (int reg_index = 0; reg_index < Integer.parseInt(modulewizardinfo[reg_ptr + 1]); reg_index++) {
				m_w.obj_Register = new JSONObject();
				m_w.obj_Register.put("reg_name", modulewizardinfo[reg_index * 4 + reg_ptr + 2]);
				m_w.obj_Register.put("data_type", modulewizardinfo[reg_index * 4 + reg_ptr + 3]);
				m_w.obj_Register.put("value", modulewizardinfo[reg_index * 4 + reg_ptr + 4]);
				m_w.obj_Register.put("data_size", Integer.parseInt(modulewizardinfo[reg_index * 4 + reg_ptr + 5]));

				m_w.arr_Register_List.add(reg_index, m_w.obj_Register);
				ptr_index = reg_index * 4 + reg_ptr + 5;
			}
		}
//		reg_index*4+reg_ptr+5 =16
		int par_ptr=ptr_index;
		if(modulewizardinfo[par_ptr+1].equals("0"))
			ptr_index++;
		else{
			for(int par_index=0; par_index<Integer.parseInt(modulewizardinfo[par_ptr+1]); par_index++){
				m_w.obj_Parameter = new JSONObject();
				m_w.obj_Parameter.put("par_name", modulewizardinfo[par_index*4+par_ptr+2]);
				m_w.obj_Parameter.put("data_type", modulewizardinfo[par_index*4+par_ptr+3]);
				m_w.obj_Parameter.put("value", modulewizardinfo[par_index*4+par_ptr+4]);
				m_w.obj_Parameter.put("data_size", Integer.parseInt(modulewizardinfo[par_index*4+par_ptr+5])); // "16"
				m_w.arr_Parameter_List.add(par_index, m_w.obj_Parameter);
//				m_w.arr_Parameter_List.add(m_w.obj_Parameter);
				ptr_index=par_index*4+par_ptr+5;
			}
		}
		
//		ptr_index=par_index*4+par_ptr+5= 25
		m_w.obj_ModuleWizard.put("process_name", modulewizardinfo[ptr_index+1]);
		m_w.obj_ModuleWizard.put("process_type", modulewizardinfo[ptr_index+2]);
		
		int sen_ptr=ptr_index;
		for(int sen_index=0; sen_index<Integer.parseInt(modulewizardinfo[sen_ptr+3]); sen_index++){
			m_w.obj_Sensitivity = new JSONObject();
			m_w.obj_Sensitivity.put("port_name", modulewizardinfo[sen_index*2+sen_ptr+4]);
			m_w.obj_Sensitivity.put("sens_type", modulewizardinfo[sen_index*2+sen_ptr+5]);
			m_w.arr_Sensitivity_List.add(sen_index,m_w.obj_Sensitivity);
//			m_w.arr_Sensitivity_List.add(m_w.obj_Sensitivity);
		}
		m_w.obj_ModuleWizard.put("port", m_w.arr_Port_List);
		m_w.obj_ModuleWizard.put("register", m_w.arr_Register_List);
		m_w.obj_ModuleWizard.put("parameter", m_w.arr_Parameter_List);
		m_w.obj_ModuleWizard.put("sensitivity", m_w.arr_Sensitivity_List);
		
		m_w.obj_JSON.put("ModuleWizard", m_w.obj_ModuleWizard);
	}
}
