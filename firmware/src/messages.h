/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _MESSAGELAYER_H    /* Guard against multiple inclusion */
#define _MESSAGELAYER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTOFTEXT 0x02
#define ENDOFTEXT 0x03
#define MAXMESSAGESIZE 300
#define SENSOR_ROVER 'SR'
#define TAG_ROVER 'TR'
#define FLAG_ROVER 'FR'
#define COUNTERMEASURE_ROVER 'CMR'
#define SERVER 'S'
#define MYMODULE SENSOR_ROVER
#define MYMODULESTRING "sensorrover"

#define INJECTERRORS 0

int CreateMessage(char buf[], char messageData[], char destination, char messagecount);

void BuildJSON(char buf[]);

char checksum(char* s);

typedef enum {
    IDLE_STATE,
    CHECK_DESTINATION_CHAR,
    CHECK_SOURCE_CHAR,
    CHECK_MESSAGE_COUNT,
    GET_DATALENGTH_UPPER,
    GET_DATALENGTH_LOWER,
    GET_DATA,
    GET_CHECK_SUM,
    CHECK_ENDCHAR,
} STATES;

bool ParseMessage(char c, char data[], char* source, char* messageCount, bool *isError);

#endif /* _MESSAGELAYER_H */

/* *****************************************************************************
 End of File
 */
