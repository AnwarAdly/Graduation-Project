/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 8/22/2020                                    */
/**********************************************************/

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#define NO_SUB_PRIORITY 0

/*  Priority Modes      */
#define GROUP3     0x05FA0300 //0 bit for sub & 4 bit For group   << 0
#define GROUP4     0x05FA0400 //1 bit for sub & 3 bit For group   << 1
#define GROUP5     0x05FA0500 //2 bit for sub & 2 bit For group   << 2
#define GROUP6     0x05FA0600 //3 bit for sub & 1 bit For group   << 3
#define GROUP7     0x05FA0700 //4 bit for sub & 0 bit For group   << 4

//#define For Interrupt ID =  Position In Vector Table
#define PEND_SV        -6
#define SYSTICK        -5
#define SV_CALL        -4
#define MEMORY_MANAGE  -3
#define BUS_FAULT      -2
#define USAGE_FAULT    -1
#define WWDG   			0
#define EXT0   			6
#define EXT1   			7
#define DMA_ID 			11

/* Functions Prototypes */
void MNVIC_voidEnablePeripheral  ( u8 Copy_u8INTID );
void MNVIC_voidDisablePeripheral ( u8 Copy_u8INTID );
void MNVIC_voidSetPending        ( u8 Copy_u8INTID );
void MNVIC_voidClearPending      ( u8 Copy_u8INTID );
u8   MNVIC_u8GetActive           ( u8 Copy_u8INTID );
void MNVIC_voidSetPriority( s8 Copy_s8INTID , u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority , u32 Copy_u32PriorityMode );

#endif /* NVIC_INTERFACE_H_ */
