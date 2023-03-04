/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 8/22/2020                                    */
/**********************************************************/



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_INTERFACE.h"
#include "NVIC_PRIVATE.h"
#include "NVIC_CONFIG.h"


void MNVIC_voidEnablePeripheral ( u8 Copy_u8INTID ){
	MNVIC->ISER[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;
}

void MNVIC_voidDisablePeripheral ( u8 Copy_u8INTID ){
	MNVIC->ICER[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;
}

void MNVIC_voidSetPending ( u8 Copy_u8INTID ){
	MNVIC->ISPR[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;
}

void MNVIC_voidClearPending ( u8 Copy_u8INTID ){
	MNVIC->ICPR[ Copy_u8INTID / 32 ] = 1 << ( Copy_u8INTID % 32 ) ;
}

u8   MNVIC_u8GetActive( u8 Copy_u8INTID ){
	u8 LOC_u8Active = GET_BIT( (MNVIC->IABR[ Copy_u8INTID/32 ]) , ( Copy_u8INTID % 32 ) );
	return LOC_u8Active ;
}


void MNVIC_voidSetPriority( s8 Copy_s8INTID , u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority , u32 Copy_u32PriorityMode ){
	/*Example1 : 	write in 00??0000	write in ??000000	   0x05FA0400(3G & 1sub)-0x05FA0300=0x100=256/256=1		*/
	/*Example2 : 	write in 00??0000	write in ??000000	   0x05FA0500(2G & 2sub)-0x05FA0300=0x200=512/256=2		*/
	u8 Priority =  Copy_u8SubPriority | Copy_u8GroupPriority << ( (Copy_u32PriorityMode - 0x05FA0300) / 256 )  ; //256=0x100
	//Core Peripheral
	if( Copy_s8INTID < 0  ){

		if( Copy_s8INTID == MEMORY_MANAGE || Copy_s8INTID == BUS_FAULT || Copy_s8INTID == USAGE_FAULT ){

			Copy_s8INTID += 3;
			SCB->SHPR1 = ( Priority ) << ( (8 * Copy_s8INTID) + 4 );

		}
		else if ( Copy_s8INTID == SV_CALL ){

			Copy_s8INTID += 7;
			SCB->SHPR2 = ( Priority ) << ( (8 * Copy_s8INTID) + 4 );

		}
		else if( Copy_s8INTID == PEND_SV || Copy_s8INTID == SYSTICK ){

			Copy_s8INTID += 8;

			SCB->SHPR3 = ( Priority ) << ( (8 * Copy_s8INTID) + 4 );

		}

	}
    //External Peripheral
	else if( Copy_s8INTID >= 0 ){

		MNVIC->IPR[ Copy_s8INTID ] = Priority << 4 ; //To put bits in MSBs

	}

	SCB->AIRCR = Copy_u32PriorityMode ;

}

