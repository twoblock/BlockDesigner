package swt_dnd;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.CCombo;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.events.ControlEvent;
import org.eclipse.swt.events.ControlListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.ExpandBar;
import org.eclipse.swt.widgets.ExpandItem;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import org.eclipse.swt.events.TouchListener;
import org.eclipse.swt.events.TouchEvent;

public class PM_viewtest {
	protected Shell shell;
	private List list_All;
	private List list_Core;
	private List list_Bus;
	private List list_Mem;
	private List list_etc;
	private ExpandBar expandBar;
	private Table table_port;
	private Table table_par;
	
	private JSONParser parser = new JSONParser();
	private Object obj;
	private JSONObject jsonObject;
	private JSONArray ModuleInfoList;
	private JSONObject ModuleObject;
	private JSONArray PortInfoList;
	private int list_Cnt = 0;
	private ArrayList UsedModuleList = new ArrayList();
	private String PastItem;
	
	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			PM_viewtest window = new PM_viewtest();
			window.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Open the window.
	 */
	public void open() {
		Display display = Display.getDefault();
		createContents();
		shell.open();
		shell.layout();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shell = new Shell();
		shell.setSize(1200, 600);
		shell.setText("SWT Application");
		shell.setLayout(new GridLayout(3, false));

		Composite composite_Toolbar = new Composite(shell, SWT.NONE);
		composite_Toolbar.setLayout(new FillLayout(SWT.HORIZONTAL));

		Image imgNew = new Image(null, "images/new_btn.png");
		Image imgOpen = new Image(null, "images/open_btn.png");
		Image imgSave = new Image(null, "images/save_btn.png");

		Button btn_new = new Button(composite_Toolbar, SWT.NONE);
		btn_new.setImage(imgNew);
		Button btn_open = new Button(composite_Toolbar, SWT.NONE);
		btn_open.setImage(imgOpen);
		Button btn_save = new Button(composite_Toolbar, SWT.NONE);
		btn_save.setImage(imgSave);
		new Label(shell, SWT.NONE);
		new Label(shell, SWT.NONE);

		Label label = new Label(shell, SWT.SEPARATOR | SWT.HORIZONTAL);
		label.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, false, false, 3, 1));
		
		Composite composite_PlatformViewer = new Composite(shell, SWT.BORDER);
		composite_PlatformViewer.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		composite_PlatformViewer.setLayout(new FillLayout(SWT.VERTICAL));
		

		expandBar = new ExpandBar(composite_PlatformViewer, SWT.V_SCROLL);
		
		{
			Composite composite_ModuleSetter = new Composite(shell, SWT.NONE);
			composite_ModuleSetter.setLayout(new GridLayout(1, false));
			GridData gd_composite_ModuleSetter = new GridData(SWT.LEFT, SWT.FILL, false, false, 1, 1);
			gd_composite_ModuleSetter.widthHint = 25;
			composite_ModuleSetter.setLayoutData(gd_composite_ModuleSetter);
			
			Label lbl_Blank_top = new Label(composite_ModuleSetter, SWT.NONE);
			lbl_Blank_top.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
			
			Button btn_Module_Add = new Button(composite_ModuleSetter, SWT.FLAT | SWT.CENTER);
			btn_Module_Add.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
			btn_Module_Add.setText("◀");
			
			new Label(composite_ModuleSetter, SWT.NONE);
			new Label(composite_ModuleSetter, SWT.NONE);
			
			Button btn_Module_Delete = new Button(composite_ModuleSetter, SWT.FLAT | SWT.CENTER);
			btn_Module_Delete.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
			btn_Module_Delete.setText("▶");
			
			Label lbl_Blank_bottom = new Label(composite_ModuleSetter, SWT.NONE);
			lbl_Blank_bottom.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
			
			btn_Module_Add.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					String Module_Name=null;
					Module_Name=list_All.getItem(list_All.getSelectionIndex());
					AddModuleSelected(Module_Name);
				}
				
				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					
				}
			});
			
			btn_Module_Delete.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					DeleteModuleSelected();
				}
				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					
				}
			});
			
		}
		
		
		Composite composite_ModuleList = new Composite(shell, SWT.NONE);
		composite_ModuleList.setLayoutData(new GridData(SWT.LEFT, SWT.FILL, false, false, 1, 1));
		composite_ModuleList.setLayout(new GridLayout(1, false));

		TabFolder tab_ModuleList = new TabFolder(composite_ModuleList, SWT.NONE);
		tab_ModuleList.setLayoutData(new GridData(SWT.LEFT, SWT.FILL, true, true, 1, 1));
		{
			TabItem tb_All = new TabItem(tab_ModuleList, SWT.NONE);
			tb_All.setText("All");
			list_All = new List(tab_ModuleList, SWT.NONE);
			tb_All.setControl(list_All);
			list_All.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleClicked(list_All);
				}

				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleDoubleClicked(list_All);
				}
			});
		}
		{
			TabItem tb_Core = new TabItem(tab_ModuleList, SWT.NONE);
			tb_Core.setText("Core");

			list_Core = new List(tab_ModuleList, SWT.NONE);
			tb_Core.setControl(list_Core);
			list_Core.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleClicked(list_Core);
				}

				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleDoubleClicked(list_Core);
				}
			});
		}
		{
			TabItem tb_Bus = new TabItem(tab_ModuleList, SWT.NONE);
			tb_Bus.setText("Bus");

			list_Bus = new List(tab_ModuleList, SWT.NONE);
			tb_Bus.setControl(list_Bus);
			list_Bus.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleClicked(list_Bus);
				}

				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleDoubleClicked(list_Bus);
				}
			});
		}
		{
			TabItem tb_Mem = new TabItem(tab_ModuleList, SWT.NONE);
			tb_Mem.setText("Mem");

			list_Mem = new List(tab_ModuleList, SWT.NONE);
			tb_Mem.setControl(list_Mem);
			list_Mem.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleClicked(list_Mem);
				}

				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleDoubleClicked(list_Mem);
				}
			});
		}
		{
			TabItem tb_etc = new TabItem(tab_ModuleList, SWT.NONE);
			tb_etc.setText("etc");

			list_etc = new List(tab_ModuleList, SWT.NONE);
			tb_etc.setControl(list_etc);
			list_etc.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleClicked(list_etc);
				}

				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					ModuleDoubleClicked(list_etc);
				}
			});
		}

		Button btn_AddModule = new Button(composite_ModuleList, SWT.NONE);
		btn_AddModule.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		btn_AddModule.setText("Add Module");

		viewsetting();
	}

	protected void AddModuleSelected(String Module_Name) {
		// TODO Auto-generated method stub
		ExpandItem Expanditem_1 = new ExpandItem(expandBar, SWT.NONE);
		Expanditem_1.setExpanded(true);
		
		String Module_Title=null;
		Module_Title=Module_Name+" ("+Module_Name+")";
		System.err.println(Module_Name);
		UsedModuleList.add(Module_Name);
		
		Expanditem_1.setText(Module_Title);
		
		Composite composite_ExpandItem_1 = new Composite(expandBar, SWT.NONE);
		composite_ExpandItem_1.setLayout(new GridLayout(2, false));
		Expanditem_1.setControl(composite_ExpandItem_1);
		Expanditem_1.setHeight(Expanditem_1.getControl().computeSize(SWT.DEFAULT, SWT.DEFAULT).y);
		
		{/* --- port table ---*/
			table_port = new Table(composite_ExpandItem_1, SWT.BORDER | SWT.FULL_SELECTION);
			table_port.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1));
			table_port.setHeaderVisible(true);
			table_port.setLinesVisible(true);
			TableColumn tblclmnNewColumn = new TableColumn(table_port, SWT.NONE);
			tblclmnNewColumn.setWidth(140);
			tblclmnNewColumn.setText("Port Name");

			TableColumn tblclmnNewColumn_1 = new TableColumn(table_port, SWT.NONE);
			tblclmnNewColumn_1.setWidth(120);
			tblclmnNewColumn_1.setText("dest Module");

			TableColumn tblclmnNewColumn_4 = new TableColumn(table_port, SWT.NONE);
			tblclmnNewColumn_4.setWidth(140);
			tblclmnNewColumn_4.setText("dest Port");
			
			int Selected_Index = 0;
			int port_Cnt=0;
			String module=null;
			// 선택한 모듈 찾기.
			for (Selected_Index = 0; Selected_Index < list_Cnt; Selected_Index++) {
				JSONObject ModuleObject = (JSONObject) ModuleInfoList.get(Selected_Index);
				module = (String) ModuleObject.get("module_name");
				if (Module_Name.equals(module) == true)
					break;
			}
			// 선택된 모듈에서 포트 가져오기.
			ModuleObject = (JSONObject) ModuleInfoList.get(Selected_Index);
			PortInfoList = (JSONArray) ModuleObject.get("port");
			port_Cnt = PortInfoList.size();

			for (int i = 0; i < port_Cnt; i++) {
			      new TableItem(table_port, SWT.NONE);
			}
			
			TableItem[] items = table_port.getItems();
			for (int port_index = 0; port_index < items.length; port_index++) {
				// 포트리스트에서 해당 index의 포트정보 -> PortObject
				JSONObject PortObject = (JSONObject) PortInfoList.get(port_index);
				
				TableEditor editor = new TableEditor(table_port);
				
				editor = new TableEditor(table_port);
				Text text = new Text(table_port,SWT.READ_ONLY);
				text.setTouchEnabled(true);
				text.setText((String) PortObject.get("sc_type")+"<"+(String) PortObject.get("data_type")+">"+(String) PortObject.get("port_name"));
				editor.grabHorizontal = true;
				editor.setEditor(text, items[port_index], 0);
						
				editor = new TableEditor(table_port);
				CCombo cmb_DestModule = new CCombo(table_port, SWT.READ_ONLY);
				cmb_DestModule.setText("Plz choose Module");
				cmb_DestModule.addListener(SWT.DROP_DOWN, new Listener() {
					@Override
					public void handleEvent(Event event) {
						PastItem = cmb_DestModule.getText();
						// TODO Auto-generated method stub
						cmb_DestModule.removeAll();
						cmb_DestModule.setText(PastItem);
						for (int destModule = 0; destModule < UsedModuleList.size(); destModule++) {
							if (UsedModuleList.get(destModule) != Module_Name) {
								cmb_DestModule.add((String) UsedModuleList.get(destModule));
							}
						}
					}
				});
				
				
				editor.grabHorizontal = true;
				editor.setEditor(cmb_DestModule, items[port_index], 1);
				
				editor = new TableEditor(table_port);
				CCombo cmb_DestPort = new CCombo(table_port, SWT.READ_ONLY);
				cmb_DestPort.setText("");
				cmb_DestPort.addListener(SWT.DROP_DOWN, new Listener() {
					@Override
					public void handleEvent(Event event) {
						// TODO Auto-generated method stub
						if ((cmb_DestPort.getText().equals(""))&&(cmb_DestModule.getText().equals("Plz choose Module") == false) &&(cmb_DestModule.getText().equals("")==false)){
							String module = null;
							int port_Cnt = 0;
							for (int DestModule_Index = 0; DestModule_Index < list_Cnt; DestModule_Index++) {
								ModuleObject = (JSONObject) ModuleInfoList.get(DestModule_Index);
								module = (String) ModuleObject.get("module_name");
								if (cmb_DestModule.getText().equals(module) == true)
									break;
							}
							PortInfoList = (JSONArray) ModuleObject.get("port");
							port_Cnt = PortInfoList.size();

							cmb_DestPort.removeAll();
							for (int destPort = 0; destPort < port_Cnt; destPort++) {
								JSONObject PortObject = (JSONObject) PortInfoList.get(destPort);
								cmb_DestPort.add(
										(String) PortObject.get("sc_type") + "<" + (String) PortObject.get("data_type")
												+ ">" + (String) PortObject.get("port_name"));
							}
						}
					}
				});
				
				// DestModule선택시 이전 DestModule과 비교해서 DestPort값의 유지 여부 결정.
				cmb_DestModule.addSelectionListener(new SelectionListener() {
					@Override
					public void widgetSelected(SelectionEvent e) {
						// TODO Auto-generated method stub
						if(PastItem.equals(cmb_DestModule.getItem((cmb_DestModule.getSelectionIndex())))==false)
							cmb_DestPort.removeAll();
					}

					@Override
					public void widgetDefaultSelected(SelectionEvent e) {
						// TODO Auto-generated method stub

					}
				});
				
				editor.grabHorizontal = true;
				editor.setEditor(cmb_DestPort, items[port_index], 2);
			}
		}
		
		{/* --- port table ---*/
			table_par = new Table(composite_ExpandItem_1, SWT.BORDER | SWT.FULL_SELECTION);
			table_par.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1));
			table_par.setHeaderVisible(true);
			table_par.setLinesVisible(true);
			
			TableColumn tblclmnNewColumn_2 = new TableColumn(table_par, SWT.NONE);
			tblclmnNewColumn_2.setWidth(100);
			tblclmnNewColumn_2.setText("Parameter");
			
			TableColumn tblclmnNewColumn_3 = new TableColumn(table_par, SWT.NONE);
			tblclmnNewColumn_3.setWidth(150);
			tblclmnNewColumn_3.setText("Value");
			
			TableColumn tblclmnNewColumn_5 = new TableColumn(table_par, SWT.NONE);
			tblclmnNewColumn_5.setWidth(150);
			tblclmnNewColumn_5.setText("Type");
		}
		
		
		Button btnMemoryMapSetting = new Button(composite_ExpandItem_1, SWT.NONE);
		btnMemoryMapSetting.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
		btnMemoryMapSetting.setText("Memory Map Setting");
		String type;
		
		type = (String) ModuleObject.get("module_type");
		if (type.equals("Bus") == false){
			btnMemoryMapSetting.setEnabled(false);
		}
		
		Button btnCheckButton = new Button(composite_ExpandItem_1, SWT.CHECK);
		btnCheckButton.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
			}
		});
		
		
		btnCheckButton.setLayoutData(new GridData(SWT.RIGHT, SWT.FILL, false, false, 1, 1));
		btnCheckButton.setText("Delete  ");
		
		btnMemoryMapSetting.pack();
		table_port.pack();
		
		Expanditem_1.setHeight(table_port.getSize().y+btnMemoryMapSetting.getSize().y+15);
		
	}
	
	protected void DeleteModuleSelected() {
		// TODO Auto-generated method stub
		
	}

	void viewsetting() {
		/* --- Parser Module list setting--- */
		String module = null;
		String type = null;
		try {
			obj = parser.parse(new FileReader("test.PMML"));
			jsonObject = (JSONObject) obj;
			ModuleInfoList = (JSONArray) jsonObject.get("PMML");
			list_Cnt = ModuleInfoList.size();
			for (int i = 0; i < list_Cnt; i++) {
				ModuleObject = (JSONObject) ModuleInfoList.get(i);
				module = (String) ModuleObject.get("module_name");
				type = (String) ModuleObject.get("module_type");
				list_All.add(module);
				if (type.equals("Core") == true)
					list_Core.add(module);
				else if (type.equals("Bus") == true)
					list_Bus.add(module);
				else if (type.equals("Mem") == true)
					list_Mem.add(module);
				else if (type.equals("etc") == true)
					list_etc.add(module);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		/* --- Parser --- */
	}

	void ModuleClicked(List SelectedTab) {
		String SelectedModule = SelectedTab.getItem(SelectedTab.getSelectionIndex());
		System.out.println("selected: " + SelectedModule);
	}

	void ModuleDoubleClicked(List SelectedTab) {
		String SelectedModule = SelectedTab.getItem(SelectedTab.getSelectionIndex());
		/* --- Parser --- */
		int list_Cnt = 0;
		int port_Cnt = 0;
		int Selected_Index = 0;
		String module = null;
		JSONParser parser = new JSONParser();
		try {
			obj = parser.parse(new FileReader("test.PMML"));
			jsonObject = (JSONObject) obj;
			ModuleInfoList = (JSONArray) jsonObject.get("PMML");
			list_Cnt = ModuleInfoList.size();

			// 선택한 모듈 찾기.
			for (Selected_Index = 0; Selected_Index < list_Cnt; Selected_Index++) {
				ModuleObject = (JSONObject) ModuleInfoList.get(Selected_Index);
				module = (String) ModuleObject.get("module_name");
				if (SelectedModule.equals(module) == true)
					break;
			}
			// 선택된 모듈에서 포트 가져오기.
			ModuleObject = (JSONObject) ModuleInfoList.get(Selected_Index);
			PortInfoList = (JSONArray) ModuleObject.get("port");
			port_Cnt = PortInfoList.size();

			System.err.println("********* Port Info *********");
			for (int port_index = 0; port_index < port_Cnt; port_index++) {
				JSONObject PortObject = (JSONObject) PortInfoList.get(port_index);
				System.out.println("port_name =" + PortObject.get("port_name"));
				System.out.println("sc_type =" + PortObject.get("sc_type"));
				System.out.println("data_type =" + PortObject.get("data_type"));
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		/* --- Parser --- */
	}
}
