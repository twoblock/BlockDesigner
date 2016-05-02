package com.twoblock.blockdesigner.datastore;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class Set_BDPMD {
	JSONObject obj_root;
	JSONObject obj_BDPMD;
	
	JSONArray arr_Channel_Info;
	JSONObject obj_Channel_Item_HCLK;
	JSONObject obj_Channel_Item_HRESETn;
	JSONObject obj_Channel_Item;
	JSONArray arr_Channel_Connection_Info_HCLK;
	JSONArray arr_Channel_Connection_Info_HRESETn;
	JSONArray arr_Channel_Connection_Info;
	
	JSONObject obj_Channel_Connection_Info;
	
	JSONArray arr_Module_Data;
	JSONObject obj_Module_Item;
	JSONObject obj_Module_Info;

	JSONArray arr_Port;
	JSONObject obj_Port;

	JSONArray arr_Register;
	JSONObject obj_Register;

	JSONArray arr_Parameter;
	JSONObject obj_Parameter;

	JSONArray arr_MemoryMap;
	JSONObject obj_MemoryMap;

	@SuppressWarnings({ "unchecked", "unused" })
	public Set_BDPMD(ModuleInfo usedModuleDataList) {
		// TODO Auto-generated constructor stub
		obj_root = new JSONObject();
		obj_BDPMD = new JSONObject();
		arr_Module_Data = new JSONArray();
		
		arr_Channel_Info = new JSONArray();
		obj_Channel_Item = new JSONObject();
		obj_Channel_Item_HCLK = new JSONObject();
		arr_Channel_Connection_Info_HCLK = new JSONArray();
		obj_Channel_Item_HRESETn = new JSONObject();
		arr_Channel_Connection_Info_HRESETn = new JSONArray();
		
		for (int ModuleDataIndex = 0; ModuleDataIndex < usedModuleDataList.mList.size(); ModuleDataIndex++) {
			obj_Module_Item = new JSONObject();
			obj_Module_Info = new JSONObject();
			
			obj_Module_Item.put("module_name", usedModuleDataList.mList.get(ModuleDataIndex).module_name);
			obj_Module_Item.put("module_location", usedModuleDataList.mList.get(ModuleDataIndex).module_location);
			obj_Module_Item.put("module_type", usedModuleDataList.mList.get(ModuleDataIndex).module_type);

			
			obj_Channel_Connection_Info = new JSONObject();
			if(ModuleDataIndex>0){
				obj_Channel_Connection_Info.put("module_name", usedModuleDataList.mList.get(ModuleDataIndex).module_name);
				obj_Channel_Connection_Info.put("port_name","HCLK");
				arr_Channel_Connection_Info_HCLK.add(obj_Channel_Connection_Info);
			}
			else{
				obj_Channel_Item_HCLK.put("channel_type", "sc_clock");
				obj_Channel_Item_HCLK.put("data_type", "bool");
				obj_Channel_Item_HCLK.put("connection_num", usedModuleDataList.mList.size()-1);
				obj_Channel_Item_HCLK.put("name", usedModuleDataList.mList.get(0).module_name+"$HCLK");
				
			}
			
			obj_Channel_Connection_Info = new JSONObject();
			if(ModuleDataIndex>0){
				obj_Channel_Connection_Info.put("module_name", usedModuleDataList.mList.get(ModuleDataIndex).module_name);
				obj_Channel_Connection_Info.put("port_name","HRESETn");
				arr_Channel_Connection_Info_HRESETn.add(obj_Channel_Connection_Info);
			}
			else{
				obj_Channel_Item_HRESETn.put("channel_type", "sc_signal");
				obj_Channel_Item_HRESETn.put("data_type", "bool");
				obj_Channel_Item_HRESETn.put("connection_num", usedModuleDataList.mList.size()-1);
				obj_Channel_Item_HRESETn.put("name", usedModuleDataList.mList.get(0).module_name+"$HRESETn");
			}
			
			
			
			/* --- set real connected port(START)--- */
			
			for (int PortIndex = 2; PortIndex < usedModuleDataList.mList.get(ModuleDataIndex).Port_List
					.size(); PortIndex++) {
//				if(!usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).cmb_dPort.getText().equals("")){
						Boolean deportCheck = false;
						String dModule=null;
						String dPort = null;
						String sModule = usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).Parent.module_instance_name;
						String sPort = usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).port_name;
						if(usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).Dest_Port != null){
							deportCheck = true;
							dModule = usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).Dest_Port.Parent.module_instance_name;
							dPort = usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).Dest_Port.port_name;
						}
						String data_type = usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).data_type;
						String sc_type = usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(PortIndex).sc_type;
						
						Boolean isUsed = false;
						for (int finder = 0; finder < arr_Channel_Info.size(); finder++) {
							isUsed = false;
							JSONObject jobj = (JSONObject) arr_Channel_Info.get(finder);
							JSONArray jarr = (JSONArray) jobj.get("connection_info");
							
//							JSONObject obj_cnecModule = (JSONObject) jarr.get(0);
//							String cnecModule = (String) obj_cnecModule.get("module_name");
//							String cnecPort = (String) obj_cnecModule.get("port_name");
							
							// This connection already write.
//							if ((cnecModule.equals(sModule)) && (cnecPort.equals(sPort))) {
//								isUsed = true;
//								break;
//							}
						}
						if(isUsed == false){
							obj_Channel_Connection_Info = new JSONObject();
							obj_Channel_Item = new JSONObject();
							arr_Channel_Connection_Info = new JSONArray();
							
							if(deportCheck==true){
								obj_Channel_Connection_Info.put("module_name", dModule);
								obj_Channel_Connection_Info.put("port_name", dPort);
							}
							arr_Channel_Connection_Info.add(obj_Channel_Connection_Info);

							obj_Channel_Item.put("channel_type", sc_type);
							if(data_type.equals("MS") | data_type.equals("MM")){
								obj_Channel_Item.put("data_type", "Master" );
							}
							else if (data_type.equals("SS") | data_type.equals("SM")) {
								obj_Channel_Item.put("data_type", "Slave" );
							}
							else{
								obj_Channel_Item.put("data_type", data_type );
							}
							
							obj_Channel_Item.put("name", sModule + "$"+sPort);
							
							if(deportCheck==true){
								obj_Channel_Item.put("connection_num", "1");
								obj_Channel_Item.put("connection_info", arr_Channel_Connection_Info);
							}
							else{
								obj_Channel_Item.put("connection_num", "0");
								obj_Channel_Item.put("connection_info", null);
							}
							arr_Channel_Info.add(obj_Channel_Item);
						}
//				}
			}
			
			/* --- set real connected port(END)--- */
			
			
			/* ============================  Module Data setting Start  ============================ */
			obj_Module_Info.put("instance_name", usedModuleDataList.mList.get(ModuleDataIndex).module_instance_name);
			
			// add Port
			arr_Port = new JSONArray();
			for (int ModulePortIndex = 0; ModulePortIndex < usedModuleDataList.mList.get(ModuleDataIndex).Port_List
					.size(); ModulePortIndex++) {
				obj_Port = new JSONObject();
				
				obj_Port.put("port",
						usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).port_name);
				obj_Port.put("sc_type",
						usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).sc_type);
				obj_Port.put("data_type",
						usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).data_type);
				arr_Port.add(obj_Port);
			}
			obj_Module_Info.put("port", arr_Port);

			// add Register
			arr_Register = new JSONArray();
			for (int ModulePortIndex = 0; ModulePortIndex < usedModuleDataList.mList.get(ModuleDataIndex).Register_List
					.size(); ModulePortIndex++) {
				obj_Register = new JSONObject();
				
				obj_Register.put("reg_name",
						usedModuleDataList.mList.get(ModuleDataIndex).Register_List.get(ModulePortIndex).reg_name);
				obj_Register.put("data_type",
						usedModuleDataList.mList.get(ModuleDataIndex).Register_List.get(ModulePortIndex).data_type);
				obj_Register.put("bits_wide",
						usedModuleDataList.mList.get(ModuleDataIndex).Register_List.get(ModulePortIndex).bits_wide);
				arr_Register.add(obj_Register);
			}
			obj_Module_Info.put("register", arr_Register);

			// add Parameter
			arr_Parameter = new JSONArray();
			for (int ModulePortIndex = 0; ModulePortIndex < usedModuleDataList.mList.get(ModuleDataIndex).Parameter_List
					.size(); ModulePortIndex++) {
				obj_Parameter = new JSONObject();
				
				obj_Parameter.put("par_name",
						usedModuleDataList.mList.get(ModuleDataIndex).Parameter_List.get(ModulePortIndex).par_name);
				obj_Parameter.put("data_type",
						usedModuleDataList.mList.get(ModuleDataIndex).Parameter_List.get(ModulePortIndex).data_type);
				obj_Parameter.put("default_value", usedModuleDataList.mList.get(ModuleDataIndex).Parameter_List
						.get(ModulePortIndex).default_value);
				obj_Parameter.put("bits_wide",
						usedModuleDataList.mList.get(ModuleDataIndex).Parameter_List.get(ModulePortIndex).bits_wide);
				arr_Parameter.add(obj_Parameter);
			}
			obj_Module_Info.put("parameter", arr_Parameter);

//			 add MemoryMap
			arr_MemoryMap = new JSONArray();
			int Memory_Map_Index=0;
			for (int ModulePortIndex = 0; ModulePortIndex < usedModuleDataList.mList.get(ModuleDataIndex).Port_List
					.size(); ModulePortIndex++) {
				if(usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).addrSize != "0"){
					obj_MemoryMap = new JSONObject();
					obj_MemoryMap.put("slave_module",
							usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).Dest_Port.Parent.module_instance_name);
					obj_MemoryMap.put("slave_module_port",
							usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).Dest_Port.port_name);
					obj_MemoryMap.put("start_address",
							usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).startAddr);
					obj_MemoryMap.put("size",
							usedModuleDataList.mList.get(ModuleDataIndex).Port_List.get(ModulePortIndex).addrSize);
					arr_MemoryMap.add(Memory_Map_Index,obj_MemoryMap);
					Memory_Map_Index++;
				}
			}
			obj_Module_Info.put("memory_map", arr_MemoryMap);
			
			
			obj_Module_Item.put("module_info", obj_Module_Info);
			arr_Module_Data.add(obj_Module_Item);
			/* ============================  Module Data setting End  ============================ */
		}
		obj_Channel_Item_HCLK.put("connection_info", arr_Channel_Connection_Info_HCLK);
		obj_Channel_Item_HRESETn.put("connection_info", arr_Channel_Connection_Info_HRESETn);
		arr_Channel_Info.add(0,obj_Channel_Item_HCLK);
		arr_Channel_Info.add(1,obj_Channel_Item_HRESETn);
		
		
		obj_BDPMD.put("Channel_Info", arr_Channel_Info);
		obj_BDPMD.put("Module_Data", arr_Module_Data);
		obj_root.put("BDPMD", obj_BDPMD);
	}
	public String Get_BDPMD(){
		
		return obj_root.toJSONString();
	}
}
