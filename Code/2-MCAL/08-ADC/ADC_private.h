/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/11/2020                                    */
/**********************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/*  Register Definitions  */
typedef struct{
	volatile u32 SR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMPR[2];
	volatile u32 JOFR[4];
	volatile u32 HTR;
	volatile u32 LTR;
	volatile u32 SQR[3];
	volatile u32 JSQR;
	volatile u32 JDR[4];
	volatile u32 DR;
}ADC_TYPE;

#define ADC1 ((ADC_TYPE*)0x40012400)
#define ADC2 ((ADC_TYPE*)0x40012800)
#define ADC3 ((ADC_TYPE*)0x40013C00)

/* Global Variables   */
static void (*ADC1_voidAWDCallBack) (void);
static void (*ADC1_voidEOCCallBack) (void);

#endif
