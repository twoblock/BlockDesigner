package swt_dnd;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.SWTException;
import org.eclipse.swt.custom.CCombo;
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

public class PM_viewtest {
	protected Shell shell;
	private List list_All;
	private List list_Core;
	private List list_Bus;
	private List list_Mem;
	private List list_etc;
	private TabFolder tab_ModuleList;
	private ExpandBar expandBar;
	private Table table_port;
	private Table table_par;
	private Button[] btnCheckButton = new Button[10];
	private Composite[] composite_ExpandItem = new Composite[10];
	private Device device = Display.getCurrent();
	private Color color_gray = new Color(device,150,150,150);
	private Color color_skyblue = new Color(device,204,204,255);
	
	private ExpandItem[] Expanditem = new ExpandItem[10];

	private JSONParser parser = new JSONParser();
	private Object obj;
	private JSONObject jsonObject;
	private JSONArray ModuleInfoList;
	private JSONObject ModuleObject;
	private JSONArray PortInfoList;
	private JSONArray ParameterInfoList;
	private int list_Cnt = 0;
	private ArrayList<String> DrawModuleList = new ArrayList<String>();
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
//		Theme a =a;
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
			btn_Module_Add.setText("<");

			new Label(composite_ModuleSetter, SWT.NONE);
			new Label(composite_ModuleSetter, SWT.NONE);

			Button btn_Module_Delete = new Button(composite_ModuleSetter, SWT.FLAT | SWT.CENTER);
			btn_Module_Delete.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
			btn_Module_Delete.setText(">");

			Label lbl_Blank_bottom = new Label(composite_ModuleSetter, SWT.NONE);
			lbl_Blank_bottom.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));

			btn_Module_Add.addSelectionListener(new SelectionListener() {
				@Override
				public void widgetSelected(SelectionEvent e) {
					// TODO Auto-generated method stub
					String Module_Name = null;
					if (list_All.getSelectionIndex() != -1) {
						Module_Name = list_All.getItem(list_All.getSelectionIndex());
						AddModuleSelected(Module_Name);
					} else if (list_Core.getSelectionIndex() != -1) {
						Module_Name = list_Core.getItem(list_Core.getSelectionIndex());
						AddModuleSelected(Module_Name);
					} else if (list_Bus.getSelectionIndex() != -1) {
						Module_Name = list_Bus.getItem(list_Bus.getSelectionIndex());
						AddModuleSelected(Module_Name);
					} else if (list_Mem.getSelectionIndex() != -1) {
						Module_Name = list_Mem.getItem(list_Mem.getSelectionIndex());
						AddModuleSelected(Module_Name);
					} else if (list_etc.getSelectionIndex() != -1) {
						Module_Name = list_etc.getItem(list_etc.getSelectionIndex());
						AddModuleSelected(Module_Name);
					}

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

		tab_ModuleList = new TabFolder(composite_ModuleList, SWT.NONE);
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
		tab_ModuleList.addSelectionListener(new SelectionListener() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				list_All.setSelection(-1);
				list_Core.setSelection(-1);
				list_Bus.setSelection(-1);
				list_Mem.setSelection(-1);
				list_etc.setSelection(-1);
			}

			@Override
			public void widgetDefaultSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
			}
		});

		Button btn_AddModule = new Button(composite_ModuleList, SWT.NONE);
		btn_AddModule.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 1, 1));
		btn_AddModule.setText("Add Module");

		viewsetting();
	}

	protected void AddModuleSelected(final String Module_Name) {
		// TODO Auto-generated method stub

		String Module_Title = null;
		int DrawModuleIndex = 0;
		Module_Title = Module_Name + " (" + Module_Name + ")";

		// Draw??紐⑤뱢?꾩씠??list?????
		DrawModuleList.add(Module_Name);
		DrawModuleIndex = DrawModuleList.size() - 1;
		
		Expanditem[DrawModuleIndex] = new ExpandItem(expandBar, SWT.NONE);
		Expanditem[DrawModuleIndex].setExpanded(true);

		Expanditem[DrawModuleIndex].setText(Module_Title);

		composite_ExpandItem[DrawModuleIndex] = new Composite(expandBar, SWT.NONE);
		
		
		composite_ExpandItem[DrawModuleIndex].setBackground(color_gray);
		
		composite_ExpandItem[DrawModuleIndex].setLayout(new GridLayout(2, false));
		Expanditem[DrawModuleIndex].setControl(composite_ExpandItem[DrawModuleIndex]);
		Expanditem[DrawModuleIndex]
				.setHeight(Expanditem[DrawModuleIndex].getControl().computeSize(SWT.DEFAULT, SWT.DEFAULT).y);

		{/* --- port table --- */
			table_port = new Table(composite_ExpandItem[DrawModuleIndex], SWT.BORDER | SWT.FULL_SELECTION);
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
			int port_Cnt = 0;
			String module = null;
			// ?좏깮??紐⑤뱢 李얘린.
			for (Selected_Index = 0; Selected_Index < list_Cnt; Selected_Index++) {
				JSONObject ModuleObject = (JSONObject) ModuleInfoList.get(Selected_Index);
				module = (String) ModuleObject.get("module_name");
				if (Module_Name.equals(module) == true)
					break;
			}
			// ?좏깮??紐⑤뱢?먯꽌 ?ы듃 媛?몄삤湲?
			ModuleObject = (JSONObject) ModuleInfoList.get(Selected_Index);
			PortInfoList = (JSONArray) ModuleObject.get("port");
			port_Cnt = PortInfoList.size();

			for (int i = 0; i < port_Cnt; i++) {
				new TableItem(table_port, SWT.NONE);
			}

			TableItem[] items = table_port.getItems();
			for (int port_index = 0; port_index < items.length; port_index++) {
				// ?ы듃由ъ뒪?몄뿉???대떦 index???ы듃?뺣낫 -> PortObject
				JSONObject PortObject = (JSONObject) PortInfoList.get(port_index);

				TableEditor editor = new TableEditor(table_port);

				editor = new TableEditor(table_port);
				Text text = new Text(table_port, SWT.READ_ONLY);
				text.setTouchEnabled(true);
				text.setText((String) PortObject.get("sc_type") + "<" + (String) PortObject.get("data_type") + ">"
						+ (String) PortObject.get("port_name"));
				editor.grabHorizontal = true;
				editor.setEditor(text, items[port_index], 0);

				editor = new TableEditor(table_port);
				final CCombo cmb_DestModule = new CCombo(table_port, SWT.READ_ONLY);
				cmb_DestModule.setText("Plz choose Module");
				cmb_DestModule.addListener(SWT.DROP_DOWN, new Listener() {
					@Override
					public void handleEvent(Event event) {
						PastItem = cmb_DestModule.getText();
						// TODO Auto-generated method stub
						cmb_DestModule.removeAll();
						cmb_DestModule.setText(PastItem);
						for (int destModule = 0; destModule < DrawModuleList.size(); destModule++) {
							if (DrawModuleList.get(destModule) != Module_Name) {
								cmb_DestModule.add((String) DrawModuleList.get(destModule));
							}
						}
					}
				});

				editor.grabHorizontal = true;
				editor.setEditor(cmb_DestModule, items[port_index], 1);

				editor = new TableEditor(table_port);
				final CCombo cmb_DestPort = new CCombo(table_port, SWT.READ_ONLY);
				cmb_DestPort.setText("");
				cmb_DestPort.addListener(SWT.DROP_DOWN, new Listener() {
					@Override
					public void handleEvent(Event event) {
						// TODO Auto-generated method stub
						if ((cmb_DestPort.getText().equals(""))
								&& (cmb_DestModule.getText().equals("Plz choose Module") == false)
								&& (cmb_DestModule.getText().equals("") == false)) {
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

				// DestModule?좏깮???댁쟾 DestModule怨?鍮꾧탳?댁꽌 DestPort媛믪쓽 ?좎? ?щ? 寃곗젙.
				cmb_DestModule.addSelectionListener(new SelectionListener() {
					@Override
					public void widgetSelected(SelectionEvent e) {
						// TODO Auto-generated method stub
						if (PastItem.equals(cmb_DestModule.getItem((cmb_DestModule.getSelectionIndex()))) == false)
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

		{/* --- para table --- */
			table_par = new Table(composite_ExpandItem[DrawModuleIndex], SWT.BORDER | SWT.FULL_SELECTION);
			table_par.setLayoutData(new GridData(SWT.CENTER, SWT.CENTER, false, false, 1, 1));
			table_par.setHeaderVisible(true);
			table_par.setLinesVisible(true);

			TableColumn tb_clmn_Parameter = new TableColumn(table_par, SWT.NONE);
			tb_clmn_Parameter.setWidth(100);
			tb_clmn_Parameter.setText("Parameter");

			TableColumn tb_clmn_Value = new TableColumn(table_par, SWT.NONE);
			tb_clmn_Value.setWidth(100);
			tb_clmn_Value.setText("Value");

			TableColumn tb_clmn_type = new TableColumn(table_par, SWT.NONE);
			tb_clmn_type.setWidth(150);
			tb_clmn_type.setText("Type");
			
			TableColumn tb_clmn_TypeWide = new TableColumn(table_par, SWT.NONE);
			tb_clmn_TypeWide.setWidth(50);
			tb_clmn_TypeWide.setText("Wide");
			
			int par_Cnt = 0;
			ParameterInfoList = (JSONArray) ModuleObject.get("parameter");
			par_Cnt = ParameterInfoList.size();
			
			
			for (int i = 0; i < par_Cnt; i++) {
				new TableItem(table_par, SWT.NONE);
			}

			TableItem[] items = table_par.getItems();
			for (int par_index = 0; par_index < items.length; par_index++) {
				// ?ы듃由ъ뒪?몄뿉???대떦 index???ы듃?뺣낫 -> PortObject
				JSONObject ParameterObject = (JSONObject) ParameterInfoList.get(par_index);
				
				//TableEditor??clmn??諛붾붾븣留덈떎 ?덈줈 ?앹꽦?댁쨾?쇳븿.
				TableEditor editor_par_table = new TableEditor(table_par);
				editor_par_table = new TableEditor(table_par);
				Text txt_ParameterName = new Text(table_par, SWT.READ_ONLY);
				txt_ParameterName.setTouchEnabled(true);
				txt_ParameterName.setText((String) ParameterObject.get("par_name"));
				editor_par_table.grabHorizontal = true;
				editor_par_table.setEditor(txt_ParameterName, items[par_index], 0);

				editor_par_table = new TableEditor(table_par);
				Text txt_ParameterValue = new Text(table_par, SWT.NONE);
				editor_par_table.grabHorizontal = true;
				txt_ParameterValue.setText((String) ParameterObject.get("default_value"));
				editor_par_table.setEditor(txt_ParameterValue, items[par_index], 1);
				
				editor_par_table = new TableEditor(table_par);
				Text txt_ParameterType = new Text(table_par, SWT.READ_ONLY);
				txt_ParameterType.setTouchEnabled(true);
				txt_ParameterType.setText((String) ParameterObject.get("par_type"));
				editor_par_table.grabHorizontal = true;
				editor_par_table.setEditor(txt_ParameterType, items[par_index], 2);
			}
		}
		String type;
		int padding=0;
		type = (String) ModuleObject.get("module_type");
		if (type.equals("Bus") == true) {
			Button btnMemoryMapSetting = new Button(composite_ExpandItem[DrawModuleIndex], SWT.FLAT);
			btnMemoryMapSetting.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
			btnMemoryMapSetting.setBackground(color_skyblue);
			btnMemoryMapSetting.setText("Memory Map Setting");
			padding=25;
		}
		else{
			Label lbl_null = new Label(composite_ExpandItem[DrawModuleIndex], SWT.NONE);
			lbl_null.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
			lbl_null.setBackground(color_gray);
			padding=10;
		}
		

		btnCheckButton[DrawModuleIndex] = new Button(composite_ExpandItem[DrawModuleIndex], SWT.CHECK);
		btnCheckButton[DrawModuleIndex].addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
			}
		});

		btnCheckButton[DrawModuleIndex].setLayoutData(new GridData(SWT.RIGHT, SWT.FILL, false, false, 1, 1));
		btnCheckButton[DrawModuleIndex].setText("Delete  ");
		btnCheckButton[DrawModuleIndex].setBackground(color_gray);
		
		btnCheckButton[DrawModuleIndex].pack();
		table_port.pack();

		Expanditem[DrawModuleIndex].setHeight(table_port.getSize().y + btnCheckButton[DrawModuleIndex].getSize().y + padding);

	}

	protected void DeleteModuleSelected() {
		// TODO Auto-generated method stub
		System.err.println("DrawModuleList="+DrawModuleList);
		System.err.println("DrawModuleList.size()="+DrawModuleList.size());
		try {
			for (int delete_index = DrawModuleList.size()-1; delete_index >= 0; delete_index--) {
				System.err.println("delete_index="+delete_index);
				if (btnCheckButton[delete_index].getSelection() == true) {
					System.err.println("set="+delete_index);
					
					DrawModuleList.remove(delete_index);
					
					btnCheckButton[delete_index].dispose();
					for (int mover_index = delete_index; mover_index < DrawModuleList.size(); mover_index++) {
						btnCheckButton[delete_index]=btnCheckButton[delete_index+1];
					}
					composite_ExpandItem[delete_index].dispose();
					for (int mover_index = delete_index; mover_index < DrawModuleList.size(); mover_index++) {
						composite_ExpandItem[delete_index]=composite_ExpandItem[delete_index+1];
					}
					Expanditem[delete_index].dispose();
					for (int mover_index = delete_index; mover_index < DrawModuleList.size(); mover_index++) {
						Expanditem[delete_index]=Expanditem[delete_index+1];
					}
					
				}
			}
		} catch (SWTException e) {
			// TODO: handle exception
			System.err.println(e);
		}

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

			// ?좏깮??紐⑤뱢 李얘린.
			for (Selected_Index = 0; Selected_Index < list_Cnt; Selected_Index++) {
				ModuleObject = (JSONObject) ModuleInfoList.get(Selected_Index);
				module = (String) ModuleObject.get("module_name");
				if (SelectedModule.equals(module) == true)
					break;
			}
			// ?좏깮??紐⑤뱢?먯꽌 ?ы듃 媛?몄삤湲?
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
