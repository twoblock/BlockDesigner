package com.twoblock.blockdesigner.datastore;

public class Parameter {
	
	public Parameter clone(){
		Parameter Par = new Parameter();
		
		Par.par_name = this.par_name;
		Par.data_type = this.data_type;
		Par.bits_wide = this.bits_wide;
		Par.default_value = this.default_value;
		
		return Par;	
	}

	public String par_name;
	public String data_type;
	public String bits_wide;
	public String default_value;
 
}
