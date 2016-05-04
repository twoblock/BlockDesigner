package com.twoblock.blockdesigner.popup;

import java.util.ArrayList;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;

public class BDDisassembleView {

	private Shell m_shell;
	private Table m_table;

	public void show() {
		m_shell.open();
	}

	private ArrayList<Long> m_addrToIndex = new ArrayList<Long>();
	private TableItem m_lastSelectedItem = null;

	public BDDisassembleView(Shell shell, String compName) {
//		m_shell = new Shell(shell, SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		m_shell = new Shell(shell.getDisplay(), SWT.CLOSE);
		
		ImageDescriptor idOpen = ImageDescriptor.createFromFile(this.getClass(), "/images/img_sbt_64.png");
		Image imgOpen = idOpen.createImage();
		m_shell.setImage(imgOpen);
		
		m_shell.setText("Disassemble View - "+compName);
		m_shell.setSize(750, 700);
		
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
		

		/* Bottom */
		GridData gdBottom = new GridData();
		gdBottom.horizontalAlignment = GridData.FILL;
		gdBottom.verticalAlignment = GridData.FILL;
		gdBottom.grabExcessVerticalSpace = true;
		gdBottom.horizontalSpan = 3;
		
		m_table = new Table(m_shell, SWT.SINGLE|SWT.FULL_SELECTION|SWT.MULTI|SWT.BORDER);
		m_table.setHeaderVisible(true);
		m_table.setLinesVisible(false);
		m_table.setLayoutData(gdBottom);

		TableColumn directCol = new TableColumn(m_table, SWT.LEFT);
		directCol.setWidth(50);
		TableColumn addrCol = new TableColumn(m_table, SWT.LEFT);
		addrCol.setText("Address");
		addrCol.setWidth(100);
		TableColumn codeCol = new TableColumn(m_table, SWT.LEFT);
		codeCol.setText("Disassemble");
		codeCol.setWidth(550);
		
		m_table.pack();
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

	public void addInstruction(long addr, String str)
	{
		String[] splited = str.split("\n");
		for(int i=0; i<splited.length; i++)
		{
			TableItem item = new TableItem(m_table, SWT.NONE);
			
			//item has an address
			if(i == 0) {
				item.setText(1, BDF.LongDecimalToStringHex(addr, 8));
				m_addrToIndex.add(addr);
			}
			else {
				m_addrToIndex.add(-1L);
			}
			
			item.setText(2, splited[i]);
		}
	}
	
	private void moveToAddress(Text text)
	{
		long addr = BDF.StringHexToLongDecimal(text.getText());
		int index = m_addrToIndex.indexOf(addr);
		
		if(index < 0) {
			BDF.printLog("Invalid address");
			return;
		}
		
		m_table.select(index);
		m_table.showItem(m_table.getItem(index));
	}
	
	public void select(long addr) {
		BDF.printLog("here::"+addr);
		
		int index = m_addrToIndex.indexOf(addr);
		if(index < 0) {
			BDF.printLog("Invalid addr: "+addr);
			return;
		}
		
		if(m_lastSelectedItem != null) {
			m_lastSelectedItem.setText(0, "");
		}
		
		m_lastSelectedItem = m_table.getItem(index);
		m_lastSelectedItem.setText(0, "▶");
		
		m_table.select(index);
		m_table.showItem(m_table.getItem(index));
		
	}
}
