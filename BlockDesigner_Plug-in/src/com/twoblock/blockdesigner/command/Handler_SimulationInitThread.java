package com.twoblock.blockdesigner.command;

public class Handler_SimulationInitThread {
	static {
		try {
			System.load("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/libBD_sim.so");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load(start)");
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
