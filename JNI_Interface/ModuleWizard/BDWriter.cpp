/*
 * BDWriter.cpp
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

BDWriter::BDWriter(BDModule* module, const char* dirPath) {
	initMembers();

	setModule(module); //assignment
	setDirPath(dirPath); //allocate memory
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
	char buffer[1024] = {0,};
	char *pStrCur = NULL;
	BDModule module;

	strcpy(buffer, inputStr);

	//module name
	pStrCur = strtok(buffer, INPUT_STR_TOKEN);
	module.setName(pStrCur);

	//target path
	pStrCur = strtok(NULL, INPUT_STR_TOKEN);
	setDirPath(pStrCur);

	//Ports
	int portSize = atoi(strtok(NULL, INPUT_STR_TOKEN));
	for(int i=0; i<portSize; i++) {
		char *portName = strtok(NULL, INPUT_STR_TOKEN);
		int portType = atoi(strtok(NULL, INPUT_STR_TOKEN));
		char *dataType = strtok(NULL, INPUT_STR_TOKEN);

		module.addPort(portName, (PORT_TYPE)portType, dataType);
	}

	//Registers
	int regSize = atoi(strtok(NULL, INPUT_STR_TOKEN));
	for(int i=0; i<regSize; i++) {
		char *regName = strtok(NULL, INPUT_STR_TOKEN);
		char *dataType = strtok(NULL, INPUT_STR_TOKEN);
		char *defVal = strtok(NULL, INPUT_STR_TOKEN);

		module.addRegister(regName, dataType, defVal);
	}

	//Parameters
	int paramSize = atoi(strtok(NULL, INPUT_STR_TOKEN));
	for(int i=0; i<paramSize; i++) {
		char *paramName = strtok(NULL, INPUT_STR_TOKEN);
		char *dataType = strtok(NULL, INPUT_STR_TOKEN);
		char *defVal = strtok(NULL, INPUT_STR_TOKEN);

		module.addParameter(paramName, dataType, defVal);
	}

	//Process
	char *procName = strtok(NULL, INPUT_STR_TOKEN);
	int procType = atoi(strtok(NULL, INPUT_STR_TOKEN));
	module.setProc(procName, (PROC_TYPE)procType);

	//Sensitivities
	int sensSize = atoi(strtok(NULL, INPUT_STR_TOKEN));
	for(int i=0; i<sensSize; i++) {
		char *portName = strtok(NULL, INPUT_STR_TOKEN);
		int sensType = atoi(strtok(NULL, INPUT_STR_TOKEN));

		module.addSensitivity(portName, (SENSE_TYPE)sensType);
	}


	//write
	setModule(&module);
	createSystemCHeader();
	createSystemCSource();


	return 0;
}





/************************************************************************
 * Methods to write Header file
 ************************************************************************/
int BDWriter::createSystemCHeader()
{
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s.h", pm_dirPath, pm_module->getName());
	ofstream fout(path);


	/**
	 * Write contents
	 */
	header_annotation(fout);	fout << endl;
	header_includePart(fout);	fout << endl;

	fout << format("SC_MODULE(%s) {", pm_module->getName()) << endl;

	header_elementPart(fout);	fout << endl;
	header_constructor(fout);	fout << endl;

	fout << "};";	fout << endl;



	//Close file stream and Return
	fout.close();
	return 0;
}


int BDWriter::header_annotation(ofstream& fout) {
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << ".h" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;

	return 0;
}


int BDWriter::header_includePart(ofstream& fout)
{
	fout << "#include \"systemc.h\"" << endl;

	return 0;
}


int BDWriter::header_elementPart(ofstream& fout)
{
	/*
	 * Port part
	 */
	fout << endl << T1 << "/* Port definition part. */" << endl;

	BDPortGroup *portGrp = pm_module->getPorts();
	if( portGrp != NULL ) {
		for(std::list<BDPort*>::iterator it=portGrp->begin(); it != portGrp->end(); ++it)
		{
			BDPort *item = (BDPort*)(*it);
			char buffer[32] = {0,};
			fout << T1 << item->getTypeText(buffer) << "<" <<item->getDataType() << "> " << item->getName() << ";" << endl;
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
			fout << T1 << item->getType() << " " << item->getName() << ";" << endl;
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
			fout << T1 << item->getType() << " " << item->getName() << ";" << endl;
		}
	}



	/*
	 * Sub module part
	 */
	fout << endl << T1 << "/* Sub module part. */" << endl;




	/*
	 * Member function part.
	 */
	fout << endl << T1 << "/* Member function part. */" << endl;

	fout << T1 << format("void %s();", FUNC_NAME_BD_INIT) << endl;



	return 0;
}


int BDWriter::header_constructor(ofstream& fout) {

	/*
	 * Process function definition
	 */
	BDProcess *proc = pm_module->getProcess();
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
	fout << endl << endl;

	header_registerProcess(fout);

	fout << T1 << "}";
	return 0;
}



int BDWriter::header_registerProcess(ofstream& fout)
{
	BDProcess *proc = pm_module->getProcess();
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

	return 0;
}






/************************************************************************
 * Methods to write Source file
 ************************************************************************/
int BDWriter::createSystemCSource()
{
	//Check members
	assert(pm_module != NULL && pm_dirPath != NULL);


	//Open file stream
	char path[MAX_PATH_SIZE] = {0,};
	sprintf(path, "%s/%s.cpp", pm_dirPath, pm_module->getName());
	ofstream fout(path);


	/**
	 * Write contents
	 */
	source_annotation(fout);	fout << endl;
	source_includePart(fout);	fout << endl;
	source_processBody(fout);	fout << endl;
	source_initFunction(fout);	fout << endl;


	//Close file stream and Return
	fout.close();
	return 0;
}


int BDWriter::source_annotation(ofstream& fout) {
	fout << "/**" << endl;
	fout << " * " << pm_module->getName() << ".cpp" << endl;
	fout << " * " << endl;
	fout << " *  Created by Block designer supported by TwoBlock." << endl;
	fout << " */" << endl;

	return 0;
}


int BDWriter::source_includePart(ofstream& fout) {
	fout << "#include \"" << pm_module->getName() << ".h\"" << endl;

	return 0;
}


int BDWriter::source_processBody(ofstream& fout)
{
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

	return 0;
}


int BDWriter::source_initFunction(ofstream& fout) {
	fout << endl << endl;
	fout << "//Initialize member variables." << endl;
	fout << format("void %s() {", FUNC_NAME_BD_INIT) << endl;
	fout << T1 << "//Auto-generated function to initialize member variables." << endl;
	fout << endl;

	std::list<BDRegister*> *regs = pm_module->getRegisters();
	for(std::list<BDRegister*>::iterator it=regs->begin(); it != regs->end(); ++it) {
		BDRegister *item = (BDRegister*)(*it);
		fout << T1 << item->getName() << " = " << item->getDefaultValue() << ";" << endl;
	}

	fout << endl;
	fout << "}" << endl;
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
