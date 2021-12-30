/*
Display LCD 1602A implementation on
Arduino Mega rv.3
*/


#include "../include/lcd1602.h"
#include "../include/ethernet.h"
#include "../include/usb.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/iom2560.h>
#include <stdbool.h>
#include <string.h>


const uint8_t customChar0[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
const uint8_t buttonChar[8] = {0x00, 0x0E, 0x0A, 0x1F, 0x11, 0x11, 0x11, 0x1F };
uint8_t progress = 0;

/* Initialize the display
 * Set Output ports
 * Send initial values
 * Set the display settings
 * */
void LCD_init(void)
{

	DDRB  |= (LCD_E | LCD_RS);           // Pins as output in port B
	DDRA  |= (LCD_ALL_DATA_PINS);		 // Pins as outputs in port A

	_delay_ms(20);						 //Wait until the power stabilizes

	LCD_send_cmd(LCD_INITIAL_VALUE);
	LCD_send_cmd(LCD_INITIAL_VALUE);
	LCD_send_cmd(LCD_INITIAL_VALUE);

	LCD_send_cmd(LCD_4BIT_MODE);
	LCD_send_cmd(LCD_FUNCTION_SET);
	LCD_send_cmd(LCD_ON_CURSOR_OFF);
	LCD_send_cmd(LCD_INCREMENT);
	LCD_send_cmd(LCD_CLEAR);

	_delay_ms(2);


}

/*Send command function to the display
 * */
void LCD_send_cmd(char cmnd)
{
	PORTA = (PORTA & 0x0F) | (cmnd & 0xF0); 	// sending upper nibble
	PORTB &= ~(LCD_RS);							// RS=0, command register.
	PORTB |= LCD_E;								// Enable pulse
	_delay_us(1);
	PORTB &= ~(LCD_E);

	_delay_us(200);

	PORTA = (PORTA & 0x0F) | (cmnd << 4);      // sending lower nibble
	PORTB |= LCD_E;
	_delay_us(1);
	PORTB &= ~(LCD_E);
	_delay_ms(2);

}

/*Send data to the display
 * */
void LCD_send_data(char data)
{
	PORTA = (PORTA & 0x0F) | (data & 0xF0); // Sending upper nibble
	PORTB |= LCD_RS;						// RS=1, data register
	PORTB |= LCD_E;							// Enable pulse
	_delay_us(1);
	PORTB &= ~(LCD_E);						// Disable pulse

	_delay_us(200);

	PORTA = (PORTA & 0x0F) | (data << 4);  // Sending lower nibble
	PORTB |= LCD_E;
	_delay_us(1);
	PORTB &= ~(LCD_E);
	_delay_ms(2);
}

/*Send a string to the display
  Send each char of string till the NULL*/
void LCD_string(char *str)
{
	for(uint8_t c = 0; str[c] !=0; c++)
	{
		LCD_send_data(str[c]);
	}
}

/* Clear display
 * */
void LCD_clear(void)
{
	LCD_send_cmd(LCD_CLEAR);
	_delay_ms(2);
	LCD_send_cmd (LCD_CURSOR_HOME);
}

/* Send string to LCD with row and position
 * */
void LCD_string_pos(char row, char pos, char *str)
{


	if ((row == LCD_FIRST_ROW) && (pos < LCD_POS_END))
	{
		LCD_send_cmd((pos & 0x0F)|0x80);	//Command of first row and required position<16
	}

	else if ((row == LCD_SECOND_ROW) && (pos < LCD_POS_END))
	{
		LCD_send_cmd((pos & 0x0F)|0xC0);	//Command of first row and required position<16
	}
	LCD_string(str);
}

/*Show the user the initialization progress
 * */
void LCD_display_init_system(void)
{
	LCD_clear();
	LCD_string_pos (LCD_FIRST_ROW, LCD_POS_4, "Ready!!");
	LCD_string_pos (LCD_SECOND_ROW, LCD_POS_1, "Push to start");

}

/*When the button is pressed the scanning port message is shown
 * */
void LCD_scanning_ports(void)
{




}

/*Generate display characters
 * the character is based on a 8x5 matrix
 *
 * 00000
 * 00000
 * 00000
 * 00000
 * 00000
 * 00000
 * 00000
 * 00000
 *
 * pixel off = 0 pixel on = 1
 * */

void LCD_generatechar(uint8_t startaddress, const uint8_t *data, uint8_t line, uint8_t column){


    // Set the start position of the character 0,1,2,3,4,5,6,7
	LCD_send_cmd( 0x40 | (startaddress << 3) );

    //Bit patterns
    for ( uint8_t i=0; i<8; i++ )
    {
    	LCD_send_data( data[i] );
    }

    LCD_send_cmd(line + column); // Set DRAM (Line1), address on the LCD where the bit patterns are displayed
    LCD_send_data(startaddress);	// Display the bit pattern on the stored address


}
/* Show the scaning results of the test
 * both for USB an Ethernet
 * */

void LCD_scanning_results(void)
{

	if(ethernet.test_passed && usb.test_passed)
	{
		LCD_string_pos(LCD_FIRST_ROW, LCD_POS_0, "Ethernet: Passed");
		LCD_string_pos(LCD_SECOND_ROW, LCD_POS_0, "USB: Passed");
	}

	else if (ethernet.test_passed && !usb.test_passed)
	{
		LCD_string_pos(LCD_FIRST_ROW, LCD_POS_0, "Ethernet: Passed");
		LCD_string_pos(LCD_SECOND_ROW, LCD_POS_0, "USB: Failed");
	}

	else if (!ethernet.test_passed && usb.test_passed)
	{
		LCD_string_pos(LCD_FIRST_ROW, LCD_POS_0, "Ethernet: Failed");
		LCD_string_pos(LCD_SECOND_ROW, LCD_POS_0, "USB: Passed");

	}

	else
	{
		LCD_string_pos(LCD_FIRST_ROW, LCD_POS_0, "Ethernet: Failed");
		LCD_string_pos(LCD_SECOND_ROW, LCD_POS_0, "USB: Failed");
	}
	usb.test_passed = false;
	ethernet.test_passed = false;


}

void LCD_loading_bar()
{

	LCD_string_pos(LCD_SECOND_ROW, progress, "=");
	progress++;

	if (progress > LCD_POS_11)
	{
		for (uint8_t fillscreen= progress; fillscreen<=LCD_POS_15; fillscreen++)
		{
			LCD_string_pos(LCD_SECOND_ROW, fillscreen, "=");
			_delay_ms(150);
		}
		progress=0;
	}
	_delay_ms(200);

}



