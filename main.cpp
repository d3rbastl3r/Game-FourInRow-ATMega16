// TODO - Show win animation
// TODO - Implement game logic
// TODO - Read buttons
// TODO - Create Folder (GameLogic, Input)

#define F_CPU 16000000UL // 16 MHz

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "Display/DisplayController.h"

DisplayController displayController = DisplayController();

// Timer 0 - Interrupt
ISR(TIMER0_COMP_vect) {
	TCNT0 = 0; // Set counter 0 to zero
	++displayController.animationCounter;
}

void setupTimer0() {
	// TODO - May be use other counter for DisplayController
	
	cli();
	
	// Config Counter0
	// 16.000.000 / 256 = 62.500
	// Output Compare 250 => 62.500 / 250 = 250HZ (1Tick per 4mS)
	
	// TCCR0: Timer/Counter Control Register
	TCCR0 = (1<<CS02); // clk / 256 (From prescaler)
	
	// OCR0: Output Compare Register
	OCR0 = 0xFA;  // Output compare 0xFA = 250
	
	// Timer Counter
	TCNT0 = 0; // Set counter 0 to zero
	
	// TIMSK: Timer/Counter Interrupt Mask Register
	TIMSK = (1<<OCIE0); // Counter0 Output Compare Match Interrupt Enable
	
	sei();
}

int main(void) {
	setupTimer0();
	//displayController.startSelectAnimation(1, 0b00000001);
	displayController.startDropAnimation(2, 0b00000010, 7);
	
	DDRB |= (1<<DDB0);
	
    while (1) {
		displayController.update();
		
		if (displayController.animationCounter >= 100) {
			PORTB |= (1<<PB0);
		} else {
			PORTB &= ~(1<<PB0);
		}
    }
}

