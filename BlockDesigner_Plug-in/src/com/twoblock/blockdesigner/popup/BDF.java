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
}
