#include "../include/lcd1602.h"
#include "../include/ethernet.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/iom2560.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Initialize
 * RJ45 (T568A) pins
 * 8=-----Brown--------=8
 * 7=-----White/Brown--=7
 * 6=-----Orange-------=6
 * 5=-----White/Blue---=5
 * 4=-----Blue---------=4
 * 3=-----White/Orange-=3
 * 2=-----Green--------=2
 * 1=-----White/Green--=1
 * */

struct Ethernet ethernet;

void Ethernet_init(void)
{

	DDRK  &= AS_INPUTS;
	PORTK |= PU_ENABLE_ETHERNET;

	DDRD  |= (RJ45_PIN1_OUT | RJ45_PIN2_OUT);
	PORTD &= SET_PINS_LOW;
	DDRH  |= (RJ45_PIN3_OUT | RJ45_PIN4_OUT);
	PORTH &= SET_PINS_LOW;
	DDRJ  |= (RJ45_PIN5_OUT | RJ45_PIN6_OUT);
	PORTJ &= SET_PINS_LOW;
	DDRE  |= (RJ45_PIN7_OUT | RJ45_PIN8_OUT);
	PORTE &= SET_PINS_LOW;

}

void Ethernet_scan_wires(void)
{

	bool isNotConnected = false;
	bool allPinsConnected = true;

	// When a pin is low the there is a connection
	for (uint8_t pin = 0; pin < ETHERNET_PIN_SIZE; pin++)
	{
		isNotConnected = (PINK & (1 << pin)) >> pin;

		if (isNotConnected)
		{
			allPinsConnected = false;
			ethernet.pin_connected[pin] = pin+PIN_OFFSET;
		}
		LCD_loading_bar();

	}

	if (allPinsConnected)
	{
		ethernet.test_passed = true;

	}
}























