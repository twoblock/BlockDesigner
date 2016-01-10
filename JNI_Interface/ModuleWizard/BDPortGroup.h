/*
 * BDPortGroup.h
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */



#include "BDConfig.h"
#include "BDPort.h"


#ifndef BDPORTGROUP_H_
#define BDPORTGROUP_H_


class BDPortGroup : public std::list<BDPort*> {

public:
	BDPortGroup();
	BDPortGroup(const char* name);
	virtual ~BDPortGroup();


private:
	void initMembers();


public:
	char* getName();
	void setName(const char* name);
	int addPort(const char* portName, enum PORT_TYPE portType, const char* dataType);


private:
	char *pm_name;

};

#endif /* BDPORTGROUP_H_ */
