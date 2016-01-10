package kr.co.twoblocktech.block.designer.module.wizard;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;

public class test_module {
	protected static int index = 1;
	private static Text text;

	public static void main(String[] args) {
		Display display = new Display();
		Shell shell = new Shell(display);
		shell.setSize(800, 400);
		shell.setText("SWT Application");
		shell.setLayout(new FillLayout(SWT.HORIZONTAL));
		Button button[] = new Button[100];

		Canvas canvas = new Canvas(shell, SWT.NONE);
		// Image image = new Image(null, "src/twoblock_logo.png");

		final Composite composite = new Composite(shell, SWT.NONE);
		composite.setLayout(new FillLayout(SWT.VERTICAL));

		Button btnNewButton = new Button(composite, SWT.BORDER | SWT.CHECK | SWT.CENTER);
		btnNewButton.setText("State = Can't Make Module");

		btnNewButton.addListener(SWT.Selection, new Listener() {
			@Override
			public void handleEvent(Event arg0) {
				// TODO Auto-generated method stub
				if (btnNewButton.getSelection() == false)
					btnNewButton.setText("State = Can't Make Module");
				else if (btnNewButton.getSelection() == true)
					btnNewButton.setText("State = Make Module");
			}
		});

		Tree tree = new Tree(composite, SWT.CHECK | SWT.BORDER | SWT.V_SCROLL | SWT.H_SCROLL);

		for (int iCnt0 = 1; iCnt0 < 3; iCnt0++) {
			TreeItem treeItem0 = new TreeItem(tree, 0);
			treeItem0.setText("Module" + iCnt0);
			for (int iCnt1 = 1; iCnt1 < 3; iCnt1++) {
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
					button[index].setBounds(e.x - 40, e.y - 20, 80, 40);
					// button[index].setImage(image);
					index++;

					System.out.println(text.getText());
				}
			}
		});
		shell.open();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}
		display.dispose();
	}
}