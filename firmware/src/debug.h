/* 
 * File:   debug.h
 * Author: Team8
 *
 *
 */

#include "system_config.h"
#include "system_definitions.h"

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define ENTER_TASK     0x01
#define BEFORE_WHILE   0x02
#define BEFORE_SEND    0x03
#define BEFORE_RECEIVE 0x04
#define AFTER_SEND     0x05
#define AFTER_RECEIVE  0x06
#define ENTER_ISR      0x07
#define LEAVE_ISR      0x08
#define UART           0x09
#define ERROR          0xFF
    
#define ENTER_USART0_ISR                       0x11
#define LEAVE_USART0_ISR                       0x12
#define BEFORE_SEND_TO_QUEUE_USART0_ISR        0x13
#define AFTER_SEND_TO_QUEUE_USART0_ISR         0x14
#define BEFORE_RECEIVE_FR_QUEUE_USART0_ISR     0x15
#define AFTER_RECEIVE_FR_QUEUE_USART0_ISR      0x16
    
#define ENTER_RXTHREAD                                  0x21
#define LEAVE_RXTHREAD                                  0x22
#define BEFORE_WHILELOOP_RXTHREAD                       0x23
#define BEFORE_SEND_TO_QUEUE_RXTHREAD                   0x24
#define AFTER_SEND_TO_QUEUE_RXTHREAD                    0x25
#define BEFORE_RECEIVE_FR_QUEUE_RXTHREAD                0x26
#define AFTER_RECEIVE_FR_QUEUE_RXTHREAD                 0x27
#define BEFORE_RECEIVE_FR_QUEUE_READFROMQUEUE_RXTHREAD  0x28
#define AFTER_RECEIVE_FR_QUEUE_READFROMQUEUE_RXTHREAD   0x29
    
#define ENTER_TXTHREAD                      0x31
#define BEFORE_WHILELOOP_TXTHREAD           0x32
#define BEFORE_SEND_TO_QUEUE_TXTHREAD       0x33
#define AFTER_SEND_TO_QUEUE_TXTHREAD        0x34
#define BEFORE_RECEIVE_FR_QUEUE_TXTHREAD    0x35
#define AFTER_RECEIVE_FR_QUEUE_TXTHREAD     0x36
    

void dbgOutputVal (unsigned char outVal);

void dbgOutputLoc (unsigned char outVal);

void dbgUARTVal( unsigned char outVal);

void dbgPinsDirection();

void dbgOutputBlock(int outVal);

void dbgOutputBlockISR(int outVal);

void error ();

#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */