
#ifndef _UART_PROTOCOL_HANDLER_H    /* Guard against multiple inclusion */
#define _UART_PROTOCOL_HANDLER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */




/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************




    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    void prepareMessagePackage(unsigned char command, volatile UART_DATA_TYPE* uartData);
    void uartCommandHandler(volatile UART_DATA_TYPE* uartData);
    void uartProcessCommand(volatile UART_DATA_TYPE* uartData);
    
    void uartCommandHandlerGeneral(volatile UART_DATA_TYPE* uartTransmit, volatile UART_DATA_TYPE* uartReceive, unsigned char uartType);
    void uartProcessCommandGeneral(volatile UART_DATA_TYPE* uartTransmit, volatile UART_DATA_TYPE* uartReceive, unsigned char uartType);




    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
