package com.twoblock.blockdesigner.datastore;

import java.util.ArrayList;

public class Module {
	
	// Deep copy
	public Module(Module module){
		this.module_instance_name = module.module_instance_name;
		this.module_name = module.module_name;
		this.module_location = module.module_location;
		this.module_type = module.module_type;
		
		for(Port p : module.Port_List){
			this.Port_List.add(p.clone(this));
		}	
		for(Register p : module.Register_List){
			this.Register_List.add(p.clone());
		}
		for(Parameter p : module.Parameter_List){
			this.Parameter_List.add(p.clone());
		}
	};

	public Module(){};
	
	public String module_instance_name;
	public String module_name;
	public String module_location = null;
	public String module_type;

	public ArrayList<Port> Port_List = new ArrayList<Port>();
	public ArrayList<Register> Register_List = new ArrayList<Register>();
	public ArrayList<Parameter> Parameter_List = new ArrayList<Parameter>();
}
 
 
 