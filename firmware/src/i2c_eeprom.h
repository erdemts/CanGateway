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

#ifndef _I2C_EEPROM_H    /* Guard against multiple inclusion */
#define _I2C_EEPROM_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    extern volatile unsigned char i2cWriteBuffer[128];
    extern volatile unsigned char i2cReadBuffer[128];

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */
#define EEPROM_TIMEOUT_TIME                 50 //ms
#define READ                                1    
#define WRITE                               0 

    // I2C Address for EEPROM 24FC1025.
#define I2C_24FC1025_DEVICE_CODE             0x00A8
#define I2C_ACK_DATA_LENGTH                  1

#define EEPROM_PAGE_SIZE                    128

#define EEPROM_SIZE                          524288 //byte. 4x24LC1025 i2c eeprom    

#define ADDRESS_INDEX_SIZE                                      2 //(3 Bytes)
#define COUNTING_DATA_INDEX_BUFFER_COUNT                        20
#define COUNTING_DATA_SIZE                                      13
#define COUNTING_DATA_INDEX_SIZE                                4
#define STATUS_DATA_INDEX_BUFFER_COUNT                          20
#define STATUS_DATA_SIZE                                        8
#define STATUS_DATA_INDEX_SIZE                                  4
#define MAX_COUNT_INDEX                                         0XFEFE 
#define MAX_STATUS_INDEX                                        0XFEFE    

#define MAX_COUNTING_LOG_COUNT                                  20000    
#define MAX_STATUS_LOG_COUNT                                    2000       


    //EEPROM MAP
#define SYSTEM_PARAMETERS_EEPROM_START_ADDRESS                  0
#define SYSTEM_DOOR_COUNT_EEADRESS                              (SYSTEM_PARAMETERS_EEPROM_START_ADDRESS) //(1 Byte)    
#define SYSTEM_COUNT_CATEGORY_COUNT_EEADRESS                    (SYSTEM_DOOR_COUNT_EEADRESS + 1) //(1 Byte)
#define SYSTEM_COUNT_CATEGORY_ID_1_EEADRESS                     (SYSTEM_COUNT_CATEGORY_COUNT_EEADRESS + 1) //(1 Byte)
#define SYSTEM_COUNT_CATEGORY_ID_2_EEADRESS                     (SYSTEM_COUNT_CATEGORY_ID_1_EEADRESS + 1) //(1 Byte) 
#define SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS             (SYSTEM_COUNT_CATEGORY_ID_2_EEADRESS + 1) //(2 Byte) 
#define SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS             (SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS + 2) //(2 Byte)    
#define SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS             (SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS + 2) //(2 Byte) 
#define SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS             (SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS + 2) //(2 Bytes)    
#define SENSOR_1_ADDRESS_EEADRESS                               (SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS + 2) //(2 Bytes)
#define SENSOR_2_ADDRESS_EEADRESS                               (SENSOR_1_ADDRESS_EEADRESS + 2) //(2 Bytes)
#define SENSOR_3_ADDRESS_EEADRESS                               (SENSOR_2_ADDRESS_EEADRESS + 2) //(2 Bytes)    
#define SENSOR_4_ADDRESS_EEADRESS                               (SENSOR_3_ADDRESS_EEADRESS + 2) //(2 Bytes)
#define SENSOR_5_ADDRESS_EEADRESS                               (SENSOR_4_ADDRESS_EEADRESS + 2) //(2 Bytes)
#define SENSOR_6_ADDRESS_EEADRESS                               (SENSOR_5_ADDRESS_EEADRESS + 2) //(2 Bytes)
#define SENSOR_7_ADDRESS_EEADRESS                               (SENSOR_6_ADDRESS_EEADRESS + 2) //(2 Bytes)
#define SENSOR_8_ADDRESS_EEADRESS                               (SENSOR_7_ADDRESS_EEADRESS + 2) //(2 Bytes)    
#define SENSOR_1_FA_EEADRESS                                    (SENSOR_8_ADDRESS_EEADRESS + 2) //(2 Bytes)
#define SENSOR_2_FA_EEADRESS                                    (SENSOR_1_FA_EEADRESS + 2) //(2 Bytes)
#define SENSOR_3_FA_EEADRESS                                    (SENSOR_2_FA_EEADRESS + 2) //(2 Bytes)
#define SENSOR_4_FA_EEADRESS                                    (SENSOR_3_FA_EEADRESS + 2) //(2 Bytes)
#define SENSOR_5_FA_EEADRESS                                    (SENSOR_4_FA_EEADRESS + 2) //(2 Bytes)
#define SENSOR_6_FA_EEADRESS                                    (SENSOR_5_FA_EEADRESS + 2) //(2 Bytes)
#define SENSOR_7_FA_EEADRESS                                    (SENSOR_6_FA_EEADRESS + 2) //(2 Bytes) 
#define SENSOR_8_FA_EEADRESS                                    (SENSOR_7_FA_EEADRESS + 2) //(2 Bytes)    
#define INPUT_TYPES_EEPROM_ADDRESS                              (SENSOR_8_FA_EEADRESS + 1)
#define SYSTEM_PARAMETERS_EEPROM_SIZE                           ((INPUT_TYPES_EEPROM_ADDRESS + 1) - SYSTEM_PARAMETERS_EEPROM_START_ADDRESS)    

#define COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS         (INPUT_TYPES_EEPROM_ADDRESS + 1) //(4 Bytes x 20)
#define STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS           (COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS + (COUNTING_DATA_INDEX_BUFFER_COUNT * COUNTING_DATA_INDEX_SIZE))//(4 Bytes x 20)

#define COUNTING_LOG_AREA_START_ADDRESS                         (STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS + (STATUS_DATA_INDEX_BUFFER_COUNT * STATUS_DATA_INDEX_SIZE))
#define COUNTING_LOG_AREA_END_ADDRESS                           (COUNTING_LOG_AREA_START_ADDRESS + (COUNTING_DATA_SIZE * MAX_COUNTING_LOG_COUNT) - 1)  

#define STATUS_LOG_AREA_START_ADDRESS                           (COUNTING_LOG_AREA_START_ADDRESS + (COUNTING_DATA_SIZE * MAX_COUNTING_LOG_COUNT))
#define STATUS_LOG_AREA_END_ADDRESS                             (STATUS_LOG_AREA_START_ADDRESS + (STATUS_DATA_SIZE * MAX_STATUS_LOG_COUNT) - 1)      


    // *****************************************************************************

    /* Application states

      Summary:
        Application states enumeration

      Description:
        This enumeration defines the valid application states.  These states
        determine the behavior of the application at various times.
     */

    typedef enum {
        /* Application's state machine's initial state. */
        I2C_STATE_INIT = 0,
        /* Application ready state */
        I2C_STATE_READY,
        /* Application transmit bytes state */
        I2C_STATE_DATA_TRANSMIT,
        /* Application acknowledge state */
        I2C_STATE_ACK_CYCLE,
        /* Application data receive state */
        I2C_STATE_DATA_RECEIVE,
        /* Application data verify state */
        I2C_STATE_DATA_VERIFY,
        /* Application success state */
        I2C_STATE_SUCCESS,
        /* Application error state */
        I2C_STATE_ERROR,
        /* Application done state */
        I2C_STATE_DONE
    } I2C_STATES;


    // *****************************************************************************

    /* Application Data

      Summary:
        Holds application data

      Description:
        This structure holds the application's data.

      Remarks:
        Application strings and buffers are be defined outside this structure.
     */

    typedef struct {
        /* The application's current state */
        I2C_STATES currentState;
        /* The application's next state */
        I2C_STATES previousState;
        /* I2C Driver Handle */
        DRV_HANDLE drvI2CHandle;
        /* Ready Buffer handle */
        DRV_I2C_BUFFER_HANDLE hReadyBuffer;
        /* Transmit buffer handle */
        DRV_I2C_BUFFER_HANDLE hTxBuffer;
        /* Acknowledge buffer handle */
        DRV_I2C_BUFFER_HANDLE hAckBuffer;
        /* Receive buffer handle */
        DRV_I2C_BUFFER_HANDLE hRxBuffer;
    } I2C_DATA;



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    void APP_I2CEventHandler(DRV_I2C_BUFFER_EVENT event,
            DRV_I2C_BUFFER_HANDLE bufferHandle,
            uintptr_t context);

    unsigned char i2cEepromReadWrite(bool rW, unsigned int address, unsigned char dataLenght, volatile unsigned char* buffer);
    void eepromWrite(unsigned int address, unsigned char length, volatile unsigned char* Data_Buffer);
    void eepromRead(unsigned int address, unsigned char length, volatile unsigned char* Data_Buffer);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
