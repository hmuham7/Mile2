/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "messages.h"
#include "debug.h"

static STATES parserstate = IDLE_STATE;
static size_t internalBufferIndex = 0;
static char internalCheckSum = 0;;
static size_t size = 0;

/**
 * Create a message using our format
 * @param buf destination for message
 * @param messageData data for the message
 * @param destination character for who message is sent to
 * @return length of the message
 */
int CreateMessage(char buf[], char messageData[], char destination, char messagecount) {
    dbgOutputLoc(ENTER_CREATEMESSAGE_MESSAGE_C);
    if (messageData == NULL) {
		//dbgOutputBlock(false);
	}
	memset(buf, 0, MAXMESSAGESIZE);
	// Pack message into string 'buf'
	// Format: start byte, destination, source, message count, data length (upper 8 bits), data length (lower 8 bits), data, checksum
	
	if (!INJECTERRORS) {
		size_t len = strlen(messageData);
		return sprintf(buf, "%c%c%c%c%c%c%s%c%c",
			STARTOFTEXT,
			destination,
			//MYMODULE,
			messagecount && 0xFF,
	        (len & 0xFF00) >> 8,
			len & 0x00FF,
			messageData,
			checksum(messageData),
			ENDOFTEXT
			);
	} else {
		char badMessage[256];
        int i;
        int len = strlen(messageData);

        /* remove bytes from message */
        for (i = 0; i < len - 1; i++) {
            badMessage[i] = messageData[i + 5];
        }

	    if(i < len) {
            badMessage[i] = '\0';
        }

        return sprintf(buf, "%c%c%c%c%c%c%s%c%c",
            STARTOFTEXT,
            destination,
            //MYMODULE,
            messagecount && 0xFF,
    		(len & 0xFF00) >> 8,
            len & 0x00FF,
            badMessage,
            checksum(messageData),
            ENDOFTEXT
            );
	}
	
    dbgOutputLoc(LEAVE_CREATEMESSAGE_MESSAGE_C);
}
// Simple string checksum
char checksum(char* s)
{
    dbgOutputLoc(ENTER_CHECKSUM_MESSAGE_C);
    char* temp = s;
	signed char sum = -1;
	while (*temp != 0)
	{
		sum += *temp;
		temp++;
	}
    dbgOutputLoc(LEAVE_CHECKSUM_MESSAGE_C);
	return sum;
}
