package com.twoblock.blockdesigner.view;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
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
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
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
import com.twoblock.blockdesigner.command.Handler_SimulationInitThread;
import com.twoblock.blockdesigner.command.Hanlder_CallBack;

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
	protected Shell parent;
	private Text txtStep;
	private Image imgStep_n;
	public static Label lblCyclesCnt;
	public static Display display =null;
	
	private void setViewState(int state) {
		IWorkbenchPage page = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
		int currentState = page.getPartState(page.getReference(this));
		if (currentState != state) {
			page.activate(this);
			page.setPartState(page.getReference(this), state);
		}
	}

	public void createPartControl(Composite parent) {
		display = Display.getDefault();
		Hanlder_CallBack.CallBack_Func();
		Handler_Command.Command_Func(0,7,System.getProperty("user.home") + "/BlockDesigner/testmodule.BDPMD","","","","");
		Handler_Command.Command_Func(0, 0, "BD_CORTEXM0DS",
				System.getProperty("user.home") + "/workspace/BlockDesigner/TestPlatform/sc_main/CM0DS.elf", 
				"","","");
		Handler_Command.Command_Func(0, 2, "BD_SRAM","par","write","0","0x20000000");
		parent.setLayout(new GridLayout(11, false));

		ImageDescriptor idOpen = ImageDescriptor.createFromFile(this.getClass(), "/images/open_btn.png");
		Image imgOpen = idOpen.createImage();
		ImageDescriptor idSave = ImageDescriptor.createFromFile(this.getClass(), "/images/save_btn.png");
		Image imgSave = idSave.createImage();
		ImageDescriptor idRun = ImageDescriptor.createFromFile(this.getClass(), "/images/run_btn16.png");
		Image imgRun = idRun.createImage();
		ImageDescriptor idStop = ImageDescriptor.createFromFile(this.getClass(), "/images/stop_btn16.png");
		Image imgStop = idStop.createImage();
		ImageDescriptor idStep = ImageDescriptor.createFromFile(this.getClass(), "/images/step_btn16.png");
		Image imgStep = idStep.createImage();
		ImageDescriptor idStep_n = ImageDescriptor.createFromFile(this.getClass(), "/images/step_n_btn16.png");
		imgStep_n = idStep_n.createImage();
		// Image imgSave = new Image(null, "images/save_btn.png");
		// Image imgRun = new Image(null, "images/run_btn.png");
		// Image imgStop = new Image(null, "images/stop_btn.png");
		// Image imgStep = new Image(null, "images/step_btn.png");
		// Image imgStep_n = new Image(null, "images/step_n_btn.png");

		Button btnOpen = new Button(parent, SWT.NONE);
		btnOpen.setLayoutData(new GridData(SWT.LEFT, SWT.BOTTOM, false, false, 1, 1));
		btnOpen.setImage(imgOpen);

		Button btnSave = new Button(parent, SWT.NONE);
		btnSave.setLayoutData(new GridData(SWT.LEFT, SWT.BOTTOM, false, false, 1, 1));
		btnSave.setImage(imgSave);

		Label sepBar1 = new Label(parent, SWT.SEPARATOR | SWT.CENTER);
		sepBar1.setLayoutData(new GridData(SWT.CENTER, SWT.BOTTOM, false, false, 1, 2));

		Button btnRun = new Button(parent, SWT.NONE);
		btnRun.setImage(imgRun);

		Button btnStop = new Button(parent, SWT.NONE);
		btnStop.setImage(imgStop);

		Button btnStep = new Button(parent, SWT.NONE);
		btnStep.setImage(imgStep);

		txtStep = new Text(parent, SWT.BORDER);
		GridData txtStep_n = new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1);
		txtStep_n.widthHint = 50;
		txtStep.setLayoutData(txtStep_n);

		Button btnStep_n = new Button(parent, SWT.NONE);
		btnStep_n.setImage(imgStep_n);

		Label sepBar2 = new Label(parent, SWT.SEPARATOR | SWT.CENTER);
		sepBar2.setLayoutData(new GridData(SWT.CENTER, SWT.BOTTOM, false, false, 1, 2));

		lblCyclesCnt = new Label(parent, SWT.BORDER | SWT.RIGHT);
		GridData gd_label = new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1);
		gd_label.widthHint = 200;
		lblCyclesCnt.setLayoutData(gd_label);
		lblCyclesCnt.setText("110254");
		// lblCyclesCnt.setAlignment(SWT.CENTER);

		Label lblCycles = new Label(parent, SWT.NONE);
		lblCycles.setAlignment(SWT.CENTER);
		lblCycles.setText("cycles");

		Label lblOpen = new Label(parent, SWT.NONE);
		lblOpen.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblOpen.setText("Open");

		Label lblSave = new Label(parent, SWT.NONE);
		lblSave.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblSave.setText("Save");

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
		lblStep_n.setLayoutData(new GridData(SWT.CENTER, SWT.TOP, false, false, 1, 1));
		lblStep_n.setText("n Step");

		/* START--- Button Listener & Action --- */
		btnOpen.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "OPEN", "NULL", "NULL", "NULL", "NULL");
				Handler_SimulationInitThread.SimInitThread_Func();
			}
		});
		btnSave.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "SAVE", "NULL", "NULL", "NULL", "NULL");
				Hanlder_CallBack.CallBack_Func();
			}
		});
		btnRun.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "RUN", "NULL", "NULL", "NULL", "NULL");
				btnStep.setEnabled(false);
				btnStep_n.setEnabled(false);
				btnRun.setEnabled(false);
				
				SetTableState(false);
				
			}
		});
		btnStop.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "STOP", "NULL", "NULL", "NULL", "NULL");
				btnStep.setEnabled(true);
				btnStep_n.setEnabled(true);
				btnRun.setEnabled(true);

				SetTableState(true);
			}
		});
		btnStep.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "STEP", "1", "NULL", "NULL", "NULL");
			}
		});
		btnStep_n.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "STEP", txtStep.getText(), "NULL", "NULL", "NULL");
				btnStep.setEnabled(false);
				btnStep_n.setEnabled(false);
				btnRun.setEnabled(false);
				
				SetTableState(false);
			}
		});
		/* --- Button Listener & Action ---END */

		// Canvas canvas = new Canvas(parent, SWT.NONE);
		// canvas.setBackground(canvas.getDisplay().getSystemColor(SWT.COLOR_TITLE_INACTIVE_BACKGROUND_GRADIENT));
		// canvas.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 11,
		// 1));
		//
		Composite composite = new Composite(parent, SWT.BORDER);
		composite.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 11, 1));
		composite.setLayout(new FillLayout(SWT.VERTICAL));

		ChannelInfoSet(composite);
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

	private ExpandBar expandBar;
	private ArrayList<ExpandItem> Expanditem = new ArrayList<ExpandItem>();
	private ArrayList<Composite> composite_ExpandItem = new ArrayList<Composite>();
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
	

	protected void ChannelInfoSet(final Composite composite){
		try {
			obj = parser.parse(new FileReader(System.getProperty("user.home")+"/BlockDesigner/testmodule.BDPMD"));
			jsonObject = (JSONObject) obj;
			obj_BDPMD = (JSONObject) jsonObject.get("BDPMD");
			
			arr_ModuleData = (JSONArray) obj_BDPMD.get("Module_Data");
			arr_ChannelInfo = (JSONArray) obj_BDPMD.get("Channel_Info");
		} catch (IOException | ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		expandBar = new ExpandBar(composite, SWT.V_SCROLL);
		
		
		Expanditem.add(0,new ExpandItem(expandBar, SWT.NONE));
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

		
			table_channel = new Table(composite_ExpandItem.get(0), SWT.BORDER | SWT.FULL_SELECTION |SWT.V_SCROLL);
			GridData gd_table = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1);
			gd_table.heightHint=140;
			table_channel.setLayoutData(gd_table);
			table_channel.setHeaderVisible(true);
			table_channel.setLinesVisible(true);

			TableColumn tb_clmn_ChannelName = new TableColumn(table_channel, SWT.CENTER);
			tb_clmn_ChannelName.setWidth(600);
			tb_clmn_ChannelName.setText("Channel Name");

			TableColumn tb_clmn_Tracing = new TableColumn(table_channel, SWT.CENTER);
			tb_clmn_Tracing.setWidth(120);
			tb_clmn_Tracing.setText("Tracing");
			
			int par_Cnt = arr_ChannelInfo.size();
				for (int i = 0; i < par_Cnt; i++) {
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
				
				for (int channel_index = 2; channel_index < items.length; channel_index++) {
					
					obj_Connection = (JSONObject) arr_ChannelInfo.get(channel_index);
					String first_Connection = (String) obj_Connection.get("name");
					String first_Connection_source = "["+first_Connection.replaceAll("[$]", "]");
					jrr_Connection = (JSONArray)obj_Connection.get("connection_info");
					if(jrr_Connection.size() != 0){
						obj_Connection_info = (JSONObject) jrr_Connection.get(0);
					}
					String first_Connection_dest = "["+(String) obj_Connection_info.get("module_name") + "]"
						+ (String) obj_Connection_info.get("port_name");
//					String padded = padRight(first_Connection_source, 70-first_Connection_source.length()*2);
					
					
					editor_channel_table = new TableEditor(table_channel);
					
					final Text txt_ChannelName = new Text(table_channel, SWT.READ_ONLY);
					txt_ChannelName.setTouchEnabled(true);
					txt_ChannelName.setText(first_Connection_source+" <---> "+first_Connection_dest);
					editor_channel_table.grabHorizontal = true;
					editor_channel_table.setEditor(txt_ChannelName, items[channel_index], 0);

					editor_channel_table = new TableEditor(table_channel);
					
					final Button ckb_Tracing = new Button(table_channel, SWT.CHECK);
					editor_channel_table.grabHorizontal = true;
					editor_channel_table.setEditor(ckb_Tracing, items[channel_index], 1);
				}
				
			
		table_channel.pack();
		Expanditem.get(0).setHeight(150);

		
		ModuleInfoIndex=0;
		for(ModuleInfoIndex=0; ModuleInfoIndex<arr_ModuleData.size(); ModuleInfoIndex++ )
		{
			Expanditem.add(new ExpandItem(expandBar, SWT.NONE));
			Expanditem.get(ModuleInfoIndex+1).setExpanded(true);
			obj_module=(JSONObject)arr_ModuleData.get(ModuleInfoIndex);
			String module_type = (String)obj_module.get("module_type");
			
			obj_module_info = (JSONObject) obj_module.get("module_info");
			String InstanceName = (String)obj_module_info.get("instance_name");
			Expanditem.get(ModuleInfoIndex+1).setText(InstanceName);
			arr_port_info = (JSONArray)obj_module_info.get("port");
			arr_par_info = (JSONArray)obj_module_info.get("parameter");
			arr_reg_info = (JSONArray)obj_module_info.get("register");
			
			switch (module_type) {
			case "Core":
				ImageDescriptor idItem1 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_core16.png");
				Image imgItemIcon1 = idItem1.createImage();
				Expanditem.get(ModuleInfoIndex+1).setImage(imgItemIcon1);
				break;
			case "Mem":
				ImageDescriptor idItem2 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_memory16.png");
				Image imgItemIcon2 = idItem2.createImage();
				Expanditem.get(ModuleInfoIndex+1).setImage(imgItemIcon2);
				break;
			case "Bus":
				ImageDescriptor idItem3 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_bus16.png");
				Image imgItemIcon3 = idItem3.createImage();
				Expanditem.get(ModuleInfoIndex+1).setImage(imgItemIcon3);
				break;
			case "etc":
				ImageDescriptor idItem4 = ImageDescriptor.createFromFile(this.getClass(), "/images/img_etc16.png");
				Image imgItemIcon4 = idItem4.createImage();
				Expanditem.get(ModuleInfoIndex+1).setImage(imgItemIcon4);
				break;
			}
			
			composite_ExpandItem.add(new Composite(expandBar, SWT.NONE));
			composite_ExpandItem.get(ModuleInfoIndex+1).setLayout(new GridLayout(3, false));
			composite_ExpandItem.get(ModuleInfoIndex+1).setBackground(color_gray);
			Expanditem.get(ModuleInfoIndex+1).setControl(composite_ExpandItem.get(ModuleInfoIndex+1));
			Expanditem.get(ModuleInfoIndex+1)
					.setHeight(Expanditem.get(ModuleInfoIndex+1).getControl().computeSize(SWT.DEFAULT, SWT.DEFAULT).y);
			
			{ /* --- port ---*/
				table_port = new Table(composite_ExpandItem.get(ModuleInfoIndex + 1),
						SWT.BORDER | SWT.FULL_SELECTION | SWT.V_SCROLL);
				GridData gd_table_port = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1);
				gd_table_port.heightHint = 140;
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
			
			{ /* --- par ---*/
				table_par = new Table(composite_ExpandItem.get(ModuleInfoIndex + 1),
						SWT.BORDER | SWT.FULL_SELECTION | SWT.V_SCROLL);
				GridData gd_table_par = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1);
				gd_table_par.heightHint = 140;
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
							System.err.println("0/2/"+module_name+"/par/write/"+table_par_index+"/"+txt_ParValue.getText());
							Handler_Command.Command_Func(0, 2, module_name ,"par", "write", table_par_index+"", txt_ParValue.getText());
						}
					});
				}
			}
			
			
			{ /* --- reg ---*/
				table_reg = new Table(composite_ExpandItem.get(ModuleInfoIndex + 1),
						SWT.BORDER | SWT.FULL_SELECTION | SWT.V_SCROLL);
				GridData gd_table_reg = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1);
				gd_table_reg.heightHint = 140;
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
							System.err.println("0/2/"+module_name+"/reg/write/"+table_reg_index+"/"+txt_regValue.getText());
							Handler_Command.Command_Func(0, 2, module_name ,"reg", "write", table_reg_index+"", txt_regValue.getText());
						}
					});
				}
			}
			Expanditem.get(ModuleInfoIndex + 1).setHeight(150);
		}

		expandBar.getVerticalBar().addListener(SWT.Selection, new Listener() {
			@Override
			public void handleEvent(Event arg0) {
				// TODO Auto-generated method stub
				for (int i = 0; i < expandBar.getItemCount(); i++) {
					composite_ExpandItem.get(i).layout(true,true);
					expandBar.getItem(i).setHeight(150);
					composite_ExpandItem.get(i).update();
					composite_ExpandItem.get(i).redraw();
					composite_ExpandItem.get(i).pack();
					
//					Control ctrol = expandBar.getItem(i).getControl();
//						ctrol.redraw();
//						ctrol.update();
//						ctrol.pack();
//						System.err.println("11");
				}
			}
		});
	}

	public static String padRight(String s, int n) {
		return String.format("%1$-" + n + "s", s);
	}

	public void setFocus() {
		setViewState(1);
	}
	
	void SetTableState(Boolean state){
		for(int moduleindex=1; moduleindex< composite_ExpandItem.size(); moduleindex++){
			Control[] ctrol_tables = composite_ExpandItem.get(moduleindex).getChildren();
			Table tb_par = (Table)ctrol_tables[1];	// get par table
			Table tb_reg = (Table)ctrol_tables[2];	// get reg table
			
			Control[] Ctrol_par_arg = tb_par.getChildren();
			Control[] Ctrol_reg_arg = tb_reg.getChildren();
			
			for(int i=0; i<Ctrol_par_arg.length/2;i++){
				Text text_par = (Text)Ctrol_par_arg[i*2+1];
				text_par.setEnabled(state);
			}
			
			for(int j=0; j<Ctrol_reg_arg.length/2;j++){
				Text text_reg = (Text)Ctrol_reg_arg[j*2+1];
				text_reg.setEnabled(state);
			}
		}
	}
	
	
	protected JSONArray arr_Result_ModuleList;
	protected JSONObject obj_Result_Module;
	protected JSONArray arr_reg_value;
	protected JSONObject obj_reg_value;
	
	public void SIM_Result(String sim_result){
		System.err.println("===========================in Sim result=============");
		 display.asyncExec(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				try {
					obj = (JSONObject)parser.parse(sim_result);
					jsonObject = (JSONObject) obj;
					arr_Result_ModuleList = (JSONArray) jsonObject.get("SIM_Result");
					String value=null;
					
					for (int refesh_index = 0; refesh_index < arr_Result_ModuleList.size(); refesh_index++) {
						obj_Result_Module=(JSONObject)arr_Result_ModuleList.get(refesh_index);
						arr_reg_value=(JSONArray)obj_Result_Module.get("register_value");
						
						Control[] ctrol_tables = composite_ExpandItem.get(refesh_index + 1).getChildren();
						Table tb_reg = (Table)ctrol_tables[2];	// get reg table
						Control[] Ctrol_reg_arg = tb_reg.getChildren();
						
						for(int reg_index=0; refesh_index<arr_reg_value.size(); reg_index++){
							obj_reg_value = (JSONObject)arr_reg_value.get(reg_index);
							value=(String)obj_reg_value.get("value");
							
							Text text_reg = (Text)Ctrol_reg_arg[reg_index*2+1];
							text_reg.setText(value);
						}
					}
					
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
		}); 
	}
}
