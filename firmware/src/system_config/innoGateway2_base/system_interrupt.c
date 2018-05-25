/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"


#include "data_types.h"
//#include "irma.h"
//#include "timerDefinitions.h"

extern volatile unsigned char commandResponseTimer;
extern volatile unsigned char commandResponseTimerEnable;
extern volatile unsigned char commandResponseTimeOutFlag;

extern volatile TIMER_TYPE systemCheckTimer;
extern volatile TIMER_TYPE uart_1_DataSendTimeoutTimer;
extern volatile TIMER_TYPE uart_5_DataSendTimeoutTimer;
extern volatile TIMER_TYPE debounceTimer;
extern volatile TIMER_TYPE eepromTimeoutTimer;
extern volatile TIMER_TYPE eepromControlTimer;

extern IRMA_CAN_MSG_BUFFER_TYPE irmaCanReceiveBuffer[IRMA_CAN_RECEIVE_BUFFER_SIZE];
extern unsigned char irmaCanReceiveBufferW;

extern volatile SYSTEM_DATA_TYPE sysData;

unsigned char count = 0;

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************


void __ISR(_I2C_2_VECTOR, ipl1AUTO) _IntHandlerDrvI2CInstance0(void)
{
    DRV_I2C_Tasks(sysObj.drvI2C0);

}

 
   

 
 
 

 




 void __ISR(_UART_1_VECTOR, ipl2AUTO) _IntHandlerDrvUsartInstance0(void)
{
    DRV_USART_TasksTransmit(sysObj.drvUsart0);
    DRV_USART_TasksError(sysObj.drvUsart0);
    DRV_USART_TasksReceive(sysObj.drvUsart0);
}

 
 

void __ISR(_UART_2_VECTOR, ipl2AUTO) _IntHandlerDrvUsartInstance1(void)
{
    DRV_USART_TasksTransmit(sysObj.drvUsart1);
    DRV_USART_TasksError(sysObj.drvUsart1);
    DRV_USART_TasksReceive(sysObj.drvUsart1);
}

 
 

void __ISR(_UART_5_VECTOR, ipl2AUTO) _IntHandlerDrvUsartInstance2(void)
{
    DRV_USART_TasksTransmit(sysObj.drvUsart2);
    DRV_USART_TasksError(sysObj.drvUsart2);
    DRV_USART_TasksReceive(sysObj.drvUsart2);
}




 

 

 
  
void __ISR(_CHANGE_NOTICE_VECTOR, ipl1AUTO) _IntHandlerChangeNotification(void)
{
    sysData.CURRENT_INPUT_STATES.input_states = readInputs();
    if (sysData.OLD_INPUT_STATES.input_states != sysData.CURRENT_INPUT_STATES.input_states) {
        setTimer10ms(&debounceTimer, DEBOUNCE_DELAY); // 5x10ms         
    }
    /* TODO: Add code to process interrupt here */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
}

 

void __ISR(_TIMER_1_VECTOR, ipl4AUTO) IntHandlerDrvTmrInstance0(void)
{
    if ((--commandResponseTimer == 0) && commandResponseTimerEnable) {
        commandResponseTimerEnable = 0;
        commandResponseTimeOutFlag = 1;
    }

    count = 0;
    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        sensorPollingTimer10msProcess(count);
        ++count;
    }

    timer10msProcess(&systemCheckTimer);
    timer10msProcess(&uart_1_DataSendTimeoutTimer);
    timer10msProcess(&uart_5_DataSendTimeoutTimer);
    timer10msProcess(&debounceTimer);
    timer10msProcess(&eepromControlTimer);
    timer10msProcess(&eepromTimeoutTimer);

    if (isTimer10msTimeoutOccured(&debounceTimer)) {
        sysData.CURRENT_INPUT_STATES.input_states = readInputs();
        if (sysData.OLD_INPUT_STATES.input_states != sysData.CURRENT_INPUT_STATES.input_states) {
            sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.CHECK_IO = 1;
        }
        disableTimer10ms(&debounceTimer);
    }
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_1);
}
 
void __ISR(_CAN_1_VECTOR, IPL4AUTO) _IntHandlerDrvCANInstance0(void)
{
    if ((PLIB_CAN_ModuleEventGet(CAN_ID_1) & (CAN_TX_EVENT)) != 0) {
        PLIB_CAN_ChannelEventDisable(CAN_ID_1, CAN_TX_CHANNEL, 0 | CAN_TX_CHANNEL_EMPTY);
        PLIB_CAN_ModuleEventClear(CAN_ID_1, CAN_TX_EVENT);
    }
    if ((PLIB_CAN_ModuleEventGet(CAN_ID_1) & (CAN_RX_EVENT)) != 0) {
        while (IRMA_Send_CAN_Channel_Receive_Buffer_To_IRMA_CAN_Receive_Buffer(CAN_RX_CHANNEL, irmaCanReceiveBuffer, &irmaCanReceiveBufferW) == false);
        PLIB_CAN_ModuleEventClear(CAN_ID_1, CAN_RX_EVENT);
    }

    if ((PLIB_CAN_ModuleEventGet(CAN_ID_1) & (CAN_RX_OVERFLOW_EVENT)) != 0) {
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_RX_OVERFLOW_EVENT_FLAG = 1;
        PLIB_CAN_ModuleEventClear(CAN_ID_1, CAN_RX_OVERFLOW_EVENT);
    }
    if ((PLIB_CAN_ModuleEventGet(CAN_ID_1) & (CAN_INVALID_RX_MESSAGE_EVENT)) != 0) {
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_INVALID_RX_MESSAGE_EVENT_FLAG = 1;
        PLIB_CAN_ModuleEventClear(CAN_ID_1, CAN_INVALID_RX_MESSAGE_EVENT);
    }
    if ((PLIB_CAN_ModuleEventGet(CAN_ID_1) & (CAN_BUS_ERROR_EVENT)) != 0) {
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_BUS_ERROR_EVENT_FLAG = 1;
        PLIB_CAN_ModuleEventClear(CAN_ID_1, CAN_BUS_ERROR_EVENT);
    }
    if ((PLIB_CAN_ModuleEventGet(CAN_ID_1) & (CAN_SYSTEM_ERROR_EVENT)) != 0) {
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_SYSTEM_ERROR_EVENT_FLAG = 1;
        PLIB_CAN_ModuleEventClear(CAN_ID_1, CAN_SYSTEM_ERROR_EVENT);
    }
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CAN_1);
}



/*******************************************************************************
 End of File
 */
