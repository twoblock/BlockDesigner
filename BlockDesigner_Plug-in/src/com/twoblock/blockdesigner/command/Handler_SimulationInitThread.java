package com.twoblock.blockdesigner.command;

public class Handler_SimulationInitThread {
	private static boolean InitCheck=false;
	public static synchronized boolean GetInitCheck(){
		return InitCheck;
	}
	public static synchronized void SetInitCheck(boolean p_InitCheck){
		InitCheck = p_InitCheck;
	}

	static {
		try {
			System.load(System.getProperty("user.home")+"/workspace/BlockDesigner/TestPlatform/sc_main/libBD_sim.so");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load(Handler_SimulationInitThread)");
		}
	}
	public Handler_SimulationInitThread(){}
	
	public native void StartSimulationThreads();
	
	static class SimInitThread_Func {
		public static void main(String[] args) {
		}
	}

	public static void SimInitThread_Func() {
		// TODO Auto-generated method stub
		Handler_SimulationInitThread SimInitThread = new Handler_SimulationInitThread();
		SimInitThread.StartSimulationThreads();
	}
}
