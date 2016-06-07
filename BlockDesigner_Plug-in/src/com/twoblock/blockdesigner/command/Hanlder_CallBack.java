package com.twoblock.blockdesigner.command;

import com.twoblock.blockdesigner.view.View_PlatformManager;
import com.twoblock.blockdesigner.view.View_SimulationEnvironment;

/* --- use for simulation interface Command --- */
public class Hanlder_CallBack {
	static {
		try {
			System.load(System.getProperty("user.home")+"/workspace/BlockDesigner/TestPlatform/sc_main/libBD_sim.so");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load(Hanlder_CallBack)");
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
	private native void InitialMemoryViewListener();
	private native void SourceCodeListener();
	private native void PCListener();
	private native void SymbolTableListener();
	private native void ProfilingTableListener();
	private native void FunctionFlowListener();
	private native void ModuleInfoListener();
	private native void ErrorListener();
	
	
	/* --- Define Callback method --- */
	private void CycleCallBack(long cycle) {
		VSE.Cycle_Setter(cycle);
	}
	private void StatusCallBack(int state) {
		if(state==3){
			View_SimulationEnvironment.Btn_ControlChecker=true;
		}
		VSE.Btn_Control(state);
	}
	private void OutputCallBack() {
		System.out.println("receive Output");
	}
	private void ResultCallBack(String sim_result){
		VSE.SIM_Result(sim_result);
	}
	
	//InitialMemory 
	private void InitialMemoryViewCallBack(String init_memoryjson){
		View_SimulationEnvironment.InitMemoryView = init_memoryjson;
	}

	//Memory View
	private void MemoryViewCallBack(String memoryjson){
		View_SimulationEnvironment.MemoryViewSet = memoryjson;
	}
	
	//assembly view
	private void SourceCodeCallBack(String jcode){ 
		View_SimulationEnvironment.SourceCode=jcode;
	}
	private void PCCallBack(String pc){
		View_SimulationEnvironment.PCCode=pc;
	}
	
	// function call & profiling table init 
	private void SymbolTableCallBack(String symboltable){
		View_SimulationEnvironment.SymbolTable=symboltable;
	}
	//get
	private void ProfilingTableCallBack(String pftable){
		View_SimulationEnvironment.ProfilingTable=pftable;
	}
	private void FunctionFlowCallBack(String functionflow){
		View_SimulationEnvironment.FunctionFlowGragh=functionflow;
	}
	
	private void ModuleInfoCallBack(String pmml) {
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
	
	public static void CallBack_RM() {
		// TODO Auto-generated method stub
		Hanlder_CallBack callback = new Hanlder_CallBack();
		callback.StatusListener();
	}
}
