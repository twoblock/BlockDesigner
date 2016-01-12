package com.twoblock.blockdesigner.command;

/* --- use for simulation interface Command --- */
public class Handler_Command {
	private int Operation;
	private int Command;
	private String Argu1;
	private String Argu2;
	private String Argu3;
	private String Argu4;
	private String Argu5;
	
	public Handler_Command
	(int oper, int cmd, String argu1, String argu2, String argu3, String argu4, String argu5)
	{
		Operation = oper;
		Command = cmd;
		Argu1 = argu1;
		Argu2 = argu2;
		Argu3 = argu3;
		Argu4 = argu4;
		Argu5 = argu5;
	}

	public Handler_Command() {}

	static {
		try {
			System.load("/home/lucas/workspace/BlockDesigner/BlockDesigner_Plug-in/libBD_sim.so");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load(command)");
		}
	}

	public native void PushCommand();

	static class Command_Func {
		public static void main(String[] args) {
		}
	}

	public static void Command_Func(int oper, int cmd, String argu1,String argu2,String argu3,String argu4,String argu5) {
		// TODO Auto-generated method stub
		Handler_Command pushcomm = new Handler_Command(oper, cmd, argu1, argu2, argu3, argu4, argu5);
		pushcomm.PushCommand();
	}
}
