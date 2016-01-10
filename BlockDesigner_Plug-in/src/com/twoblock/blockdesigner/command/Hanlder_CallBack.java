package com.twoblock.blockdesigner.command;

import java.util.Map;

/* --- use for simulation interface Command --- */
public class Hanlder_CallBack {
	static {
		try {
			System.load("/home/lucas/workspace/BlockDesigner/libBD_sim.so");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load");
		}
	}
	public enum ErrorCode{
		aaa(1,"a1"),
		bbb(2,"b1");
		
		private int code;
		private String message;
		
		private static Map<integer, Status> codeToStatusMapping;
		
		private ErrorCode(int code, String message){
			this.code =code;
			this.message = message;
		}
	}
	
	public long cycle;
	public int status;
	public int message;
	
	public Hanlder_CallBack() {}
	
	
	/* --- Define native Listener --- */
	private native void CycleListener();
	private native void StatusListener();
	private native void OutputListener();
	private native void ModuleInfoListener();
	private native void ErrorListener();
	
	
	/* --- Define Callback method --- */
	private void CycleCallBack(long cycle) {
		System.out.println("cycle = "+cycle);
	}
	private void StatusCallBack(int status) {
		System.out.println("Status = "+status);
	}
	private void OutputCallBack() {
		System.out.println("receive Output");
	}
	private void ModuleInfoCallBack() {
		System.out.println("receive ModuleInfo");
	}
	private void ErrorCallBack(int message) {
		System.out.println("ErroCode = "+message);
		System.err.println("ErroMessage = "+"ss");
	}
	
	
	static class CallBack_Func {
		public static void main(String[] args) {
			System.out.println("errorcode");
			CallBack_Func();
		}
	}
	
	public static void CallBack_Func() {
		// TODO Auto-generated method stub
		Hanlder_CallBack callback = new Hanlder_CallBack();
		callback.CycleListener();
		callback.StatusListener();
		callback.OutputListener();
		callback.ModuleInfoListener();
		callback.ErrorListener();
	}
}
