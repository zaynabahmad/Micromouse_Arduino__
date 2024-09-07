/**
*/

#include "DIO.h"



void Set_PinDirection(u8 Copy_Port,u8 Copy_Pin,u8 Copy_Direction)
{
	if(Copy_Direction == Output)
	{
		switch(Copy_Port)
		{
		case PORT_A : Set_Bit(_DDRA,Copy_Pin); break;
		case PORT_B : Set_Bit(_DDRB,Copy_Pin); break;
		case PORT_C : Set_Bit(_DDRC,Copy_Pin); break;
		case PORT_D : Set_Bit(_DDRD,Copy_Pin); break;
		}
	}
	else if(Copy_Direction == Input)
	{
		switch(Copy_Port)
		{
		case PORT_A : Clr_Bit(_DDRA,Copy_Pin); break;
		case PORT_B : Clr_Bit(_DDRB,Copy_Pin); break;
		case PORT_C : Clr_Bit(_DDRC,Copy_Pin); break;
		case PORT_D : Clr_Bit(_DDRD,Copy_Pin); break;
		}
	}
}

/**/
void Set_PinValue(u8 Copy_Port, u8 Copy_Pin, u8 Copy_Value)
{
	switch (Copy_Port)
	{
	case PORT_A:
		if (Copy_Value==LOW)
		{
			Clr_Bit(_PORTA, Copy_Pin);
		}
		else if (Copy_Value==HIGH)
		{
			Set_Bit(_PORTA, Copy_Pin);
		}
		break;
	case PORT_B:

		if (Copy_Value==LOW)
		{
			Clr_Bit(_PORTB, Copy_Pin);
		}
		else if (Copy_Value==HIGH)
		{
			Set_Bit(_PORTB, Copy_Pin);
		}
		break;

	case PORT_C:
		if (Copy_Value==LOW)
		{
			Clr_Bit(_PORTC, Copy_Pin);
		}
		else if (Copy_Value==HIGH)
		{
			Set_Bit(_PORTC, Copy_Pin);
		}
		break;
	case PORT_D:
		if (Copy_Value==LOW)
		{
			Clr_Bit(_PORTD, Copy_Pin);
		}
		else if (Copy_Value==HIGH)
		{
			Set_Bit(_PORTD, Copy_Pin);
		}

		break;
	}

}

void DIO_voidPinToggle(u8 Copy_Port , u8 Copy_Pin)
{
	switch(Copy_Port)
	{
	case PORT_A : Toggle_Bit(_DDRA,Copy_Pin); break;
	case PORT_B : Toggle_Bit(_DDRB,Copy_Pin); break;
	case PORT_C : Toggle_Bit(_DDRC,Copy_Pin); break;
	case PORT_D : Toggle_Bit(_DDRD,Copy_Pin); break;
	}
}

u8 Get_PinValue(u8 Copy_Port,u8 Copy_Pin)
{
	u8 Local_var ;
	switch(Copy_Port)
	{
	case PORT_A: Local_var = Get_Bit(_PINA,Copy_Pin); break;
	case PORT_B: Local_var = Get_Bit(_PINB,Copy_Pin); break;
	case PORT_C: Local_var = Get_Bit(_PINC,Copy_Pin); break;
	case PORT_D: Local_var = Get_Bit(_PIND,Copy_Pin); break;
	}

	return Local_var ;
}




void Set_PortDirection(u8 Copy_Port , u8 Copy_Direction)
{
	switch(Copy_Port)
	{
	case PORT_A : _DDRA = Copy_Direction; break;
	case PORT_B : _DDRB = Copy_Direction; break;
	case PORT_C : _DDRC = Copy_Direction; break;
	case PORT_D : _DDRD = Copy_Direction; break;
	}
}


void Set_PortValue    (u8 Copy_Port , u8 Copy_Value)
{
	switch(Copy_Port)
	{
	case PORT_A : _PORTA = Copy_Value; break;
	case PORT_B : _PORTB = Copy_Value; break;
	case PORT_C : _PORTC = Copy_Value; break;
	case PORT_D : _PORTD = Copy_Value; break;
	}
}

