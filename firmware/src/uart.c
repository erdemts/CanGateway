/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "system_definitions.h"
#include "uart.h"
#include "fifoBuffer.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
DRV_HANDLE USART_1_Handle;
DRV_HANDLE USART_2_Handle;
DRV_HANDLE USART_5_Handle;
volatile UART_DATA_TYPE UART_1;
volatile UART_DATA_TYPE UART_2;
volatile UART_DATA_TYPE UART_5;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */
void USART_1_Initialize(const SYS_MODULE_INDEX index) {
    bool appInitialized = true;
    USART_1_Handle = DRV_HANDLE_INVALID;

    if (USART_1_Handle == DRV_HANDLE_INVALID) {
        USART_1_Handle = DRV_USART_Open(index, DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING);
        appInitialized &= (DRV_HANDLE_INVALID != USART_1_Handle);
    }
    if (appInitialized) {
        DRV_USART_ByteReceiveCallbackSet(index, USART_1_ReceiveEventHandler);
        DRV_USART_ByteTransmitCallbackSet(index, USART_1_TransmitEventHandler);
        DRV_USART_ByteErrorCallbackSet(index, USART_1_ErrorEventHandler);
    }
}

void USART_1_ReceiveEventHandler(const SYS_MODULE_INDEX index) {
    addDataToBuffer(&UART_1.uartReceiveBuffer, DRV_USART_ReadByte(USART_1_Handle), BUFFER_SIZE);
}

void USART_1_TransmitEventHandler(const SYS_MODULE_INDEX index) {
    if (UART_1.uartTransmitBuffer.R != UART_1.uartTransmitBuffer.W) {
        DRV_USART_WriteByte(USART_1_Handle, getDataFromBuffer(&UART_1.uartTransmitBuffer, BUFFER_SIZE));
    }
}

void USART_1_ErrorEventHandler(const SYS_MODULE_INDEX index) {
    // Error has occurred. Handle the event.
}

void USART_1_StartTransmit(void) {
    if (UART_1.uartTransmitBuffer.R != UART_1.uartTransmitBuffer.W) {
        DRV_USART_WriteByte(USART_1_Handle, getDataFromBuffer(&UART_1.uartTransmitBuffer, BUFFER_SIZE));
    }
}

void USART_2_Initialize(const SYS_MODULE_INDEX index) {
    bool appInitialized = true;
    USART_2_Handle = DRV_HANDLE_INVALID;
    UART_2_EN = RECEIVE;

    if (USART_2_Handle == DRV_HANDLE_INVALID) {
        USART_2_Handle = DRV_USART_Open(index, DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING);
        appInitialized &= (DRV_HANDLE_INVALID != USART_2_Handle);
    }
    if (appInitialized) {
        DRV_USART_ByteReceiveCallbackSet(index, USART_2_ReceiveEventHandler);
        DRV_USART_ByteTransmitCallbackSet(index, USART_2_TransmitEventHandler);
        DRV_USART_ByteErrorCallbackSet(index, USART_2_ErrorEventHandler);
    }
}

void USART_2_ReceiveEventHandler(const SYS_MODULE_INDEX index) {
    addDataToBuffer(&UART_2.uartReceiveBuffer, DRV_USART_ReadByte(USART_2_Handle), BUFFER_SIZE);
}

void USART_2_TransmitEventHandler(const SYS_MODULE_INDEX index) {
    if (UART_2.uartTransmitBuffer.R != UART_2.uartTransmitBuffer.W) {
        DRV_USART_WriteByte(USART_2_Handle, getDataFromBuffer(&UART_2.uartTransmitBuffer, BUFFER_SIZE));
    }
}

void USART_2_ErrorEventHandler(const SYS_MODULE_INDEX index) {
    // Error has occurred. Handle the event.
}

void USART_2_StartTransmit(void) {
    if (UART_2.uartTransmitBuffer.R != UART_2.uartTransmitBuffer.W) {
        DRV_USART_WriteByte(USART_2_Handle, getDataFromBuffer(&UART_2.uartTransmitBuffer, BUFFER_SIZE));
    }
}

void USART_5_Initialize(const SYS_MODULE_INDEX index) {
    bool appInitialized = true;
    USART_5_Handle = DRV_HANDLE_INVALID;
    UART_5_EN = RECEIVE;

    if (USART_5_Handle == DRV_HANDLE_INVALID) {
        USART_5_Handle = DRV_USART_Open(index, DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING);
        appInitialized &= (DRV_HANDLE_INVALID != USART_5_Handle);
    }
    if (appInitialized) {
        DRV_USART_ByteReceiveCallbackSet(index, USART_5_ReceiveEventHandler);
        DRV_USART_ByteTransmitCallbackSet(index, USART_5_TransmitEventHandler);
        DRV_USART_ByteErrorCallbackSet(index, USART_5_ErrorEventHandler);
    }
}

void USART_5_ReceiveEventHandler(const SYS_MODULE_INDEX index) {
    addDataToBuffer(&UART_5.uartReceiveBuffer, DRV_USART_ReadByte(USART_5_Handle), BUFFER_SIZE);
}

void USART_5_TransmitEventHandler(const SYS_MODULE_INDEX index) {
    if (UART_5.uartTransmitBuffer.R != UART_5.uartTransmitBuffer.W) {
        DRV_USART_WriteByte(USART_5_Handle, getDataFromBuffer(&UART_5.uartTransmitBuffer, BUFFER_SIZE));
    } else {
        UART_2_EN = RECEIVE;
        UART_5_EN = RECEIVE;
    }
}

void USART_5_ErrorEventHandler(const SYS_MODULE_INDEX index) {
    // Error has occurred. Handle the event.
}

void USART_5_StartTransmit(void) {
    UART_2_EN = TRANSMIT;
    UART_5_EN = TRANSMIT;
    if (UART_5.uartTransmitBuffer.R != UART_5.uartTransmitBuffer.W) {
        DRV_USART_WriteByte(USART_5_Handle, getDataFromBuffer(&UART_5.uartTransmitBuffer, BUFFER_SIZE));
    } else {
        UART_2_EN = RECEIVE;
        UART_5_EN = RECEIVE;
    }
}

void USART_StartTransmit(const SYS_MODULE_INDEX index) {
    switch (index) {
        case DRV_USART_INDEX_0:
            if (UART_1.uartTransmitBuffer.R != UART_1.uartTransmitBuffer.W)
                DRV_USART_WriteByte(USART_1_Handle, getDataFromBuffer(&UART_1.uartTransmitBuffer, BUFFER_SIZE));
            break;
        case DRV_USART_INDEX_1:
            if (UART_2.uartTransmitBuffer.R != UART_2.uartTransmitBuffer.W)
                DRV_USART_WriteByte(USART_2_Handle, getDataFromBuffer(&UART_2.uartTransmitBuffer, BUFFER_SIZE));
            break;
        case DRV_USART_INDEX_2:
            if (UART_5.uartTransmitBuffer.R != UART_5.uartTransmitBuffer.W)
                DRV_USART_WriteByte(USART_5_Handle, getDataFromBuffer(&UART_5.uartTransmitBuffer, BUFFER_SIZE));
            break;
    }
}

/* *****************************************************************************
 End of File
 */
