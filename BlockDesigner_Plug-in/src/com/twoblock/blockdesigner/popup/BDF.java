package com.twoblock.blockdesigner.popup;

public class BDF {
	public static long StringHexToLongDecimal(String str) {
		if(str.contains("0x"))
			str = str.replace("0x", "");

		str = str.replace("X", "");

		if(str.length() == 0)
			return 0;
		else
			return Long.parseLong(str, 16);
	}

	public static String LongDecimalToStringHex(long l, int width) {
		String str = Long.toHexString(l).toUpperCase();
		while(str.length() < width) {
			str = "0"+str;
		}
		return "0x"+str;
	}
	
	public static void printLog(String message)
	{
		StackTraceElement stack = new Throwable().getStackTrace()[1];
		StringBuffer buffer = new StringBuffer();
		
		//class
		String className = stack.getClassName();
		int indexOfPoint;
		if((indexOfPoint = className.lastIndexOf(".")) != -1)
		{
			className = className.substring(indexOfPoint + 1);
		}
		buffer.append(className);
		buffer.append(".");

		//method name
		buffer.append(stack.getMethodName());
		buffer.append("()");
		
		//line number
		buffer.append(":");
		buffer.append(stack.getLineNumber());

//		System.out.println("["+buffer.toString()+"]"+message);
	}
}
