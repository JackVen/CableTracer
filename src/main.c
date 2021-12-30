
#include <util/delay.h>
#include <avr/io.h>
#include <avr/iom2560.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/iom2560.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "../include/ethernet.h"
#include "../include/lcd1602.h"
#include "../include/button.h"
#include "../include/usb.h"

uint8_t pressed_cofidence_level=0;
uint8_t released_cofidence_level =0;
uint8_t pressed=0;

void init_system(void)
{
	LCD_init();
	Ethernet_init();
	Button_init();
	Usb_init();
	sei();
	LCD_display_init_system();

}


/*
* ISR(Interrupt Service Routine)
* Button pressed
* */
ISR(PCINT0_vect)
{
	pressed_cofidence_level++;
}

int main (void)
{

	init_system();

	while(true)
	{
		//TODO calibrate the cpfidence level
		if (pressed_cofidence_level > 3)
		{
			if (pressed == 0)
			{

				LCD_clear();
				LCD_string_pos(LCD_FIRST_ROW, LCD_POS_3, "Scanning");
				Ethernet_scan_wires();
				Usb_scan_wires();
				LCD_clear();
				LCD_scanning_results();
				pressed = 1;


			}
			pressed_cofidence_level=0;
		}

		else
		{
			released_cofidence_level++;
			if (released_cofidence_level > 2)
			{
				pressed = 0;
				released_cofidence_level=0;
			}

		}


	}
	return 0;
}
