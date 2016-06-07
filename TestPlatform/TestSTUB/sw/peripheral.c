// Implement file IO handling, only console output is supported.

#include "peripheral.h"
#ifdef CORTEXM0DS

//extern __irq void IRQ00_Handler(void){
	//timer0_overflows++;
	//TIMER0->int_clear = 0x1;
//}
//static void timer0_reset_cycle_count(void){
	//TIMER0->cnt_en = 0x0;
	//TIMER0->int_clear = 0x1;
	//TIMER0->load = 0x00FFFFFF;
	//timer0_overflows = 0;
//}
//
//static void timer0_start_cycle_count(void){	
	//TIMER0->cnt_en = 0x1;
//}
//
//static unsigned int timer0_get_cycle_count(void){
	//unsigned int overflows = timer0_overflows;
	//unsigned int cycle_cnt = TIMER0->current;
	//unsigned int new_overflows = timer0_overflows;
	//if(overflows != new_overflows){
		//cycle_cnt = TIMER0->current;
		//overflows = new_overflows;
	//}
	//return ((overflows<<24)+(0x00FFFFFF - cycle_cnt));
//}
//
//extern void timer0_clock_init(void){
	//timer0_reset_cycle_count();
	//timer0_start_cycle_count();
//}
//
//extern clock_t clock(void){
	//return timer0_get_cycle_count();
//}
//
//extern time_t time(time_t * t){
	//return (timer0_get_cycle_count()>>CLOCK_PERIOD_SHIFT);
	//return timer0_get_cycle_count();
//}

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
#endif //CORTEXM0DS


