/*
 * BDProcess.h
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */


#include "BDConfig.h"
#include "BDSensitive.h"

#ifndef BDPROCESS_H_
#define BDPROCESS_H_


namespace blockdesigner {
enum PROC_TYPE {
	METHOD=0,
	THREAD,
	CTHREAD
};
}


class BDProcess
{
public:
	BDProcess();
	BDProcess(const char* name, enum PROC_TYPE type);
	virtual ~BDProcess();

private:
	void initMembers();


public:
	void setName(const char* name);
	void setType(enum PROC_TYPE type);
	char* getName();
	enum PROC_TYPE getType();


private:
	char *pm_name;
	enum PROC_TYPE m_type;


};


#endif /* BDPROCESS_H_ */
