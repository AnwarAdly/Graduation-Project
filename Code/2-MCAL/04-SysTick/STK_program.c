/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 8/26/2020                                    */
/**********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

void STK_voidInit(){
	CLR_BIT(STK_Ptr ->CTRL,TICK_INT); // Disable Interrupt 
	CLR_BIT(STK_Ptr ->CTRL,ENABLE);   // Disable Timer
	#if SYSTICK_CLKSOURCE == AHB_8
	CLR_BIT(STK_Ptr ->CTRL,CLK_SOURCE);
	#elif SYSTICK_CLKSOURCE == AHB
	SET_BIT(STK_Ptr ->CTRL,CLK_SOURCE);
	#endif
}
void STK_voidSetBusyWait(u32 Copy_u32Ticks){
	STK_Ptr ->LOAD = Copy_u32Ticks;
	SET_BIT(STK_Ptr ->CTRL,ENABLE); 				 // Start Timer
	while ((GET_BIT(STK_Ptr ->CTRL,COUNT_FLAG))==0); // Wait till flag is set
	CLR_BIT(STK_Ptr ->CTRL,ENABLE); 				 // Stop Timer
	STK_Ptr -> LOAD = 0;
	STK_Ptr -> VAL  = 0;	
}
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks , void (*Copy_ptr)(void)){
	CLR_BIT(STK_Ptr ->CTRL,ENABLE);   			// Stop Timer
	STK_Ptr -> VAL = 0;	
	STK_Ptr -> LOAD = Copy_u32Ticks;
	SET_BIT(STK_Ptr ->CTRL,ENABLE);   			// Start Timer
    STK_CallBack = Copy_ptr;           			// Save CallBack function
    STK_u8ModeOfInterval = STK_SINGLE_INTERVAL; // Set Mode to Single
	SET_BIT(STK_Ptr ->CTRL,TICK_INT); 			// Enable Interrupt
}
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr)(void)){
	STK_Ptr ->LOAD = Copy_u32Ticks;
	SET_BIT(STK_Ptr ->CTRL,ENABLE);   			// Start Timer
    STK_CallBack = Copy_ptr;           			// Save CallBack function
    STK_u8ModeOfInterval = STK_PERIOD_INTERVAL; // Set Mode to Period
	SET_BIT(STK_Ptr ->CTRL,TICK_INT); 			// Enable Interrupt	
}
void STK_voidStopInterval(void){
	CLR_BIT(STK_Ptr ->CTRL,TICK_INT); // Disable Interrupt 
	CLR_BIT(STK_Ptr ->CTRL,ENABLE);   // Stop Timer
	STK_Ptr -> LOAD = 0;
	STK_Ptr -> VAL  = 0;	
}
u32  STK_u32GetElapsedTime(void){
	u32 Local_u32ElapsedTime = 0;
	Local_u32ElapsedTime = (STK_Ptr ->LOAD) - (STK_Ptr ->VAL);
	return Local_u32ElapsedTime;
}
u32  STK_u32GetRemainingTime(void){
	u32 Local_u32RemainingTime = 0;
	Local_u32RemainingTime = (STK_Ptr ->VAL);
	return Local_u32RemainingTime;
}
void SysTick_Handler(void){
	u8 Local_u8Temporary;
	if (STK_u8ModeOfInterval == STK_SINGLE_INTERVAL){
		CLR_BIT(STK_Ptr ->CTRL,TICK_INT); // Disable Interrupt 
        CLR_BIT(STK_Ptr ->CTRL,ENABLE);   // Stop Timer
	    STK_Ptr -> LOAD = 0;
	    STK_Ptr -> VAL  = 0;
	}	
	STK_CallBack(); // Callback notification
	Local_u8Temporary = GET_BIT(STK_Ptr -> CTRL,COUNT_FLAG); // Clear interrupt flag
}
