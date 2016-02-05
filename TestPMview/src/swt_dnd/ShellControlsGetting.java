package swt_dnd;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

public class ShellControlsGetting {
  public static void main(String[] args) {
    Display display = new Display();
    final Shell shell = new Shell(display);
    shell.setLayout(new FillLayout());
    
    for (int i = 0; i < 20; i++) {
      Button button = new Button(shell, SWT.TOGGLE);
      button.setText("B" + i);
      button.addMouseListener(new MouseListener() {
  		
  		@Override
  		public void mouseUp(MouseEvent arg0) {
  			// TODO Auto-generated method stub
  			arg0.getSource();
  			System.err.println(getControl(shell, arg0.x, arg0.y));
  		}
  		
  		@Override
  		public void mouseDown(MouseEvent arg0) {
  			// TODO Auto-generated method stub
  			
  		}
  		
  		@Override
  		public void mouseDoubleClick(MouseEvent arg0) {
  			// TODO Auto-generated method stub
  			
  		}
  	});
      
    }
    Control[] children = shell.getChildren();
    for (int i = 0; i < children.length; i++) {
      Control child = children[i];
    }

    
    shell.pack();
    shell.open();
    while (!shell.isDisposed()) {
      if (!display.readAndDispatch())
        display.sleep();
    }
    display.dispose();
  }
  
  public static Control getControl(Composite shell, int x, int y)
	{
	  System.err.println("on");
	  Control control = null;
	  Control[] children = shell.getChildren();
	  if (children.length == 0)
	     control = shell;
	  else
	    for (Control tmp : children) {
	       // The check below will not work because x, y and the control's bounds could be
	       // relative to different parents... Better to convert all coordinates to display
	       // by using Control.toDisplay() and then compare below
	       if (tmp.getBounds().contains(x, y)) 
	       {
	         if (control instanceof Composite)
	             control = getControl((Composite) tmp, x, y);
	         else
	             control =  tmp;
	         break;
	       }

	    }
	  
	  return control;
	}
  
  
}