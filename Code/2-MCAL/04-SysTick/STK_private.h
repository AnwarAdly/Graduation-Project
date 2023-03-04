/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 8/26/2020                                    */
/**********************************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

/* Register Definitions */
typedef struct {
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	volatile u32 CALIB;
}STK_t;
#define STK_Ptr ((volatile STK_t*) 0xE000E010)

/*   Bits Definitions   */
#define ENABLE     			   0
#define TICK_INT    		   1
#define CLK_SOURCE  		   2
#define COUNT_FLAG  		   16

/*  Clock Source Modes  */
#define AHB_8       		   0
#define AHB        			   1

/*   Interval Modes     */
#define STK_SINGLE_INTERVAL    0
#define STK_PERIOD_INTERVAL    1

/*   Global Variables   */
static void(*STK_CallBack)(void); // Define CallBack Global Variable
static u8 STK_u8ModeOfInterval;  // Define Global variable for interval mode

#endif