package com.twoblock.blockdesigner.view;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Device;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.ExpandBar;
import org.eclipse.swt.widgets.ExpandItem;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
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
	private void setViewState(int state) {
		IWorkbenchPage page 
                    = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
		int currentState = page.getPartState(page.getReference(this));
		if(currentState != state) {
			page.activate(this);
			page.setPartState(page.getReference(this), state);
		}
	}
	public void createPartControl(Composite parent) {
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
//		Image imgSave = new Image(null, "images/save_btn.png");
//		Image imgRun = new Image(null, "images/run_btn.png");
//		Image imgStop = new Image(null, "images/stop_btn.png");
//		Image imgStep = new Image(null, "images/step_btn.png");
//		Image imgStep_n = new Image(null, "images/step_n_btn.png");
		
		 
		
		
		Button btnOpen = new Button(parent, SWT.NONE);
		btnOpen.setLayoutData(new GridData(SWT.LEFT, SWT.BOTTOM, false, false, 1, 1));
		btnOpen.setImage(imgOpen);
		
		Button btnSave= new Button(parent, SWT.NONE);
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
		
		lblCyclesCnt = new Label(parent, SWT.BORDER|SWT.RIGHT);
		GridData gd_label = new GridData(SWT.RIGHT,SWT.CENTER,false,false,1,1);
		gd_label.widthHint=200;
		lblCyclesCnt.setLayoutData(gd_label);
		lblCyclesCnt.setText("110254");
//		lblCyclesCnt.setAlignment(SWT.CENTER);
		
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
			}
		});
		btnStop.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				Handler_Command.Command_Func(0, 1, "STOP", "NULL", "NULL", "NULL", "NULL");
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
				Handler_Command.Command_Func(0, 1, "STEP",txtStep.getText(), "NULL", "NULL", "NULL");
			}
		});
		/* --- Button Listener & Action ---END */
		
		
//		Canvas canvas = new Canvas(parent, SWT.NONE);
//		canvas.setBackground(canvas.getDisplay().getSystemColor(SWT.COLOR_TITLE_INACTIVE_BACKGROUND_GRADIENT)); 
//		canvas.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 11, 1));
//		
		Composite composite = new Composite(parent, SWT.BORDER);
		composite.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 11, 1));
		composite.setLayout(new FillLayout(SWT.VERTICAL));
		
		ChannelInfoSet(composite);
	}
	
	private Device device = Display.getCurrent();
	private Color color_gray = new Color(device, 150, 150, 150);
	private Color color_skyblue = new Color(device, 204, 204, 255);
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
	
	private JSONArray jrr_HCLK_connection;
	private JSONObject obj_HCLK;
	private JSONObject obj_HCLK_info;
	
	private JSONArray jrr_HRESETn_connection;
	private JSONObject obj_HRESETn;
	private JSONObject obj_HRESETn_info;
	private JSONObject obj_module_info;
	
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
		
			Label lbl_HCLK = new Label(composite_ExpandItem.get(0), SWT.READ_ONLY);
			lbl_HCLK.setLayoutData(new GridData(SWT.RIGHT, SWT.TOP, true, true, 1, 1));
			lbl_HCLK.setText("HCLK");
			Combo cmb_HCLK = new Combo(composite_ExpandItem.get(0), SWT.DROP_DOWN|SWT.READ_ONLY);
			cmb_HCLK.setLayoutData(new GridData(SWT.FILL, SWT.TOP, true, true, 1, 1));
			
			obj_HCLK = (JSONObject) arr_ChannelInfo.get(0);
			String first_HCLK = (String) obj_HCLK.get("name");
			String [] first_HCLK_tok = first_HCLK.split("[$]");
			cmb_HCLK.add(first_HCLK_tok[0]);

			jrr_HCLK_connection = (JSONArray)obj_HCLK.get("connection_info");
			for(int HCLK_index=0; HCLK_index < jrr_HCLK_connection.size() ; HCLK_index++){
				obj_HCLK_info = (JSONObject)jrr_HCLK_connection.get(HCLK_index);
				cmb_HCLK.add((String)obj_HCLK_info.get("module_name"));
			}
			
			Label lbl_HRESETn = new Label(composite_ExpandItem.get(0), SWT.READ_ONLY);
			lbl_HRESETn.setLayoutData(new GridData(SWT.RIGHT, SWT.TOP, true, true, 1, 1));
			lbl_HRESETn.setText("HRESETn");
			Combo cmb_HRESETn = new Combo(composite_ExpandItem.get(0), SWT.DROP_DOWN|SWT.READ_ONLY);
			cmb_HRESETn.setLayoutData(new GridData(SWT.FILL, SWT.TOP, true, true, 1, 1));
			obj_HRESETn = (JSONObject) arr_ChannelInfo.get(1);
			String first_HRESETn = (String) obj_HRESETn.get("name");
			String [] first_HRESETn_tok = first_HRESETn.split("[$]");
			cmb_HRESETn.add(first_HRESETn_tok[0]);

			jrr_HRESETn_connection = (JSONArray)obj_HRESETn.get("connection_info");
			for(int HRESETn=0; HRESETn < jrr_HRESETn_connection.size() ; HRESETn++){
				obj_HRESETn_info = (JSONObject)jrr_HRESETn_connection.get(HRESETn);
				cmb_HRESETn.add((String)obj_HRESETn_info.get("module_name"));
			}

			Label lbl_Connection = new Label(composite_ExpandItem.get(0), SWT.READ_ONLY);
			lbl_Connection.setLayoutData(new GridData(SWT.RIGHT, SWT.TOP, true, true, 1, 1));
			lbl_Connection.setText("Connections");
			Combo cmb_Connection = new Combo(composite_ExpandItem.get(0), SWT.DROP_DOWN|SWT.READ_ONLY);
			cmb_Connection.setLayoutData(new GridData(SWT.FILL, SWT.TOP, true, true, 1, 1));
			
			for(int i=2; i< arr_ChannelInfo.size(); i++){
				obj_Connection = (JSONObject) arr_ChannelInfo.get(i);
				String first_Connection = (String) obj_Connection.get("name");
				String first_Connection_source = "["+first_Connection.replaceAll("[$]", "]");
				jrr_Connection = (JSONArray)obj_Connection.get("connection_info");
				obj_Connection_info = (JSONObject) jrr_Connection.get(0);
				String first_Connection_dest = "["+(String) obj_Connection_info.get("module_name") + "]"
					+ (String) obj_Connection_info.get("port_name");
				String padded = padRight(first_Connection_source, 70-first_Connection_source.length()*2);
				cmb_Connection.add(padded+" <----->              "+first_Connection_dest);
			}
			
		cmb_HRESETn.pack();
		cmb_HCLK.pack();
		cmb_Connection.pack();
		
		Expanditem.get(0).setHeight(cmb_HRESETn.getSize().y + cmb_HCLK.getSize().y + cmb_Connection.getSize().y + 10);

		
		int ModuleInfoIndex;
		for(ModuleInfoIndex=0; ModuleInfoIndex<arr_ModuleData.size(); ModuleInfoIndex++ )
		{
			Expanditem.add(new ExpandItem(expandBar, SWT.NONE));
			Expanditem.get(ModuleInfoIndex+1).setExpanded(true);
			obj_module=(JSONObject)arr_ModuleData.get(ModuleInfoIndex);
			String module_type = (String)obj_module.get("module_type");
			
			obj_module_info = (JSONObject) obj_module.get("module_info");
			String InstanceName = (String)obj_module_info.get("instance_name");
			Expanditem.get(ModuleInfoIndex+1).setText(InstanceName);
			
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
			composite_ExpandItem.get(ModuleInfoIndex+1).setLayout(new GridLayout(2, false));
			
			Expanditem.get(ModuleInfoIndex+1).setControl(composite_ExpandItem.get(ModuleInfoIndex+1));
			Expanditem.get(ModuleInfoIndex+1)
					.setHeight(Expanditem.get(ModuleInfoIndex+1).getControl().computeSize(SWT.DEFAULT, SWT.DEFAULT).y);
		}
	}
	
	public static String padRight(String s, int n) {
	     return String.format("%1$-" + n + "s", s);  
	}
	
	public void setFocus() {
		setViewState(1);
	}
}
