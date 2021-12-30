#include "../include/lcd1602.h"
#include "../include/usb.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/iom2560.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Initialize USB pins
 * U---4=-----GND---------=4--U
 * S---3=----VBUS---------=3--S
 * B---2=-----D(+)--------=2--B
 * C---1=-----D(-)--------=1--A
 * */

struct USB usb;

/*
 * Initialize port for USBC & USBA*/
void Usb_init(void)
{

	DDRC  &= AS_INPUTS;   		// PC0, PC1, PC2 & PC3 as inputs
	PORTC |= PU_ENABLE;			// Enable pull-up resistor on the inputs
	DDRL  |= AS_OUTPUTS;        // PL0, PL1, PL2, PL3 as outputs
	PORTL &= SET_PINS_LOW;		// Set output pins as ground

}

void Usb_scan_wires(void)
{

	bool isNotConnected = false;
	bool allPinsConnected = true;



	// When a pin is low the there is a connection
	for (uint8_t pin = 0; pin < USB_PIN_SIZE; pin++)
	{
		isNotConnected = (PINC & (1 << pin)) >> pin;

		if (isNotConnected)
		{
			allPinsConnected = false;
			usb.pin_connected[pin] = pin+PIN_OFFSET;
		}
		LCD_loading_bar();
	}

	if (allPinsConnected)
	{
		usb.test_passed = true;


	}

}
