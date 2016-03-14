package com.twoblock.blockdesigner.command;

import com.twoblock.blockdesigner.view.View_PlatformManager;
import com.twoblock.blockdesigner.view.View_SimulationEnvironment;

/* --- use for simulation interface Command --- */
public class Hanlder_CallBack {
	static {
		try {
			System.load(System.getProperty("user.home")+"/workspace/BlockDesigner/TestPlatform/sc_main/libBD_sim.so");		
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load(callback)");
		}
	}

	
	public long cycle;
	public int status;
	public String message;
	public int errorcode;
	
	public Hanlder_CallBack() {}
	
	
	/* --- Define native Listener --- */
	private native void CycleListener();
	private native void StatusListener();
	private native void OutputListener();
	private native void ModuleInfoListener();
	private native void ErrorListener();
	
	
	/* --- Define Callback method --- */
	private void CycleCallBack(long cycle) {
//		System.out.println("cycle = "+cycle);
//		View_SimulationEnvironment.lblCyclesCnt.setText(""+cycle);
	}
	private void StatusCallBack(int status) {
		//System.out.println("Status = "+status);
	}
	private void OutputCallBack() {
		System.out.println("receive Output");
	}
	private void ModuleInfoCallBack(String pmml) {
		System.err.println(pmml);
		View_PlatformManager vs = new View_PlatformManager();
		vs.viewsetting(pmml);
	}
	private void ErrorCallBack(int errorcode) {
		switch (errorcode) {
		case 1:	message = "AAA Error"; break;
		case 2:	message = "BBB Error"; break;
		case 3:	message = "CCC Error"; break;
		case 4:	message = "DDD Error"; break;
		}
	}
	
	static class CallBack_Func {
		public static void main(String[] args) {
			CallBack_Func();
		}
	}
	
	public static void CallBack_Func() {
		// TODO Auto-generated method stub
		Hanlder_CallBack callback = new Hanlder_CallBack();
//		callback.CycleListener();
//		callback.StatusListener();
		callback.OutputListener();
//		callback.ModuleInfoListener();
//		callback.ErrorListener();
	}
}
