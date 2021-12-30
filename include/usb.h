/***
 * Project name:			Cable Tracer
 * Project number:
 * File name:				usb.h
 * Description:				usb implementation.h
 * Compiler
 * Controller:
 * Created:
 * SW version				1.0
 * Author:					Jack Venturi
***/

#include <stdint.h>
#include <stdbool.h>

struct USB{

	int pin_connected[4];
	bool test_passed;

};

extern struct USB usb;

#define USB_PIN_SIZE		   0x04
#define PIN_DISCONNECTED       0x00

#define PIN_OFFSET			   0x01
#define GND					   0x01
#define VBUS				   0x02
#define DP					   0x03
#define DM					   0x04


//Pins on USB C PORT
#define  USB_C_DP_IN    		0x08
#define  USB_C_DN_IN    		0x04
#define  USB_C_VBUS_IN    		0x02
#define  USB_C_GND_IN    		0x01
#define  AS_INPUTS              0x00


//Pins on USB A PORT
#define  USB_A_DP_OUT    		0x08
#define  USB_A_DN_OUT  	 		0x04
#define  USB_A_VBUS_OUT 	 	0x02
#define  USB_A_GND_OUT 	 		0x01
#define  AS_OUTPUTS             0x0F
#define  PU_ENABLE              0x0F
#define  SET_PINS_LOW           0x00


// All pins OK
#define ALL_USB_PINS_OK			0xFF

// Function prototypes
void Usb_init(void);
void Usb_scan_wires(void);

