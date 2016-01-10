/*
 * BDWriter.h
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */

#ifndef SRC_BDWRITER_H_
#define SRC_BDWRITER_H_



#include "BlockDesigner.h"

#define INPUT_STR_TOKEN ","


class BDWriter
{

public:
	BDWriter();
	BDWriter(BDModule* module, const char* dirPath);
	virtual ~BDWriter();
private:
	void initMembers();



public:
	int writeModuleCode(const char *inputStr);


private:
	int createSystemCHeader();
	int createSystemCSource();

	void setModule(BDModule* module);
	void setDirPath(const char* dirPath);
	BDModule*& getModule();
	char* getDirPath();


	int header_annotation(ofstream& fout);
	int header_includePart(ofstream& fout);
	int header_elementPart(ofstream& fout);
	int header_constructor(ofstream& fout);
	int header_registerProcess(ofstream& fout);

	int source_annotation(ofstream& fout);
	int source_includePart(ofstream& fout);
	int source_processBody(ofstream& fout);
	int source_initFunction(ofstream& fout);


	char* format(char* fmt, ...);
	char* toLower(char* pstr);
	char* toUpper(char* pstr);


private:
	BDModule *pm_module;
	char *pm_dirPath;


};



#endif /* SRC_BDWRITER_H_ */
