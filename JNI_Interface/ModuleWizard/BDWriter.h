/*
 * BDWriter.h
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */

#ifndef SRC_BDWRITER_H_
#define SRC_BDWRITER_H_



#include "BlockDesigner.h"
#include "json.h"


class BDWriter
{

public:
	BDWriter();
	virtual ~BDWriter();
private:
	void initMembers();



public:
	int writeModuleCode(const char *inputStr);


private:
	int createModuleHeader();
	int createModuleSource();
	int createBDDIHeader();
	int createBDDISource();
	int createBDMMIHeader();
	int createBDMMISource();
	int createMakeFile();

	void setModule(BDModule* module);
	void setDirPath(const char* dirPath);
	BDModule*& getModule();
	char* getDirPath();

	char* format(char* fmt, ...);
	char* toLower(char* pstr);
	char* toUpper(char* pstr);


private:
	BDModule *pm_module;
	char *pm_dirPath;


};



#endif /* SRC_BDWRITER_H_ */
