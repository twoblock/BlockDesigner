package jni_struct;

public class Date {
	private String month;
	private String day;
	private int year;
	public static int temp=0;

	public Date(String m, String d, int y) {
		month = m;
		day = d;
		year = y;
		temp=y;
	}
	public Date(){
		
	}

	static {
		try {
			System.loadLibrary("libtest_struct");
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Native code library failed to load.");
		}
	}

	native public void printDate();
	private native void nativeMethod();
	
	private void callback(int a){
		System.out.println("callback complete");
		System.out.println(temp+"+1000 = "+a);
	}
	
	
	public String getMonth() {
		return month;
	}

	public String getDay() {
		return day;
	}

	public int getYear() {
		return year;
	}

	public String toString() 
	{
		return month +"/"+ day + "/" + year; 
	}

	static class TestDate {
		public static void main(String[] args) {
			// class 전달.
			Date d = new Date("Two", "Block", 2016);
			d.printDate();
			// callback Test.
			Date nm= new Date();
			nm.nativeMethod();
		}
	}
}
