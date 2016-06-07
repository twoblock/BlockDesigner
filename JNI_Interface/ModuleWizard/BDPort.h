/*
 * BDPort.h
 *
 *  Created on: 2015. 11. 5.
 *      Author: Sungkyu Hong
 */


#include "BDConfig.h"


#ifndef BDPORT_H_
#define BDPORT_H_

#define STR_SC_IN "sc_in"
#define STR_SC_OUT "sc_out"
#define STR_SC_INOUT "sc_inout"
#define STR_SC_IN_RV "sc_in_rv"
#define STR_SC_OUT_RV "sc_out_rv"
#define STR_SC_INOUT_RV "sc_inout_rv"
#define STR_AHB_MM "BD_AHBPort_MM"
#define STR_AHB_MS "BD_AHBPort_MS"
#define STR_AHB_SM "BD_AHBPort_SM"
#define STR_AHB_SS "BD_AHBPort_SS"
#define STR_AHB_LITE_MM "BD_AHBLitePort_MM"
#define STR_AHB_LITE_MS "BD_AHBLitePort_MS"
#define STR_AHB_LITE_SM "BD_AHBLitePort_SM"
#define STR_AHB_LITE_SS "BD_AHBLitePort_SS"


namespace blockdesigner {
enum PORT_TYPE {
	SC_IN=0,
	SC_OUT,
	SC_INOUT,
	SC_IN_RV,
	SC_OUT_RV,
	SC_INOUT_RV,
	AHB_MM,
	AHB_MS,
	AHB_SM,
	AHB_SS,
	AHB_LITE_MM,
	AHB_LITE_MS,
	AHB_LITE_SM,
	AHB_LITE_SS
};
}

class BDPort {

public:
	BDPort();
	BDPort(const char* name, const char* type, const char* dataType);
	virtual ~BDPort();


private:
	void initMembers();


public:
	void setName(const char* name);
	void setType(const char* strType);
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
