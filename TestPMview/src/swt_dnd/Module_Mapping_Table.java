package swt_dnd;

import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class Module_Mapping_Table {
	public void SetModuleMapping(String module_path, String module_name){
		try{
			String Script=null;
			try {
				JSONParser parser = new JSONParser();
				Object obj = parser.parse(new FileReader("test.MPM"));
				JSONObject past_MPM = (JSONObject) obj;
				
				Script = past_MPM.toJSONString();
						
			} catch (Exception e) {
				// TODO: handle exception
			}
			BufferedWriter out = new BufferedWriter(new FileWriter("test.MPM"));
			
			
			
			
			
			JSONObject jsonObj =new JSONObject();
			JSONArray jArr = new JSONArray();
			
			JSONObject obj = new JSONObject();
			obj.put("name", module_name);
			obj.put("path", module_path);
			
			JSONObject obj1 = new JSONObject();
			obj1.put("name", module_name);
			obj1.put("path", module_path);
			
			jArr.add(obj);
			jArr.add(obj1);
		
			jsonObj.put("MPM", jArr);
			
			
//			out.write(module_path);
//			out.newLine();
//			out.write(module_name);
//			out.newLine();
			
			Script =jsonObj.toJSONString();
			
			out.write(Script);
			
			out.close();
			
		}catch(IOException e){
			System.err.println(e);
		}
	}
}
