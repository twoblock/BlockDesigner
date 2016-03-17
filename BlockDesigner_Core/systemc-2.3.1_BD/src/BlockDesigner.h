#ifndef __BD_AHB_MASTER_PORT_H__ 
#define __BD_AHB_MASTER_PORT_H__ 

#include "systemc.h"

namespace sc_core
{
	class BD_AHBPort_MM 
	{
		public:
			sc_out<bool>		HBUSREQ;
			sc_out<unsigned int>   HADDR;
			sc_out<unsigned int>   HBURST;
			sc_out<unsigned int>   HPROT;
			sc_out<unsigned int>   HSIZE;
			sc_out<unsigned int>   HTRANS;
			sc_out<unsigned int>   HWDATA;
			sc_out<bool>   HWRITE;
			sc_out<bool>	HLOCK;
			sc_in<bool>		HGRANT;
			sc_in<bool>		HREADY;
			sc_in<bool>		HRESP;
			sc_in<unsigned int>	HRDATA;

			char temp[13][256];

			BD_AHBPort_MM(char *Name)
			{
				for(int i=0; i<13; i++)
					memset(temp[i], 0, 256);
				
				strcpy(temp[0], "$AHBHADDR_");
				strcpy(temp[1], "$AHBHBURST_");
				strcpy(temp[2], "$AHBHPROT_");
				strcpy(temp[3], "$AHBHSIZE_");
				strcpy(temp[4], "$AHBHTRANS_");
				strcpy(temp[5], "$AHBHWDATA_");
				strcpy(temp[6], "$AHBHWRITE_");
				strcpy(temp[7], "$AHBHBUSREQ_");
				strcpy(temp[8], "$AHBHGRANT_");
				strcpy(temp[9], "$AHBHLCOK_");
				strcpy(temp[10], "$AHBHREADY_");
				strcpy(temp[11], "$AHBHRESP_");
				strcpy(temp[12], "$AHBHRDATA_");

				if(Name != NULL)	{
					for(int i=0; i<13; i++)
						strcat(temp[i], Name);
				}

				HADDR.set_port_name(temp[0]);
				HBURST.set_port_name(temp[1]);
				HPROT.set_port_name(temp[2]);
				HSIZE.set_port_name(temp[3]);
				HTRANS.set_port_name(temp[4]);
				HWDATA.set_port_name(temp[5]);
				HWRITE.set_port_name(temp[6]);
				HBUSREQ.set_port_name(temp[7]);
				HGRANT.set_port_name(temp[8]);
				HLOCK.set_port_name(temp[9]);
				HREADY.set_port_name(temp[10]);
				HRESP.set_port_name(temp[11]);
				HRDATA.set_port_name(temp[12]);
			}
	};

	class BD_AHBPort_MS 
	{
		public:
			sc_in<bool>		HBUSREQ;
			sc_in<unsigned int>   HADDR;
			sc_in<unsigned int>   HBURST;
			sc_in<unsigned int>   HPROT;
			sc_in<unsigned int>   HSIZE;
			sc_in<unsigned int>   HTRANS;
			sc_in<unsigned int>   HWDATA;
			sc_in<bool>   HWRITE;
			sc_in<bool>		HLOCK;
			sc_out<bool>		HGRANT;
			sc_out<bool>		HREADY;
			sc_out<bool>		HRESP;
			sc_out<unsigned int>		HRDATA;

			char temp[13][256];

			BD_AHBPort_MS(char *Name)
			{
				for(int i=0; i<13; i++)
					memset(temp[i], 0, 256);
				
				strcpy(temp[0], "$AHBHADDR_");
				strcpy(temp[1], "$AHBHBURST_");
				strcpy(temp[2], "$AHBHPROT_");
				strcpy(temp[3], "$AHBHSIZE_");
				strcpy(temp[4], "$AHBHTRANS_");
				strcpy(temp[5], "$AHBHWDATA_");
				strcpy(temp[6], "$AHBHWRITE_");
				strcpy(temp[7], "$AHBHBUSREQ_");
				strcpy(temp[8], "$AHBHGRANT_");
				strcpy(temp[9], "$AHBHLOCK_");
				strcpy(temp[10], "$AHBHREADY_");
				strcpy(temp[11], "$AHBHRESP_");
				strcpy(temp[12], "$AHBHRDATA_");

				if(Name != NULL)	{
					for(int i=0; i<13; i++)
						strcat(temp[i], Name);
				}

				HADDR.set_port_name(temp[0]);
				HBURST.set_port_name(temp[1]);
				HPROT.set_port_name(temp[2]);
				HSIZE.set_port_name(temp[3]);
				HTRANS.set_port_name(temp[4]);
				HWDATA.set_port_name(temp[5]);
				HWRITE.set_port_name(temp[6]);
				HBUSREQ.set_port_name(temp[7]);
				HGRANT.set_port_name(temp[8]);
				HLOCK.set_port_name(temp[9]);
				HREADY.set_port_name(temp[10]);
				HRESP.set_port_name(temp[11]);
				HRDATA.set_port_name(temp[12]);

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

				strcpy(temp[0], "$AHBHADDR_");
				strcpy(temp[1], "$AHBHBURST_");
				strcpy(temp[2], "$AHBHLOCK_");
				strcpy(temp[3], "$AHBHPROT_");
				strcpy(temp[4], "$AHBHSIZE_");
				strcpy(temp[5], "$AHBHTRANS_");
				strcpy(temp[6], "$AHBHWDATA_");
				strcpy(temp[7], "$AHBHWRITE_");
				strcpy(temp[8], "$AHBHREADY_");
				strcpy(temp[9], "$AHBHSEL_");
				strcpy(temp[10], "$AHBHREADYOUT_");
				strcpy(temp[11], "$AHBHRESP_");
				strcpy(temp[12], "$AHBHRDATA_");

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

				strcpy(temp[0], "$AHBHADDR_");
				strcpy(temp[1], "$AHBHBURST_");
				strcpy(temp[2], "$AHBHLOCK_");
				strcpy(temp[3], "$AHBHPROT_");
				strcpy(temp[4], "$AHBHSIZE_");
				strcpy(temp[5], "$AHBHTRANS_");
				strcpy(temp[6], "$AHBHWDATA_");
				strcpy(temp[7], "$AHBHWRITE_");
				strcpy(temp[8], "$AHBHREADY_");
				strcpy(temp[9], "$AHBHSEL_");
				strcpy(temp[10], "$AHBHREADYOUT_");
				strcpy(temp[11], "$AHBHRESP_");
				strcpy(temp[12], "$AHBHRDATA_");

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

	class BD_AHBLitePort_MM
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

			BD_AHBLitePort_MM(char *Name)
			{
				for(int i=0; i<11; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_");
				strcpy(temp[1], "$HBURST_");
				strcpy(temp[2], "$HLOCK_");
				strcpy(temp[3], "$HPROT_");
				strcpy(temp[4], "$HSIZE_");
				strcpy(temp[5], "$HTRANS_");
				strcpy(temp[6], "$HWDATA_");
				strcpy(temp[7], "$HWRITE_");
				strcpy(temp[8], "$HRDATA_");
				strcpy(temp[9], "$HREADY_");
				strcpy(temp[10], "$HRESP_");

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

	class BD_AHBLitePort_MS 
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

			BD_AHBLitePort_MS(char *Name)
			{
				for(int i=0; i<11; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_");
				strcpy(temp[1], "$HBURST_");
				strcpy(temp[2], "$HLOCK_");
				strcpy(temp[3], "$HPROT_");
				strcpy(temp[4], "$HSIZE_");
				strcpy(temp[5], "$HTRANS_");
				strcpy(temp[6], "$HWDATA_");
				strcpy(temp[7], "$HWRITE_");
				strcpy(temp[8], "$HRDATA_");
				strcpy(temp[9], "$HREADY_");
				strcpy(temp[10], "$HRESP_");

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

	class BD_AHBLitePort_SM
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

			BD_AHBLitePort_SM(char *Name)
			{
				for(int i=0; i<13; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_");
				strcpy(temp[1], "$HBURST_");
				strcpy(temp[2], "$HLOCK_");
				strcpy(temp[3], "$HPROT_");
				strcpy(temp[4], "$HSIZE_");
				strcpy(temp[5], "$HTRANS_");
				strcpy(temp[6], "$HWDATA_");
				strcpy(temp[7], "$HWRITE_");
				strcpy(temp[8], "$HREADY_");
				strcpy(temp[9], "$HSEL_");
				strcpy(temp[10], "$HREADYOUT_");
				strcpy(temp[11], "$HRESP_");
				strcpy(temp[12], "$HRDATA_");

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

	class BD_AHBLitePort_SS
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

			BD_AHBLitePort_SS(char *Name)
			{
				for(int i=0; i<13; i++)
					memset(temp[i], 0, 256);

				strcpy(temp[0], "$HADDR_");
				strcpy(temp[1], "$HBURST_");
				strcpy(temp[2], "$HLOCK_");
				strcpy(temp[3], "$HPROT_");
				strcpy(temp[4], "$HSIZE_");
				strcpy(temp[5], "$HTRANS_");
				strcpy(temp[6], "$HWDATA_");
				strcpy(temp[7], "$HWRITE_");
				strcpy(temp[8], "$HREADY_");
				strcpy(temp[9], "$HSEL_");
				strcpy(temp[10], "$HREADYOUT_");
				strcpy(temp[11], "$HRESP_");
				strcpy(temp[12], "$HRDATA_");

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
