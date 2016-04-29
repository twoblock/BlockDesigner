package com.twoblock.blockdesigner.datastore;

public class Register {

	public Register clone(){
		Register Reg = new Register();

		Reg.reg_name = this.reg_name;
		Reg.data_type = this.data_type;
		Reg.bits_wide = this.bits_wide;

		return Reg;	
	}

	public String reg_name;
	public String data_type;
	public String bits_wide;
}
