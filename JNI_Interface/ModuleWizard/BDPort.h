/*
 * BDPort.h
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */


#include "BDConfig.h"


#ifndef BDPORT_H_
#define BDPORT_H_

namespace blockdesigner {
enum PORT_TYPE {
	SC_IN=0,
	SC_OUT,
	SC_INOUT,
	SC_IN_RV,
	SC_OUT_RV,
	SC_INOUT_RV
};
}

class BDPort {

public:
	BDPort();
	BDPort(const char* name, enum PORT_TYPE type, const char* dataType);
	virtual ~BDPort();


private:
	void initMembers();


public:
	void setName(const char* name);
	void setType(enum PORT_TYPE type);
	void setDataType(const char* dataType);


	char* getName();
	enum PORT_TYPE getType();
	char* getTypeText(char* buffer);
	char* getDataType();



private:
	char *pm_name;
	enum PORT_TYPE m_type;
	char *pm_dataType;

};


#endif /* BDPORT_H_ */
