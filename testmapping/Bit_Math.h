#ifndef SERVICES_BIT_MATH_H_
#define SERVICES_BIT_MATH_H_


#define Set_Bit(Register,Bit_Number)      (Register |= (1<<Bit_Number))
#define Clr_Bit(Register,Bit_Number)      (Register &=~ (1<<Bit_Number))
#define Toggle_Bit(Register,Bit_Number)   (Register ^= (1<<Bit_Number))
#define Get_Bit(Register,Bit_Number)      ((Register>>Bit_Number) & 0b00000001)

#endif /* SERVICES_BIT_MATH_H_ */
