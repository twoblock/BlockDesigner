/*
e * BDWriter.cpp
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */

#include "BDWriter.h"

/************************************************************************
 * Constructor & Destructor
 ************************************************************************/
BDWriter::BDWriter() {
	initMembers();
}


BDWriter::~BDWriter() {
	if(pm_dirPath != NULL)
		free(pm_dirPath);

	pm_module = NULL;
}


void BDWriter::initMembers() {
	pm_module = NULL;

	pm_dirPath = (char*) malloc(ARR_SIZE(char, MAX_PATH_SIZE) + 1);
	setDirPath("./");
}






int BDWriter::writeModuleCode(const char* inputStr)
{
	BDModule module;
	Json::Reader jsonReader;
	Json::Value root;

	bool parsingRet = jsonReader.parse(inputStr, root, false);
	if(!parsingRet) {
		cout << "parsing error" << endl;
	}
	root = root["ModuleWizard"];


	//module name
	module.setName(root["module_name"].asString().c_str());

	//module type
	module.setType(root["module_type"].asString().c_str());

	//target path
	setDirPath(format("%s/%s", root["module_location"].asString().c_str(), module.getName()));
	system(format("mkdir %s", pm_dirPath));

	//Ports
	const Json::Value ports = root["port"];
	if(!ports.isNull()) {
		for(int i=0; i<ports.size(); i++) {
			Json::Value item = ports[i];
			module.addPort(item["port_name"].asString().c_str(), item["sc_type"].asString().c_str(), item["data_type"].asString().c_str());
		}
	}

	//Registers
	const Json::Value regs = root["register"];
	if(!regs.isNull()) {
		for(int i=0; i<regs.size(); i++) {
			Json::Value item = regs[i];
			module.addRegister(item["reg_name"].asString().c_str(), item["data_type"].asString().c_str(), item["data_size"].asInt(), item["value"].asString().c_str());
		}
	}

	//Parameters
	const Json::Value params = root["parameter"];
	if(!params.isNull()) {
		for(int i=0; i<params.size(); i++) {
			Json::Value item = params[i];
			module.addParameter(item["par_name"].asString().c_str(), item["data_type"].asString().c_str(), item["data_size"].asInt(), item["value"].asString().c_str());
		}
	}

	//Process
	module.setProc(root["process_name"].asString().c_str(), root["process_type"].asString().c_str());

	//Sensitivities
	const Json::Value sens = root["sensitivity"];
	if(!sens.isNull()) {
		for(int i=0; i<sens.size(); i++) {
			Json::Value item = sens[i];
			module.addSensitivity(item["port_name"].asString().c_str(), item["sens_type"].asString().c_str());
		}
	}


	//write
	setModule(&module);
	createModuleHeader();
	createModuleSource();
	createBDDIHeader();
	createBDDISource();
	if(strcmp(pm_module->getType(), "bus") == 0) {
		createBDMMIHeader();
		createBDMMISource();
	}
	createMakeFile();


	return 0;
}





/************************************************************************
 * Methods to write Header file
 ************************************************************************/
int BDWriter::createModuleHeader()
{
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s.h", pm_dirPath, pm_module->getName());
	ofstream fout(path);


	BDProcess *proc = pm_module->getProcess();


	//header_annotation///////////////////////////////////////////////////////////////////////
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << ".h" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;
	fout << "#ifndef    __" << pm_module->getName() << "_H__" << endl;
	fout << "#define    __" << pm_module->getName() << "_H__" << endl;
	fout << endl;


	//header_includePart///////////////////////////////////////////////////////////////////////
	fout << "#include \"BlockDesigner.h\"" << endl;
	fout << "#include <stdio.h>" << endl;
	fout << "#include <string.h>" << endl;

	fout << "#include \"" << pm_module->getName() << "_BDDI.h\"" << endl;
	if(strcmp(pm_module->getType(), "bus") == 0) {
		fout << "#include \"" << pm_module->getName() << "_BDMMI.h\"" << endl;
	}

	fout << endl;



	fout << format("SC_MODULE(%s) {", pm_module->getName()) << endl;



	//header_elementPart///////////////////////////////////////////////////////////////////////
	/*
	 * Port part
	 */
	fout << endl << T1 << "/* Global Clock & Resetn */" << endl;
	fout << T1 << "sc_in<bool> HCLK;" << endl;
	fout << T1 << "sc_in<bool> HRESETn;" << endl;



	fout << endl << T1 << "/* Port definition part. */" << endl;
	BDPortGroup *portGrp = pm_module->getPorts();
	if( portGrp != NULL ) {
		for(std::list<BDPort*>::iterator it=portGrp->begin(); it != portGrp->end(); ++it)
		{
			BDPort *item = (BDPort*)(*it);
			char buffer[32] = {0,};

			switch(item->getType()) {
			case SC_IN:
			case SC_OUT:
			case SC_INOUT:
			case SC_IN_RV:
			case SC_OUT_RV:
			case SC_INOUT_RV:
				fout << T1 << item->getTypeText(buffer) << "<" <<item->getDataType() << "> " << item->getName() << ";" << endl;
				break;

			case AHB_MM:
			case AHB_MS:
			case AHB_SM:
			case AHB_SS:
			case AHB_LITE_MM:
			case AHB_LITE_MS:
			case AHB_LITE_SM:
			case AHB_LITE_SS:
				fout << T1 << item->getTypeText(buffer) << " *" << item->getName() << ";" << endl;
				break;
			}
		}
	}


	/*
	 * Internal signal part
	 */
	fout << endl << T1 << "/* Internal signal part. */" << endl;

	std::list<BDSignal*> *signals = pm_module->getSignals();
	if( signals != NULL ) {
		for(std::list<BDSignal*>::iterator it=signals->begin(); it != signals->end(); ++it)
		{
			BDSignal *item = (BDSignal*)(*it);
			char buffer[32] = {0,};
			fout << T1 << item->getTypeText(buffer) << "<" << item->getDataType() << "> " << item->getName() << ";" << endl;
		}
	}



	/*
	 * Internal register part
	 */
	fout << endl << T1 << "/* Register part. */" << endl;

	std::list<BDRegister*> *regs = pm_module->getRegisters();
	if( regs != NULL) {
		for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end(); ++it)
		{
			BDRegister *item = (BDRegister*)(*it);
			fout << T1 << item->getDataType() << " " << item->getName() << ";" << endl;
		}
	}




	/*
	 * Internal parameter part
	 */
	fout << endl << T1 << "/* Parameter part. */" << endl;

	std::list<BDParameter*> *params = pm_module->getParams();
	if( params != NULL) {
		for(std::list<BDParameter*>::iterator it=params->begin(); it != params->end(); ++it)
		{
			BDParameter *item = (BDParameter*)(*it);
			fout << T1 << item->getDataType() << " " << item->getName() << ";" << endl;
		}
	}

	fout << endl << T1 << "/* Block Designer Debugging Interface. */" << endl;
	fout << T1 << "BDDI* bddi;" << endl;
	if(strcmp(pm_module->getType(), "bus") == 0) {
		fout << T1 << "BDMMI* bdmmi;" << endl;
	}

	fout << T1 << "BDDI* GetBDDI();" << endl;
	if(strcmp(pm_module->getType(), "bus") == 0) {
		fout << T1 << "BDMMI* GetBDMMI();" << endl;
	}

	fout << T1 << "char* GetModuleName();" << endl;
	fout << endl << endl;



	/*
	 * Sub module part
	 */
	fout << endl << T1 << "/* Sub module part. */" << endl;




	/*
	 * Member function part.
	 */
	fout << endl << T1 << "/* Member function part. */" << endl;
	fout << T1 << format("void %s();", FUNC_NAME_BD_INIT) << endl;

	fout << endl;



	//header_constructor///////////////////////////////////////////////////////////////////////
	/*
	 * Process function definition
	 */
	fout << endl << T1 << "//main process" << endl;
	fout << T1 << format("void %s();", proc->getName()) << endl;
	fout << endl;



	/*
	 * SC_CTOR
	 */
	fout << endl;
	fout << T1 << "/* SC Constructor */" << endl;
	fout << T1 << format("SC_CTOR(%s) {", pm_module->getName()) << endl;

	fout << endl;
	fout << T2 << "//initialize members" << endl;
	fout << T2 << format("%s();", FUNC_NAME_BD_INIT) << endl;
	fout << endl;



	//header_registerProcess///////////////////////////////////////////////////////////////////////
	switch(proc->getType())
	{
	case METHOD:
	{
		fout << T2 << format("SC_METHOD(%s);", proc->getName()) << endl;

		std::list<BDSensitive*> *senseList = pm_module->getSensitives();
		if(senseList != NULL) {
			for(std::list<BDSensitive*>::iterator it=senseList->begin(); it!=senseList->end(); ++it) {
				BDSensitive *item = (BDSensitive*)(*it);
				char buffer[32] = {0,};
				if(item->getMethodNameForSensitive(buffer) != NULL)
					fout << T2 << "sensitive" << " << " << item->getPortName() << buffer << ";" << endl;
				else
					fout << T2 << "sensitive" << " << " << buffer << ";" << endl;
			}
		}
	}
	break;

	case THREAD:
	{
		fout << T2 << format("SC_THREAD(%s);", proc->getName()) << endl;

		std::list<BDSensitive*> *senseList = pm_module->getSensitives();
		if(senseList != NULL) {
			for(std::list<BDSensitive*>::iterator it=senseList->begin(); it!=senseList->end(); ++it) {
				BDSensitive *item = (BDSensitive*)(*it);
				char buffer[32] = {0,};
				if(item->getMethodNameForSensitive(buffer) != NULL)
					fout << T2 << "sensitive" << " << " << item->getPortName() << buffer << ";" << endl;
				else
					fout << T2 << "sensitive" << " << " << buffer << ";" << endl;
			}
		}
	}
	break;

	case CTHREAD:
	{
		std::list<BDSensitive*> *senseList = pm_module->getSensitives();
		if(senseList != NULL) {
			BDSensitive *sens = senseList->front();
			char buffer[32] = {0,};
			fout << T2 << format("SC_CTHREAD(%s, %s%s);", proc->getName(), sens->getPortName(), sens->getMethodNameForSensitive(buffer)) << endl;
		}
	}
	break;
	}
	fout << T1 << "}";
	fout << endl;

	fout << T1 << format("~%s();", pm_module->getName()) << endl;
	fout << endl;

	fout << "};";	fout << endl;
	fout << endl;


	fout << "extern \"C\" sc_module* CreateInstance(const char *ModuleInstanceName);" << endl;
	fout << "#endif     // __" << pm_module->getName() << "_H__" << endl;
	fout << endl;


	//Close file stream and Return
	fout.close();
	return 0;
}





/************************************************************************
 * Methods to write Source file
 ************************************************************************/
int BDWriter::createModuleSource()
{
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s.cpp", pm_dirPath, pm_module->getName());
	ofstream fout(path);


	std::list<BDPort*> *ports = pm_module->getPorts();
	std::list<BDRegister*> *regs = pm_module->getRegisters();
	std::list<BDParameter*> *params = pm_module->getParams();


	//source_annotation///////////////////////////////////////////////////////////////////////
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << ".cpp" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;

	fout << endl;


	//source_includePart///////////////////////////////////////////////////////////////////////
	fout << "#include \"" << pm_module->getName() << ".h\"" << endl;
	fout << endl;


	//Desctructor///////////////////////////////////////////////////////////////////////
	fout << "" << pm_module->getName() << "::~" << pm_module->getName() << "() {" << endl;
	if(ports != NULL) {
		for(std::list<BDPort*>::iterator it=ports->begin(); it!=ports->end(); ++it)
		{
			BDPort *item = (BDPort*)(*it);
			switch(item->getType()) {
			case AHB_MM:
			case AHB_MS:
			case AHB_SM:
			case AHB_SS:
			case AHB_LITE_MM:
			case AHB_LITE_MS:
			case AHB_LITE_SM:
			case AHB_LITE_SS:
				fout << T1 << format("delete %s;", item->getName()) << endl;
				break;
			}
		} // end of for
	}
	fout << endl;

	fout << T1 << "delete bddi;" << endl;
	if(strcmp(pm_module->getType(), "bus") == 0) {
		fout << T1 << "delete bdmmi;" << endl;
	}

	fout << "}" << endl;
	fout << endl;



	fout << "BDDI* " << pm_module->getName() << "::GetBDDI() {" << endl;
	fout << T1 << "return bddi;" << endl;
	fout << "}" << endl;

	if(strcmp(pm_module->getType(), "bus") == 0) {
		fout << "BDMMI* " << pm_module->getName() << "::GetBDMMI() {" << endl;
		fout << T1 << "return bdmmi;" << endl;
		fout << "}" << endl;
	}

	fout << "char* " << pm_module->getName() << "::GetModuleName() {" << endl;
	fout << T1 << "return (char*)\"" << pm_module->getName() << "\";" << endl;
	fout << "}" << endl;



	//source_processBody///////////////////////////////////////////////////////////////////////
	BDProcess *proc = pm_module->getProcess();
	fout << "void " << pm_module->getName() << "::" << proc->getName() << "() {" << endl;

	switch(proc->getType()) {
	case METHOD:
	{
		fout << T1 << "//Auto-generated METHOD Stub" << endl;
	}
	break;

	case THREAD:
	{
		fout << T1 << "//Auto-generated THREAD Stub" << endl;
		fout << endl << endl;

		fout << T1 << "//a THREAD type process must have a infinite loop." << endl;
		fout << T1 << "while(true) {" << endl;
		fout << endl;
		fout << T2 << "/* do something */" << endl;
		fout << endl;
		fout << T2 << "//the infinite loop must have a wait statement." << endl;
		fout << T2 << "wait();" << endl;
		fout << T1 << "} " << endl;
	}
	break;

	case CTHREAD:
	{
		fout << T1 << "//Auto-generated THREAD Stub" << endl;
		fout << endl << endl;

		fout << T1 << "//a CTHREAD type process must have a infinite loop." << endl;
		fout << T1 << "while(true) {" << endl;
		fout << endl;
		fout << T2 << "/* do something */" << endl;
		fout << endl;
		fout << T2 << "//the infinite loop must have a wait statement." << endl;
		fout << T2 << "wait();" << endl;
		fout << T1 << "} " << endl;
	}
	break;
	}

	fout << "}" << endl;
	fout << endl;


	//source_initFunction///////////////////////////////////////////////////////////////////////
	fout << endl << endl;
	fout << "//Initialize member variables." << endl;
	fout << format("void %s::%s() {", pm_module->getName(), FUNC_NAME_BD_INIT) << endl;
	fout << T1 << "//Auto-generated function to initialize member variables." << endl;
	fout << endl;

	fout << T1 << "HCLK.set_port_name(\"HCLK\");" << endl;
	fout << T1 << "HRESETn.set_port_name(\"HRESETn\");" << endl;
	fout << endl;

	if(ports != NULL) {
		for(std::list<BDPort*>::iterator it=ports->begin(); it!=ports->end(); ++it)
		{
			BDPort *item = (BDPort*)(*it);
			switch(item->getType()) {
			case SC_IN:
			case SC_OUT:
			case SC_INOUT:
			case SC_IN_RV:
			case SC_OUT_RV:
			case SC_INOUT_RV:
				fout << T1 << item->getName() << ".set_port_name(\"" << item->getName() << "\");";
				break;

			case AHB_MM:			fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_MM, item->getName()); break;
			case AHB_MS:			fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_MS, item->getName()); break;
			case AHB_SM:			fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_SM, item->getName()); break;
			case AHB_SS:			fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_SS, item->getName()); break;
			case AHB_LITE_MM:	fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_LITE_MM, item->getName()); break;
			case AHB_LITE_MS:	fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_LITE_MS, item->getName()); break;
			case AHB_LITE_SM:	fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_LITE_SM, item->getName()); break;
			case AHB_LITE_SS:	fout << T1 << format("%s = new %s((char*)\"%s\");", item->getName(), STR_AHB_LITE_SS, item->getName()); break;
			}

			fout << endl;
		}
		fout << endl;
	}

	if(regs != NULL) {
		for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end(); ++it) {
			BDRegister *item = (BDRegister*)(*it);
			fout << T1 << item->getName() << " = " << item->getDefaultValue() << ";" << endl;
		}
		fout << endl;
	}


	if(params != NULL) {
		for(std::list<BDParameter*>::iterator it=params->begin(); it != params->end(); ++it) {
			BDParameter *item = (BDParameter*)(*it);
			fout << T1 << item->getName() << " = " << item->getDefaultValue() << ";" << endl;
		}
		fout << endl;
	}


	fout << T1 << "bddi = new " << pm_module->getName() << "_BDDI(this);" << endl;
	if(strcmp(pm_module->getType(), "bus") == 0) {
		fout << T1 << "bdmmi = new " << pm_module->getName() << "_BDMMI(this);" << endl;
	}
	fout << "}" << endl;
	fout << endl;




	fout << "extern \"C\" sc_module* CreateInstance(const char *ModuleInstanceName) {" << endl;
	fout << T1 << "return new " << pm_module->getName() << "(ModuleInstanceName);" << endl;
	fout << "}" << endl;


	//Close file stream and Return
	fout.close();
	return 0;
}



int BDWriter::createBDDIHeader()
{
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s_BDDI.h", pm_dirPath, pm_module->getName());
	ofstream fout(path);



	//header_annotation///////////////////////////////////////////////////////////////////////
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << "_BDDI.h" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;
	fout << "#ifndef    __" << pm_module->getName() << "_BDDI_H__" << endl;
	fout << "#define    __" << pm_module->getName() << "_BDDI_H__" << endl;
	fout << endl;



	//header_includePart///////////////////////////////////////////////////////////////////////
	fout << "#include \"systemc.h\"" << endl;
	fout << endl;
	fout << "using namespace BDapi;" << endl;
	fout << endl;

	fout << "class " << pm_module->getName() << ";" << endl;
	fout << endl;

	fout << "class " << pm_module->getName() << "_BDDI : public BDDIBase" << endl;
	fout << "{" << endl;

	fout << T1 << "public:" << endl;
	fout << T1 << T1 << "" << pm_module->getName() << "_BDDI(" << pm_module->getName() << " *c);" << endl;
	fout << T1 << T1 << "virtual ~" << pm_module->getName() << "_BDDI();" << endl;
	fout << endl;

	fout << T1 << "public:" << endl;
	fout << T1 << T1 << "BDDIReturn BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue);" << endl;
	fout << T1 << T1 << "BDDIReturn BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue);" << endl;
	fout << T1 << T1 << "BDDIReturn BDDIGetParameterValues(unsigned int ParIndex, char *OutValue);" << endl;
	fout << T1 << T1 << "BDDIReturn BDDISetParameterValues(unsigned int ParIndex, const char *SetValue);" << endl;
	fout << endl;

	fout << T1 << T1 << "char* BDDIGetModuleType();" << endl;
	fout << endl;

	fout << T1 << T1 << "BDDIRegInfo* BDDIGetModuleRegInfo();" << endl;
	fout << T1 << T1 << "BDDIParInfo* BDDIGetModuleParInfo();" << endl;
	fout << endl;

	fout << T1 << T1 << "unsigned int BDDIGetModuleTotalRegNum();" << endl;
	fout << T1 << T1 << "unsigned int BDDIGetModuleTotalParNum();" << endl;
	fout << endl;

	fout << T1 << "private:" << endl;
	fout << T1 << T1 << "" << pm_module->getName() << " *p_Target;" << endl;
	fout << T1 << T1 << "BDDIRegInfo *pst_OutRegInfo;" << endl;
	fout << T1 << T1 << "BDDIParInfo *pst_OutParInfo;" << endl;
	fout << "};" << endl;
	fout << endl;

	fout << "#endif    // __" << pm_module->getName() << "_BDDI_H__" << endl;



	//Close file stream and Return
	fout.close();
	return 0;
}

int BDWriter::createBDDISource() {
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s_BDDI.cpp", pm_dirPath, pm_module->getName());
	ofstream fout(path);


	std::list<BDRegister*> *regs = pm_module->getRegisters();
	std::list<BDParameter*> *params = pm_module->getParams();
	int i = 0;


	//header_annotation///////////////////////////////////////////////////////////////////////
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << "_BDDI.cpp" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;

	fout << "#include \"" << pm_module->getName() << "_BDDI.h\"" << endl;
	fout << "#include \"" << pm_module->getName() << ".h\"" << endl;
	fout << endl;


	fout << "BDDIRegInfo ast_" << pm_module->getName() << "RegInfo[] =" << endl;
	fout << "{" << endl;
	if(regs != NULL) {
		for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end();)
		{
			BDRegister *item = (BDRegister*)(*it);
			fout << T1 << format("{\"%s\", %d, BDDIRegType%s}", item->getName(), item->getDataSize(), item->getType());

			if(++it != regs->end())
				fout << ",";

			fout << endl;
		}
	}
	fout << "};" << endl;
	fout << endl;


	fout << "BDDIParInfo ast_" << pm_module->getName() << "ParInfo[] =" << endl;
	fout << "{" << endl;
	if(params != NULL) {
		for(std::list<BDParameter*>::iterator it=params->begin(); it != params->end();)
		{
			BDParameter *item = (BDParameter*)(*it);
			fout << T1 << format("{\"%s\", %d, BDDIParType%s, \"\"}", item->getName(), item->getDataSize(), item->getType());

			if(++it != params->end())
				fout << ",";

			fout << endl;
		}
	}
	fout << "};" << endl;
	fout << endl;




	fout << "static const UINT32 dw_RegCnt = sizeof(ast_" << pm_module->getName() << "RegInfo) / sizeof(ast_" << pm_module->getName() << "RegInfo[0]);" << endl;
	fout << "static const UINT32 dw_ParCnt = sizeof(ast_" << pm_module->getName() << "ParInfo) / sizeof(ast_" << pm_module->getName() << "ParInfo[0]);" << endl;




	//Constructor///////////////////////////////////////////////////////////////////////
	fout << "" << pm_module->getName() << "_BDDI::" << pm_module->getName() << "_BDDI(" << pm_module->getName() << " *c) : p_Target(c)" << endl;
	fout << "{" << endl;
	fout << T1 << "UINT32 dw_Index = 0;" << endl;
	fout << T1 << "char a_Temp[BDDI_STRING_SIZE];" << endl;
	fout << endl;

	fout << T1 << "pst_OutRegInfo = new BDDIRegInfo[dw_RegCnt];" << endl;
	fout << T1 << "pst_OutParInfo = new BDDIParInfo[dw_ParCnt];" << endl;
	fout << endl;

	fout << T1 << "for(dw_Index=0; dw_Index<dw_RegCnt; dw_Index++) {" << endl;
	fout << T1 << T1 << "strcpy(pst_OutRegInfo[dw_Index].Name,                   ast_" << pm_module->getName() << "RegInfo[dw_Index].Name);" << endl;
	fout << T1 << T1 << "pst_OutRegInfo[dw_Index].Bitswide                       = ast_" << pm_module->getName() << "RegInfo[dw_Index].Bitswide;" << endl;
	fout << T1 << T1 << "pst_OutRegInfo[dw_Index].Type                               = ast_" << pm_module->getName() << "RegInfo[dw_Index].Type;" << endl;
	fout << T1 << "}" << endl;
	fout << endl;

	fout << T1 << "for(dw_Index=0; dw_Index<dw_ParCnt; dw_Index++) {" << endl;
	fout << T1 << T1 << "strcpy(pst_OutParInfo[dw_Index].Name,                   ast_" << pm_module->getName() << "ParInfo[dw_Index].Name);" << endl;
	fout << T1 << T1 << "pst_OutParInfo[dw_Index].Bitswide                       = ast_" << pm_module->getName() << "ParInfo[dw_Index].Bitswide;" << endl;
	fout << T1 << T1 << "pst_OutParInfo[dw_Index].Type                               = ast_" << pm_module->getName() << "ParInfo[dw_Index].Type;" << endl;
	fout << endl;

	fout << T1 << T1 << "BDDIGetParameterValues(dw_Index, a_Temp);" << endl;
	fout << endl;

	fout << T1 << T1 << "strcpy(pst_OutParInfo[dw_Index].Value,              a_Temp);" << endl;
	fout << T1 << "}" << endl;
	fout << "}" << endl;
	fout << endl;




	//Desctructor///////////////////////////////////////////////////////////////////////
	fout << "" << pm_module->getName() << "_BDDI::~" << pm_module->getName() << "_BDDI()" << endl;
	fout << "{" << endl;
	fout << T1 << "if(pst_OutRegInfo)  delete [] pst_OutRegInfo;" << endl;
	fout << T1 << "if(pst_OutParInfo)  delete [] pst_OutParInfo;" << endl;
	fout << "}" << endl;




	//BDDIGetRegisterValues()///////////////////////////////////////////////////////////////////////
	fout << "// regsiter access function" << endl;
	fout << "BDDIReturn " << pm_module->getName() << "_BDDI::BDDIGetRegisterValues(unsigned int RegIndex, char *OutValue)" << endl;
	fout << "{" << endl;
	fout << T1 << "BDDIRegValue st_Temp;" << endl;
	fout << endl;

	if(regs != NULL) {
		for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end(); ++it) {
			BDRegister *item = (BDRegister*)(*it);
			fout << T1 << format("%s %s_Temp;", item->getDataType(), item->getName()) << endl;
		}
		fout << endl;
	}


	fout << T1 << "switch(RegIndex)" << endl;
	fout << T1 << "{" << endl;

	if(regs != NULL) {
		i = 0;
		for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end(); ++it)
		{
			BDRegister *item = (BDRegister*)(*it);
			fout << T1 << T1 << format("case %d:", i++) << endl;
			fout << T1 << T1 << T1 << format("%s_Temp = p_Target->%s;", item->getName(), item->getName()) << endl;
			fout << T1 << T1 << T1 << format("BDDIPutInRegisterValue(&st_Temp, &ast_%sRegInfo[RegIndex], &%s_Temp);", pm_module->getName(), item->getName()) << endl;
			fout << T1 << T1 << T1 << format("BDDIConvertRegisterValueToString(&st_Temp, OutValue);") << endl;
			fout << T1 << T1 << T1 << "break;" << endl;
		}
		fout << endl;
	}

	fout << T1 << T1 << "default:	return BDDIStatusError;" << endl;
	fout << T1 << "}" << endl;
	fout << endl;

	fout << T1 << "return BDDIStatusOK;" << endl;
	fout << "}" << endl;




	//BDDISetRegisterValues()///////////////////////////////////////////////////////////////////////
	fout << "// regsiter access function" << endl;
	fout << "BDDIReturn " << pm_module->getName() << "_BDDI::BDDISetRegisterValues(unsigned int RegIndex, const char *SetValue)" << endl;
	fout << "{" << endl;
	fout << T1 << "BDDIRegValue st_Temp;" << endl;
	fout << endl;

	if(regs != NULL) {
		for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end(); ++it) {
			BDRegister *item = (BDRegister*)(*it);
			fout << T1 << format("%s %s_Temp;", item->getDataType(), item->getName()) << endl;
		}
		fout << endl;
	}


	fout << T1 << "switch(RegIndex)" << endl;
	fout << T1 << "{" << endl;

	if(regs != NULL) {
		i = 0;
		for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end(); ++it)
		{
			BDRegister *item = (BDRegister*)(*it);
			fout << T1 << T1 << format("case %d:", i++) << endl;
			fout << T1 << T1 << T1 << format("BDDIConvertStringToRegisterValue(&st_Temp, &ast_%sRegInfo[RegIndex], SetValue);", pm_module->getName()) << endl;
			fout << T1 << T1 << T1 << format("BDDIExtractRegisterValue(&st_Temp, &%s_Temp);", item->getName()) << endl;
			fout << T1 << T1 << T1 << format("p_Target->%s = %s_Temp;", item->getName(), item->getName()) << endl;
			fout << T1 << T1 << T1 << "break;" << endl;
			fout << endl;
		}
	}

	fout << T1 << T1 << "default:	return BDDIStatusError;" << endl;
	fout << T1 << "}" << endl;
	fout << endl;

	fout << T1 << "return BDDIStatusOK;" << endl;
	fout << "}" << endl;




	//BDDIGetParameterValues()///////////////////////////////////////////////////////////////////////
	fout << "// parameter access function" << endl;
	fout << "BDDIReturn " << pm_module->getName() << "_BDDI::BDDIGetParameterValues(unsigned int ParIndex, char *OutValue)" << endl;
	fout << "{" << endl;
	fout << T1 << "BDDIParValue st_Temp;" << endl;
	fout << endl;

	if(params != NULL) {
		for(std::list<BDParameter*>::iterator it=params->begin(); it != params->end(); ++it) {
			BDParameter *item = (BDParameter*)(*it);
			fout << T1 << format("%s %s_Temp;", item->getDataType(), item->getName()) << endl;
		}
		fout << endl;
	}


	fout << T1 << "switch(ParIndex)" << endl;
	fout << T1 << "{" << endl;

	if(params != NULL) {
		i = 0;
		for(std::list<BDParameter*>::iterator it=params->begin(); it != params->end(); ++it)
		{
			BDParameter *item = (BDParameter*)(*it);
			fout << T1 << T1 << format("case %d:", i++) << endl;
			fout << T1 << T1 << T1 << format("%s_Temp = p_Target->%s;", item->getName(), item->getName()) << endl;
			fout << T1 << T1 << T1 << format("BDDIPutInParameterValue(&st_Temp, &ast_%sParInfo[ParIndex], &%s_Temp);", pm_module->getName(), item->getName()) << endl;
			fout << T1 << T1 << T1 << format("BDDIConvertParameterValueToString(&st_Temp, OutValue);") << endl;
			fout << T1 << T1 << T1 << "break;" << endl;
		}
		fout << endl;
	}

	fout << T1 << T1 << "default:	return BDDIStatusError;" << endl;
	fout << T1 << "}" << endl;
	fout << endl;

	fout << T1 << "return BDDIStatusOK;" << endl;
	fout << "}" << endl;





	//BDDISetParameterValues()///////////////////////////////////////////////////////////////////////
	fout << "// parameter access function" << endl;
	fout << "BDDIReturn " << pm_module->getName() << "_BDDI::BDDISetParameterValues(unsigned int ParIndex, const char *SetValue)" << endl;
	fout << "{" << endl;
	fout << T1 << "BDDIParValue st_Temp;" << endl;
	fout << endl;

	if(params != NULL) {
		for(std::list<BDParameter*>::iterator it=params->begin(); it != params->end(); ++it) {
			BDParameter *item = (BDParameter*)(*it);
			fout << T1 << format("%s %s_Temp;", item->getDataType(), item->getName()) << endl;
		}
		fout << endl;
	}


	fout << T1 << "switch(ParIndex)" << endl;
	fout << T1 << "{" << endl;

	if(params != NULL) {
		i = 0;
		for(std::list<BDParameter*>::iterator it=params->begin(); it != params->end(); ++it)
		{
			BDParameter *item = (BDParameter*)(*it);
			fout << T1 << T1 << format("case %d:", i++) << endl;
			fout << T1 << T1 << T1 << format("BDDIConvertStringToParameterValue(&st_Temp, &ast_%sParInfo[ParIndex], SetValue);", pm_module->getName()) << endl;
			fout << T1 << T1 << T1 << format("BDDIExtractParameterValue(&st_Temp, &%s_Temp);", item->getName()) << endl;
			fout << T1 << T1 << T1 << format("p_Target->%s = %s_Temp;", item->getName(), item->getName()) << endl;
			fout << T1 << T1 << T1 << "break;" << endl;
		}
		fout << endl;
	}

	fout << T1 << T1 << "default:	return BDDIStatusError;" << endl;
	fout << T1 << "}" << endl;
	fout << endl;

	fout << T1 << "return BDDIStatusOK;" << endl;\
	fout << "}" << endl;



	//ETC functions///////////////////////////////////////////////////////////////////////
	fout << "char* " << pm_module->getName() << "_BDDI::BDDIGetModuleType()" << endl;
	fout << "{" << endl;
	fout << T1 << format("return (char*)\"%s\";", pm_module->getType()) << endl;
	fout << "}" << endl;
	fout << endl;

	fout << "BDDIRegInfo* " << pm_module->getName() << "_BDDI::BDDIGetModuleRegInfo()" << endl;
	fout << "{" << endl;
	fout << T1 << "return pst_OutRegInfo;" << endl;
	fout << "}" << endl;
	fout << endl;

	fout << "BDDIParInfo* " << pm_module->getName() << "_BDDI::BDDIGetModuleParInfo()" << endl;
	fout << "{" << endl;
	fout << T1 << "return pst_OutParInfo;" << endl;
	fout << "}" << endl;
	fout << endl;

	fout << "unsigned int " << pm_module->getName() << "_BDDI::BDDIGetModuleTotalRegNum()" << endl;
	fout << "{" << endl;
	fout << T1 << "return dw_RegCnt;" << endl;
	fout << "}" << endl;
	fout << endl;

	fout << "unsigned int " << pm_module->getName() << "_BDDI::BDDIGetModuleTotalParNum()" << endl;
	fout << "{" << endl;
	fout << T1 << "return dw_ParCnt;" << endl;
	fout << "}" << endl;
	fout << endl;


	//Close file stream and Return
	fout.close();
	return 0;
}

int BDWriter::createBDMMIHeader() {
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s_BDMMI.h", pm_dirPath, pm_module->getName());
	ofstream fout(path);



	//header_annotation///////////////////////////////////////////////////////////////////////
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << "_BDMMI.h" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;
	fout << "#ifndef    __" << pm_module->getName() << "_BDMMI_H__" << endl;
	fout << "#define    __" << pm_module->getName() << "_BDMMI_H__" << endl;
	fout << endl;



	//header_includePart///////////////////////////////////////////////////////////////////////
	fout << "#include \"systemc.h\"" << endl;
	fout << endl;


	fout << "// TODO : user can modify slave number" << endl;
	fout << "#define SlaveNumber 10" << endl;
	fout << endl;

	fout << "using namespace BDapi;" << endl;
	fout << endl;

	fout << "class " << pm_module->getName() << ";" << endl;
	fout << endl;

	fout << "class " << pm_module->getName() << "_BDMMI : public BDMMI" << endl;
	fout << "{" << endl;
	fout << T1 << "public:" << endl;
	fout << T1 << T1 << "// this function set this bus memory map" << endl;
	fout << T1 << T1 << "// TODO : user have to implement this function" << endl;
	fout << T1 << T1 << "void SetMemoryMap();" << endl;
	fout << endl;

	fout << T1 << T1 << "// return slave number for generating PMML.json" << endl;
	fout << T1 << T1 << "unsigned int GetSlaveNumber();" << endl;
	fout << endl;

	fout << T1 << T1 << "" << pm_module->getName() << "_BDMMI(" << pm_module->getName() << " *c);" << endl;
	fout << T1 << T1 << "virtual ~" << pm_module->getName() << "_BDMMI();" << endl;
	fout << endl;

	fout << T1 << "private:" << endl;
	fout << T1 << T1 << "" << pm_module->getName() << " *p_Target;" << endl;
	fout << T1 << T1 << "// array to store all slave memorymap" << endl;
	fout << T1 << T1 << "SlaveMemoryMap ast_BusSlave[SlaveNumber];" << endl;
	fout << "};" << endl;
	fout << endl;

	fout << "#endif    // __" << pm_module->getName() << "_BDMMI_H__" << endl;
	fout << endl;



	//Close file stream and Return
	fout.close();
	return 0;
}

int BDWriter::createBDMMISource() {
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s_BDMMI.cpp", pm_dirPath, pm_module->getName());
	ofstream fout(path);



	//header_annotation///////////////////////////////////////////////////////////////////////
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << "_BDMMI.cpp" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;


	//header_includePart///////////////////////////////////////////////////////////////////////
	fout << "#include \"" << pm_module->getName() << "_BDMMI.h\"" << endl;
	fout << "#include \"" << pm_module->getName() << ".h\"" << endl;
	fout << endl;





	fout << "/*" << endl;
	fout << "* function    : SetMemoryMap" << endl;
	fout << "* design      : set this bus memory map by using BDMMI" << endl;
	fout << "*/" << endl;

	fout << "void " << pm_module->getName() << "_BDMMI::SetMemoryMap()" << endl;
	fout << "{" << endl;
	fout << T1 << "// TODO : user have to implement this area" << endl;
	fout << endl;

	fout << T1 << "/* example of setting memory map" << endl;
	fout << endl;

	fout << T1 << T1 << "for(int i = 0; i < SlaveNumber; i++) {" << endl;
	fout << T1 << T1 << T1 << "p_Target->StartAddr[i] = BDMMIMemoryMap[i].StartAddress;" << endl;
	fout << T1 << T1 << T1 << "p_Target->EndAddr[i] = BDMMIMemoryMap[i].StartAddress + BDMMIMemoryMap[i].Size - 1;" << endl;
	fout << T1 << T1 << "}" << endl;
	fout << endl;
	fout << T1 << "*/" << endl;
	fout << "}" << endl;
	fout << endl;

	fout << "/*" << endl;
	fout << "* function    : GetSlaveNumber" << endl;
	fout << "* design      : return slave number" << endl;
	fout << "* return      : unsigned int - SlaveNumber" << endl;
	fout << "*/" << endl;
	fout << "unsigned int " << pm_module->getName() << "_BDMMI::GetSlaveNumber()" << endl;
	fout << "{" << endl;
	fout << T1 << "return SlaveNumber;" << endl;
	fout << "}" << endl;
	fout << endl;

	fout << "/*" << endl;
	fout << "* function    : " << pm_module->getName() << "_BDMMI" << endl;
	fout << "* design      : Constructor" << endl;
	fout << "*/" << endl;
	fout << "" << pm_module->getName() << "_BDMMI::" << pm_module->getName() << "_BDMMI(" << pm_module->getName() << " *c) : p_Target(c)" << endl;
	fout << "{" << endl;
	fout << T1 << "// initialize this bus memory map" << endl;
	fout << T1 << "for(int SlaveIndex = 0; SlaveIndex < SlaveNumber; SlaveIndex++) {" << endl;
	fout << endl;

	fout << T1 << T1 << "// initialize a slave memory map" << endl;
	fout << T1 << T1 << "memset(ast_BusSlave[SlaveIndex].SlaveModule, 0, sizeof(ast_BusSlave[SlaveIndex].SlaveModule));" << endl;
	fout << T1 << T1 << "memset(ast_BusSlave[SlaveIndex].SlavePort, 0, sizeof(ast_BusSlave[SlaveIndex].SlavePort));" << endl;
	fout << T1 << T1 << "ast_BusSlave[SlaveIndex].StartAddress = 0x0;" << endl;
	fout << T1 << T1 << "ast_BusSlave[SlaveIndex].Size = 0x0;" << endl;
	fout << endl;

	fout << T1 << T1 << "// push each slave memory map to bus memory map" << endl;
	fout << T1 << T1 << "BDMMIMemoryMap.push_back(ast_BusSlave[SlaveIndex]);" << endl;
	fout << T1 << "}" << endl;
	fout << "}" << endl;
	fout << endl;

	fout << "/*" << endl;
	fout << "* function    : ~" << pm_module->getName() << "_BDMMI" << endl;
	fout << "* design      : Destructor" << endl;
	fout << "*/" << endl;
	fout << pm_module->getName() << "_BDMMI::~" << pm_module->getName() << "_BDMMI()" << endl;
	fout << "{" << endl;
	fout << "}" << endl;
	fout << endl;



	//Close file stream and Return
	fout.close();
	return 0;
}

int BDWriter::createMakeFile() {
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/Makefile", pm_dirPath);
	ofstream fout(path);


	fout << "PACKAGE    = " << pm_module->getName() << "" << endl;
	fout << "#######################################" << endl;
	fout << "BUILDFLAGS = -g3 -fPIC  -Wall -W -pedantic -Wno-long-long -Wwrite-strings -Wpointer-arith" << endl;
	fout << "CXX        = g++" << endl;
	fout << "CXXFLAGS = -fPIC -I$(SYSTEMC_INCLUDE)" << endl;
	fout << "LDFLAGS  = -Wl,--export-dynamic" << endl;
	fout << "COMMON_LIBS = -L$(SYSTEMC_LIBDIR) -lsystemc" << endl;
	fout << endl;

	fout << "PACKAGE_SOURCES =   " << pm_module->getName() << ".cpp " << pm_module->getName() << "_BDDI.cpp";
	if(strcmp(pm_module->getType(), "bus") == 0) {
		fout << " " << pm_module->getName() << "_BDMMI.cpp";
	}
	fout << endl;

	fout << "#######################################" << endl;
	fout << endl;

	fout << "SO = lib$(PACKAGE).so" << endl;
	fout << endl;

	fout << "$(SO) : $(PACKAGE_SOURCES:.cpp=.o)" << endl;
	fout << T1 << "$(CXX) $(CXXFLAGS) -o $@ -shared $^ $(COMMON_LIBS) $(LDFLAGS)" << endl;
	fout << endl;

	fout << "clean:" << endl;
	fout << T1 << "rm -f $(SO)" << endl;
	fout << T1 << "rm -f *.o" << endl;




	//Close file stream and Return
	fout.close();
	return 0;
}







/************************************************************************
 * etc
 ************************************************************************/


//ref. http://stackoverflow.com/questions/15106102/how-to-use-c-stdostream-with-printf-like-formatting
char* BDWriter::format(char* fmt, ...)
{
	static char buffer[1024] = {0,};
	va_list argptr;

	va_start(argptr, fmt);
	vsprintf(buffer, fmt, argptr);
	va_end(argptr);

	return buffer;
}


char* BDWriter::toLower(char* pstr) {
	int size = strlen(pstr);
	for(int i=0; i<size; i++) {
		pstr[i] = tolower(pstr[i]);
	}

	return pstr;
}


char* BDWriter::toUpper(char* pstr) {
	int size = strlen(pstr);
	for(int i=0; i<size; i++) {
		pstr[i] = toupper(pstr[i]);
	}

	return pstr;
}





/********************************************************************
 * getter & setter
 ********************************************************************/
char* BDWriter::getDirPath() {
	return pm_dirPath;
}

void BDWriter::setDirPath(const char* dirPath) {
	memset(pm_dirPath, 0x0, ARR_SIZE(char, MAX_PATH_SIZE) + 1);
	strcpy(pm_dirPath, dirPath);
}

BDModule*& BDWriter::getModule() {
	return pm_module;
}

void BDWriter::setModule(BDModule* module) {
	pm_module = module;
}
