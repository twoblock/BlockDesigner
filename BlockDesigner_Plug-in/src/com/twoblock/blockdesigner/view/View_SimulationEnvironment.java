package com.twoblock.blockdesigner.view;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Device;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.ExpandBar;
import org.eclipse.swt.widgets.ExpandItem;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.part.ViewPart;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import com.twoblock.blockdesigner.command.Handler_Command;
import com.twoblock.blockdesigner.command.Hanlder_CallBack;
import com.twoblock.blockdesigner.popup.BDDisassembleView;
import com.twoblock.blockdesigner.popup.BDF;
import com.twoblock.blockdesigner.popup.BDMemoryView;
import com.twoblock.blockdesigner.popup.BDMemoryViewItem;
import com.twoblock.blockdesigner.popup.BDMemoryViewItemArray;
import com.twoblock.blockdesigner.popup.BDSWCallStackView;
import com.twoblock.blockdesigner.popup.BDSWProfilingView;
import com.twoblock.blockdesigner.popup.IBDMemoryViewListener;
import com.twoblock.blockdesigner.popup.SoftwareLoadingView;

/**
 * This sample class demonstrates how to plug-in a new workbench view. The view
 * shows data obtained from the model. The sample creates a dummy model on the
 * fly, but a real implementation would connect to the model available either in
 * this or another plug-in (e.g. the workspace). The view is connected to the
 * model using a content provider.
 * <p>
 * The view uses a label provider to define how model objects should be
 * presented in the view. Each view can present the same model objects using
 * different labels and icons, if needed. Alternatively, a single label provider
 * can be shared between views in order to ensure that objects of the same type
 * are presented in the same way everywhere.
 * <p>
 */

public class View_SimulationEnvironment extends ViewPart {
	public static Composite c_parent;
	private Text txtStep;
	private static BDDisassembleView dv;
	private static BDSWCallStackView csv;
	private static BDSWProfilingView swpv;
	private static BDMemoryView mv;
	private Image imgStep_n;
	protected String coreList="";
	protected String BDPMD_Location;
	public static boolean Btn_ControlChecker;
	public static String SourceCode;
	public static String InitMemoryView;
	public static String MemoryViewSet;
	public static String SymbolTable;
	public static String PCCode;
	public static String FunctionFlowGragh;
	public static String ProfilingTable;
	public static String Selected_core_check=null;
	private static Button btnOpen_sw;
	private static Button btnClose;
	private static Button btnRun;
	private static Button btnStop;
	private static Button btnStep;
	private static Button btnStep_n;
	private static Button btnOpen;
	private static Button chkASV;
	private static Button chkCSV;
	private static Button chkSPV;
	private static Label lblCyclesCnt;
	public static Display display = null;
	public static boolean SWLoadCheck = false;

	private void setViewState(int state) {
		IWorkbenchPage page = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
		int currentState = page.getPartState(page.getReference(this));
		if (currentState != state) {
			page.activate(this);
			page.setPartState(page.getReference(this), state);
		}
	}

	public void createPartControl(Composite ori_parent) {
		final Composite parent = ori_parent;
		display = Display.getDefault();

		c_parent=parent;

		display.asyncExec(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				Hanlder_CallBack.CallBack_Func();
				Btn_Control(0);
				
//				Handler_Command.Command_Func(0, 7, System.getProperty("user.home") + "/BlockDesigner/testmodule.BDPMD",
//						"", "", "", "");
//				Handler_Command.Command_Func(0, 0, "BD_CORTEXM0DS",
//						System.getProperty("user.home") + "/workspace/BlockDesigner/TestPlatform/sc_main/CM0DS.elf", "",
//						"", "");

				try {
					Thread.sleep(500);
				} catch (Exception e) {
					// TODO: handle exception
				}
			}
		});

		parent.setLayout(new GridLayout(15, false));
		ImageDescriptor idOpen = ImageDescriptor.createFromFile(this.getClass(), "/images/open_btn.png");
		Image imgOpen = idOpen.createImage();
		ImageDescriptor idOpen_sw = ImageDescriptor.createFromFile(this.getClass(), "/images/open_sw_btn16.png");
		Image imgOpen_sw = idOpen_sw.createImage();
		ImageDescriptor idClose = ImageDescriptor.createFromFile(this.getClass(), "/images/close_btn_16.png");
		Image imgClose = idClose.createImage();
		ImageDescriptor idRun = ImageDescriptor.createFromFile(this.getClass(), "/images/run_btn16.png");
		Image imgRun = idRun.createImage();
		ImageDescriptor idStop = ImageDescriptor.createFromFile(this.getClass(), "/images/stop_btn16.png");
		Image imgStop = idStop.createImage();
		ImageDescriptor idStep = ImageDescriptor.createFromFile(this.getClass(), "/images/step_btn16.png");
		Image imgStep = idStep.createImage();
		ImageDescriptor idStep_n = ImageDescriptor.createFromFile(this.getClass(), "/images/step_n_btn16.png");
		imgStep_n = idStep_n.createImage();

		btnOpen = new Button(parent, SWT.NONE);
		btnOpen.setLayoutData(new GridData(SWT.CENTER, SWT.BOTTOM, false, false, 1, 1));
		btnOpen.setImage(imgOpen);
		
		btnOpen_sw = new Button(parent, SWT.NONE);
		btnOpen_sw.setLayoutData(new GridData(SWT.CENTER, SWT.BOTTOM, false, false, 1, 1));
		btnOpen_sw.setImage(imgOpen_sw);

		btnClose = new Button(parent, SWT.NONE);
		btnClose.setLayoutData(new GridData(SWT.CENTER, SWT.BOTTOM, false, false, 1, 1));
		btnClose.setImage(imgClose);

		Label sepBar1 = new Label(parent, SWT.SEPARATOR | SWT.CENTER);
		sepBar1.setLayoutData(new GridData(SWT.CENTER, SWT.BOTTOM, false, false, 1, 2));

		btnRun = new Button(parent, SWT.NONE);
		btnRun.setImage(imgRun);

		btnStop = new Button(parent, SWT.NONE);
		btnStop.setImage(imgStop);

		btnStep = new Button(parent, SWT.NONE);
		btnStep.setImage(imgStep);

		txtStep = new Text(parent, SWT.BORDER);
		GridData txtStep_n = new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1);
		txtStep_n.widthHint = 50;
		txtStep.setLayoutData(txtStep_n);

		btnStep_n = new Button(parent, SWT.NONE);
		btnStep_n.setImage(imgStep_n);

		Label sepBar2 = new Label(parent, SWT.SEPARATOR | SWT.CENTER);
		sepBar2.setLayoutData(new GridData(SWT.CENTER, SWT.BOTTOM, false, false, 1, 2));

		lblCyclesCnt = new Label(parent, SWT.BORDER | SWT.RIGHT);
		GridData gd_label = new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1);
		gd_label.widthHint = 200;
		lblCyclesCnt.setLayoutData(gd_label);
		lblCyclesCnt.setText("0");

		Label lblCycles = new Label(parent, SWT.NONE);
		lblCycles.setAlignment(SWT.LEFT);
		lblCycles.setText("cycles");
		lblCycles.setLayoutData(new GridData(SWT.LEFT, SWT.BOTTOM, false, false, 4, 1));


		Label lblOpen = new Label(parent, SWT.NONE);
		lblOpen.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblOpen.setText("Open");
		
		Label lblOpen_sw = new Label(parent, SWT.NONE);
		lblOpen_sw.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblOpen_sw.setText("S/W");

		Label lblClose = new Label(parent, SWT.NONE);
		lblClose.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblClose.setText("Close");

		Label lblRun = new Label(parent, SWT.NONE);
		lblRun.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblRun.setText("Run");

		Label lblStop = new Label(parent, SWT.NONE);
		lblStop.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblStop.setText("Stop");

		Label lblStep = new Label(parent, SWT.NONE);
		lblStep.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblStep.setText("Step");

		Label lblStep_n = new Label(parent, SWT.NONE);
		lblStep_n.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 2, 1));
		lblStep_n.setText("n Step");

		Label lblnull = new Label(parent, SWT.NONE);
		lblnull.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		
		chkASV = new Button(parent, SWT.CHECK);
		chkASV.setLayoutData(new GridData(SWT.LEFT, SWT.BOTTOM, false, false, 1, 1));
		chkASV.setText("Show Disassembly View");
		chkASV.setEnabled(false);
		
		chkCSV = new Button(parent, SWT.CHECK);
		chkCSV.setLayoutData(new GridData(SWT.LEFT, SWT.BOTTOM, false, false, 1, 1));
		chkCSV.setText("Show CallStack View");
		chkCSV.setEnabled(false);
		
		chkSPV = new Button(parent, SWT.CHECK);
		chkSPV.setLayoutData(new GridData(SWT.LEFT, SWT.BOTTOM, false, false, 1, 1));
		chkSPV.setText("Show S/W Profiling View");
		chkSPV.setEnabled(false);
		
		Button btnFold = new Button(parent, SWT.NONE);
		btnFold.setLayoutData(new GridData(SWT.RIGHT, SWT.BOTTOM, false, false, 1, 1));
		btnFold.setText("All Fold");
		
		/* --- Button Listener & Action ---END */
		final Composite composite = new Composite(parent, SWT.BORDER);
		composite.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 15, 1));
		composite.setLayout(new FillLayout(SWT.VERTICAL));
		
		/* START--- Button Listener & Action --- */
		btnOpen.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				coreList="";
				
				btnOpen.addSelectionListener(new SelectionAdapter() {
					@Override
					public void widgetSelected(SelectionEvent arg0) {
						// TODO Auto-generated method stub
						FileDialog file_dlg = new FileDialog(parent.getShell() , SWT.OPEN);
						
						file_dlg.setText("BDPMD Loading");
						String[] filterExt={"*.BDPMD"};
						file_dlg.setFilterExtensions(filterExt);
						file_dlg.setFilterPath(System.getProperty("user.home"));
						
						BDPMD_Location = file_dlg.open();
						
						if (BDPMD_Location != null) {
							// File directory = new File(saveTarget);
							BDPMD_Location = BDPMD_Location.replace("\\", "/");
							Handler_Command.Command_Func(0, 7, BDPMD_Location, "", "","", "");
							ChannelInfoSet(composite);
						}
					}
				});
				Handler_Command.Command_Func(0, 1, "OPEN", "NULL", "NULL", "NULL", "NULL");
			}
		});
		btnOpen_sw.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				
				SoftwareLoadingView swl = new SoftwareLoadingView(parent.getShell(), coreList);
				swl.show();
			}
		});
		
		btnClose.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "SAVE", "NULL", "NULL", "NULL", "NULL");
				Hanlder_CallBack.CallBack_Func();
			}
		});
		btnRun.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Tracer();

				Handler_Command.Command_Func(0, 1, "RUN", "NULL", "NULL", "NULL", "NULL");
				Btn_Control(2);
				SetTableState(false);
			}
		});
		btnStop.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "STOP", "NULL", "NULL", "NULL", "NULL");
				Btn_ControlChecker=true;
				Btn_Control(3);
				SetTableState(true);
			}
		});
		btnStep.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Tracer();

				Handler_Command.Command_Func(0, 1, "STEP", "1", "NULL", "NULL", "NULL");
			}
		});
		
		txtStep.addListener(SWT.Verify, new Listener() {
            public void handleEvent(Event e) {
                String string = e.text;
                char[] chars = new char[string.length()];
                string.getChars(0, chars.length, chars, 0);
                for (int i = 0; i < chars.length; i++) {
                    if (!('0' <= chars[i] && chars[i] <= '9')) {
                        e.doit = false;
                        return;
                    }
                }
            }
        });
		
		btnStep_n.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				if (!(txtStep.getText().equals("") || txtStep.getText().equals(null))) {
					Tracer();
					Handler_Command.Command_Func(0, 1, "STEP", txtStep.getText(), "NULL", "NULL", "NULL");
					Btn_Control(2);
					SetTableState(false);
				}
			}
		});
		btnFold.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent arg0) {
				// TODO Auto-generated method stub
				for (int i = 0; i < expandBar.getItemCount(); i++) {
					expandBar.getItem(i).setExpanded(false);
				}
			}
		});
	}

	private Device device = Display.getCurrent();
	private Color color_gray = new Color(device, 150, 150, 150);
	// private Color color_skyblue = new Color(device, 204, 204, 255);
	private Object obj;
	private JSONParser parser = new JSONParser();
	private JSONObject jsonObject;
	private JSONObject obj_BDPMD;
	private JSONArray arr_ModuleData;
	private JSONArray arr_ChannelInfo;

	private static ExpandBar expandBar;
	private static ArrayList<ExpandItem> Expanditem = new ArrayList<ExpandItem>();
	private static ArrayList<Composite> composite_ExpandItem = new ArrayList<Composite>();
	private JSONObject obj_module;

	private JSONArray jrr_Connection;
	private JSONObject obj_Connection;
	private JSONObject obj_Connection_info;

	// private JSONArray jrr_HCLK_connection;
	// private JSONObject obj_HCLK;
	// private JSONObject obj_HCLK_info;
	//
	// private JSONArray jrr_HRESETn_connection;
	// private JSONObject obj_HRESETn;
	// private JSONObject obj_HRESETn_info;

	private JSONObject obj_module_info;
	private Table table_channel;
	private Table table_port;
	private Table table_par;
	private Table table_reg;

	private JSONArray arr_port_info;
	private JSONArray arr_par_info;
	private JSONArray arr_reg_info;
	private JSONObject obj_port;
	private JSONObject obj_par;
	private JSONObject obj_reg;
	private int par_index;
	private int ModuleInfoIndex;
	private int reg_index;

	private JSONObject jsonObject_sc;
	private JSONObject obj_sc;
	private JSONArray arr_SourceLine;
	private JSONObject obj_sc_OneLine;

	private JSONObject jsonObject_sb;
	private JSONObject obj_sb;
	private JSONArray arr_SymbolLine;
	private JSONObject obj_sb_OneLine;

	private JSONObject jsonObject_ffg;
	private JSONObject obj_ffg;
	private JSONArray arr_ffgLine;
	private JSONObject obj_ffg_OneLine;

	private JSONObject jsonObject_pt;
	private JSONObject obj_pt;
	private JSONArray arr_ptItem;
	private JSONObject obj_pt_OneItem;
	private String HCLK_channel_name;
	private String HRESETn_channel_name;
	private String InstanceName;
	private boolean isExisted=false;
	private BDMemoryViewItemArray tmp_data;

	protected void ChannelInfoSet(final Composite composite) {
		try {
			obj = parser.parse(new FileReader(BDPMD_Location));
			System.err.println("Call ChannelInfoSet");
//			obj = parser.parse(new FileReader(System.getProperty("user.home") + "/BlockDesigner/testmodule.BDPMD"));
			jsonObject = (JSONObject) obj;
			obj_BDPMD = (JSONObject) jsonObject.get("BDPMD");

			arr_ModuleData = (JSONArray) obj_BDPMD.get("Module_Data");
			arr_ChannelInfo = (JSONArray) obj_BDPMD.get("Channel_Info");
		} catch (IOException | ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		expandBar = new ExpandBar(composite, SWT.V_SCROLL);
		Expanditem.add(0, new ExpandItem(expandBar, SWT.NONE));
		Expanditem.get(0).setExpanded(true);
		Expanditem.get(0).setText("Channel Info");
		composite_ExpandItem.add(new Composite(expandBar, SWT.NONE));
		composite_ExpandItem.get(0).setBackground(color_gray);
		composite_ExpandItem.get(0).setLayout(new GridLayout(2, false));
		Expanditem.get(0).setControl(composite_ExpandItem.get(0));
		Expanditem.get(0).setHeight(Expanditem.get(0).getControl().computeSize(SWT.DEFAULT, SWT.DEFAULT).y);

		ImageDescriptor idItem = ImageDescriptor.createFromFile(this.getClass(), "/images/img_connection16.png");
		Image imgConnectionIcon = idItem.createImage();
		Expanditem.get(0).setImage(imgConnectionIcon);

		table_channel = new Table(composite_ExpandItem.get(0), SWT.BORDER | SWT.FULL_SELECTION | SWT.V_SCROLL);
		GridData gd_table = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1);
		gd_table.heightHint = 250;
		table_channel.setLayoutData(gd_table);
		table_channel.setHeaderVisible(true);
		table_channel.setLinesVisible(true);

		TableColumn tb_clmn_ChannelName = new TableColumn(table_channel, SWT.CENTER);
		tb_clmn_ChannelName.setWidth(800);
		tb_clmn_ChannelName.setText("Channel Name");

		TableColumn tb_clmn_Tracing = new TableColumn(table_channel, SWT.CENTER);
		tb_clmn_Tracing.setWidth(120);
		tb_clmn_Tracing.setText("Tracing");

		for (int channel_index = 0; channel_index < arr_ChannelInfo.size();	channel_index++ ) {
			obj_Connection = (JSONObject) arr_ChannelInfo.get(channel_index);
			jrr_Connection = (JSONArray) obj_Connection.get("connection_info");
			if(jrr_Connection.size() != 0)
				new TableItem(table_channel, SWT.NONE);
		}

		TableItem[] items = table_channel.getItems();

		TableEditor editor_channel_table = new TableEditor(table_channel);
		{
			editor_channel_table = new TableEditor(table_channel);
			final Text txt_HCLK = new Text(table_channel, SWT.READ_ONLY);
			txt_HCLK.setTouchEnabled(true);
			txt_HCLK.setText("HCLK");
			editor_channel_table.grabHorizontal = true;
			editor_channel_table.setEditor(txt_HCLK, items[0], 0);
			editor_channel_table = new TableEditor(table_channel);
			final Button ckb_HCLK_Tracing = new Button(table_channel, SWT.CHECK);
			editor_channel_table.grabHorizontal = true;
			editor_channel_table.setEditor(ckb_HCLK_Tracing, items[0], 1);

			editor_channel_table = new TableEditor(table_channel);
			final Text txt_HRESETn = new Text(table_channel, SWT.READ_ONLY);
			txt_HRESETn.setTouchEnabled(true);
			txt_HRESETn.setText("HRESETn");
			editor_channel_table.grabHorizontal = true;
			editor_channel_table.setEditor(txt_HRESETn, items[1], 0);
			editor_channel_table = new TableEditor(table_channel);
			final Button ckb_HRESETn_Tracing = new Button(table_channel, SWT.CHECK);
			editor_channel_table.grabHorizontal = true;
			editor_channel_table.setEditor(ckb_HRESETn_Tracing, items[1], 1);
		}

		obj_Connection = (JSONObject) arr_ChannelInfo.get(0);
		HCLK_channel_name = (String) obj_Connection.get("name");
		obj_Connection = (JSONObject) arr_ChannelInfo.get(1);
		HRESETn_channel_name = (String) obj_Connection.get("name");

		int channel_temp=1;
		for (int channel_index = 2; channel_index < arr_ChannelInfo.size();	channel_index++ ) {
			obj_Connection = (JSONObject) arr_ChannelInfo.get(channel_index);

			String first_Connection = (String) obj_Connection.get("name");
			String first_Connection_source = "[" + first_Connection.replaceAll("[$]", "]");
			jrr_Connection = (JSONArray) obj_Connection.get("connection_info");

			if (jrr_Connection.size() != 0) {
				String channel_type = (String) obj_Connection.get("channel_type");

				channel_temp++;
				obj_Connection_info = (JSONObject) jrr_Connection.get(0);
				String first_Connection_dest = "[" + (String) obj_Connection_info.get("module_name") + "]"
						+ (String) obj_Connection_info.get("port_name");

				editor_channel_table = new TableEditor(table_channel);

				final Text txt_ChannelName = new Text(table_channel, SWT.READ_ONLY);
				txt_ChannelName.setTouchEnabled(true);
				txt_ChannelName.setText(first_Connection_source + "<-----"+channel_type+"----->" + first_Connection_dest);
				editor_channel_table.grabHorizontal = true;
				editor_channel_table.setEditor(txt_ChannelName, items[channel_temp], 0);

				editor_channel_table = new TableEditor(table_channel);

				final Button ckb_Tracing = new Button(table_channel, SWT.CHECK);
				editor_channel_table.grabHorizontal = true;
				editor_channel_table.setEditor(ckb_Tracing, items[channel_temp], 1);
			}
		}

		table_channel.pack();
		Expanditem.get(0).setHeight(250);

		ModuleInfoIndex = 0;
		for (ModuleInfoIndex = 0; ModuleInfoIndex < arr_ModuleData.size(); ModuleInfoIndex++) {
			Expanditem.add(new ExpandItem(expandBar, SWT.NONE));
			Expanditem.get(ModuleInfoIndex + 1).setExpanded(false);
			obj_module = (JSONObject) arr_ModuleData.get(ModuleInfoIndex);
			String module_type = (String) obj_module.get("module_type");

			obj_module_info = (JSONObject) obj_module.get("module_info");
			InstanceName = (String) obj_module_info.get("instance_name");
			Expanditem.get(ModuleInfoIndex + 1).setText(InstanceName);
			arr_port_info = (JSONArray) obj_module_info.get("port");
			arr_par_info = (JSONArray) obj_module_info.get("parameter");
			arr_reg_info = (JSONArray) obj_module_info.get("register");


			composite_ExpandItem.add(new Composite(expandBar, SWT.NONE));

			composite_ExpandItem.get(ModuleInfoIndex + 1).setLayout(new GridLayout(3, false));
			composite_ExpandItem.get(ModuleInfoIndex + 1).setBackground(color_gray);
			Expanditem.get(ModuleInfoIndex + 1).setControl(composite_ExpandItem.get(ModuleInfoIndex + 1));
			Expanditem.get(ModuleInfoIndex + 1).setHeight(
					Expanditem.get(ModuleInfoIndex + 1).getControl().computeSize(SWT.DEFAULT, SWT.DEFAULT).y);

			{ /* --- port --- */
				table_port = new Table(composite_ExpandItem.get(ModuleInfoIndex + 1),
						SWT.BORDER | SWT.FULL_SELECTION | SWT.V_SCROLL);
				GridData gd_table_port = new GridData(SWT.FILL, SWT.TOP, true, false, 1, 0);
				gd_table_port.heightHint = 120;
				table_port.setLayoutData(gd_table_port);
				table_port.setHeaderVisible(true);
				table_port.setLinesVisible(true);

				TableColumn tb_clmn_Port = new TableColumn(table_port, SWT.CENTER);
				tb_clmn_Port.setWidth(200);
				tb_clmn_Port.setText("Port Name");
				int port_cnt = arr_port_info.size();
				for (int i = 0; i < port_cnt; i++) {
					new TableItem(table_port, SWT.NONE);
				}

				TableItem[] items_port = table_port.getItems();

				for (int port_index = 0; port_index < items_port.length; port_index++) {
					obj_port = (JSONObject) arr_port_info.get(port_index);

					TableEditor editor_port_table = new TableEditor(table_port);
					editor_port_table = new TableEditor(table_port);

					final Text txt_PortName = new Text(table_port, SWT.READ_ONLY);
					txt_PortName.setTouchEnabled(true);
					txt_PortName.setText((String) obj_port.get("port"));
					editor_port_table.grabHorizontal = true;
					editor_port_table.setEditor(txt_PortName, items_port[port_index], 0);
				}
			}

			{ /* --- par --- */
				table_par = new Table(composite_ExpandItem.get(ModuleInfoIndex + 1),
						SWT.BORDER | SWT.FULL_SELECTION | SWT.V_SCROLL);
				GridData gd_table_par = new GridData(SWT.FILL, SWT.TOP, true, false, 1, 0);
				gd_table_par.heightHint = 120;
				table_par.setLayoutData(gd_table_par);
				table_par.setHeaderVisible(true);
				table_par.setLinesVisible(true);

				TableColumn tb_clmn_Par = new TableColumn(table_par, SWT.CENTER);
				tb_clmn_Par.setWidth(300);
				tb_clmn_Par.setText("Parameter Name");

				TableColumn tb_clmn_Par_value = new TableColumn(table_par, SWT.CENTER);
				tb_clmn_Par_value.setWidth(100);
				tb_clmn_Par_value.setText("Value");

				int par_cnt = arr_par_info.size();
				for (int i = 0; i < par_cnt; i++) {
					new TableItem(table_par, SWT.NONE);
				}

				TableItem[] items_par = table_par.getItems();

				for (par_index = 0; par_index < items_par.length; par_index++) {
					obj_par = (JSONObject) arr_par_info.get(par_index);

					TableEditor editor_par_table = new TableEditor(table_par);
					editor_par_table = new TableEditor(table_par);

					final Text txt_ParName = new Text(table_par, SWT.READ_ONLY);
					txt_ParName.setTouchEnabled(true);
					txt_ParName.setText((String) obj_par.get("par_name"));
					editor_par_table.grabHorizontal = true;
					editor_par_table.setEditor(txt_ParName, items_par[par_index], 0);

					editor_par_table = new TableEditor(table_par);
					final Text txt_ParValue = new Text(table_par, SWT.NONE);
					txt_ParValue.setTouchEnabled(true);
					txt_ParValue.setText((String) obj_par.get("default_value"));
					editor_par_table.grabHorizontal = true;
					editor_par_table.setEditor(txt_ParValue, items_par[par_index], 1);
					txt_ParValue.addListener(SWT.FOCUSED, new Listener() {
						@Override
						public void handleEvent(Event arg0) {
							// TODO Auto-generated method stub
							txt_ParValue.selectAll();
						}
					});
					txt_ParValue.addListener(SWT.FocusOut, new Listener() {
						final int table_par_index = par_index;
						final String module_name = Expanditem.get(ModuleInfoIndex + 1).getText();

						@Override
						public void handleEvent(Event arg0) {
							// TODO Auto-generated method stub
							System.err.println("0/2/" + module_name + "/par/write/" + table_par_index + "/"
									+ txt_ParValue.getText());
							Handler_Command.Command_Func(0, 2, module_name, "par", "write", table_par_index + "",
									txt_ParValue.getText());
						}
					});
				}
			}

			{ /* --- reg --- */
				table_reg = new Table(composite_ExpandItem.get(ModuleInfoIndex + 1),
						SWT.BORDER | SWT.FULL_SELECTION | SWT.V_SCROLL);
				GridData gd_table_reg = new GridData(SWT.FILL, SWT.TOP, true, false, 1, 0);
				gd_table_reg.heightHint = 120;
				table_reg.setLayoutData(gd_table_reg);
				table_reg.setHeaderVisible(true);
				table_reg.setLinesVisible(true);

				TableColumn tb_clmn_reg = new TableColumn(table_reg, SWT.CENTER);
				tb_clmn_reg.setWidth(300);
				tb_clmn_reg.setText("Register Name");

				TableColumn tb_clmn_reg_value = new TableColumn(table_reg, SWT.CENTER);
				tb_clmn_reg_value.setWidth(100);
				tb_clmn_reg_value.setText("Value");

				int reg_cnt = arr_reg_info.size();
				for (int i = 0; i < reg_cnt; i++) {
					new TableItem(table_reg, SWT.NONE);
				}

				TableItem[] items_reg = table_reg.getItems();

				reg_index = 0;
				for (reg_index = 0; reg_index < items_reg.length; reg_index++) {
					obj_reg = (JSONObject) arr_reg_info.get(reg_index);

					TableEditor editor_reg_table = new TableEditor(table_reg);
					editor_reg_table = new TableEditor(table_reg);

					final Text txt_regName = new Text(table_reg, SWT.READ_ONLY);
					txt_regName.setTouchEnabled(true);
					txt_regName.setText((String) obj_reg.get("reg_name"));
					editor_reg_table.grabHorizontal = true;
					editor_reg_table.setEditor(txt_regName, items_reg[reg_index], 0);

					editor_reg_table = new TableEditor(table_reg);
					final Text txt_regValue = new Text(table_reg, SWT.NONE);
					txt_regValue.setTouchEnabled(true);
					editor_reg_table.grabHorizontal = true;
					editor_reg_table.setEditor(txt_regValue, items_reg[reg_index], 1);
					txt_regValue.addListener(SWT.FOCUSED, new Listener() {

						@Override
						public void handleEvent(Event arg0) {
							// TODO Auto-generated method stub
							txt_regValue.selectAll();
						}
					});

					txt_regValue.addListener(SWT.FocusOut, new Listener() {
						final int table_reg_index = reg_index;
						final String module_name = Expanditem.get(ModuleInfoIndex + 1).getText();

						@Override
						public void handleEvent(Event arg0) {
							// TODO Auto-generated method stub
							System.err.println("0/2/" + module_name + "/reg/write/" + table_reg_index + "/"
									+ txt_regValue.getText());
							Handler_Command.Command_Func(0, 2, module_name, "reg", "write", table_reg_index + "",
									txt_regValue.getText());
						}
					});
				}
			}
			Expanditem.get(ModuleInfoIndex + 1).setHeight(150);

			switch (module_type) {
			case "cpu":
				ImageDescriptor idItem1 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_core16.png");
				Image imgItemIcon1 = idItem1.createImage();
				Expanditem.get(ModuleInfoIndex + 1).setImage(imgItemIcon1);
				coreList=","+InstanceName;
				isExisted=true;
				break;
			case "mem":
				ImageDescriptor idItem2 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_memory16.png");
				Image imgItemIcon2 = idItem2.createImage();
				Expanditem.get(ModuleInfoIndex + 1).setImage(imgItemIcon2);
				Expanditem.get(ModuleInfoIndex + 1).setHeight(180);

				final Button btnMemorymap = new Button(composite_ExpandItem.get(ModuleInfoIndex + 1), SWT.NONE);
				btnMemorymap.setLayoutData(new GridData(SWT.RIGHT, SWT.BOTTOM, true, true, 3, 1));
				btnMemorymap.setText("Memory View");
				btnMemorymap.addSelectionListener(new SelectionListener() {
					final String Memory_name = InstanceName;
					@Override
					public void widgetSelected(SelectionEvent arg0) {
						// TODO Auto-generated method stub
						//						MemoryViewSetter(c_parent,Memory_name);

						MemoryViewOpen(c_parent,Memory_name);
					}

					@Override
					public void widgetDefaultSelected(SelectionEvent arg0) {
						// TODO Auto-generated method stub
					}
				});

				break;
			case "bus":
				ImageDescriptor idItem3 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_bus16.png");
				Image imgItemIcon3 = idItem3.createImage();
				Expanditem.get(ModuleInfoIndex + 1).setImage(imgItemIcon3);
				break;
			case "other":
				ImageDescriptor idItem4 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_etc16.png");
				Image imgItemIcon4 = idItem4.createImage();
				Expanditem.get(ModuleInfoIndex + 1).setImage(imgItemIcon4);
				break;
			}
		}
		Btn_Control(1);
		composite.setSize(composite.getParent().getSize().x-10, composite.getParent().getSize().y-80);
	}

	public static String padRight(String s, int n) {
		return String.format("%1$-" + n + "s", s);
	}

	public void setFocus() {
		setViewState(1);
	}

	void SetTableState(Boolean state) {
		for (int moduleindex = 1; moduleindex < composite_ExpandItem.size(); moduleindex++) {
			Control[] ctrol_tables = composite_ExpandItem.get(moduleindex).getChildren();
			Table tb_par = (Table) ctrol_tables[1]; // get par table
			Table tb_reg = (Table) ctrol_tables[2]; // get reg table

			Control[] Ctrol_par_arg = tb_par.getChildren();
			Control[] Ctrol_reg_arg = tb_reg.getChildren();

			for (int i = 0; i < Ctrol_par_arg.length / 2; i++) {
				Text text_par = (Text) Ctrol_par_arg[i * 2 + 1];
				text_par.setEnabled(state);
			}

			for (int j = 0; j < Ctrol_reg_arg.length / 2; j++) {
				Text text_reg = (Text) Ctrol_reg_arg[j * 2 + 1];
				text_reg.setEnabled(state);
			}
		}
	}

	protected static JSONArray arr_Result_ModuleList;
	protected static JSONObject obj_Result_Module;
	protected static JSONArray arr_reg_value;
	protected static JSONObject obj_reg_value;
	protected static Control[] ctrol_tables;
	protected static Table tb_reg;
	protected static Control[] Ctrol_reg_arg;

	
	public void SIM_Result(String ori_sim_result) {
		System.err.println("ori_sim_result="+ori_sim_result);
		final String sim_result=ori_sim_result;
		display.asyncExec(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				try {
					obj = (JSONObject) parser.parse(sim_result);
					jsonObject = (JSONObject) obj;
					arr_Result_ModuleList = (JSONArray) jsonObject.get("SIM_Result"); 
					String InstanceName = null;
					String value = null;
					if(arr_Result_ModuleList != null){
						for (int refesh_index = 0; refesh_index < arr_Result_ModuleList.size(); refesh_index++) {
							obj_Result_Module = (JSONObject) arr_Result_ModuleList.get(refesh_index);
							arr_reg_value = (JSONArray) obj_Result_Module.get("register_value");
							InstanceName = (String) obj_Result_Module.get("instance_name");

							for (int expandItem_index = 1; expandItem_index < Expanditem.size(); expandItem_index++) {

								if (InstanceName.equals(Expanditem.get(expandItem_index).getText())) {
									ctrol_tables = composite_ExpandItem.get(expandItem_index).getChildren();
									tb_reg = (Table) ctrol_tables[2]; // get reg
									// table
									Ctrol_reg_arg = tb_reg.getChildren();
									for (int reg_index = 0; reg_index < arr_reg_value.size(); reg_index++) {

										obj_reg_value = (JSONObject) arr_reg_value.get(reg_index);
										value = (String) obj_reg_value.get("value");

										if (value != null) {
											Text text_reg = (Text) Ctrol_reg_arg[reg_index * 2 + 1];
											text_reg.setText(value);
										}
									}
								}
							}
						}
					}
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		});
	}

	
	
	public void Btn_Control(int ori_state) {
		final int state = ori_state;
		/*
		 * case state 
		 * state 0 : nothing 
		 * state 1 : run 
		 * state 2 : step 
		 * state 3 : stop
		 */
		display.asyncExec(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				switch (state) {
				case 0: // initial
					System.err.println("SE Open");
					btnOpen_sw.setEnabled(false);
					btnClose.setEnabled(false);
					btnStop.setEnabled(false);
					btnStep.setEnabled(false);
					btnStep_n.setEnabled(false);
					btnRun.setEnabled(false);
					break;
				case 1:
					System.err.println("BDPMD Open");
					if(isExisted==true){
						btnOpen_sw.setEnabled(true);
						chkSPV.setEnabled(true);
						chkASV.setEnabled(true);
						chkCSV.setEnabled(true);
					}
					else{
						btnOpen_sw.setEnabled(false);
						chkSPV.setEnabled(false);
						chkASV.setEnabled(false);
						chkCSV.setEnabled(false);
						Btn_Control(3);
						Btn_ControlChecker=false;
						break;
					}
					btnClose.setEnabled(true);
					btnStop.setEnabled(false);
					btnStep.setEnabled(false);
					btnStep_n.setEnabled(false);
					btnRun.setEnabled(false);
					SetTableState(true);
					break;
				case 2: 
					System.err.println("RUN");
					btnOpen.setEnabled(false);
					btnClose.setEnabled(false);
					btnStop.setEnabled(true);
					btnOpen_sw.setEnabled(false);
					btnStep.setEnabled(false);
					btnStep_n.setEnabled(false);
					btnRun.setEnabled(false);
					SetTableState(false);
					break;
				case 3:
					System.err.println("STOP");
					btnStop.setEnabled(false);
					btnClose.setEnabled(true);
					btnStep.setEnabled(true);
					btnStep_n.setEnabled(true);
					btnRun.setEnabled(true);
					SetTableState(true);

					display.asyncExec(new Runnable() {
						@Override
						public void run() {
							// TODO Auto-generated method stub
							if((Selected_core_check != null) && (Btn_ControlChecker)){
								Btn_ControlChecker=false;
								if(chkASV.getSelection() == true){
									/* --- Disassemble View Setter ---START--- */
									dv = new BDDisassembleView(c_parent.getShell(), "CORE");
									AssemblySetter();
									dv.show();
									dv.select(BDF.StringHexToLongDecimal(PCCode));
									/* --- Disassemble View Setter ---END--- */
								}
								if(chkCSV.getSelection() == true){
									/* --- Call Stack View Setter ---START--- */
									csvSetter(c_parent);
									/* --- Call Stack View Setter ---END--- */
								}
								if(chkSPV.getSelection() == true){
									/* --- Profiling Table Setter ---START--- */
									ptSetter(c_parent);
									/* --- Profiling Table Setter ---END--- */
								}
							}

						}
					});
					break;
				}
			}
		});
	}

	public void Cycle_Setter(long ori_cycles){
		final long cycles = ori_cycles;
		display.asyncExec(new Runnable() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				lblCyclesCnt.setText(""+cycles);
			}
		});
	}

	public void MemoryViewSetter(String start_addr, BDMemoryViewItemArray tmp_data){

		tmp_data.clear();

		boolean datacheck=true;
		while(datacheck){
			if(MemoryViewSet != null)
				datacheck=false;
		}
		String receive_data=MemoryViewSet;
//		System.err.println("MemoryViewSet="+receive_data);

		tmp_data.baseAddr=BDF.StringHexToLongDecimal(start_addr);
		String[] value = receive_data.split(",");

		String Memory_value1,Memory_value2,Memory_value3,Memory_value4=null;
		for(int memory_index=0; memory_index< value.length; memory_index++){
			Memory_value1 = value[memory_index++];
			if(memory_index==value.length){
				Memory_value2 = "0";
				Memory_value3 = "0";
				Memory_value4 = "0";
				tmp_data.add(new BDMemoryViewItem(BDF.StringHexToLongDecimal(Memory_value1),
						BDF.StringHexToLongDecimal(Memory_value2), 
						BDF.StringHexToLongDecimal(Memory_value3), 
						BDF.StringHexToLongDecimal(Memory_value4)));
				break;
			}
			Memory_value2 = value[memory_index++];
			if(memory_index==value.length){
				Memory_value3 = "0";
				Memory_value4 = "0";
				tmp_data.add(new BDMemoryViewItem(BDF.StringHexToLongDecimal(Memory_value1),
						BDF.StringHexToLongDecimal(Memory_value2), 
						BDF.StringHexToLongDecimal(Memory_value3), 
						BDF.StringHexToLongDecimal(Memory_value4)));
				break;
			}
			Memory_value3 = value[memory_index++];
			if(memory_index==value.length){
				Memory_value4 = "0";
				tmp_data.add(new BDMemoryViewItem(BDF.StringHexToLongDecimal(Memory_value1),
						BDF.StringHexToLongDecimal(Memory_value2), 
						BDF.StringHexToLongDecimal(Memory_value3), 
						BDF.StringHexToLongDecimal(Memory_value4)));
				break;
			}
			Memory_value4 = value[memory_index];


			tmp_data.add(new BDMemoryViewItem(BDF.StringHexToLongDecimal(Memory_value1),
					BDF.StringHexToLongDecimal(Memory_value2), 
					BDF.StringHexToLongDecimal(Memory_value3), 
					BDF.StringHexToLongDecimal(Memory_value4)));
		}

	}

	public void MemoryViewOpen(Composite parent, String ori_memory_name){
		final String memory_name = ori_memory_name;
		tmp_data = new BDMemoryViewItemArray();

		mv = new BDMemoryView(parent.getShell(), memory_name, new IBDMemoryViewListener() {
			@Override
			public void onChangeData(long addr, long data) {
				// TODO Auto-generated method stub
				MemoryViewSet=null;
				Handler_Command.Command_Func(0, 2,memory_name ,"mem", "write", BDF.LongDecimalToStringHex(addr, 8),BDF.LongDecimalToStringHex(data, 8));
			}

			@Override
			public void onDataLoad(BDMemoryView view, long startAddr, long size) {
				// TODO Auto-generated method stub

				MemoryViewSet=null;
				Handler_Command.Command_Func(1, 1,memory_name ,"mem", "read", BDF.LongDecimalToStringHex(startAddr, 8),"NULL");
				
				try {
					Thread.sleep(500);
				} catch (Exception e) {
					// TODO: handle exception
				}
				
				MemoryViewSetter(BDF.LongDecimalToStringHex(startAddr, 8), tmp_data);
				view.setData(tmp_data);
				view.show();
			}
		});

		MemoryViewSet=null;
		Handler_Command.Command_Func(1, 1,memory_name ,"mem", "read", "0x00000000","NULL");

		MemoryViewSetter("0x00000000", tmp_data);
		mv.setData(tmp_data);
		mv.show();
	}


	private void AssemblySetter() {
		// TODO Auto-generated method stub
		try {
			obj_sc = (JSONObject)parser.parse(SourceCode);
			jsonObject_sc = (JSONObject) obj_sc;	
			arr_SourceLine = (JSONArray) jsonObject_sc.get("SourceCode");

			for (int i = 0; i < arr_SourceLine.size(); i++) {
				obj_sc_OneLine = (JSONObject) arr_SourceLine.get(i);
				dv.addInstruction(BDF.StringHexToLongDecimal(((String)obj_sc_OneLine.get("address")).trim())
						,((String)obj_sc_OneLine.get("assembly_code")).trim());
			}
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void SymbolSetter_csv(){
		try {
			obj_sb = (JSONObject)parser.parse(SymbolTable);
			jsonObject_sb = (JSONObject) obj_sb;	
			arr_SymbolLine = (JSONArray) jsonObject_sb.get("SymbolTable");

			String function_name=null;
			for (int i = 0; i < arr_SymbolLine.size(); i++) {
				obj_sb_OneLine = (JSONObject) arr_SymbolLine.get(i);
				function_name= (String)obj_sb_OneLine.get("function_name");
				csv.addFunctionName(function_name);
			}
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void SymbolSetter_swpv(){
		try {
			obj_sb = (JSONObject)parser.parse(SymbolTable);
			jsonObject_sb = (JSONObject) obj_sb;	
			arr_SymbolLine = (JSONArray) jsonObject_sb.get("SymbolTable");

			String function_name=null;
			for (int i = 0; i < arr_SymbolLine.size(); i++) {
				obj_sb_OneLine = (JSONObject) arr_SymbolLine.get(i);
				function_name= (String)obj_sb_OneLine.get("function_name");
				swpv.addFunctionName(function_name);
			}
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


	private void ptSetter(Composite parent){
		swpv = new BDSWProfilingView(parent.getShell(), "CM0(big)");
		SymbolSetter_swpv();
		swpv.show();
		try {
			obj_pt = (JSONObject)parser.parse(ProfilingTable);
			jsonObject_pt = (JSONObject) obj_pt;	
			arr_ptItem = (JSONArray) jsonObject_pt.get("ProfilingTable");
			int index=0;
			long call=0;
			long durCycle=0;
			float durPer=0;
			long selfDurCycle=0;
			float selfDurPer=0;
			for (int i = 0; i < arr_ptItem.size(); i++) {
				obj_pt_OneItem = (JSONObject) arr_ptItem.get(i);

				index=Integer.parseInt((String) obj_pt_OneItem.get("function_index"));
				call=Long.parseLong((String)obj_pt_OneItem.get("function_call"));
				durCycle=Long.parseLong((String)obj_pt_OneItem.get("function_duration"));
				durPer=Float.parseFloat((String)obj_pt_OneItem.get("function_duration_per"));
				selfDurCycle=Long.parseLong((String)obj_pt_OneItem.get("function_selfduration"));
				selfDurPer=Float.parseFloat((String)obj_pt_OneItem.get("function_selfduration_per"));

				swpv.updateData(index, call, durCycle,  durPer,  selfDurCycle,   selfDurPer);
			}
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void csvSetter(Composite parent) {
		// TODO Auto-generated method stub
		csv = new BDSWCallStackView(parent.getShell(), "CM0(big)", null);
		SymbolSetter_csv();

		csv.show();
		try {
			obj_ffg = (JSONObject)parser.parse(FunctionFlowGragh);
			jsonObject_ffg = (JSONObject) obj_ffg;	
			arr_ffgLine = (JSONArray) jsonObject_ffg.get("FunctionFlowGragh");
			int ffg_index=0;
			long ffg_cycle=0;
			for (int i = 0; i < arr_ffgLine.size(); i++) {
				obj_ffg_OneLine = (JSONObject) arr_ffgLine.get(i);
				ffg_index=Integer.parseInt((String) obj_ffg_OneLine.get("function_index"));
				ffg_cycle=Long.parseLong((String)obj_ffg_OneLine.get("function_cycle"));
				csv.addCallData(ffg_index, ffg_cycle);
			}
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private boolean TraceChecking=true;

	private void Tracer() {
		// TODO Auto-generated method stub
		/* --- Tracing Process ---START--- */
		if(TraceChecking){
			Control[] ctr_channel_info = table_channel.getChildren();
			for(int index=0; index<ctr_channel_info.length/2; index++){
				if(((Button)ctr_channel_info[index*2+1]).getSelection() == true){
					if(index==0)
						Handler_Command.Command_Func(0, 4, "0", HCLK_channel_name , "NULL", "NULL", "NULL");
					else if(index==1)
						Handler_Command.Command_Func(0, 4, "0", HRESETn_channel_name , "NULL", "NULL", "NULL");
					else{
						String rex = "(\\[|\\]|<-----|----->)";
						String str = ((Text)ctr_channel_info[index*2]).getText();
						String[] strlist =str.split(rex, 0);
						String tracing_cmd = strlist[1]+"$"+strlist[2]+"&"+strlist[5]+"$"+strlist[6];
						if(strlist[3].equals("sc_signal"))
							Handler_Command.Command_Func(0, 4, "0", strlist[1]+"$"+strlist[2],"NULL", "NULL", "NULL");	
						else
							Handler_Command.Command_Func(0, 4, "0", tracing_cmd, strlist[3], "NULL", "NULL");
					}
				}
			}
			TraceChecking=false;
		}
		/* --- Tracing Process ---END--- */
	}

	public void SWLoadCheckFun(){
		if(SWLoadCheck==true){
			btnOpen_sw.setEnabled(false);
			btnStop.setEnabled(false);
			btnClose.setEnabled(true);
			btnStep.setEnabled(true);
			btnStep_n.setEnabled(true);
			btnRun.setEnabled(true);
			SetTableState(true);
		}
	}
}
