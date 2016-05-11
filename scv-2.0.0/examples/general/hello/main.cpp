//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************

	The following code is derived, directly or indirectly, from the SystemC
	source code Copyright (c) 1996-2014 by all Contributors.
	All Rights reserved.

	The contents of this file are subject to the restrictions and limitations
	set forth in the SystemC Open Source License (the "License");
	You may not use this file except in compliance with such restrictions and
	limitations. You may obtain instructions on how to receive a copy of the
	License at http://www.accellera.org/. Software distributed by Contributors
	under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
	ANY KIND, either express or implied. See the License for the specific
	language governing rights and limitations under the License.

 *****************************************************************************/
#include "scv.h"

// Changed by Harold.

int sc_main(int argc, char** argv) {
	scv_smart_ptr<unsigned int> data;
	scv_bag<unsigned int> dist;
	scv_extensions<unsigned int> data_t;

	unsigned int data_temp;

	data->keep_only(0,15);
	//data->keep_out(6,9);
	
	for(int i=0; i<30; i++)	{
		cout << "randomize : " << endl;
		data->next();
		data->print();
	}

	data_temp = data->get_unsigned();

	cout << "convert : " << data_temp << endl;

	exit(0);
}
