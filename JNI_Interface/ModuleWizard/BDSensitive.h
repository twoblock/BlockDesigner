/*
 * BDSensitive.h
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */


#include "BDConfig.h"
#include "BDPort.h"
using namespace blockdesigner;


#ifndef BDSENSITIVE_H_
#define BDSENSITIVE_H_


namespace blockdesigner {
enum SENSE_TYPE {
	NEITHER =0, //not sensitive
	NEG,	//negative
	POS,	//positive
	EVAL	//evaluation
};
}





class BDSensitive
{
public:
	BDSensitive();
	BDSensitive(const char *portName, enum SENSE_TYPE edgeType);
	virtual ~BDSensitive();

private:
	void initMembers();

public:
	void setSenseType(enum SENSE_TYPE senseType);
	void setPortName(const char* portName);

	enum SENSE_TYPE getSenseType();
	char* getPortName() const;
	char* getMethodNameForSensitive(char *buffer);


	/**
	 * member
	 */
private:
	char *pm_portName;
	enum SENSE_TYPE m_senseType;

};

#endif /* BDSENSITIVE_H_ */
