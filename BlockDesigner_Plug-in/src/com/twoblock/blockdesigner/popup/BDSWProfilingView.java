package com.twoblock.blockdesigner.popup;

import org.eclipse.jface.viewers.ArrayContentProvider;
import org.eclipse.jface.viewers.ITableLabelProvider;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;

/*
 * example code
 * 
		BDSWProfilingView swpv = new BDSWProfilingView(shell, "CM0(big)");
		
		swpv.addFunctionName("Summary");
		swpv.addFunctionName("__main");
		swpv.addFunctionName("__scatterload_rt2");         
		swpv.addFunctionName("__scatterload_copy");        
		swpv.addFunctionName("NMI_Handler");       
		swpv.addFunctionName("Hardfault_Handler");      
		swpv.addFunctionName("SVC_Handler");       
		swpv.show();
		
		swpv.updateData(1, 9L, 9999L,  99.10000f,  99L,   99.90000f);
 */

public class BDSWProfilingView {

	private static Shell m_shell;
	private TableViewer m_tableViewer;
	private Table m_table;

	public void show() {
		m_shell.open();
		m_shell.setVisible(true);
	}

	private String[] columnNames = new String[] {"Function Name", "Call", "Duration(Cycles)", "Duration(%)", "Self Duration(Cycles)", "Self Duration(%)"};
	private final int columnWidth = 150;
	private BDSWProfilingItemArray m_data = new BDSWProfilingItemArray();


	public BDSWProfilingView(Shell shell, String compName) {
		m_shell = new Shell(shell.getDisplay() , SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
//		m_shell = new Shell(display , SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);

		m_shell.setText("Software Profiling View - "+compName);
		m_shell.setSize(980, 700);
		m_shell.setLayout(new FillLayout());

		if(m_data == null) {
			m_data = new BDSWProfilingItemArray();
		}

		m_tableViewer = new TableViewer(m_shell, SWT.SINGLE|SWT.FULL_SELECTION|SWT.BORDER);
		m_table = m_tableViewer.getTable();
		m_table.setHeaderVisible(true);
		m_table.setLinesVisible(true);

		for(int i=0; i<columnNames.length; i++) {
			TableColumn col = new TableColumn(m_table, SWT.CENTER);
			col.setText(columnNames[i]);
			if(i==0){
				col.setWidth(200);
			}
			else
				col.setWidth(columnWidth);
		}

		m_table.pack();
		m_tableViewer.setLabelProvider(new SWProfilingTableLabelProvider());
		m_tableViewer.setContentProvider(new ArrayContentProvider());
		
		m_shell.addListener(SWT.Close, new Listener() {
			@Override
			public void handleEvent(Event arg0) {
				// TODO Auto-generated method stub
				arg0.doit= false;
				m_shell.setVisible(false);
			}
		});
	}
	
	
	public void addFunctionName(String funcName) {
		addData(funcName, 0, 0, 0, 0, 0);
	}
	
	private void addData(String funcName, long call, long durCycle, float durPer, long selfDurCycle, float selfDurPer) {
		BDSWProfilingItem item = new BDSWProfilingItem(funcName, call, durCycle, durPer, selfDurCycle, selfDurPer);
		m_data.add(item);
		
		refreshTable();
	}
	
	public void updateData(int index, long call, long durCycle, float durPer, long selfDurCycle, float selfDurPer) {
		BDSWProfilingItem item = m_data.get(index);
		item.call = call;
		item.durCycle = durCycle;
		item.durPer = durPer;
		item.selfDurCycle = selfDurCycle;
		item.selfDurPer = selfDurPer;
		
		refreshTable();
	}

	
	
	
	public void refreshTable() {
		m_tableViewer.setInput(m_data.toArray());
	}

	private class SWProfilingTableLabelProvider extends LabelProvider implements ITableLabelProvider {

		@Override
		public Image getColumnImage(Object arg0, int index) {
			// TODO Auto-generated method stub
			return null;
		}

		@Override
		public String getColumnText(Object obj, int index) {
			// TODO Auto-generated method stub
			BDSWProfilingItem item = (BDSWProfilingItem)obj;

			switch(index)
			{
			case 0:	return item.funcName;
			case 1:	return item.call+"";
			case 2:	return item.durCycle+"";
			case 3:	return item.durPer+"%";
			case 4:	return item.selfDurCycle+"";
			case 5:	return item.selfDurPer+"%";
			default: return "unknown index "+index;
			}
		}
	}
}
