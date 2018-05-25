#ifndef _UART_H    /* Guard against multiple inclusion */
#define _UART_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "fifoBuffer.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */
#define TRANSMIT    1
#define RECEIVE     0   

#define ETH_        0
#define KIFI_       1   
#define BOTH_       1     

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef struct {
        BUFFER_TYPE uartTransmitBuffer;
        BUFFER_TYPE uartReceiveBuffer;

        unsigned char commandHandlerState;
        unsigned char command;
        unsigned char dataSize;
        unsigned char lenght;
        unsigned char dataCount;
        unsigned char oldData;
        unsigned char crcLenght;
        unsigned short receivedCRC;
        unsigned short calculatedCRC;

        BUFFER_TYPE messageBuffer;
        BUFFER_TYPE transmitDataBuffer;
        BUFFER_TYPE receivedDataBuffer;

        unsigned char receivedCommand;
        BUFFER_TYPE commandDataBuffer;
    } UART_DATA_TYPE;
    
    
    

    extern volatile UART_DATA_TYPE UART_1;
    extern volatile UART_DATA_TYPE UART_2;
    extern volatile UART_DATA_TYPE UART_5;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    void USART_1_Initialize(const SYS_MODULE_INDEX index);
    void USART_1_ReceiveEventHandler(const SYS_MODULE_INDEX index);
    void USART_1_TransmitEventHandler(const SYS_MODULE_INDEX index);
    void USART_1_ErrorEventHandler(const SYS_MODULE_INDEX index);
    void USART_1_StartTransmit(void);

    void USART_2_Initialize(const SYS_MODULE_INDEX index);
    void USART_2_ReceiveEventHandler(const SYS_MODULE_INDEX index);
    void USART_2_TransmitEventHandler(const SYS_MODULE_INDEX index);
    void USART_2_ErrorEventHandler(const SYS_MODULE_INDEX index);
    void USART_2_StartTransmit(void);

    void USART_5_Initialize(const SYS_MODULE_INDEX index);
    void USART_5_ReceiveEventHandler(const SYS_MODULE_INDEX index);
    void USART_5_TransmitEventHandler(const SYS_MODULE_INDEX index);
    void USART_5_ErrorEventHandler(const SYS_MODULE_INDEX index);
    void USART_5_StartTransmit(void);
    
    void USART_StartTransmit(const SYS_MODULE_INDEX index);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
