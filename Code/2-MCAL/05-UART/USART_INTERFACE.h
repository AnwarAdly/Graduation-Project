/**********************************************************/
/* Author  : Anwar Ahmad                                  */
/* Version : 01                                           */
/* Date    : 9/20/2020                                    */
/**********************************************************/

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H


#define USART1_DISABLE          0
#define USART1_ENABLE           1

#define _8BIT_WORD_LENGTH       0
#define _9BIT_WORD_LENGTH       1

#define PARITY_DISABLE          0
#define EVEN_PARITY             1
#define ODD_PARITY              2

#define INT_DISABLE             0
#define TXE_INT_ENABLE          1
#define TCE_INT_ENABLE          3
#define RXNE_INT_ENABLE         5

#define TRANSMITTER_DISABLE     0
#define TRANSMITTER_ENABLE      1

#define RECEIVER_DISBLE         0
#define RECEIVER_ENABLE         1

#define ONE_STOP_BIT            0
#define HALF_STOP_BIT           1
#define TWO_STOP_BIT            2
#define ONE_AND_HALF_STOP_BIT   3

/* Function Prototypes  */
void MUSART_voidInit            ( void                ) ;
void MUSART1_voidSendChar       ( u8 Copy_u8Char      ) ;
void MUSART1_voidSendString     ( u8 * Copy_ptrString ) ;
u8   MUSART1_u8RecChar          ( void                ) ;
u8 * MUSART1_PtrReadString      ( u8 * Copy_ptrString ) ;
void MUSART1_voidClearFlags     ( void                ) ;
u8   MUSART1_u8ReadDataRegister ( void                ) ;
void MUSART1_voidSetCallBack    ( void (*ptr) (void)  ) ;

#endif /* USART_INTERFACE_H_ */
