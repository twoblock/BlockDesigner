package com.twoblock.blockdesigner.perspective;

import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.osgi.framework.BundleContext;

/**
 * The activator class controls the plug-in life cycle
 */
public class Activator extends AbstractUIPlugin {

	// The plug-in ID
	public static final String PLUGIN_ID = "com.twoblock.blockdesigner.perspective"; //$NON-NLS-1$

	// The shared instance
	private static Activator plugin;
	
	
	// AbstractUIPlugin handle sharing images with my plugins
	
//	public class ExamplesPlugin extends AbstractUIPlugin {
//		public static final String PLUGIN_ID = "org.eclipse.faq.examples";
//		public static final String IMAGE_ID = "sample.image";
//
//		protected void initializeImageRegistry(ImageRegistry registry) {
//			Bundle bundle = Platform.getBundle(PLUGIN_ID);
//			IPath path = new Path("src/icon.png");
//			URL url = FileLocator.find(bundle, path, null);
//			ImageDescriptor desc = ImageDescriptor.createFromURL(url);
//			registry.put(IMAGE_ID, desc);
//		}
//	}
    //end.
    
    
	
	/**
	 * The constructor
	 */
	public Activator() {
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#start(org.osgi.framework.BundleContext)
	 */
	public void start(BundleContext context) throws Exception {
		super.start(context);
		plugin = this;
	}

	/*
	 * (non-Javadoc)
	 * @see org.eclipse.ui.plugin.AbstractUIPlugin#stop(org.osgi.framework.BundleContext)
	 */
	public void stop(BundleContext context) throws Exception {
		plugin = null;
		super.stop(context);
	}

	/**
	 * Returns the shared instance
	 *
	 * @return the shared instance
	 */
	public static Activator getDefault() {
		return plugin;
	}

	/**
	 * Returns an image descriptor for the image file at the given
	 * plug-in relative path
	 *
	 * @param path the path
	 * @return the image descriptor
	 */
	public static ImageDescriptor getImageDescriptor(String path) {
		return imageDescriptorFromPlugin(PLUGIN_ID, path);
	}
}
