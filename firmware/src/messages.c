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

bool ParseMessage(char c, char data[], char* source, char* messageCount, bool *isError) {
    dbgOutputLoc(ENTER_PARSEMESSAGE_MESSAGE_C);
	switch (parserstate) {
	case IDLE_STATE: {
        dbgOutputLoc(CASE_IDLE_STATE_PARSEMESSAGE_MESSAGE_C);
        *isError = false;
		internalBufferIndex = 0;
		internalCheckSum = NULL;
		size = 0;
		memset(data, 0, MAXMESSAGESIZE);
		if (c == STARTOFTEXT) {
			parserstate = CHECK_DESTINATION_CHAR;
		}
		return false;
	}
	case CHECK_DESTINATION_CHAR: {
        *isError = false;
        dbgOutputLoc(CASE_CHECK_DESTINATION_CHAR_PARSEMESSAGE_MESSAGE_C);
        if (c == MYMODULE) {
			parserstate = CHECK_SOURCE_CHAR;
		}
        else {
            parserstate = IDLE_STATE;
        }
		return false;
	}
    case CHECK_SOURCE_CHAR: {
        dbgOutputLoc(CASE_CHECK_SOURCE_CHAR_PARSEMESSAGE_MESSAGE_C);
        switch(c) {
            case SENSOR_ROVER: {
                *source = SENSOR_ROVER;
                break;
            }
            case TAG_ROVER: {
                *source = TAG_ROVER;
                break;
            }
            case FLAG_ROVER: {
                *source = FLAG_ROVER;
                break;
            }
            case COUNTERMEASURE_ROVER: {
                *source = COUNTERMEASURE_ROVER;
                break;
            }
            case SERVER: {
                *source = SERVER;
                break;
            }
            default: {
                *isError = true;
                parserstate = IDLE_STATE;
                return false;
            }
            return false;
        }
        parserstate = CHECK_MESSAGE_COUNT;
        return false;
    }
	case CHECK_MESSAGE_COUNT: {
        dbgOutputLoc(CASE_CHECK_MESSAGE_COUNT_PARSEMESSAGE_MESSAGE_C);
        parserstate = GET_DATALENGTH_UPPER;
        //Pass the message count back
        *messageCount = c;
		return false;
	}
	case GET_DATALENGTH_UPPER: {
        dbgOutputLoc(CASE_GET_DATALENGTH_UPPER_PARSEMESSAGE_MESSAGE_C);
        size = (c & 0xFF) << 8;
		parserstate = GET_DATALENGTH_LOWER;
		return false;
	}
	case GET_DATALENGTH_LOWER: {
        dbgOutputLoc(CASE_GET_DATALENGTH_LOWER_PARSEMESSAGE_MESSAGE_C);
        size = size | (c & 0x00FF);
        if(size > (MAXMESSAGESIZE - 8)) {
            parserstate = IDLE_STATE;
            *isError = true;
            return false;
        }
		parserstate = GET_DATA;
		return false;
	}
	case GET_DATA: {
        dbgOutputLoc(CASE_GET_DATA_PARSEMESSAGE_MESSAGE_C);
        data[internalBufferIndex] = c;
		internalBufferIndex = internalBufferIndex + 1;
        dbgOutputLoc(BEFORE_FIRST_IF_GET_DATA_PARSEMESSAGE_MESSAGE_C);
        if (internalBufferIndex >= size || internalBufferIndex >= MAXMESSAGESIZE) {
			parserstate = GET_CHECK_SUM;
            internalBufferIndex = 0;
		}
        if(c == STARTOFTEXT) {
            *isError = true;
            parserstate = CHECK_DESTINATION_CHAR;
        }
        if(c == ENDOFTEXT) {
            *isError = true;
            parserstate = IDLE_STATE;
        }
        dbgOutputLoc(AFTER_THIRD_IF_GET_DATA_PARSEMESSAGE_MESSAGE_C);
		return false;
	}
	case GET_CHECK_SUM: {
        dbgOutputLoc(CASE_GET_CHECK_SUM_PARSEMESSAGE_MESSAGE_C);
        internalCheckSum = c;
		if (internalCheckSum != checksum(data)) {
            *isError = true;
			parserstate = IDLE_STATE;
		}
		else {
            parserstate = CHECK_ENDCHAR;
        }
		return false;
	}
	case CHECK_ENDCHAR: {
        dbgOutputLoc(CASE_CHECK_ENDCHAR_PARSEMESSAGE_MESSAGE_C);
        parserstate = IDLE_STATE;
        *isError = c != ENDOFTEXT;
		return !(*isError);
	}
	}
    dbgOutputLoc(LEAVE_PARSEMESSAGE_MESSAGE_C);
}

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
