/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "system_config.h"
#include "system_definitions.h"
#include "IRMA.h"
#include "uart.h"


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
    // DOM-IGNORE-END 

    // *****************************************************************************
    // *****************************************************************************
    // Section: Type Definitions
    // *****************************************************************************
    // *****************************************************************************

#define INPUT_1         PORTBbits.RB0
#define INPUT_2         PORTBbits.RB1
#define INPUT_3         PORTBbits.RB2
#define INPUT_4         PORTBbits.RB3
#define INPUT_5         PORTBbits.RB4
#define INPUT_6         PORTDbits.RD11
#define UART_2_EN       LATFbits.LATF3
#define UART_5_EN       LATAbits.LATA1
#define INPUT_MASK      0b0000000000011111
#define INPUT_PORT      PORTB    

#define bit_set(var,bitno)          ((var) |= 1 << (bitno))
#define bit_clear(var,bitno)        ((var) &= ~(1 << (bitno)))
#define bit_test(data,bitno)        ((data>>bitno)&0x01)
#define hibyte(x)                   (unsigned char)	((x>>8) & 0xFF)
#define lobyte(x)                   (unsigned char)	(x & 0xFF)
#define toShort(HiByte, LoByte)     (unsigned short)(((unsigned short)(HiByte << 8) & 0xFF00) | (unsigned short)LoByte)

    //Device specific defines  
#define MAX_SUPPORTED_SENSOR_COUNT                  4
#define TOTAL_DIGITAL_INPUT                         6  




#define ACTIVE_HIGH                                     1    
#define ACTIVE_LOW                                      0   
#define DOOR_IS_OPEN                                    1       
#define DOOR_IS_CLOSE                                   0    

    typedef enum {
        WAIT_STX = 0,
        WAIT_COMMAND,
        WAIT_LENGHT,
        WAIT_DATA,
        WAIT_CRC_LENGHT,
        WAIT_CRC_H,
        WAIT_CRC_L,
        WAIT_ETX,
        WAIT_ACK,
        RUN_COMMAND
    } COMMAND_HANDLE_STATE;

    typedef enum {
        STATE_SENSOR_IDLE = 0,
        STATE_START_COUNTING,
        STATE_WAIT_DOOR_CLOSING,
        STATE_STOP_COUNTING,
        STATE_WAIT_FA_TIMEOUT,
        STATE_GET_FA_STATUS,
        STATE_GET_COUNT_RESULT,
        STATE_GET_SENSOR_STATUS
    } SENSOR_STATES;

    typedef enum {
        P_STATE_IDLE = 0,
        P_STATE_COUNT_DATA_SEND,
        P_STATE_COUNT_DATA_WAIT_ACK,
        P_STATE_COUNT_DATA_RECORD_EEPROM,
        P_STATE_STATUS_DATA_SEND,
        P_STATE_STATUS_DATA_WAIT_ACK,
        P_STATE_STATUS_DATA_RECORD_EEPROM,
        P_STATE_RECORDED_COUNT_DATA_SEND,
        P_STATE_RECORDED_COUNT_DATA_WAIT_ACK,
        P_STATE_RECORDED_STATUS_DATA_SEND,
        P_STATE_RECORDED_STATUS_DATA_WAIT_ACK
    } DATA_PROCESS_STATES;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Application Initialization and State Machine Functions
    // *****************************************************************************
    // *****************************************************************************

    void APP_Initialize(void);
    void APP_Tasks(void);


    void initializeSystem(void);
    void checkIOProcess(void);
    unsigned short readInputs(void);
    void checkInputsAndChangeSensorStates(unsigned char inputNo);
    void countingProcess(void);
    bool updateSystemTime(unsigned char day, unsigned char month, unsigned char year, unsigned char hour, unsigned char min, unsigned char sec);
    bool updateCoordinates(unsigned char Lat0, unsigned char Lat1, unsigned char Lat2, unsigned char Lat3, unsigned char Lon0, unsigned char Lon1, unsigned char Lon2, unsigned char Lon3);
    time_t getCurrentTime(void);
    void dataProcessManager(void);

    void updateCountDataLogWriteIndexToEEprom(void);
    void updateCountDataLogReadIndexToEEprom(void);
    void updateCountDataIndexFromEEprom(void);
    void updateStatusDataLogWriteIndexToEEprom(void);
    void updateStatusDataLogReadIndexToEEprom(void);
    void updateStatusDataIndexFromEEprom(void);

    void updateSystemParametersFromEEprom(void);
    void recordSystemParametersToEEprom(void);

    void getSensorParameters(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sourceSensors, volatile IRMA_SENSOR_TYPE* destinationSensors);
    void checkAllSensorParameters(void);

    void systemStartupCheck(volatile UART_DATA_TYPE* uartTransmit, volatile UART_DATA_TYPE* uartReceive, unsigned char uartType);

    void fakeInit(void);


#endif /* _APP_H */

    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

