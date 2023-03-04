/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 8/15/2020                                    */
/**********************************************************/

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/* Register Definitions */
typedef struct{

	volatile u32 CRL  ;//0x00
	volatile u32 CRH  ;//0x04
	volatile u32 IDR  ;//0x08
	volatile u32 ODR  ;
	volatile u32 BSRR ;
	volatile u32 BRR  ;
	volatile u32 LCKR ;

}GPIO;

#define MGPIOA ((volatile GPIO*)0x40010800)
#define MGPIOB ((volatile GPIO*)0x40010C00)
#define MGPIOC ((volatile GPIO*)0x40011000)

#endif