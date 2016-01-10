#include"Control_Signal.h"
namespace BDapi
{
	int Control_Flag = 0;
	void sig_handler( int signo )
	{
		if ( signo == SIGUSR2 )		Control_Flag = STEP;
		else if ( signo == SIGUSR1)     Control_Flag = NOTHING;
		else if ( signo == SIGCONT)	Control_Flag = RUN;
		else if ( signo == SIGINT)	Control_Flag = STOP;
		else if ( signo == SIGTERM)	Control_Flag = PAUSE;
	}
}
