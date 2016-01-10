package com.twoblock.blockdesigner.command;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.handlers.HandlerUtil;

public class Handler_AboutTwoblock extends AbstractHandler {
	public static final String ID = "rcp.eclipse";
    public static final String MY_IMAGE_ID = "image.myimage";

	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		Display display = HandlerUtil.getActiveShellChecked(event).getDisplay();
		Shell shell = new Shell(display);
		//shell.setSize(380, 420);
		shell.setSize(400, 240);
		shell.setText("About TwoBlock...");
		shell.setLayout(new FillLayout(SWT.VERTICAL));

//		ImageDescriptor id = ImageDescriptor.createFromFile(this.getClass(), "/images/twoblock_solution.png");
//		Image image = id.createImage();
//		
//		Canvas canvas = new Canvas(shell, SWT.NONE);
//		canvas.setSize(shell.getBounds().width, shell.getBounds().height/2);
//		canvas.addPaintListener(new PaintListener() {
//			public void paintControl(PaintEvent e) {
//				GC gc = e.gc;
//				gc.drawImage(image, 0, 0, image.getBounds().width, image.getBounds().height, 
//						0, 0, canvas.getBounds().width, canvas.getBounds().height);
//			}
//		});
//		Image image = new Image(null, "src/twoblock_solution.png");
		
		shell.setLayout(new GridLayout(2, false));
		new Label(shell, SWT.NONE);

		Composite composite = new Composite(shell, SWT.NONE);
		FillLayout fl_composite = new FillLayout(SWT.VERTICAL);
		composite.setLayout(fl_composite);
		
		Label lblNewLabel = new Label(composite, SWT.CENTER);
		lblNewLabel.setText("\r\nSolution for system architecture\r\n2015");
		
		Label lblNewLabel_1 = new Label(composite, SWT.NONE);
		lblNewLabel_1.setText("Application : Block Designer\r\nSoftware version : 1.0\r\nDevelop Website : http://twoblock.co\r\nSupport / Feedback : twoblock@twoblock.co\r\n\r\n(C) Copy Right TwobBlock Corp. 2015, 2016 All right reserved. ");

	    shell.open();
		return null;
	}
	
	
	
	
	
//	public static void loadImages(ImageRegistry registry) {
//		  registry.put("icon", ImageDescriptor.createFromFile(Handler_AboutTwoblock.class, "src/twoblock_solution.gif"));
//		}
	
	

}