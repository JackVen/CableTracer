/***
 * Project name:			Cable Tracer
 * Project number:
 * File name:				ethernet.h
 * Description:				Implementation of buttons.h
 * Compiler
 * Controller:
 * Created:
 * SW version				1.0
 * Author:					Jack Venturi
***/

#include <stdint.h>
#include <stdbool.h>

struct Ethernet{

	int pin_connected[8];
	bool test_passed;

};

extern struct Ethernet ethernet;

#define ETHERNET_PIN_SIZE		   0x08
#define PIN_DISCONNECTED       0x00
#define PORTK_INPUT			   0x00
#define PIN_OFFSET			   0x01


//Inputs pins on RJ45
#define  RJ45_PIN1_IN  	 		0x01	 // White/Green
#define  RJ45_PIN2_IN  	 		0x02	 // Green solid
#define  RJ45_PIN3_IN    		0x04	 // White/Orange
#define  RJ45_PIN4_IN    		0x08	 // Blue solid
#define  RJ45_PIN5_IN    		0x10	 // White/Blue
#define  RJ45_PIN6_IN    		0x20	 // Orange solid
#define  RJ45_PIN7_IN    		0x40	 // White/Brown
#define  RJ45_PIN8_IN    		0x80	 // Brown
#define  RJ45_INPUT_SIDE 		0x00
#define  RJ45_INPUT_SIDE_RESET  0x00
#define  PU_ENABLE_ETHERNET     0xFF
#define  AS_INPUTS              0x00
// PIN names
#define  WHITE_GREEN			0x01
#define  GREEN_SOLID            0x02
#define  WHITE_ORANGE			0x03
#define  BLUE_SOLID				0x04
#define  WHITE_BLUE				0x05
#define  ORANGE_SOLID			0x06
#define  WHITE_BROWN			0x07
#define  BROWN					0x08
//Outputs pins on RJ45
#define  RJ45_PIN1_OUT     		0x04
#define  RJ45_PIN2_OUT 	 		0x08
#define  RJ45_PIN3_OUT 	 		0x01
#define  RJ45_PIN4_OUT 	 		0x02
#define  RJ45_PIN5_OUT      	0x01
#define  RJ45_PIN6_OUT      	0x02
#define  RJ45_PIN7_OUT      	0x01
#define  RJ45_PIN8_OUT      	0x02
#define  RJ45_PIN1_OUT_SET      0x04
#define  RJ45_PIN2_OUT_SET 	    0x08
#define  RJ45_PIN3_OUT_SET 	    0x01
#define  RJ45_PIN4_OUT_SET 	    0x02
#define  RJ45_PIN5_OUT_SET      0x01
#define  RJ45_PIN6_OUT_SET      0x02
#define  RJ45_PIN7_OUT_SET      0x01
#define  RJ45_PIN8_OUT_SET      0x02
#define  RJ45_HALFPINS_INPUT  	0x00
#define  RJ45_ALLPINS_RESET  	0x00
#define  SET_PINS_LOW           0x00

// All pins OK
#define ALL_PINS_OK				0xFF

// Function prototypes
void Ethernet_init(void);
void Ethernet_scan_wires(void);
