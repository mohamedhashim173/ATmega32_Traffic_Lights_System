/*
 * main.c
 *
 *  Created on: Sep 18, 2022
 *      Author: Mohamed Hashim Attiya Said
 */


#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"

void count_down(u8 time_end);


// 7-segment multiplexing, counter 1-99
void main(void)
{
	u8 rgb[3] = {
			0b00000001,		// green
			0b00000010,		// yellow
			0b00000100		// red
	};


	u8 arr[10] = {
			// DOT G F E D C B A
			0b00111111, // 0
			0b00000110, // 1
			0b01011011, // 2
			0b01001111, // 3
			0b01100110, // 4
			0b01101101, // 5
			0b01111101, // 6
			0b00000111, // 7
			0b01111111, // 8
			0b01101111  // 9
	};



	// PortA: 7-Segment Port
	DIO_voidSetPortDirection(DIO_u8PORTA, DIO_u8PORT_OUTPUT);

	// PortB: Selection Port
	DIO_voidSetPortDirection(DIO_u8PORTB, DIO_u8PORT_OUTPUT);

	// PortC: LEDs Port
	DIO_voidSetPortDirection(DIO_u8PORTC, DIO_u8PORT_OUTPUT);

	while(1)
	{
		// Green Light
		DIO_voidSetPortValue(DIO_u8PORTC, rgb[0]);
		count_down(10);

		// Yellow Light
		DIO_voidSetPortValue(DIO_u8PORTC, rgb[1]);
		count_down(3);

		// Red Light
		DIO_voidSetPortValue(DIO_u8PORTC, rgb[2]);
		count_down(10);
	}

}


// SSD count-down
void count_down(u8 time_end)
{
	u16 delay = 300;		// delay between counts
	u16 pov = 20;			// total delay of the two displays
	u16 complete1s = delay/pov;

	u8 arr[10] = {
			// DOT G F E D C B A
			0b00111111, // 0
			0b00000110, // 1
			0b01011011, // 2
			0b01001111, // 3
			0b01100110, // 4
			0b01101101, // 5
			0b01111101, // 6
			0b00000111, // 7
			0b01111111, // 8
			0b01101111  // 9
	};

	for(s8 i = time_end; i >= 0; i--)
	{

		for(s8 j = 0; j < complete1s; j++)
		{
			// SS Display 1
			DIO_voidSetPortValue(DIO_u8PORTA, arr[i % 10]);
			DIO_voidSetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_LOW);		// activate SSD1
			DIO_voidSetPinValue(DIO_u8PORTB, DIO_u8PIN1, DIO_u8PIN_HIGH);
			_delay_ms(pov/2);

			// SS Display 2
			DIO_voidSetPortValue(DIO_u8PORTA, arr[i / 10]);
			DIO_voidSetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_HIGH);
			DIO_voidSetPinValue(DIO_u8PORTB, DIO_u8PIN1, DIO_u8PIN_LOW);		// activate SSD2
			_delay_ms(pov/2);
		}
	}
}
