package com.twoblock.blockdesigner.perspective;

import org.eclipse.ui.IFolderLayout;
import org.eclipse.ui.IPageLayout;
import org.eclipse.ui.IPerspectiveFactory;

public class Perspective_BD_Sim implements IPerspectiveFactory {
	public final static String BD_SIM_ID = "com.twoblock.blockdesigner.view.View_SimulationEnvironment";

	@Override
	public void createInitialLayout(IPageLayout layout) {
		
		defineActions(layout);
		defineLayout(layout);
		layout.setFixed(true);
		layout.getViewLayout(BD_SIM_ID);
	}

	private void defineLayout(IPageLayout layout) {
		// "new wizards"�� �߰�. File->New
		layout.addNewWizardShortcut("org.eclipse.ui.wizards.new.folder");// folder
		layout.addNewWizardShortcut("org.eclipse.ui.wizards.new.file");// file
	}

	private void defineActions(IPageLayout layout) {
		// Editors are placed for free.
		String editorArea = layout.getEditorArea();
		IFolderLayout top = layout.createFolder("top", IPageLayout.TOP, 1, editorArea);
		top.addView(BD_SIM_ID);
	}
}