package com.twoblock.blockdesigner.popup;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;


/*
 * Example code
 * Ryan, TwoBlock
 * 
 		BDSWCallStackView csv = new BDSWCallStackView(shell, "CM0(big)", null);
		for(int i=0; i<30; i++) {
			csv.addFunctionName("func");
		}
		csv.show();
		
		csv.addCallData(3, 3000);
 */


public class BDSWCallStackView {

	private final int MAX_COLUMN_SIZE = 100;
	private final int COLUMN_WIDTH = 150;

	private Shell m_shell;
	private Display m_display;
	private Table m_dataTable;
	
	private int m_lastFuncIndex = -1;

	public void show() {
		m_shell.open();
	}



	public BDSWCallStackView(Shell shell, String compName, BDSWProfilingItemArray data) {
//		m_shell = new Shell(shell, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		m_shell = new Shell(shell.getDisplay(), SWT.CLOSE);
		m_display = m_shell.getDisplay();

		ImageDescriptor idOpen = ImageDescriptor.createFromFile(this.getClass(), "/images/img_csv_64.png");
		Image imgOpen = idOpen.createImage();
		m_shell.setImage(imgOpen);
		
		m_shell.setText("Software CallStack View - "+compName);
		m_shell.setSize(1000, 600);
		m_shell.setLayout(new FillLayout());

		m_dataTable = new Table(m_shell, SWT.FULL_SELECTION|SWT.BORDER);
		m_dataTable.setHeaderVisible(false);
		m_dataTable.setLinesVisible(false);
		m_dataTable.addListener(SWT.Selection, new Listener() {

			@Override
			public void handleEvent(Event event) {
				// TODO Auto-generated method stub
				m_dataTable.deselectAll(); //prevent to click row
			}
		});

		TableColumn col = new TableColumn(m_dataTable, SWT.CENTER);
		col.setWidth(200);
	}

	public void addFunctionName(String str) {
		TableItem item = new TableItem(m_dataTable, SWT.NONE);
		item.setText(str);
	}

	public void addCallData(int funcIndex, long cycles) {
		
		int colCount = m_dataTable.getColumnCount(); 
		if(colCount > 1) {
//			System.out.println("add");
			TableItem tableItem = m_dataTable.getItem(m_lastFuncIndex);
			tableItem.setBackground(colCount-1, new Color(m_display, 192, 192, 192));
		}
		
		if(colCount > MAX_COLUMN_SIZE) {
			removeColumnForward(1);
		}

		/* Add line column */
		if(m_lastFuncIndex != -1) {
			TableColumn lineCol = new TableColumn(m_dataTable, SWT.CENTER);
			lineCol.setWidth(5);
			
			int colIndex = m_dataTable.indexOf(lineCol);
			int higher = Math.max(funcIndex, m_lastFuncIndex);
			int lower = Math.min(funcIndex, m_lastFuncIndex);
			
			for(int i=lower; i<=higher; i++) {
				TableItem item = m_dataTable.getItem(i);
				item.setBackground(colIndex, new Color(m_display, 192, 192, 192));
			}
		}

		/* Add Data column */
		TableColumn dataCol = new TableColumn(m_dataTable, SWT.CENTER);
		dataCol.setWidth(COLUMN_WIDTH);
		
		int curColIndex = m_dataTable.indexOf(dataCol);
		TableItem tableItem = m_dataTable.getItem(funcIndex);
		
		tableItem.setText(curColIndex, cycles+" cycles");
		tableItem.setBackground(curColIndex, new Color(m_display, 255, 0, 0));
		
		
		m_lastFuncIndex = funcIndex;
		m_dataTable.showColumn(dataCol);
	}
	
	private void removeColumnForward(int size) {
		for(int i=0; i<size; i++) {
			m_dataTable.getColumn(1).dispose();
			m_dataTable.getColumn(1).dispose();
		}
	}
}
