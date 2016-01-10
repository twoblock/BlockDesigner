package com.twoblock.blockdesigner.view;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;
import org.eclipse.ui.part.ViewPart;

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

public class View_PlatformManager extends ViewPart {
	//protected Shell shell;
	protected int index=1;
	private Text text;
	
	public void createPartControl(Composite parent) {
		
//		shell = new Shell();
//		shell.setSize(800, 400);
//		shell.setText("SWT Application");
		parent.setLayout(new FillLayout(SWT.HORIZONTAL));
		Button button[] = new Button[100];
		
		Canvas canvas = new Canvas(parent, SWT.NONE);
		//Image image = new Image(null, "src/twoblock_logo.png");
		
		
		
		
		Composite composite = new Composite(parent, SWT.NONE);
		composite.setLayout(new FillLayout(SWT.VERTICAL));
		
		
		Button btnNewButton = new Button(composite, SWT.BORDER | SWT.CHECK | SWT.CENTER);
		btnNewButton.setText("button 1");
		
		Tree tree = new Tree(composite, SWT.CHECK|SWT.BORDER|SWT.V_SCROLL|SWT.H_SCROLL);
		
		for (int iCnt0 = 1; iCnt0 < 3; iCnt0++) {
		      TreeItem treeItem0 = new TreeItem(tree, 0);
		      treeItem0.setText("Module" + iCnt0);
		      for (int iCnt1 = 1; iCnt1 <3; iCnt1++) {
		        TreeItem treeItem1 = new TreeItem(treeItem0, 0);
		        treeItem1.setText("type " + iCnt1);
		        for (int iCnt2 = 1; iCnt2 < 4; iCnt2++) {
		          TreeItem treeItem2 = new TreeItem(treeItem1, 0);
		          treeItem2.setText("model" + iCnt2);
		        }
		      }
		    }
		
		text = new Text(composite, SWT.BORDER);
		tree.addListener(SWT.Selection, new Listener() {
			@Override
			public void handleEvent(Event event) {
		        if (event.detail == SWT.CHECK) {
		          text.setText(event.item + " was checked.");
		        } else {
		          text.setText(event.item + " was selected");
		        }
		      }
		});
		
		canvas.addMouseListener(new MouseListener() {
			@Override
			public void mouseUp(MouseEvent e) {
				
			}

			@Override
			public void mouseDown(MouseEvent e) {
				// TODO Auto-generated method stub

			}

			@Override
			public void mouseDoubleClick(MouseEvent e) {
				// TODO Auto-generated method stub
				if (btnNewButton.getSelection() == true) {
					// TODO Auto-generated method stub
					button[index] = new Button(canvas, SWT.NONE);
					button[index].setText("Module" + index);
					button[index].setBounds(e.x, e.y, 80, 40);
					//button[index].setImage(image);
					index++;
					
					System.out.println(text.getText());
				}
			}
		});
		
		
	}

	public void setFocus() {
	}
}
