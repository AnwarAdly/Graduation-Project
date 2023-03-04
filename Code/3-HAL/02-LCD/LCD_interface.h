/******************************************************/
/* Author    : Asmaa Ahmed                            */
/* Date      : 18 jan 2021                            */
/* Version   : V01                                    */
/******************************************************/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define GPIOA_CRL                 *((u32*)(GPIOA_Base_Address + 0x00))
#define GPIOA_CRH                 *((u32*)(GPIOA_Base_Address + 0x04))
#define GPIOA_BRR                 *((u32*)(GPIOA_Base_Address + 0x14))
#define GPIOA_BSRR                *((u32*)(GPIOA_Base_Address + 0x10))   /* FROM Bits 15:0 0: No action on the corresponding ODRx bit , 1: Set the corresponding ODRx bit*/
#define GPIOA_ODR                 *((u32*)(GPIOA_Base_Address + 0x0c))

#define GPIOA_Base_Address ((volatile u32*)0x40010800)

/* LCD Commands */
#define CLEAR_COMMAND					0x01
#define FOUR_BITS_DATA_MODE		   		0x20
#define TWO_LINE_LCD_Four_BIT_MODE  	0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 	0x38
#define CURSOR_OFF						0x0C
#define CURSOR_ON						0x0E
#define SET_CURSOR_LOCATION_FIRST_LINE	0x80
#define SET_CURSOR_LOCATION_SECOND_LINE	0xC0

#define FOUR_BITS  4
#define EIGHT_BITS 8

void HLCD_voidInit(void);
void HLCD_voidDisplayCharacter(u8 data);
void HLCD_voidDisplayString(const char *Str);
void HLCD_voidSendCommand(u8 command); 
void HLCD_voidClearScreen(void);
void HLCD_voidDisplayStringRowColumn(u8 row,u8 col,const char *Str);
void HLCD_voidGoToRowColumn(u8 row,u8 col);
void HLCD_voidIntgerToString(int data);



#endif