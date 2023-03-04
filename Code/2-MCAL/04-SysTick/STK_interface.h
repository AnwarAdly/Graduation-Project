/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 8/26/2020                                    */
/**********************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

/* Functions Prototypes */
void STK_voidInit(void); /*Apply required Clock source ,Disable SysTick interrupt and Disable SysTick */
void STK_voidSetBusyWait(u32 Copy_u32Ticks); // As a delay function , Synchronous Function
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks , void (*Copy_ptr)(void)); // Pointer to function That contain ISR when counts ends , Asynchronous Function
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr)(void)); // Asynchronous Function
void STK_voidStopInterval(void);
u32  STK_u32GetElapsedTime(void);
u32  STK_u32GetRemainingTime(void);

#endif