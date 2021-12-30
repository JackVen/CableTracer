/*
Display LCD 1602A header file
Arduino Mega rv.3 (ATMega 2560)
 * */
#include <stdint.h>


// LCD Pins
#define LCD_E   0x40  // PB6 Enable Signal
#define LCD_RS  0x80  // PB7 Register Select RS=0 (write) RS=1 (Read)
#define LCD_D7  0x40  // PA7 Data bus 7
#define LCD_D6  0x20  // PA6 Data bus 6
#define LCD_D5  0x10  // PA5 Data bus 5
#define LCD_D4  0x08  // PA4 Data bus 4
#define LCD_ALL_DATA_PINS 0xF0 // All data buses

//LCD Commands
#define LCD_CLEAR 				0x01
#define LCD_CURSOR_HOME			0x80
#define LCD_SHIFT_LEFT  		0x07    // Shift the left increase cursor to the right
#define LCD_BLINK_CURSOR_ON   	0x0F  	// LCD on, cursor on and blinking
#define LCD_FUNCTION_SET 		0x28 	// Display settings, 4-bit data bus, 2 lines display, 5x8 dots format
#define LCD_SHIFT_CURSORS_RIGHT	0x1C 	// Shift display right, cursors follows display shift
#define LCD_BUSY_FLAG 			0x80
#define LCD_INITIAL_VALUE 		0x30
#define LCD_4BIT_MODE			0x02
#define LCD_ON_CURSOR_OFF		0x0C
#define LCD_INCREMENT			0x06

//LCD Position
#define LCD_POS_BEGIN			0
#define LCD_POS_END				16
#define LCD_FIRST_ROW 			0
#define LCD_SECOND_ROW 			1
#define LCD_POS_0				0
#define LCD_POS_1				1
#define LCD_POS_2				2
#define LCD_POS_3				3
#define LCD_POS_4				4
#define LCD_POS_5				5
#define LCD_POS_6				6
#define LCD_POS_7				7
#define LCD_POS_8				8
#define LCD_POS_9				9
#define LCD_POS_10				10
#define LCD_POS_11				11
#define LCD_POS_12				12
#define LCD_POS_13				13
#define LCD_POS_14				14
#define LCD_POS_15				15


//LCD Characters
#define LCD_GC_CHAR0            0





//LCD Functions
void LCD_init(void);
void LCD_send_cmd(char cmd);
void LCD_send_data(char data);
void LCD_string(char *str);
void LCD_clear(void);
void LCD_string_pos (char row, char pos, char *str);
void LCD_display_init_system();
void LCD_scanning(void);
void LCD_generatechar(uint8_t startaddress, const uint8_t *data, uint8_t line, uint8_t column);  // Character generator, start address and data
void LCD_scanning_ports(void);
void LCD_scanning_results(void);
void LCD_loading_bar(void);
