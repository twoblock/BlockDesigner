package com.twoblock.blockdesigner.popup;

import java.util.ArrayList;

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
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;

public class BDMemoryMapEditor {

	final int COL_INDEX_START_ADDR = 2;
	final int COL_INDEX_SIZE_ADDR = 3;
	final int COL_INDEX_END_ADDR = 4;
	final long MAX_ADDR_SIZE = 4294967295L;
	
	private Shell m_shell;
	private IBDMemoryMapEditorListener m_listener;
	private TableViewer m_tableViewer;
	private Table m_table;

	public void show() {
		m_shell.open();
	}


	private String[] columnNames = new String[] {"Module", "Connected Port", "Start Addr", "Size", "End Addr"};
	private int[] columnWidths = new int[] {150, 150, 100, 100, 100};
	private int[] columnAligns = new int[] {SWT.LEFT, SWT.LEFT, SWT.RIGHT, SWT.RIGHT, SWT.RIGHT};

	private ArrayList<BDMemoryMapItem> m_mmItems = new ArrayList<BDMemoryMapItem>();
	

	public BDMemoryMapEditor(Shell shell, String compName, com.twoblock.blockdesigner.popup.IBDMemoryMapEditorListener ibdMemoryMapEditorListener)
	{
		m_shell = new Shell(shell, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		m_listener = ibdMemoryMapEditorListener;

		m_shell.setText("Memory Map Editor - "+compName);
		m_shell.setSize(633, 300);


		GridLayout gridLayout = new GridLayout();
		gridLayout.numColumns = 6;
		gridLayout.makeColumnsEqualWidth = true;
		m_shell.setLayout(gridLayout);



		/* Top */
		GridData gdTop = new GridData(); //oh. GD&TOP
		gdTop.horizontalAlignment = SWT.FILL;
		gdTop.horizontalSpan = 6;

		Label labelTop = new Label(m_shell, SWT.LEFT);
		labelTop.setText(" Address regions (enter start address and region size)");
		labelTop.setLayoutData(gdTop);;



		/* Edit list */
		GridData gdEdit = new GridData();
		gdEdit.horizontalAlignment = SWT.FILL;
		gdEdit.verticalAlignment = SWT.FILL;
		gdEdit.grabExcessHorizontalSpace = true;
		gdEdit.grabExcessVerticalSpace = true;
		gdEdit.horizontalSpan = 6;


		m_tableViewer = new TableViewer(m_shell, SWT.SINGLE|SWT.FULL_SELECTION|SWT.BORDER);
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
		m_table.setLayoutData(gdEdit);

		final TableEditor editor = new TableEditor(m_table);
		editor.horizontalAlignment = SWT.RIGHT;
		editor.grabHorizontal = true;
		editor.minimumWidth = 50;
		
		/* Add Cell edit listener */
		m_table.addMouseListener(new MouseListener() {

			@Override
			public void mouseUp(MouseEvent e) {}

			@Override
			public void mouseDown(MouseEvent e) {
				// TODO Auto-generated method stub

				/* Find cell row index, col index */
				Point pt = new Point(e.x, e.y);
				TableItem item = m_table.getItem(pt);
				ViewerCell vc = m_tableViewer.getCell(pt);
				
				if(vc == null || item == null) {
					Control oldEditor = editor.getEditor();
					if(oldEditor != null)
						oldEditor.dispose();
					
					return;
				}

				TableItem[] items = m_table.getItems();
				int index = 0;
				for(; index<items.length && items[index]!=item; index++);

				final int row = index;
				final int col = vc.getColumnIndex();

				System.out.println(String.format("row:%d, col:%d, text:%s", row, col, vc.getText()));

				if(!(col == 2 || col == 3)) {
					Control oldEditor = editor.getEditor();
					if(oldEditor != null)
						oldEditor.dispose();
					
					return;
				}



				/* Replace widget */
				Control oldEditor = editor.getEditor();
				if(oldEditor != null)
					oldEditor.dispose();

				Text newEditor = new Text(m_table, SWT.RIGHT);
				newEditor.setText(item.getText(col));
				newEditor.setTextLimit(11);
				newEditor.addListener(SWT.Verify, m_textAllowHexListener);
				newEditor.addListener(SWT.Modify, new Listener() {

					@Override
					public void handleEvent(Event event) {
						// TODO Auto-generated method stub
						
						Text text = (Text)editor.getEditor();
						String str = text.getText();
						BDMemoryMapItem mmItem = m_mmItems.get(row);

						if(col == COL_INDEX_START_ADDR) {
							mmItem.StartAddr = BDF.StringHexToLongDecimal(str);
						}
						else if(col == COL_INDEX_SIZE_ADDR) {
							mmItem.Size = BDF.StringHexToLongDecimal(str);
						}


						if(mmItem.Size > 0) {
							long result = mmItem.StartAddr + mmItem.Size - 1;
							if(result >= 0)
								mmItem.EndAddr = result;
						}
						else {
							mmItem.EndAddr = mmItem.StartAddr;
						}

						m_tableViewer.refresh();
					}
				});
				newEditor.addKeyListener(new KeyListener() {

					@Override
					public void keyReleased(KeyEvent e) {
						// TODO Auto-generated method stub

					}

					@Override
					public void keyPressed(KeyEvent e) {
						// TODO Auto-generated method stub

						if(e.keyCode == SWT.CR) {
							Control oldEditor = editor.getEditor();
							if(oldEditor != null)
								oldEditor.dispose();
							
							return;
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
			TableColumn col = new TableColumn(m_table, columnAligns[i]);
			col.setText(columnNames[i]);
			col.setWidth(columnWidths[i]);
			col.setResizable(false);
		}

		m_tableViewer.setLabelProvider(new MMTableLabelProvider());
		m_tableViewer.setContentProvider(new ArrayContentProvider());
		refreshList();
		


		/* Buttons */
		GridData gdBtns = new GridData();
		gdBtns.horizontalAlignment = SWT.FILL;
		gdBtns.grabExcessHorizontalSpace = true;

		Button btnClear = new Button(m_shell, SWT.PUSH);
		btnClear.setText("Clear All");
		btnClear.setLayoutData(gdBtns);
		btnClear.addSelectionListener(new SelectionListener() {

			@Override
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				for(BDMemoryMapItem item : m_mmItems) {
					item.StartAddr = 0;
					item.Size = 0;
					item.EndAddr = 0;
				}

				refreshList();
			}

			@Override
			public void widgetDefaultSelected(SelectionEvent e) {
				// TODO Auto-generated method stub

			}
		});

		Label labelDummy1 = new Label(m_shell, SWT.CENTER);
		labelDummy1.setLayoutData(gdBtns);
		Label labelDummy2 = new Label(m_shell, SWT.CENTER);
		labelDummy2.setLayoutData(gdBtns);
		Label labelDummy3 = new Label(m_shell, SWT.CENTER);
		labelDummy3.setLayoutData(gdBtns);

		Button btnCancel = new Button(m_shell, SWT.PUSH);
		btnCancel.setText("Cancel");
		btnCancel.setLayoutData(gdBtns);
		btnCancel.addSelectionListener(new SelectionListener() {
			
			@Override
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				if(m_listener != null)
					m_listener.onCancel();
				
				m_mmItems.clear();
				m_shell.dispose();
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				
			}
		});

		Button btnOk = new Button(m_shell, SWT.PUSH);
		btnOk.setText("Ok");
		btnOk.setLayoutData(gdBtns);
		btnOk.addSelectionListener(new SelectionListener() {
			
			@Override
			public void widgetSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				if(m_listener != null)
					m_listener.onOk(m_mmItems);
				
				m_mmItems.clear();
				m_shell.dispose();
			}
			
			@Override
			public void widgetDefaultSelected(SelectionEvent e) {
				// TODO Auto-generated method stub
				
			}
		});
	}

	public int addSlave(String slaveName, String connectedPortName, String startAddr, String addrSize) {
		m_mmItems.add(new BDMemoryMapItem(slaveName, connectedPortName, BDF.StringHexToLongDecimal(startAddr),
				BDF.StringHexToLongDecimal(addrSize),BDF.StringHexToLongDecimal(startAddr) + BDF.StringHexToLongDecimal(addrSize) - 1));
		refreshList();

		return m_mmItems.size();
	}

	public int addSlave(String slaveName, String connectedPortName) {
		m_mmItems.add(new BDMemoryMapItem(slaveName, connectedPortName, 0, 0, 0));
		refreshList();

		return m_mmItems.size();
	}
        
	
	private void refreshList() {
		m_tableViewer.setInput(m_mmItems.toArray());
	}


	Listener m_textAllowHexListener = new Listener() {

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
							return;
						}
					}
				}
			}
		}
	};


	private class MMTableLabelProvider extends LabelProvider implements ITableLabelProvider {

		@Override
		public Image getColumnImage(Object arg0, int arg1) {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public String getColumnText(Object obj, int index) {
			// TODO Auto-generated method stub

			BDMemoryMapItem item = (BDMemoryMapItem)obj;
			switch(index) {
			case 0:
				return item.SlaveName;

			case 1:
				return item.SlavePort;

			case 2:
				return BDF.LongDecimalToStringHex(item.StartAddr, 8);

			case 3:
				return BDF.LongDecimalToStringHex(item.Size, 8);

			case 4:
				if(item.EndAddr > MAX_ADDR_SIZE)
					return "Invalid Address Region";
				else
					return BDF.LongDecimalToStringHex(item.EndAddr, 8);

			default:
				return "unknown " + index;
			}
		}
	}
}
