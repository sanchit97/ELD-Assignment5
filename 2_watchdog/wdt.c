#define F_CPU 16000000UL

#include <avr/interrupt.h>

//#define MCUSR (*((volatile unsigned char *)0x54))
#define DDRB (*((volatile unsigned char *)0x24))
#define PORTB (*((volatile unsigned char *)0x25))
#define WDTCSR (*((volatile unsigned char *)0x60)) //watchdog timer control register

ISR(WDT_vect) //watchdog interrupt
{
	PORTB ^= (0b00100000);
}

int main(void)
{
	DDRB |= 0xFF;

	// Disable all interrupts	
	cli();
	WDTCSR = (1<<3) | (1<<4); // 3:wde(system rest enable) is set
	// 4: wdce - changes watchdog enable
	WDTCSR = (1 << 6) | (1<<2) | (1<<0) | (0<<1) | (0<<5); // 6: interrupt enable
	// 0 1 0 1 set to wdp3, p2, p1, p0 [5,2,1,0]


	
	// Enable all interrupts.
	sei();

    while(1);
}