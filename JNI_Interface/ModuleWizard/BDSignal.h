/*
 * BDSignal.h
 *
 *  Created on: 2015. 11. 16.
 *      Author: Sungkyu Hong
 */



#include "BDConfig.h"

#ifndef SRC_COMP_BDSIGNAL_H_
#define SRC_COMP_BDSIGNAL_H_



namespace blockdesigner {
enum SIGNAL_TYPE {
	SC_SIGNAL=0,
	SC_SIGNAL_RV
};
}


class BDSignal
{
public:
	BDSignal();
	BDSignal(const char* name, enum SIGNAL_TYPE type, const char* dataType);
	virtual ~BDSignal();


private:
	void initMembers();


public:
	void setName(const char* name);
	void setType(enum SIGNAL_TYPE type);
	char* getTypeText(char* buffer);
	void setDataType(const char* dataType);


	char* getName();
	enum SIGNAL_TYPE getType();
	char* getDataType();



private:
	char *pm_name;
	enum SIGNAL_TYPE m_type;
	char *pm_dataType;
};

#endif /* SRC_COMP_BDSIGNAL_H_ */
