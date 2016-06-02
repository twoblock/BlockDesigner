/*
 * main.cpp
 *
 *  Created on: 2015. 11. 23.
 *      Author: ChoiDM
 */

#include "BlockDesigner.h"
#include <stdio.h>

#define INPUT_STR "{\"ModuleWizard\":{\"module_type\":\"bus\",\"port\":[{\"port_name\":\"ahb_mm\",\"sc_type\":\"BD_AHBPort_MM\",\"data_type\":\"Master\"},{\"port_name\":\"ahb_ms\",\"sc_type\":\"BD_AHBPort_MS\",\"data_type\":\"Master\"},{\"port_name\":\"ahb_sm\",\"sc_type\":\"BD_AHBPort_SM\",\"data_type\":\"Slave\"},{\"port_name\":\"ahb_ss\",\"sc_type\":\"BD_AHBPort_SS\",\"data_type\":\"Slave\"},{\"port_name\":\"ahblite_mm\",\"sc_type\":\"BD_AHBLitePort_MM\",\"data_type\":\"Master\"},{\"port_name\":\"ahblite_ms\",\"sc_type\":\"BD_AHBLitePort_MS\",\"data_type\":\"Master\"},{\"port_name\":\"ahblite_sm\",\"sc_type\":\"BD_AHBLitePort_SM\",\"data_type\":\"Slave\"},{\"port_name\":\"ahblite_ss\",\"sc_type\":\"BD_AHBLitePort_SS\",\"data_type\":\"Slave\"}],\"process_name\":\"qwdwdas\",\"module_location\":\".\",\"parameter\":[{\"data_size\":16,\"data_type\":\"UINT\",\"value\":\"0\",\"par_name\":\"pa\"}],\"process_type\":\"SC_METHOD\",\"module_name\":\"moduleName\",\"sensitivity\":[],\"register\":[{\"data_size\":16,\"data_type\":\"UINT\",\"reg_name\":\"re\",\"value\":\"0\"}]}}"

int main() {
	BDWriter writer;
	writer.writeModuleCode(INPUT_STR);

	return 0;
}
