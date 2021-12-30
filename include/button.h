/*
 * Project name:			Cable Tracer
 * Project number:
 * File name:				button.h
 * Description:				Implementation of buttons.h
 * Compiler
 * Controller:
 * Created:
 * SW version				1.0
 * Author:					Jack Venturi
*/


#ifndef BUTTON_H_
#define BUTTON_H_

/*
 * Button Port, de-bounce limit, etc
 */
#define	FIVE			0x00	// Any change on any enabled PCINT [7:0] will cause an interrupt
#define	DEBOUNCE_LIM	0x01

// Function Prototypes
void Button_init(void);


#endif /* BUTTONS_H_ */
