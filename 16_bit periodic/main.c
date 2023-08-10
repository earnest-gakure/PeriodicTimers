//creating delays using timers
//BLUE led blinks after every 1 sec
#include "TM4C123.h"                    // Device header
#define BLUE (1U<<2)
void period_timer (int time );

int main (){
	SYSCTL->RCGCGPIO |=0x20;
	GPIOF->DIR       |=BLUE;
	GPIOF->DEN       |=BLUE;
	
	while (1){
		GPIOF->DATA ^= BLUE; //togle BLUE LED
		period_timer(1000);     //1 Second deley
		
	}
}
void period_timer (int time )
{
	int j;
	SYSCTL->RCGCTIMER |= 0x01 ;  //enable clock for Timer 0
	TIMER0->CTL       |= 0x00 ; //DISSALBE TIMER
	TIMER0->CFG       |= 0x04 ; //selecting our timer as 16-bits
	TIMER0->TAMR      |= 0x02 ;  //selecting periodic timer
	TIMER0->TAILR     |= 16000000 -1 ; //interval value
	TIMER0->ICR       |= 0x01 ;     //clear timeout flag
	TIMER0->CTL       |= 0x01 ;     //enable timer
	
	for (j=0;j<time ;j++){
		while ((TIMER0->RIS &0x1)==0);
		TIMER0->ICR =0x01;
	}
}
