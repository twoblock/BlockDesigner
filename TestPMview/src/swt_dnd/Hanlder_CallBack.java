package swt_dnd;


/* --- use for simulation interface Command --- */
public class Hanlder_CallBack {
	static {
		try {
			System.load("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/libBD_sim.so");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load(callback)");
		}
	}
	
	public String message;
	
	public Hanlder_CallBack() {}
	
	
	/* --- Define native Listener --- */
	private native void JNIInitializer();
	private native void ModuleInfoListener();
	
	
	/* --- Define Callback method --- */
	private void ModuleInfoCallBack() {
		//System.out.println("receive ModuleInfo");
	}
	
	static class CallBack_Func {
		public static void main(String[] args) {
			CallBack_Func();
		}
	}
	
	public static void CallBack_Func() {
		// TODO Auto-generated method stub
		Hanlder_CallBack callback = new Hanlder_CallBack();
		callback.JNIInitializer();
	}
}
