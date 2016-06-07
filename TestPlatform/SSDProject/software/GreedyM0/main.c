#include "jasmine.h"

volatile unsigned char *console   = (volatile unsigned char *) 0xB0000000U;

struct __FILE{int handle;};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)    
{ 
	*console = ch; 
	return ch; 
}
int ferror(FILE *f)           
{
	return 0; 
}
int fgetc(FILE *f)
{ 
	return -1; 
}
int __backspace(FILE *stream)
{
	return 0; 
}
void _ttywrch(int ch)
{
	fputc(ch,&__stdout); 
}
void _sys_exit(void )          
{ 
	//printf("System stop is requested!\n");
	//*exit_req = 0xFFFFFFFF;
	fputc(0x0D,&__stdout);
	while(1); 
}

int main(void)
{
	init_jasmine();
	Main();
/*
	int SearchIndex = 0;

 	mem_set_sram(0x20001000, 0xffff, 0x400);
	mem_set_sram(0x20002000, 0xffff, 0x400);
	mem_set_sram(0x20003000, 0xffff, 0x400);
	mem_set_sram(0x20004000, 0xffff, 0x400);
	mem_copy(0x20005000, 0x20004000, 0x400);
	mem_copy(0x20006000, 0x20002000, 0x400);
	mem_copy(0x20007000, 0x20003000, 0x400);
	mem_copy(0x20008000, 0x20004000, 0x400);  

  mem_set_dram(0x60001000, 0xffff, 0x400);
	mem_copy(0x60002000, 0x20001000, 0x400);
	mem_copy(0x20009000, 0x60002000, 0x400);	

	printf("Welcome to TwoBlock Technologies!\n");
	printf("Happy Engineering with us!\n");
*/
	return 0;
}
