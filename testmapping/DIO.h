#ifndef _DIO_H_
#define _DIO_H_

#include"STD_LIB.h"
#include "Bit_Math.h"

// CONFIGRATIONS 

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3


#define Pin_0 0
#define Pin_1 1
#define Pin_2 2
#define Pin_3 3
#define Pin_4 4
#define Pin_5 5
#define Pin_6 6
#define Pin_7 7


#define Output 1
#define Input  0

#define HIGH 1
#define LOW  0



// PRIVATE 

// Register of port A
#define _PORTA   *((volatile u8*)0x3B)
#define _DDRA    *((volatile u8*)0x3A)
#define _PINA    *((volatile u8*)0x39)

// Register of port B
#define _PORTB   *((volatile u8*)0x38)
#define _DDRB	 *((volatile u8*)0x37)
#define _PINB	 *((volatile u8*)0x36)

// Register of port C
#define _PORTC	 *((volatile u8*)0x35)
#define _DDRC	 *((volatile u8*)0x34)
#define _PINC	 *((volatile u8*)0x33)

// Register of port D
#define _PORTD	 *((volatile u8*)0x32)
#define _DDRD	 *((volatile u8*)0x31)
#define _PIND	 *((volatile u8*)0x30)





// FUNCTIONS 

void Set_PinDirection (u8 Copy_Port , u8 Copy_Pin , u8 Copy_Direction);
void Set_PinValue (u8 Copy_Port , u8 Copy_Pin , u8 Copy_Value);
void DIO_voidPinToggle(u8 Copy_Port , u8 Copy_Pin);
u8 Get_PinValue(u8 Copy_Port , u8 Copy_Pin);


void Set_PortDirection(u8 Copy_Port , u8 Copy_Direction);
void Set_PortValue    (u8 Copy_Port , u8 Copy_Value);


#endif // _DIO_H_
