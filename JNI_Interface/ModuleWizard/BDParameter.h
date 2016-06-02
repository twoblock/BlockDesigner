/*
 * BDParameter.h
 *
 *  Created on: 2015. 11. 9.
 *      Author: Sungkyu Hong
 */

#include "BDConfig.h"


#ifndef BDPARAMETER_H_
#define BDPARAMETER_H_


class BDParameter {

public:
	BDParameter();
	BDParameter(const char* name, const char* type, int dataSize, const char* defVal);
	virtual ~BDParameter();


private:
	void initMembers();


public:
	void setName(const char* name);
	void setType(const char* type);
	void setDataSize(int dataSize);
	void setDefaultValue(const char* defVal);
	char* getName() const;
	char* getDataType() const;
	char* getType() const;
	int getDataSize() const;
	char* getDefaultValue() const;


private:
	char *pm_name;
	char *pm_type;
	int pm_dataSize;
	char *pm_defaultValue;

};

#endif /* BDPARAMETER_H_ */
