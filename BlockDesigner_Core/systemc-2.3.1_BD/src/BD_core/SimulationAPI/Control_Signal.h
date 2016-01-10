#ifndef CONTROL_SIGNAL_H
#define CONTROL_SIGNAL_H

#include<signal.h>

namespace BDapi 
{

#define NOTHING 0
#define RUN     1
#define PAUSE   2
#define STEP    3
#define STOP    4

	extern int Control_Flag;
	extern void sig_handler( int signo );
}
#endif

