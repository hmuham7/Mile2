/* 
 * File:   app_public.h
 * Author: Muhammad
 *
 * Created on February 16, 2017, 12:10 AM
 */
#ifndef _APP_PUBLIC_H
#define _APP_PUBLIC_H

/*TODO: single message type for each queue*/

/*An enum describing from where the message originates*/
typedef enum {
    S_Timer = 0,
    S_Encoder,
    S_Control,
    S_Motor,
    S_UART
} SOURCE;

/*An enum describing the intended destination of the message*/
typedef enum {
    Timer = 0,
    Encoder,
    Control,
    Motor,
    UART
} DEST;

/*CONTROL_MSG
 * Any message sent to the control queue
 *
 * change in distance calculated from the encoders
 *
 * int encoder1Val  - encoder
 * int encoder2Val  - encoder
 * int orientation : head 1 = original orientation, 2 = reverse - encoder
 * int sensorData[8] - timer
 * int mapInfo - uart
 * */
typedef struct{
    int encoder1Val;
    int encoder2Val;
    int orientation;
    int sensorData[8];
    int mapInfo;
}CONTROL_MSG;

/*ENCODER_MSG
 * The message to be sent from the Encoder Interrupt to the Encoder Queue
 *
 * int encoderVal
 * */
typedef struct{
    int encoderVal;

}ENCODER_MSG;
  
/*CONTROL_ENCODER_MSG
 * Message to be sent from Control thread to Encoder Queue
 *
 * int MotorSignal
 * */
typedef struct{
    int MotorSignal;

}CONTROL_ENCODER_MSG;
  
  
/*CONTROL_RECEIVE_MSG
 * Message to be sent from Control thread to UARTreceive queue
 *
 * bool operation = 0 : Tx = 0, Rx = 0
 * int mapInfo : this will most likely be changed as it is determined what exactly needs to be sent to the R-tau/2 (Rpi)
 * */
typedef struct{
    bool operation;
    int mapInfo;
}CONTROL_RECEIVE_MSG;

/*UART_TRANSMIT_MSG
 * Message to be sent from UART thread to UARTtransmit queue
 *
 * int mapInfo : see above
 * */
typedef struct{
    int mapInfo;
}UART_TRANSMIT_MSG;

/*NETWORK_MESSAGE is a struct that contains the structure for all messages
 * to be sent over WiFi
 *
 * startID and endID are 4 bytes each
 * seqNumber should start at 1 and is 2 bytes
 * the SOURCE and DEST are 4 bytes eachj
 *
 * */
typedef struct {
    char startID[4]; // "&&&&";
    short seqNumber;  
    SOURCE msgSource;   
    DEST msgDest;   
    UART_TRANSMIT_MSG message;
    char endID[4]; // = "&&&&";
}NETWORK_MESSAGE;


/*NOTE: sendMsg functions must be implemented in the .c file of where the receiving Queue exists*/

//void appSendTimerValtoMsgQ(void); // declaration of function which is in app.c

/*sendMsgToControlQueue
 * send a message to the control queue
 * implementation in control.c */
void sendMsgToControlQueue(CONTROL_MSG msgToSend);

/*sendMsgToControlQueue_FromISR
 * send a message to the Control Queue from an interrupt
 * implementation in control.c */
void sendMsgToControlQueue_FromISR(CONTROL_MSG msgToSend);

/*sendMsgToEncoder1Queue
 * send a message from the control thread to the encoder queue
 * implementation in motor.c */
void sendMsgToEncoder1Queue(CONTROL_ENCODER_MSG msgToSend);

/*sendMsgToEncoder2Queue
 * send a message from control thread to encoder queue
 * implementation in motor.c */
void sendMsgToEncoder2Queue(CONTROL_ENCODER_MSG msgToSend);

/*sendMsgToEncoder1Queue_FromISR
 * send a message from the encoder isr to the encoder queue
 * implementation in motor.c */
void sendMsgToEncoder1Queue_FromISR(ENCODER_MSG msgToSend);

/*sendMsgToEncoder2Queue_FromISR
 * send a message from the encoder isr to the encoder queue
 * implementation in motor.c */
void sendMsgToEncoder2Queue_FromISR(ENCODER_MSG msgToSend);

void sendMsgToUARTQueue(uint32_t ADCin);    //in uart_tx.c

#endif // _APP_PUBLIC_H
#endif	/* APP_PUBLIC_H */

