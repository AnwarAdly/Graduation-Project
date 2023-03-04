/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/20/2020                                    */
/**********************************************************/

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

/*  Register Definitions    */
typedef struct{

	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;

}USART_Type;
#define MUSART1 ( ( volatile USART_Type* ) 0x40013800 )

/* Global Variables   */
void (*MUSART1_CallBack)(void);

#endif 
