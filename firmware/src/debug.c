/* 
 * File:   debug.c
 * Author: Team8
 *
 *
 */
#include "debug.h"

// Routine to output value of "Team 8" characters to 8 PIC i/o lines.
void dbgOutputVal (unsigned char outVal)
{
    if (outVal & 0x01) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6);
    }
    if (outVal & 0x02) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1);
    }
    if (outVal & 0x04) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0);
    }
    if (outVal & 0x08) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10);
    }
    if (outVal & 0x10) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8);
    }
    if (outVal & 0x20) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12);
    }
    if (outVal & 0x40) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13);
    }
    if (outVal & 0x80) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11);
    }
}
/* 
 * This Routine writes data to the E channel, which all appear adjacent to each other on the board. 
 */ 
void dbgOutputLoc (unsigned char outVal)
{
    //PLIB_PORTS_Set (PORTS_ID_0, PORT_CHANNEL_E, outVal, 0x00FF);
    
    if (outVal & 0x01) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_0);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_0);
    }
    if (outVal & 0x02) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1);
    }
    if (outVal & 0x04) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2);
    }
    if (outVal & 0x08) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3);
    }
    if (outVal & 0x10) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_4);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_4);
    }
    if (outVal & 0x20) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_5);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_5);
    }
    if (outVal & 0x40) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6);
    }
    if (outVal & 0x80) {
        PLIB_PORTS_PinSet (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7);
    }
    else {
        PLIB_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7);
    }
}

void dbgUARTVal( unsigned char outVal)
{
    DRV_USART0_WriteByte(outVal);
}
void error ()
{
    dbgOutputLoc(ERROR);
    while (1);
}

/*
void dbgUARTVal (unsigned char outVal)
{
    DRV_USART_WriteByte(debugData.uart_txrx1, outVal);
}
*/

