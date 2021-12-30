/*
 * button.c
 *
 * Created on: Nov 14, 2021
 * Author: jack
 **/


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../include/button.h"
#include "../include/lcd1602.h"
#include <avr/iom2560.h>


/*
 * Button initialization:
 * Enable interrupt 5
 **/
 void Button_init(void)
{
	DDRB &= ~(1<<PB5); // as input
	PORTB |= _BV(PORTB5);

	PCICR  |= (1<< PCIE0);
	PCMSK0 |= (1<<PCINT5);

}


