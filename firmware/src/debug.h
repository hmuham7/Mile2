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

void dbgOutputVal (unsigned char outVal);

void dbgOutputLoc (unsigned char outVal);

void dbgUARTVal( unsigned char outVal);

void error ();

#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */