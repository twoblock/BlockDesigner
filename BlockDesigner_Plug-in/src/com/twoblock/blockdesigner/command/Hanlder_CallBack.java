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
	View_SimulationEnvironment VSE = new View_SimulationEnvironment();
	public Hanlder_CallBack() {}
	
	
	/* --- Define native Listener --- */
	private native void CycleListener();
	private native void StatusListener();
	private native void OutputListener();
	private native void ResultListener();
	private native void MemoryViewListener();
	private native void ModuleInfoListener();
	private native void ErrorListener();
	
	
	/* --- Define Callback method --- */
	private void CycleCallBack(long cycle) {
		VSE.Cycle_Setter(cycle);
	}
	private void StatusCallBack(int state) {
		System.out.println("STATE = "+state);
		VSE.Btn_Control(state);
	}
	private void OutputCallBack() {
		System.out.println("receive Output");
	}
	private void ResultCallBack(String sim_result){
		System.err.println(sim_result);
		VSE.SIM_Result(sim_result);
	}
	private void MemoryViewCallBack(String memoryjson){
		System.err.println(memoryjson);
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
		callback.OutputListener();
	}
}
