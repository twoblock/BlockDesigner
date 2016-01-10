package com.twoblock.blockdesigner.perspective;

import org.eclipse.ui.IFolderLayout;
import org.eclipse.ui.IPageLayout;
import org.eclipse.ui.IPerspectiveFactory;

public class Perspective_BlockDesigner implements IPerspectiveFactory {
	public final static String PLATFORM_MANAGER_ID = "com.twoblock.blockdesigner.view.View_PlatformManager";
	public final static String CView_ID = "org.eclipse.cdt.ui.CView";
	@Override
	public void createInitialLayout(IPageLayout layout) {
	   defineActions(layout);
	   defineLayout(layout);
	   
//	   PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage().openEditor(input, 
//			   ClientEditor.ID);	
//	   PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage().activate(editor);
	}
	 
	private void defineLayout(IPageLayout layout) {
	   // "new wizards"�� �߰�. File->New
	   layout.addNewWizardShortcut("org.eclipse.ui.wizards.new.folder");// folder
	   layout.addNewWizardShortcut("org.eclipse.ui.wizards.new.file");// file
	 
	   // "show views"�� �߰�.Window->Show View
	   layout.addShowViewShortcut(IPageLayout.ID_PROJECT_EXPLORER);
	   layout.addShowViewShortcut(IPageLayout.ID_BOOKMARKS);// bookmark
	   layout.addShowViewShortcut(IPageLayout.ID_OUTLINE);// outline
	   layout.addShowViewShortcut(IPageLayout.ID_PROP_SHEET);// Properties
	   layout.addShowViewShortcut(IPageLayout.ID_TASK_LIST);// Tasklist
	   layout.addShowViewShortcut(IPageLayout.ID_PROBLEM_VIEW);
	}
	 
	private void defineActions(IPageLayout layout) {
	   // Editors are placed for free.
	   String editorArea = layout.getEditorArea();
	 
	   // navigator�� outline�� editor ���� ���� ���̾ƿ��ȿ� �߰��Ѵ�.
	   IFolderLayout left = layout.createFolder("left", IPageLayout.LEFT,(float) 0.2, editorArea);
	   left.addView(CView_ID);
	   left.addView(IPageLayout.ID_PROJECT_EXPLORER);
	   
	   IFolderLayout bottom = layout.createFolder("bottom", IPageLayout.BOTTOM , (float) 0.7, editorArea);
	   bottom.addView(IPageLayout.ID_PROBLEM_VIEW);
	   bottom.addView(IPageLayout.ID_PROP_SHEET);
	   
	   IFolderLayout right = layout.createFolder("right", IPageLayout.RIGHT, (float) 0.8, editorArea);
	   right.addView(IPageLayout.ID_OUTLINE);
	   right.addView(IPageLayout.ID_TASK_LIST);
	   
	   IFolderLayout top = layout.createFolder("top", IPageLayout.TOP, (float) 0 , editorArea);
	   top.addView(PLATFORM_MANAGER_ID);
//	   layout.addView("", IPageLayout.TOP,
//				0, IPageLayout.ID_EDITOR_AREA);
	   
	   
 
	}
	 
//	public interface IPerspectivePlugin {
//	   /**
//	    * Plugin id.
//	    */
//	   public final static String PLUGIN_ID = "com.twoblock.blockdesigner.perspective.views.PlatformManagerView";
//	 
//	   /**
//	    * Test perspective id.
//	    */
//	   public final static String TEST_PERSPECTIVE_ID = PLUGIN_ID + ".Test";
//	}
}
