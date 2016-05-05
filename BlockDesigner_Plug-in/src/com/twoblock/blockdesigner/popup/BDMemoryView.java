package com.twoblock.blockdesigner.popup;
import org.eclipse.jface.viewers.ArrayContentProvider;
import org.eclipse.jface.viewers.ITableLabelProvider;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.jface.viewers.ViewerCell;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;


/*
 * Example code
 * Ryan, TwoBlock
 * 
		BDMemoryView mv = new BDMemoryView(shell, "DRAM(AXI Memory)", new IBDMemoryViewListener() {

			@Override
			public void onChangeData(long addr, long data) {
				// TODO Auto-generated method stub
				System.out.println(String.format("Addr.:%s, Data:%s", 
						BDF.LongDecimalToStringHex(addr, 8),
						BDF.LongDecimalToStringHex(data, 8)));
			}

			@Override
			public void onDataLoad(BDMemoryView view, long startAddr, long size) {
				// TODO Auto-generated method stub
				System.out.println("startAddr.:"+BDF.LongDecimalToStringHex(startAddr, 8)+" size:"+size);
			}
		});

		//Dummy data
		long max = 16;
		BDMemoryViewItemArray tmp_data = new BDMemoryViewItemArray();
		tmp_data.baseAddr = 0xFF000000L;
		for(long i=0; i<=max; i++) {
			tmp_data.add(new BDMemoryViewItem(i+0, i+1, i+2, i+3));
			System.out.println("i="+i);
		}
		mv.setData(tmp_data);
		mv.show();
 */


public class BDMemoryView {

	private final int DATA_LOAD_AMOUNT = 256;
	private final int ADDR_AMOUNT = 16;

	private BDMemoryView m_instance = this;
	private Shell m_shell;
	private Display m_display;
	private TableViewer m_tableViewer;
	private Table m_table;

	private IBDMemoryViewListener m_listener;

	public void show() {
		m_shell.open();
	}

	private String[] columnNames = new String[] {"Address", "data1", "data2", "data3", "data4"};
	private BDMemoryViewItemArray m_data = new BDMemoryViewItemArray();


	public BDMemoryView(Shell shell, String compName, IBDMemoryViewListener l)
	{
		m_shell = new Shell(shell.getDisplay(), SWT.CLOSE);
		m_display = m_shell.getDisplay();
		m_listener = l;

		m_shell.setText("Memory View - "+compName);
		m_shell.setSize(570, 550);
		GridLayout gridLayout = new GridLayout();
		gridLayout.numColumns = 3;
		m_shell.setLayout(gridLayout);



		/* Top */
		GridData gdAddr = new GridData();
		gdAddr.horizontalAlignment = GridData.FILL;
		gdAddr.grabExcessHorizontalSpace = true;

		Label labelAddr = new Label(m_shell, SWT.LEFT);
		labelAddr.setText("Address ");

		final Text textAddr = new Text(m_shell, SWT.SINGLE|SWT.BORDER);
		textAddr.setMessage("0x0000FFFF");
		textAddr.setLayoutData(gdAddr);
		textAddr.addListener(SWT.Verify, m_textAllowHexListener);
		textAddr.addKeyListener(new KeyListener() {

			@Override
			public void keyReleased(KeyEvent e) {}

			@Override
			public void keyPressed(KeyEvent e) {
				// TODO Auto-generated method stub
				if(e.keyCode == SWT.CR) {
					moveToAddress(textAddr);
				}
			}
		});
		textAddr.addListener(SWT.FocusOut, new Listener() {
			
			@Override
			public void handleEvent(Event event) {
				// TODO Auto-generated method stub
				moveToAddress(textAddr);
			}
		});
		Button btnAddr = new Button(m_shell, SWT.PUSH);
		btnAddr.setText("이동");
		btnAddr.addSelectionListener(new SelectionListener() {
			
			@Override
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				moveToAddress(textAddr);
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent e) {}
		});



		/* Memory Data */
		GridData gdMemory = new GridData();
		gdMemory.horizontalAlignment = GridData.FILL;
		gdMemory.verticalAlignment = GridData.FILL;
		gdMemory.grabExcessVerticalSpace = true;
		gdMemory.horizontalSpan = 3;

		m_tableViewer = new TableViewer(m_shell, SWT.SINGLE|SWT.FULL_SELECTION|SWT.BORDER|SWT.VIRTUAL);
		m_table = m_tableViewer.getTable();
		m_table.setHeaderVisible(true);
		m_table.setLinesVisible(true);
		m_table.addListener(SWT.Selection, new Listener() {

			@Override
			public void handleEvent(Event event) {
				// TODO Auto-generated method stub
				m_table.deselectAll(); //prevent to click row
			}
		});
		m_table.pack();
		m_table.setLayoutData(gdMemory);


		final TableEditor editor = new TableEditor(m_table);
		editor.horizontalAlignment = SWT.RIGHT;
		editor.grabHorizontal = true;
		editor.minimumWidth = 60;

		m_table.addMouseListener(new MouseListener() {

			@Override
			public void mouseUp(MouseEvent e) {}

			@Override
			public void mouseDown(MouseEvent e) {
				// TODO Auto-generated method stub

				disposeOldEditorAndUpdateData(editor);

				/* Find cell row index, col index */
				Point pt = new Point(e.x, e.y);
				TableItem item = m_table.getItem(pt);
				ViewerCell vc = m_tableViewer.getCell(pt);

				if(vc == null || item == null) {
					return;
				}

				final int row = m_table.indexOf(item);
				final int col = vc.getColumnIndex();
				item.setData(new Integer(col)); //set column index

				System.out.println(String.format("row:%d, col:%d, text:%s", row, col, vc.getText()));

				if(!(col > 0)) {
					return;
				}

				/* Replace widget */
				Text newEditor = new Text(m_table, SWT.RIGHT);
				newEditor.setText(item.getText(col));
				newEditor.setTextLimit(10);
				newEditor.addListener(SWT.Verify, m_textAllowHexListener);
				newEditor.addKeyListener(new KeyListener() {

					@Override
					public void keyReleased(KeyEvent e) {
						// TODO Auto-generated method stub

					}

					@Override
					public void keyPressed(KeyEvent e) {
						// TODO Auto-generated method stub
						System.out.println("keycode: "+e.keyCode);

						if(e.keyCode == SWT.CR) {
							disposeOldEditorAndUpdateData(editor);
						}
					}
				});
				newEditor.selectAll();
				newEditor.setFocus();
				editor.setEditor(newEditor, item, col);
			}

			@Override
			public void mouseDoubleClick(MouseEvent e) {}
		});

		for(int i=0; i<columnNames.length; i++) {
			TableColumn col = new TableColumn(m_table, SWT.CENTER);
			col.setText(columnNames[i]);
			if(i==0)
				col.setWidth(130);
			else
				col.setWidth(100);
			col.setResizable(false);
		}

		m_tableViewer.setLabelProvider(new MVTableLabelProvider());
		m_tableViewer.setContentProvider(new ArrayContentProvider());
		setData(m_data);
		
	}


	private void disposeOldEditorAndUpdateData(TableEditor editor)
	{
		Text text = (Text)editor.getEditor();
		if(text != null && !text.isDisposed()) 
		{
			String str = text.getText().replace("0x", "").toUpperCase();
			str = str.replace("X", "");
			while(str.length() < 8)
				str = "0"+str;

			
			TableItem item = editor.getItem();
			int index = m_table.indexOf(item);
			int col = (Integer)item.getData();
			item.setText(col, str);

			if(m_listener != null) {
				m_listener.onChangeData(m_data.baseAddr + index*ADDR_AMOUNT+((col-1)*4), BDF.StringHexToLongDecimal(str));
			}
		}

		Control oldEditor = editor.getEditor();
		if(oldEditor != null)
			oldEditor.dispose();
	}

	private Listener m_textAllowHexListener = new Listener() {

		@Override
		public void handleEvent(Event e) {
			// TODO Auto-generated method stub

			String str = e.text;
			char[] chars = new char[str.length()];
			str.getChars(0, chars.length, chars, 0);
			for(int i=0; i<chars.length; i++) {
				if(!(('0' <= chars[i] && chars[i] <= '9'))) {
					if(!(('a' <= chars[i] && chars[i] <= 'f') || chars[i] == 'x')) {
						if(!('A' <= chars[i] && chars[i] <= 'F')) {
							e.doit = false;
							System.out.println("Invalid character input!");
							return;
						}
					}
				}
			}
		}
	};
	
	private void moveToAddress(Text text) {
		String str = text.getText();
		long addr = BDF.StringHexToLongDecimal(str);
		addr -= addr%16;
		
		if(m_listener != null) {
			m_listener.onDataLoad(m_instance, addr, DATA_LOAD_AMOUNT);
		}
	}


	public void setData(BDMemoryViewItemArray data) {
		m_data = data;
		m_tableViewer.setInput(m_data.toArray());
//		m_table.pack();
//		m_shell.pack();
	}
	
	public BDMemoryViewItemArray getData() {
		return m_data;
	}


	private class MVTableLabelProvider extends LabelProvider implements ITableLabelProvider {

		@Override
		public Image getColumnImage(Object arg0, int index) {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public String getColumnText(Object obj, int index) {
			// TODO Auto-generated method stub

			BDMemoryViewItem item = (BDMemoryViewItem)obj;
			long addr = m_data.baseAddr + (m_data.indexOf(item)*ADDR_AMOUNT);

			switch(index) {
			case 0: //address area
				return BDF.LongDecimalToStringHex(addr, 8);

			case 1: //data1
				return BDF.LongDecimalToStringHex(item.data1, 8).replace("0x", "");
				
			case 2:
				return BDF.LongDecimalToStringHex(item.data2, 8).replace("0x", "");
				
			case 3:
				return BDF.LongDecimalToStringHex(item.data3, 8).replace("0x", "");
				
			case 4:
				return BDF.LongDecimalToStringHex(item.data4, 8).replace("0x", "");

			default:
				return "unknown " + index;
			}
		}
	}
}
