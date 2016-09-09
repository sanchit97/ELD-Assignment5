#define F_CPU 16000000UL
#define DDRB (*((volatile unsigned char *)0x24))
#define PORTB (*((volatile unsigned char *)0x25))
#define PRR (*((volatile unsigned char *)0x64))
#define TCNT0 (*((volatile unsigned char *)0x46)) //Timer/counter register
#define TCCR0 (*((volatile unsigned char *)0x45)) //Timer/counter control register
#define TIMSK (*((volatile unsigned char *)0x6E)) //Timer/counter interrupt mask

#include <avr/interrupt.h>


volatile uint8_t tot_overflow; //variable to count overflows
  

void timer0_init() //timer, interrupt, variable initialization
{
    
    TCCR0 |= (1 << 2); //prescaler setup = 256 (CS02 bit)
  
    
    TCNT0 = 0; //counter initialize
  
    TIMSK |= (1 << 0); //oveflow interrupt enable
  
    
    sei(); //enables global interrupts
  
   
    tot_overflow = 0; //overflow counter variable initialize
}
  

ISR(TIMER0_OVF_vect) // called after overflow of TCNT0
{
    
    tot_overflow++; //no. of overflows
}

int main(void)
{
    PRR = 0xFF;
    PRR &= (0<<5);
    DDRB|=0xFF; //led connected
	timer0_init(); //timer initialize
	while(1)
	{
		if (tot_overflow >= 122) //no. of overflows checker
        {
           
            if (TCNT0 >= 53) //checks if counter reaches 53
            {
                PORTB ^= (1 << 5);  //led toggles  
                TCNT0 = 0;           // counter is reset 
                tot_overflow = 0;     //overflow counter reset
            }
        }
	}
	return 0;
}