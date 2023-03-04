/******************************************************/
/*Auther name : Asmaa Ahmed   */
/*Date        : 1 jan 2021    */
/*verion      : 01            */
/******************************************************/
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

/* the control pins(E,RS,RW)*/
#define ENABLE_PIN                   GPIOB , 0
#define REGISTER_SELECT              GPIOB , 1

/*data pins*/
#define  DATA_PIN0                   GPIOA, 0
#define  DATA_PIN1                   GPIOA, 1
#define  DATA_PIN2                   GPIOA, 2
#define  DATA_PIN3                   GPIOA, 3
#define  DATA_PIN4                   GPIOA, 7
#define  DATA_PIN5                   GPIOA, 6
#define  DATA_PIN6                   GPIOA, 5
#define  DATA_PIN7                   GPIOA, 4

/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 		FOUR_BITS 

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == FOUR_BITS)
#define UPPER_PORT_PINS  // A4->A7 if it LOWEST A0->A3
#endif






#endif 