#ifndef __BD_AHB_MASTER_PORT_H__ 
#define __BD_AHB_MASTER_PORT_H__ 

#include "systemc.h"

namespace sc_core
{
	class BD_AHBPort_MM
	{
		public:
			sc_out<unsigned int>   HADDR;
			sc_out<unsigned int>   HBURST;
			sc_out<bool>   HLOCK;
			sc_out<unsigned int>   HPROT;
			sc_out<unsigned int>   HSIZE;
			sc_out<unsigned int>   HTRANS;
			sc_out<unsigned int>   HWDATA;
			sc_out<bool>   HWRITE;
			sc_in<unsigned int>    HRDATA;
			sc_in<bool>    HREADY;
			sc_in<bool>    HRESP;

			char temp[11][256];

			BD_AHBPort_MM(char *Name)
			{
				for(int i=0; i<11; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_MM_");
				strcpy(temp[1], "$HBURST_MM_");
				strcpy(temp[2], "$HLOCK_MM_");
				strcpy(temp[3], "$HPROT_MM_");
				strcpy(temp[4], "$HSIZE_MM_");
				strcpy(temp[5], "$HTRANS_MM_");
				strcpy(temp[6], "$HWDATA_MM_");
				strcpy(temp[7], "$HWRITE_MM_");
				strcpy(temp[8], "$HRDATA_MM_");
				strcpy(temp[9], "$HREADY_MM_");
				strcpy(temp[10], "$HRESP_MM_");

				if(Name != NULL)	{
					for(int i=0; i<11; i++)
						strcat(temp[i], Name);
				}

				HADDR.set_port_name(temp[0]);
				HBURST.set_port_name(temp[1]);
				HLOCK.set_port_name(temp[2]);
				HPROT.set_port_name(temp[3]);
				HSIZE.set_port_name(temp[4]);
				HTRANS.set_port_name(temp[5]);
				HWDATA.set_port_name(temp[6]);
				HWRITE.set_port_name(temp[7]);
				HRDATA.set_port_name(temp[8]);
				HREADY.set_port_name(temp[9]);
				HRESP.set_port_name(temp[10]);
			}
	};

	class BD_AHBPort_MS 
	{
		public:
			sc_in<unsigned int>   HADDR;
			sc_in<unsigned int>   HBURST;
			sc_in<bool>   HLOCK;
			sc_in<unsigned int>   HPROT;
			sc_in<unsigned int>   HSIZE;
			sc_in<unsigned int>   HTRANS;
			sc_in<unsigned int>   HWDATA;
			sc_in<bool>   HWRITE;
			sc_out<unsigned int>    HRDATA;
			sc_out<bool>    HREADY;
			sc_out<bool>    HRESP;

			char temp[11][256];

			BD_AHBPort_MS(char *Name)
			{
				for(int i=0; i<11; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_MS_");
				strcpy(temp[1], "$HBURST_MS_");
				strcpy(temp[2], "$HLOCK_MS_");
				strcpy(temp[3], "$HPROT_MS_");
				strcpy(temp[4], "$HSIZE_MS_");
				strcpy(temp[5], "$HTRANS_MS_");
				strcpy(temp[6], "$HWDATA_MS_");
				strcpy(temp[7], "$HWRITE_MS_");
				strcpy(temp[8], "$HRDATA_MS_");
				strcpy(temp[9], "$HREADY_MS_");
				strcpy(temp[10], "$HRESP_MS_");

				if(Name != NULL)	{
					for(int i=0; i<11; i++)
						strcat(temp[i], Name);
				}

				HADDR.set_port_name(temp[0]);
				HBURST.set_port_name(temp[1]);
				HLOCK.set_port_name(temp[2]);
				HPROT.set_port_name(temp[3]);
				HSIZE.set_port_name(temp[4]);
				HTRANS.set_port_name(temp[5]);
				HWDATA.set_port_name(temp[6]);
				HWRITE.set_port_name(temp[7]);
				HRDATA.set_port_name(temp[8]);
				HREADY.set_port_name(temp[9]);
				HRESP.set_port_name(temp[10]);
			}
	};

	class BD_AHBPort_SM
	{
		public:
			sc_out<unsigned int>  HADDR;
			sc_out<unsigned int>  HBURST;
			sc_out<bool>    HLOCK;
			sc_out<unsigned int>  HPROT;
			sc_out<unsigned int>  HSIZE;
			sc_out<unsigned int>  HTRANS;
			sc_out<unsigned int>  HWDATA;
			sc_out<bool>    HWRITE;
			sc_out<bool>    HREADY;
			sc_out<bool>    HSEL;
			sc_in<bool>     HREADYOUT;
			sc_in<bool>     HRESP;
			sc_in<unsigned int>   HRDATA;

			char temp[13][256];

			BD_AHBPort_SM(char *Name)
			{
				for(int i=0; i<13; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_SM_");
				strcpy(temp[1], "$HBURST_SM_");
				strcpy(temp[2], "$HLOCK_SM_");
				strcpy(temp[3], "$HPROT_SM_");
				strcpy(temp[4], "$HSIZE_SM_");
				strcpy(temp[5], "$HTRANS_SM_");
				strcpy(temp[6], "$HWDATA_SM_");
				strcpy(temp[7], "$HWRITE_SM_");
				strcpy(temp[8], "$HREADY_SM_");
				strcpy(temp[9], "$HSEL_SM_");
				strcpy(temp[10], "$HREADYOUT_SM_");
				strcpy(temp[11], "$HRESP_SM_");
				strcpy(temp[12], "$HRDATA_SM_");

				if(Name != NULL)	{
					for(int i=0; i<13; i++)
						strcat(temp[i], Name);
				}

				HADDR.set_port_name(temp[0]);
				HBURST.set_port_name(temp[1]);
				HLOCK.set_port_name(temp[2]);
				HPROT.set_port_name(temp[3]);
				HSIZE.set_port_name(temp[4]);
				HTRANS.set_port_name(temp[5]);
				HWDATA.set_port_name(temp[6]);
				HWRITE.set_port_name(temp[7]);
				HREADY.set_port_name(temp[8]);
				HSEL.set_port_name(temp[9]);
				HREADYOUT.set_port_name(temp[10]);
				HRESP.set_port_name(temp[11]);
				HRDATA.set_port_name(temp[12]);
			}
	};


	class BD_AHBPort_SS
	{
		public:
			sc_in<unsigned int>  HADDR;
			sc_in<unsigned int>  HBURST;
			sc_in<bool>    HLOCK;
			sc_in<unsigned int>  HPROT;
			sc_in<unsigned int>  HSIZE;
			sc_in<unsigned int>  HTRANS;
			sc_in<unsigned int>  HWDATA;
			sc_in<bool>    HWRITE;
			sc_in<bool>    HREADY;
			sc_in<bool>    HSEL;
			sc_out<bool>     HREADYOUT;
			sc_out<bool>     HRESP;
			sc_out<unsigned int>   HRDATA;

			char temp[13][256];

			BD_AHBPort_SS(char *Name)
			{
				for(int i=0; i<13; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_SS_");
				strcpy(temp[1], "$HBURST_SS_");
				strcpy(temp[2], "$HLOCK_SS_");
				strcpy(temp[3], "$HPROT_SS_");
				strcpy(temp[4], "$HSIZE_SS_");
				strcpy(temp[5], "$HTRANS_SS_");
				strcpy(temp[6], "$HWDATA_SS_");
				strcpy(temp[7], "$HWRITE_SS_");
				strcpy(temp[8], "$HREADY_SS_");
				strcpy(temp[9], "$HSEL_SS_");
				strcpy(temp[10], "$HREADYOUT_SS_");
				strcpy(temp[11], "$HRESP_SS_");
				strcpy(temp[12], "$HRDATA_SS_");

				if(Name != NULL)	{
					for(int i=0; i<13; i++)
						strcat(temp[i], Name);
				}

				HADDR.set_port_name(temp[0]);
				HBURST.set_port_name(temp[1]);
				HLOCK.set_port_name(temp[2]);
				HPROT.set_port_name(temp[3]);
				HSIZE.set_port_name(temp[4]);
				HTRANS.set_port_name(temp[5]);
				HWDATA.set_port_name(temp[6]);
				HWRITE.set_port_name(temp[7]);
				HREADY.set_port_name(temp[8]);
				HSEL.set_port_name(temp[9]);
				HREADYOUT.set_port_name(temp[10]);
				HRESP.set_port_name(temp[11]);
				HRDATA.set_port_name(temp[12]);
			}
	};
}



#endif 
