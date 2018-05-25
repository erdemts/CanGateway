// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include <time.h>
#include "app.h"
#include "data_types.h"
#include "IRMA.h"
#include "uart.h"
#include "uart_protocol_handler.h"
#include "commands.h"
#include "fifoBuffer.h"
#include "timerDefinitions.h"
#include "driver/i2c/drv_i2c.h"
#include "i2c_eeprom.h"
#include "system_interrupt.c"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define _debug

volatile SYSTEM_DATA_TYPE sysData;
volatile SYSTEM_PARAMETERS_TYPE SYSTEM_PARAMETERS;
time_t currentTime;
struct tm *sysTime_str;
struct tm info;
volatile COUNT_DATA_BUFFER_TYPE countDataBuffer;
volatile STATUS_DATA_BUFFER_TYPE statusDataBuffer;

extern IRMA_RESPONSE_BUFFER_TYPE commandResponseBuffer;
bool stateA = 0;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************
unsigned int m = 0;

void APP_Initialize(void) {
    //    fakeInit();
    SYS_WDT_Enable(false);
    initializeSystem();
    USART_1_Initialize(DRV_USART_INDEX_0);
    USART_2_Initialize(DRV_USART_INDEX_1);
    USART_5_Initialize(DRV_USART_INDEX_2);
    setTimer10ms(&systemCheckTimer, 100);
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )
 */
void APP_Tasks(void) {
        //    checkCanbusErrors();
    SYS_WDT_TimerClear();
    checkIOProcess();
    countingProcess();
    dataProcessManager();
    uartCommandHandlerGeneral(&UART_1, &UART_1, ETH_);
    uartCommandHandlerGeneral(&UART_5, &UART_2, KIFI_);
    if (isTimer10msTimeoutOccured(&systemCheckTimer)) {
        LED_STATUS_Toggle();
        setTimer10ms(&systemCheckTimer, 100);
    }
}

void initializeSystem(void) {
    unsigned char count = 0;
    ETH_RESET_Off();
    ETH_RELOAD_Off();
    ETH_ENABLE_On(); //TODO:Hardware init buraya yazilacak
    LED_STATUS_Off();
    OUTPUT_1_Off();
    OUTPUT_2_Off();
    sysData.SYSTEM_STATUS.system_status = 0;
    sysData.CAN_ERRORS.can_1_Errors = 0;
    sysData.OLD_CAN_ERRORS.can_1_Errors = 0;
    sysData.CURRENT_INPUT_STATES.input_states = readInputs();
    sysData.OLD_INPUT_STATES.input_states = sysData.CURRENT_INPUT_STATES.input_states;
    sysData.CURRENT_DOOR_STATES.door_states = 0;
    sysData.LATITUDE.latitude = 0;
    sysData.LONGITUDE.longitude = 0;

    sysData.CAT_1_IN_TOTAL = 0;
    sysData.CAT_1_OUT_TOTAL = 0;
    sysData.CAT_2_IN_TOTAL = 0;
    sysData.CAT_2_OUT_TOTAL = 0;
    sysData.countDataIndex = 0;
    sysData.countDataLogReadIndex = 0;
    sysData.countDataLogWriteIndex = 0;
    sysData.statusDataIndex = 0;
    sysData.statusDataLogReadIndex = 0;
    sysData.statusDataLogWriteIndex = 0;
    sysData.dataProcessCurrentState = P_STATE_IDLE;

    updateSystemParametersFromEEprom();

    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        sysData.Door[count].TEMP_CAT_1_IN_B = 0;
        sysData.Door[count].TEMP_CAT_1_OUT_B = 0;
        sysData.Door[count].TEMP_CAT_1_IN_T = 0;
        sysData.Door[count].TEMP_CAT_1_OUT_T = 0;
        sysData.Door[count].TEMP_CAT_2_IN_B = 0;
        sysData.Door[count].TEMP_CAT_2_OUT_B = 0;
        sysData.Door[count].TEMP_CAT_2_IN_T = 0;
        sysData.Door[count].TEMP_CAT_2_OUT_T = 0;

        sysData.Door[count].COUNT_CATEGORY_COUNT = SYSTEM_PARAMETERS.SystemCountCategoryCount;
        sysData.Door[count].COUNT_CATEGORY_1_ID = SYSTEM_PARAMETERS.SystemCountCategory_ID_1;
        sysData.Door[count].COUNT_CATEGORY_1_DESC = PERSON;
        sysData.Door[count].COUNT_CATEGORY_1_PARAMETER_1 = SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1;
        sysData.Door[count].COUNT_CATEGORY_1_PARAMETER_2 = SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2;

        sysData.Door[count].COUNT_CATEGORY_2_ID = SYSTEM_PARAMETERS.SystemCountCategory_ID_2;
        sysData.Door[count].COUNT_CATEGORY_2_DESC = PERSON;
        sysData.Door[count].COUNT_CATEGORY_2_PARAMETER_1 = SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1;
        sysData.Door[count].COUNT_CATEGORY_2_PARAMETER_2 = SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2;

        sysData.sensorCheckStatus[count].sensorCheckStatusData = 0;
        sysData.checkedSensor[count].sensorStatus = 0;
        sysData.Door[count].sensorStatus = 0;
        sysData.checkedSensor[count].sensorStatus = sysData.Door[count].sensorStatus;
        sysData.Door[count].SENSOR_STATE = STATE_SENSOR_IDLE;
        ++count;
    }

    updateCountDataIndexFromEEprom();
    updateStatusDataIndexFromEEprom();
    //systemStartupCheck(&UART_5, &UART_2, KIFI_);
}

void checkIOProcess(void) {
    unsigned char count = 0;
    if (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.CHECK_IO) {
        while (count < SYSTEM_PARAMETERS.SystemDoorCount) //TODO: input kontrolu main icinde yapilacak.
        {
            checkInputsAndChangeSensorStates(count);
            ++count;
        }
        sysData.OLD_INPUT_STATES.input_states = sysData.CURRENT_INPUT_STATES.input_states;
        sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.CHECK_IO = 0;
    }
}

unsigned short readInputs(void) {
    return (INPUT_PORT & INPUT_MASK);
}

void checkInputsAndChangeSensorStates(unsigned char inputNo) {
    unsigned char inputTemp;
    if (inputNo < SYSTEM_PARAMETERS.SystemDoorCount) {
        switch (inputNo) {
            case 0:
                inputTemp = INPUT_1;
                break;
            case 1:
                inputTemp = INPUT_2;
                break;
            case 2:
                inputTemp = INPUT_3;
                break;
            case 3:
                inputTemp = INPUT_4;
                break;
            case 4:
                inputTemp = INPUT_5;
                break;
            case 5:
                inputTemp = INPUT_6;
                break;
            default:
                break;
        }
        if (SYSTEM_PARAMETERS.INPUT_TYPES.INPUT_TYPES_FLAGS.INPUT_1_TYPE == ACTIVE_HIGH) {
            if (inputTemp == 0) {
                bit_set(sysData.CURRENT_DOOR_STATES.door_states, inputNo);
                //#ifdef _debug
                //                LED_STATUS_On();
                //#endif                
                sysData.Door[inputNo].DOOR_OPEN_TIME = getCurrentTime();
                if (sysData.Door[inputNo].SENSOR_STATE != STATE_START_COUNTING) {
                    sysData.Door[inputNo].SENSOR_STATUS_FLAGS.NEW_COUNTING_RESULT_AVAIBLE = 0;
                    sysData.Door[inputNo].SENSOR_STATE = STATE_START_COUNTING;
                }
            } else {
                bit_clear(sysData.CURRENT_DOOR_STATES.door_states, inputNo);
                //#ifdef _debug
                //                LED_STATUS_Off();
                //#endif
                sysData.Door[inputNo].DOOR_CLOSE_TIME = getCurrentTime();
                if (sysData.Door[inputNo].SENSOR_STATE != STATE_STOP_COUNTING) {
                    sysData.Door[inputNo].SENSOR_STATE = STATE_STOP_COUNTING;
                }
            }
        } else if (SYSTEM_PARAMETERS.INPUT_TYPES.INPUT_TYPES_FLAGS.INPUT_1_TYPE == ACTIVE_LOW) {
            if (inputTemp == 1) {
                bit_set(sysData.CURRENT_DOOR_STATES.door_states, inputNo);
                //#ifdef _debug
                //                LED_STATUS_On();
                //#endif                
                sysData.Door[inputNo].DOOR_OPEN_TIME = getCurrentTime();
                if (sysData.Door[inputNo].SENSOR_STATE != STATE_START_COUNTING) {
                    sysData.Door[inputNo].SENSOR_STATUS_FLAGS.NEW_COUNTING_RESULT_AVAIBLE = 0;
                    sysData.Door[inputNo].SENSOR_STATE = STATE_START_COUNTING;
                }
            } else {
                bit_clear(sysData.CURRENT_DOOR_STATES.door_states, inputNo);
                //#ifdef _debug
                //                LED_STATUS_Off();
                //#endif
                sysData.Door[inputNo].DOOR_CLOSE_TIME = getCurrentTime();
                if (sysData.Door[inputNo].SENSOR_STATE != STATE_STOP_COUNTING) {
                    sysData.Door[inputNo].SENSOR_STATE = STATE_STOP_COUNTING;
                }
            }
        }
    }
}

void countingProcess(void) {
    unsigned char count = 0;
    unsigned char repeatCount = 0;
    bool result = 0;

    while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
        if (sysData.Door[count].SENSOR_STATE == STATE_START_COUNTING) {
            do {
                IRMA_startCounting(sysData.Door[count].SENSOR_ADDRESS, sysData.Door);
                ++repeatCount;
            } while ((repeatCount < MAX_GENERAL_TRY_COUNT) && (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR));
            if (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR) {
                sysData.Door[count].SENSOR_STATE = STATE_SENSOR_IDLE;
            } else {
                sysData.Door[count].SENSOR_STATE = STATE_WAIT_DOOR_CLOSING;
            }
        }
        ++count;
    }

    count = 0;
    repeatCount = 0;
    while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
        if (sysData.Door[count].SENSOR_STATE == STATE_STOP_COUNTING) {
            do {
                IRMA_stopCounting(sysData.Door[count].SENSOR_ADDRESS, sysData.Door);
                ++repeatCount;
            } while ((repeatCount < MAX_GENERAL_TRY_COUNT) && (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR));
            if (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR) {
                sysData.Door[count].SENSOR_STATE = STATE_SENSOR_IDLE;
            } else {
                setSensorPollingTimer10ms(count, SENSOR_READ_COUNT_DATA_DELAY); //SENSOR_READ_COUNT_DATA_DELAY x 10ms timeout 
                sysData.Door[count].SENSOR_STATE = STATE_WAIT_FA_TIMEOUT;
            }
        }
        ++count;
    }

    count = 0;
    repeatCount = 0;
    while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
        if (sysData.Door[count].SENSOR_STATE == STATE_WAIT_FA_TIMEOUT) {
            if (isSensorPollingTimer10msTimeoutOccured(count)) {
                disableSensorPollingTimer10ms(count);
                sysData.Door[count].SENSOR_STATE = STATE_GET_FA_STATUS;
            }
        }
        ++count;
    }

    count = 0;
    repeatCount = 0;
    while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
        if (sysData.Door[count].SENSOR_STATE == STATE_GET_FA_STATUS) {
            do {
                IRMA_getFunctionAreaStatus(sysData.Door[count].SENSOR_ADDRESS, sysData.Door);
                ++repeatCount;
            } while ((repeatCount < MAX_GENERAL_TRY_COUNT) && (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR) && (!sysData.Door[count].SENSOR_STATUS_FLAGS.NEW_COUNTING_RESULT_AVAIBLE));
            if (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR) {
                sysData.Door[count].SENSOR_STATE = STATE_SENSOR_IDLE;
            } else {
                sysData.Door[count].SENSOR_STATE = STATE_GET_COUNT_RESULT;
            }
        }
        ++count;
    }

    count = 0;
    repeatCount = 0;
    while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
        if (sysData.Door[count].SENSOR_STATE == STATE_GET_COUNT_RESULT && sysData.Door[count].SENSOR_STATUS_FLAGS.NEW_COUNTING_RESULT_AVAIBLE) {
            do {
                result = IRMA_getCountResultsWithOptionalReset(sysData.Door[count].SENSOR_ADDRESS, sysData.Door[count].FA, WITH_RESET, 'B', SYSTEM_PARAMETERS.SystemCountCategory_ID_1, sysData.Door);
                ++repeatCount;
            } while ((repeatCount < MAX_GENERAL_TRY_COUNT) && (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR));
            if (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR) {
                sysData.Door[count].SENSOR_STATE = STATE_SENSOR_IDLE;
            } else {
                sysData.CAT_1_IN_TOTAL += sysData.Door[count].TEMP_CAT_1_IN_B;
                sysData.CAT_1_OUT_TOTAL += sysData.Door[count].TEMP_CAT_1_OUT_B;
                sysData.CAT_2_IN_TOTAL += sysData.Door[count].TEMP_CAT_2_IN_B;
                sysData.CAT_2_OUT_TOTAL += sysData.Door[count].TEMP_CAT_2_OUT_B;
                sysData.Door[count].CAT_1_IN_B += sysData.Door[count].TEMP_CAT_1_IN_B;
                sysData.Door[count].CAT_1_OUT_B += sysData.Door[count].TEMP_CAT_1_OUT_B;
                sysData.Door[count].CAT_2_IN_B += sysData.Door[count].TEMP_CAT_2_IN_B;
                sysData.Door[count].CAT_2_OUT_B += sysData.Door[count].TEMP_CAT_2_OUT_B;
                sysData.Door[count].TEMP_CAT_1_IN_B = 0;
                sysData.Door[count].TEMP_CAT_1_OUT_B = 0;
                sysData.Door[count].TEMP_CAT_2_IN_B = 0;
                sysData.Door[count].TEMP_CAT_2_OUT_B = 0;
                sysData.Door[count].SENSOR_STATE = STATE_GET_SENSOR_STATUS;
                sysData.Door[count].SENSOR_STATUS_FLAGS.NEW_COUNTING_RESULT_AVAIBLE = 0;
                sysData.Door[count].SENSOR_STATUS_FLAGS.NEW_COUNT_DATA_FLAG = 1;
            }
        }
        ++count;
    }

    count = 0;
    repeatCount = 0;
    while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
        if (sysData.Door[count].SENSOR_STATE == STATE_GET_SENSOR_STATUS) {
            do {
                IRMA_getSensorStatus(sysData.Door[count].SENSOR_ADDRESS, sysData.Door);
                ++repeatCount;
            } while ((repeatCount < MAX_GENERAL_TRY_COUNT) && (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR));
            if (sysData.Door[count].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR) {
                sysData.Door[count].SENSOR_STATE = STATE_SENSOR_IDLE;
            } else {
                sysData.Door[count].SENSOR_STATE = STATE_SENSOR_IDLE;
            }
        }
        ++count;
    }
}

bool updateSystemTime(unsigned char day, unsigned char month, unsigned char year, unsigned char hour, unsigned char min, unsigned char sec) {
    //TODO: Zaman saat entegresinden alinacak
    info.tm_year = (2000 + year) - 1900;
    info.tm_mon = month - 1;
    info.tm_mday = day;
    info.tm_hour = hour;
    info.tm_min = min;
    info.tm_sec = sec;
    info.tm_isdst = -1;
    currentTime = mktime(&info);
    sysTime_str = gmtime(&currentTime); //for debug
}

bool updateCoordinates(unsigned char Lat0, unsigned char Lat1, unsigned char Lat2, unsigned char Lat3,
        unsigned char Lon0, unsigned char Lon1, unsigned char Lon2, unsigned char Lon3) {

    sysData.LATITUDE.Lat0 = Lat0;
    sysData.LATITUDE.Lat1 = Lat1;
    sysData.LATITUDE.Lat2 = Lat2;
    sysData.LATITUDE.Lat3 = Lat3;

    sysData.LONGITUDE.Lon0 = Lon0;
    sysData.LONGITUDE.Lon1 = Lon1;
    sysData.LONGITUDE.Lon2 = Lon2;
    sysData.LONGITUDE.Lon3 = Lon3;
}

time_t getCurrentTime(void) {
    return currentTime;
}

void dataProcessManager(void) {
    unsigned char count = 0;

    //Count Data
    if (sysData.dataProcessCurrentState == P_STATE_IDLE) {
        while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
            if ((sysData.Door[count].SENSOR_STATUS_FLAGS.NEW_COUNT_DATA_FLAG) && (!bit_test(sysData.CURRENT_DOOR_STATES.door_states, count))) {
                countDataBuffer.doorNo = count;
                countDataBuffer.openTime = sysData.Door[count].DOOR_OPEN_TIME;
                countDataBuffer.closeTime = sysData.Door[count].DOOR_CLOSE_TIME;
                countDataBuffer.Cat_1_In = (unsigned char) (sysData.Door[count].CAT_1_IN_B & 0x00FF);
                countDataBuffer.Cat_1_Out = (unsigned char) (sysData.Door[count].CAT_1_OUT_B & 0x00FF);
                countDataBuffer.Cat_2_In = (unsigned char) (sysData.Door[count].CAT_2_IN_B & 0x00FF);
                countDataBuffer.Cat_2_Out = (unsigned char) (sysData.Door[count].CAT_2_OUT_B & 0x00FF);
                sysData.Door[count].CAT_1_IN_B = 0;
                sysData.Door[count].CAT_1_OUT_B = 0;
                sysData.Door[count].CAT_2_IN_B = 0;
                sysData.Door[count].CAT_2_OUT_B = 0;
                sysData.Door[count].SENSOR_STATUS_FLAGS.NEW_COUNT_DATA_FLAG = 0;
                sysData.dataProcessCurrentState = P_STATE_COUNT_DATA_SEND;
                break;
            }
            ++count;
        }
    }
    //Sensor Status
    if (sysData.dataProcessCurrentState == P_STATE_IDLE) {
        count = 0;
        while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
            if ((sysData.checkedSensor[count].sensorStatus & 0x0000FFFF) != (sysData.Door[count].sensorStatus & 0x0000FFFF)) {
                statusDataBuffer.currentTime = getCurrentTime();
                statusDataBuffer.statusType = EVENT_SENSOR_STATUS;
                statusDataBuffer.doorNo = count;
                statusDataBuffer.status = (unsigned short) (sysData.Door[count].sensorStatus & 0x0000FFFF);
                sysData.checkedSensor[count].sensorStatus = sysData.Door[count].sensorStatus;
                sysData.dataProcessCurrentState = P_STATE_STATUS_DATA_SEND;
                break;
            }
            ++count;
        }
    }
    //CANBUS Status
    if (sysData.dataProcessCurrentState == P_STATE_IDLE) {
        if (sysData.CAN_ERRORS.can_1_Errors != sysData.OLD_CAN_ERRORS.can_1_Errors) {
            statusDataBuffer.currentTime = getCurrentTime();
            statusDataBuffer.statusType = EVENT_CANBUS_STATUS;
            statusDataBuffer.doorNo = 0;
            statusDataBuffer.status = (unsigned short) (sysData.CAN_ERRORS.can_1_Errors & 0x0000FFFF);
            sysData.OLD_CAN_ERRORS.can_1_Errors = sysData.CAN_ERRORS.can_1_Errors;
            sysData.dataProcessCurrentState = P_STATE_STATUS_DATA_SEND;
        }
    }
    //Recorded Count Data. //&& isTimer10msTimeoutOccured(&systemCheckTimer)
    if ((sysData.dataProcessCurrentState == P_STATE_IDLE) && !sysData.CURRENT_DOOR_STATES.door_states) {
        if (sysData.countDataLogWriteIndex != sysData.countDataLogReadIndex) {
            //            setTimer10ms(&systemCheckTimer, RECORDED_DATA_CHECK_DELAY_TIME);
            eepromRead(COUNTING_LOG_AREA_START_ADDRESS + (sysData.countDataLogReadIndex * COUNTING_DATA_SIZE), COUNTING_DATA_SIZE, i2cReadBuffer);
#ifdef _debug           
            clearDataBuffer(&UART_1.transmitDataBuffer, BUFFER_SIZE);
#endif         
            clearDataBuffer(&UART_5.transmitDataBuffer, BUFFER_SIZE);
            count = 0;
            while (count < COUNTING_DATA_SIZE) {
#ifdef _debug
                addDataToBuffer(&UART_1.transmitDataBuffer, i2cReadBuffer[count], BUFFER_SIZE);
#endif
                addDataToBuffer(&UART_5.transmitDataBuffer, i2cReadBuffer[count], BUFFER_SIZE);
                ++count;
            }
#ifdef _debug
            prepareMessagePackage(EVENT_COUNT_DATA, &UART_1);
#endif
            prepareMessagePackage(EVENT_COUNT_DATA, &UART_5);
            sysData.dataProcessCurrentState = P_STATE_RECORDED_COUNT_DATA_SEND;
        }
    }

    //Recorded Status Data
    if ((sysData.dataProcessCurrentState == P_STATE_IDLE) && !sysData.CURRENT_DOOR_STATES.door_states) {
        if (sysData.statusDataLogWriteIndex != sysData.statusDataLogReadIndex) {
            //            setTimer10ms(&systemCheckTimer, RECORDED_DATA_CHECK_DELAY_TIME);
            eepromRead(STATUS_LOG_AREA_START_ADDRESS + (sysData.statusDataLogReadIndex * STATUS_DATA_SIZE), STATUS_DATA_SIZE, i2cReadBuffer);
#ifdef _debug            
            clearDataBuffer(&UART_1.transmitDataBuffer, BUFFER_SIZE);
#endif
            clearDataBuffer(&UART_5.transmitDataBuffer, BUFFER_SIZE);
            count = 0;
            while (count < STATUS_DATA_SIZE) {
#ifdef _debug                
                addDataToBuffer(&UART_1.transmitDataBuffer, i2cReadBuffer[count], BUFFER_SIZE);
#endif          
                addDataToBuffer(&UART_5.transmitDataBuffer, i2cReadBuffer[count], BUFFER_SIZE);
                ++count;
            }
#ifdef _debug            
            prepareMessagePackage(EVENT_STATUS_DATA, &UART_1);
#endif        
            prepareMessagePackage(EVENT_STATUS_DATA, &UART_5);
            sysData.dataProcessCurrentState = P_STATE_RECORDED_STATUS_DATA_SEND;
        }
    }

    switch (sysData.dataProcessCurrentState) {
        case P_STATE_COUNT_DATA_SEND:
#ifdef _debug            
            clearDataBuffer(&UART_1.transmitDataBuffer, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, countDataBuffer.doorNo, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((countDataBuffer.openTime >> 24) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((countDataBuffer.openTime >> 16) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((countDataBuffer.openTime >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) (countDataBuffer.openTime & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((countDataBuffer.closeTime >> 24) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((countDataBuffer.closeTime >> 16) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((countDataBuffer.closeTime >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) (countDataBuffer.closeTime & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, countDataBuffer.Cat_1_In, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, countDataBuffer.Cat_1_Out, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, countDataBuffer.Cat_2_In, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, countDataBuffer.Cat_2_Out, BUFFER_SIZE);
            prepareMessagePackage(EVENT_COUNT_DATA, &UART_1);
            addBufferToBuffer(&UART_1.messageBuffer, &UART_1.uartTransmitBuffer, BUFFER_SIZE);
            USART_1_StartTransmit();
            setTimer10ms(&uart_1_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
#endif        
            clearDataBuffer(&UART_5.transmitDataBuffer, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, countDataBuffer.doorNo, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((countDataBuffer.openTime >> 24) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((countDataBuffer.openTime >> 16) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((countDataBuffer.openTime >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) (countDataBuffer.openTime & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((countDataBuffer.closeTime >> 24) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((countDataBuffer.closeTime >> 16) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((countDataBuffer.closeTime >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) (countDataBuffer.closeTime & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, countDataBuffer.Cat_1_In, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, countDataBuffer.Cat_1_Out, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, countDataBuffer.Cat_2_In, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, countDataBuffer.Cat_2_Out, BUFFER_SIZE);
            prepareMessagePackage(EVENT_COUNT_DATA, &UART_5);
            addBufferToBuffer(&UART_5.messageBuffer, &UART_5.uartTransmitBuffer, BUFFER_SIZE);
            USART_5_StartTransmit();
            setTimer10ms(&uart_5_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
            sysData.dataProcessCurrentState = P_STATE_COUNT_DATA_WAIT_ACK;
            break;

        case P_STATE_COUNT_DATA_WAIT_ACK:
#ifdef _debug
            if ((UART_1.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
                sysData.dataProcessCurrentState = P_STATE_IDLE;
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
            } else if (isTimer10msTimeoutOccured(&uart_1_DataSendTimeoutTimer)) {
                sysData.dataProcessCurrentState = P_STATE_COUNT_DATA_RECORD_EEPROM;
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
            }
#endif       
            if ((UART_5.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
                sysData.dataProcessCurrentState = P_STATE_IDLE;
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
            } else if (isTimer10msTimeoutOccured(&uart_5_DataSendTimeoutTimer)) {
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif                
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                sysData.dataProcessCurrentState = P_STATE_COUNT_DATA_RECORD_EEPROM;
            }
            break;
        case P_STATE_COUNT_DATA_RECORD_EEPROM:
            i2cWriteBuffer[0] = countDataBuffer.doorNo;
            i2cWriteBuffer[1] = (countDataBuffer.openTime >> 24) & 0x000000FF;
            i2cWriteBuffer[2] = (countDataBuffer.openTime >> 16) & 0x000000FF;
            i2cWriteBuffer[3] = (countDataBuffer.openTime >> 8) & 0x000000FF;
            i2cWriteBuffer[4] = countDataBuffer.openTime & 0x000000FF;
            i2cWriteBuffer[5] = (countDataBuffer.closeTime >> 24) & 0x000000FF;
            i2cWriteBuffer[6] = (countDataBuffer.closeTime >> 16) & 0x000000FF;
            i2cWriteBuffer[7] = (countDataBuffer.closeTime >> 8) & 0x000000FF;
            i2cWriteBuffer[8] = countDataBuffer.closeTime & 0x000000FF;
            i2cWriteBuffer[9] = countDataBuffer.Cat_1_In;
            i2cWriteBuffer[10] = countDataBuffer.Cat_1_Out;
            i2cWriteBuffer[11] = countDataBuffer.Cat_2_In;
            i2cWriteBuffer[12] = countDataBuffer.Cat_2_Out;
            eepromWrite(COUNTING_LOG_AREA_START_ADDRESS + (sysData.countDataLogWriteIndex * COUNTING_DATA_SIZE), COUNTING_DATA_SIZE, i2cWriteBuffer);
            updateCountDataLogWriteIndexToEEprom();
            sysData.dataProcessCurrentState = P_STATE_IDLE;
            break;

        case P_STATE_STATUS_DATA_SEND:
#ifdef _debug  
            clearDataBuffer(&UART_1.transmitDataBuffer, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((statusDataBuffer.currentTime >> 24) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((statusDataBuffer.currentTime >> 16) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((statusDataBuffer.currentTime >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) (statusDataBuffer.currentTime & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, statusDataBuffer.statusType, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, statusDataBuffer.doorNo, BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) ((statusDataBuffer.status >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_1.transmitDataBuffer, (unsigned char) (statusDataBuffer.status & 0x000000FF), BUFFER_SIZE);
            prepareMessagePackage(EVENT_STATUS_DATA, &UART_1);
            addBufferToBuffer(&UART_1.messageBuffer, &UART_1.uartTransmitBuffer, BUFFER_SIZE);
            USART_1_StartTransmit();
            setTimer10ms(&uart_1_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
#endif      
            clearDataBuffer(&UART_5.transmitDataBuffer, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((statusDataBuffer.currentTime >> 24) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((statusDataBuffer.currentTime >> 16) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((statusDataBuffer.currentTime >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) (statusDataBuffer.currentTime & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, statusDataBuffer.statusType, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, statusDataBuffer.doorNo, BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) ((statusDataBuffer.status >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&UART_5.transmitDataBuffer, (unsigned char) (statusDataBuffer.status & 0x000000FF), BUFFER_SIZE);
            prepareMessagePackage(EVENT_STATUS_DATA, &UART_5);
            addBufferToBuffer(&UART_5.messageBuffer, &UART_5.uartTransmitBuffer, BUFFER_SIZE);
            USART_5_StartTransmit();
            setTimer10ms(&uart_5_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
            sysData.dataProcessCurrentState = P_STATE_STATUS_DATA_WAIT_ACK;
            break;
            //
        case P_STATE_STATUS_DATA_WAIT_ACK:
#ifdef _debug            
            if ((UART_1.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
                sysData.dataProcessCurrentState = P_STATE_IDLE;
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
            } else if (isTimer10msTimeoutOccured(&uart_1_DataSendTimeoutTimer)) {
                sysData.dataProcessCurrentState = P_STATE_STATUS_DATA_RECORD_EEPROM;
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
            }
#endif        
            if ((UART_5.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
                sysData.dataProcessCurrentState = P_STATE_IDLE;
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif                 
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
            } else if (isTimer10msTimeoutOccured(&uart_5_DataSendTimeoutTimer)) {
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif                 
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                sysData.dataProcessCurrentState = P_STATE_STATUS_DATA_RECORD_EEPROM;
            }
            break;
        case P_STATE_STATUS_DATA_RECORD_EEPROM:
            i2cWriteBuffer[0] = (unsigned char) ((statusDataBuffer.currentTime >> 24) & 0x000000FF);
            i2cWriteBuffer[1] = (unsigned char) ((statusDataBuffer.currentTime >> 16) & 0x000000FF);
            i2cWriteBuffer[2] = (unsigned char) ((statusDataBuffer.currentTime >> 8) & 0x000000FF);
            i2cWriteBuffer[3] = (unsigned char) (statusDataBuffer.currentTime & 0x000000FF);
            i2cWriteBuffer[4] = statusDataBuffer.statusType;
            i2cWriteBuffer[5] = statusDataBuffer.doorNo;
            i2cWriteBuffer[6] = (unsigned char) ((statusDataBuffer.status >> 8) & 0x000000FF);
            i2cWriteBuffer[7] = (unsigned char) (statusDataBuffer.status & 0x000000FF);
            eepromWrite(STATUS_LOG_AREA_START_ADDRESS + (sysData.statusDataLogWriteIndex * STATUS_DATA_SIZE), STATUS_DATA_SIZE, i2cWriteBuffer);
            updateStatusDataLogWriteIndexToEEprom();
            sysData.dataProcessCurrentState = P_STATE_IDLE;
            break;
        case P_STATE_RECORDED_COUNT_DATA_SEND:
#ifdef _debug
            addBufferToBuffer(&UART_1.messageBuffer, &UART_1.uartTransmitBuffer, BUFFER_SIZE);
            USART_1_StartTransmit();
            setTimer10ms(&uart_1_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
#endif            
            addBufferToBuffer(&UART_5.messageBuffer, &UART_5.uartTransmitBuffer, BUFFER_SIZE);
            USART_5_StartTransmit();
            setTimer10ms(&uart_5_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
            sysData.dataProcessCurrentState = P_STATE_RECORDED_COUNT_DATA_WAIT_ACK;
            break;
        case P_STATE_RECORDED_COUNT_DATA_WAIT_ACK:
#ifdef _debug
            if ((UART_1.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                updateCountDataLogReadIndexToEEprom();
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            } else if (isTimer10msTimeoutOccured(&uart_1_DataSendTimeoutTimer)) {
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            }
#endif            
            if ((UART_5.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif                 
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                updateCountDataLogReadIndexToEEprom();
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            } else if (isTimer10msTimeoutOccured(&uart_5_DataSendTimeoutTimer)) {
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif 
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            }
            break;
        case P_STATE_RECORDED_STATUS_DATA_SEND:
#ifdef _debug
            addBufferToBuffer(&UART_1.messageBuffer, &UART_1.uartTransmitBuffer, BUFFER_SIZE);
            USART_1_StartTransmit();
            setTimer10ms(&uart_1_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
            sysData.dataProcessCurrentState = P_STATE_RECORDED_STATUS_DATA_WAIT_ACK;
#endif         
            addBufferToBuffer(&UART_5.messageBuffer, &UART_5.uartTransmitBuffer, BUFFER_SIZE);
            USART_5_StartTransmit();
            setTimer10ms(&uart_5_DataSendTimeoutTimer, DATA_SEND_DELAY_TIME);
            sysData.dataProcessCurrentState = P_STATE_RECORDED_STATUS_DATA_WAIT_ACK;
            break;
        case P_STATE_RECORDED_STATUS_DATA_WAIT_ACK:
#ifdef _debug
            if ((UART_1.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                updateStatusDataLogReadIndexToEEprom();
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            } else if (isTimer10msTimeoutOccured(&uart_1_DataSendTimeoutTimer)) {
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            }
#endif            
            if ((UART_5.receivedCommand == RSP_ACK) && (sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE == 1)) {
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif                    
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                updateStatusDataLogReadIndexToEEprom();
                sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            } else if (isTimer10msTimeoutOccured(&uart_5_DataSendTimeoutTimer)) {
#ifdef _debug
                disableTimer10ms(&uart_1_DataSendTimeoutTimer);
#endif                    
                disableTimer10ms(&uart_5_DataSendTimeoutTimer);
                sysData.dataProcessCurrentState = P_STATE_IDLE;
            }
            break;
        default:
            sysData.dataProcessCurrentState = P_STATE_IDLE;
            break;
    }
}

void updateCountDataLogWriteIndexToEEprom(void) {
    sysData.countDataLogWriteIndex++;
    i2cWriteBuffer[0] = hibyte(sysData.countDataLogWriteIndex);
    i2cWriteBuffer[1] = lobyte(sysData.countDataLogWriteIndex);
    i2cWriteBuffer[2] = hibyte(sysData.countDataLogReadIndex);
    i2cWriteBuffer[3] = lobyte(sysData.countDataLogReadIndex);
    i2cWriteBuffer[4] = 0xFF;
    i2cWriteBuffer[5] = 0xFF;
    i2cWriteBuffer[6] = 0xFF;
    i2cWriteBuffer[7] = 0xFF;

    eepromWrite((COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS + (sysData.countDataIndex * COUNTING_DATA_INDEX_SIZE)), COUNTING_DATA_INDEX_SIZE * 2, i2cWriteBuffer);
    ++sysData.countDataIndex;
    if (sysData.countDataLogWriteIndex == MAX_COUNT_INDEX)
        sysData.countDataLogWriteIndex = 0;
    if (sysData.countDataIndex == COUNTING_DATA_INDEX_BUFFER_COUNT)
        sysData.countDataIndex = 0;
}

void updateCountDataLogReadIndexToEEprom(void) {
    sysData.countDataLogReadIndex++;
    i2cWriteBuffer[0] = hibyte(sysData.countDataLogWriteIndex);
    i2cWriteBuffer[1] = lobyte(sysData.countDataLogWriteIndex);
    i2cWriteBuffer[2] = hibyte(sysData.countDataLogReadIndex);
    i2cWriteBuffer[3] = lobyte(sysData.countDataLogReadIndex);
    i2cWriteBuffer[4] = 0xFF;
    i2cWriteBuffer[5] = 0xFF;
    i2cWriteBuffer[6] = 0xFF;
    i2cWriteBuffer[7] = 0xFF;

    eepromWrite((COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS + (sysData.countDataIndex * COUNTING_DATA_INDEX_SIZE)), COUNTING_DATA_INDEX_SIZE * 2, i2cWriteBuffer);
    sysData.countDataIndex++;
    if (sysData.countDataLogReadIndex == MAX_COUNT_INDEX)
        sysData.countDataLogReadIndex = 0;
    if (sysData.countDataIndex == COUNTING_DATA_INDEX_BUFFER_COUNT)
        sysData.countDataIndex = 0;
}

void updateCountDataIndexFromEEprom(void) {
    unsigned char index = 0;
    unsigned char address = 0;

    eepromRead(COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, COUNTING_DATA_INDEX_BUFFER_COUNT * COUNTING_DATA_INDEX_SIZE, i2cReadBuffer);
    //    i2cEepromReadWrite(READ, COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, COUNTING_DATA_INDEX_BUFFER_COUNT * COUNTING_DATA_INDEX_SIZE, i2cReadBuffer);
    while (index < COUNTING_DATA_INDEX_BUFFER_COUNT) {
        address = index * COUNTING_DATA_INDEX_SIZE;
        if (i2cReadBuffer[address] == 0xFF) {
            ++address;
            if (i2cReadBuffer[address] == 0xFF) {
                ++address;
                if (i2cReadBuffer[address] == 0xFF) {
                    ++address;
                    if (i2cReadBuffer[address] == 0xFF) {
                        sysData.countDataIndex = index;
                        --index;
                        if (index == 0xFF) {
                            index = COUNTING_DATA_INDEX_BUFFER_COUNT - 1;
                        }
                        address = index * COUNTING_DATA_INDEX_SIZE;
                        sysData.countDataLogWriteIndex = i2cReadBuffer[address++];
                        sysData.countDataLogWriteIndex <<= 8;
                        sysData.countDataLogWriteIndex |= i2cReadBuffer[address++];
                        sysData.countDataLogReadIndex = i2cReadBuffer[address++];
                        sysData.countDataLogReadIndex <<= 8;
                        sysData.countDataLogReadIndex |= i2cReadBuffer[address];
                        if (sysData.countDataLogWriteIndex == 0xFFFF)
                            sysData.countDataLogWriteIndex = 0;
                        if (sysData.countDataLogReadIndex == 0xFFFF)
                            sysData.countDataLogReadIndex = 0;
                        break;
                    }
                }
            }
        }
        ++index;
    }
}

void updateStatusDataLogWriteIndexToEEprom(void) {
    sysData.statusDataLogWriteIndex++;
    i2cWriteBuffer[0] = hibyte(sysData.statusDataLogWriteIndex);
    i2cWriteBuffer[1] = lobyte(sysData.statusDataLogWriteIndex);
    i2cWriteBuffer[2] = hibyte(sysData.statusDataLogReadIndex);
    i2cWriteBuffer[3] = lobyte(sysData.statusDataLogReadIndex);
    i2cWriteBuffer[4] = 0xFF;
    i2cWriteBuffer[5] = 0xFF;
    i2cWriteBuffer[6] = 0xFF;
    i2cWriteBuffer[7] = 0xFF;

    eepromWrite((STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS + (sysData.statusDataIndex * STATUS_DATA_INDEX_SIZE)), STATUS_DATA_INDEX_SIZE * 2, i2cWriteBuffer);
    ++sysData.statusDataIndex;
    if (sysData.statusDataLogWriteIndex == MAX_STATUS_INDEX)
        sysData.statusDataLogWriteIndex = 0;
    if (sysData.statusDataIndex == STATUS_DATA_INDEX_BUFFER_COUNT)
        sysData.statusDataIndex = 0;
}

void updateStatusDataLogReadIndexToEEprom(void) {
    sysData.statusDataLogReadIndex++;
    i2cWriteBuffer[0] = hibyte(sysData.statusDataLogWriteIndex);
    i2cWriteBuffer[1] = lobyte(sysData.statusDataLogWriteIndex);
    i2cWriteBuffer[2] = hibyte(sysData.statusDataLogReadIndex);
    i2cWriteBuffer[3] = lobyte(sysData.statusDataLogReadIndex);
    i2cWriteBuffer[4] = 0xFF;
    i2cWriteBuffer[5] = 0xFF;
    i2cWriteBuffer[6] = 0xFF;
    i2cWriteBuffer[7] = 0xFF;

    eepromWrite((STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS + (sysData.statusDataIndex * STATUS_DATA_INDEX_SIZE)), STATUS_DATA_INDEX_SIZE * 2, i2cWriteBuffer);
    sysData.statusDataIndex++;
    if (sysData.statusDataLogReadIndex == MAX_STATUS_INDEX)
        sysData.statusDataLogReadIndex = 0;
    if (sysData.statusDataIndex == STATUS_DATA_INDEX_BUFFER_COUNT)
        sysData.statusDataIndex = 0;
}

void updateStatusDataIndexFromEEprom(void) {
    unsigned char index = 0;
    unsigned char address = 0;

    eepromRead(STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, STATUS_DATA_INDEX_BUFFER_COUNT * STATUS_DATA_INDEX_SIZE, i2cReadBuffer);
    //    i2cEepromReadWrite(READ, COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, COUNTING_DATA_INDEX_BUFFER_COUNT * COUNTING_DATA_INDEX_SIZE, i2cReadBuffer);
    while (index < STATUS_DATA_INDEX_BUFFER_COUNT) {
        address = index * STATUS_DATA_INDEX_SIZE;
        if (i2cReadBuffer[address] == 0xFF) {
            ++address;
            if (i2cReadBuffer[address] == 0xFF) {
                ++address;
                if (i2cReadBuffer[address] == 0xFF) {
                    ++address;
                    if (i2cReadBuffer[address] == 0xFF) {
                        sysData.statusDataIndex = index;
                        --index;
                        if (index == 0xFF) {
                            index = STATUS_DATA_INDEX_BUFFER_COUNT - 1;
                        }
                        address = index * STATUS_DATA_INDEX_SIZE;
                        sysData.statusDataLogWriteIndex = i2cReadBuffer[address++];
                        sysData.statusDataLogWriteIndex <<= 8;
                        sysData.statusDataLogWriteIndex |= i2cReadBuffer[address++];
                        sysData.statusDataLogReadIndex = i2cReadBuffer[address++];
                        sysData.statusDataLogReadIndex <<= 8;
                        sysData.statusDataLogReadIndex |= i2cReadBuffer[address];
                        if (sysData.statusDataLogWriteIndex == 0xFFFF)
                            sysData.statusDataLogWriteIndex = 0;
                        if (sysData.statusDataLogReadIndex == 0xFFFF)
                            sysData.statusDataLogReadIndex = 0;
                        break;
                    }
                }
            }
        }
        ++index;
    }
}

void updateSystemParametersFromEEprom(void) {
    unsigned char address = 0;
    unsigned char count = 0;

    eepromRead(SYSTEM_PARAMETERS_EEPROM_START_ADDRESS, SYSTEM_PARAMETERS_EEPROM_SIZE, i2cReadBuffer);

    SYSTEM_PARAMETERS.SystemDoorCount = i2cReadBuffer[SYSTEM_DOOR_COUNT_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategoryCount = i2cReadBuffer[SYSTEM_COUNT_CATEGORY_COUNT_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_1 = i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_1_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_2 = i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_2_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 = i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 <<= 8;
    SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 |= i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS + 1];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 = i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 <<= 8;
    SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 |= i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS + 1];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 = i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 <<= 8;
    SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 |= i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS + 1];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 = i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS];
    SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 <<= 8;
    SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 |= i2cReadBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS + 1];

    count = 0;
    address = SENSOR_1_ADDRESS_EEADRESS;
    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        sysData.Door[count].SENSOR_ADDRESS = (unsigned int) i2cReadBuffer[address + count];
        ++address;
        sysData.Door[count].SENSOR_ADDRESS <<= 8;
        sysData.Door[count].SENSOR_ADDRESS |= (unsigned int) i2cReadBuffer[address + count];
        ++count;
    }

    count = 0;
    address = SENSOR_1_FA_EEADRESS;
    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        sysData.Door[count].FA = (unsigned int) i2cReadBuffer[address + count];
        ++address;
        sysData.Door[count].FA <<= 8;
        sysData.Door[count].FA |= (unsigned int) i2cReadBuffer[address + count];
        ++count;
    }
    SYSTEM_PARAMETERS.INPUT_TYPES.input_types = i2cReadBuffer[INPUT_TYPES_EEPROM_ADDRESS];

    count = 0;

}

void recordSystemParametersToEEprom(void) {
    unsigned char address = 0;
    unsigned char count = 0;

    i2cWriteBuffer[SYSTEM_DOOR_COUNT_EEADRESS] = SYSTEM_PARAMETERS.SystemDoorCount;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_COUNT_EEADRESS] = SYSTEM_PARAMETERS.SystemCountCategoryCount;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_EEADRESS] = SYSTEM_PARAMETERS.SystemCountCategory_ID_1;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_EEADRESS] = SYSTEM_PARAMETERS.SystemCountCategory_ID_2;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 >> 8) & 0x00FF);
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS + 1] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1) & 0x00FF);
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 >> 8) & 0x00FF);
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS + 1] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2) & 0x00FF);
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 >> 8) & 0x00FF);
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS + 1] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1) & 0x00FF);
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 >> 8) & 0x00FF);
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS + 1] = (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2) & 0x00FF);

    count = 0;
    address = SENSOR_1_ADDRESS_EEADRESS;
    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        i2cWriteBuffer[address + count] = (unsigned char) ((sysData.Door[count].SENSOR_ADDRESS >> 8)&0x000000FF);
        ++address;
        i2cWriteBuffer[address + count] = (unsigned char) (sysData.Door[count].SENSOR_ADDRESS & 0x000000FF);
        ++count;
    }

    count = 0;
    address = SENSOR_1_FA_EEADRESS;
    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        i2cWriteBuffer[address + count] = (unsigned char) ((sysData.Door[count].FA >> 8)&0x000000FF);
        ++address;
        i2cWriteBuffer[address + count] = (unsigned char) (sysData.Door[count].FA & 0x000000FF);
        ++count;
    }
    i2cWriteBuffer[INPUT_TYPES_EEPROM_ADDRESS] = SYSTEM_PARAMETERS.INPUT_TYPES.input_types;
    eepromWrite(SYSTEM_PARAMETERS_EEPROM_START_ADDRESS, SYSTEM_PARAMETERS_EEPROM_SIZE, i2cWriteBuffer);
}

void getSensorParameters(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sourceSensors, volatile IRMA_SENSOR_TYPE* destinationSensors) {
    IRMA_getSensorFA(sensorAddress, sourceSensors, destinationSensors);
    IRMA_getSensorCountParameters(sensorAddress, sourceSensors, destinationSensors);
}

void checkAllSensorParameters(void) { //Ramdaki ve sensorlerdeki parametreleri karsilastirir ve sonucu sysData.sensorCheckStatus[]'a yazar.
    unsigned int i = 0;
    unsigned char address = 0;
    unsigned short temp = 0;
    unsigned char temp1 = 0;

    updateSystemParametersFromEEprom();
    //Clear flags
    for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
        sysData.sensorCheckStatus[i].sensorCheckStatusData = 0;
    }
    //Get all sensor parameters to sysData.checkedSensors[]
    for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
        getSensorParameters(sysData.Door[i].SENSOR_ADDRESS, sysData.Door, sysData.checkedSensor);
    }
    for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
        if (sysData.Door[i].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR)
            sysData.sensorCheckStatus[i].SENSOR_CHECK_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
    }
    for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
        if (sysData.Door[i].FA != sysData.checkedSensor[i].FA) {
            sysData.sensorCheckStatus[i].SENSOR_CHECK_STATUS_FLAGS.FA_DOES_NOT_MATCH = 1;
        }
    }
    for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
        if (sysData.Door[i].COUNT_CATEGORY_COUNT != sysData.checkedSensor[i].COUNT_CATEGORY_COUNT) {
            sysData.sensorCheckStatus[i].SENSOR_CHECK_STATUS_FLAGS.COUNT_CATEGORY_COUNT_DOES_NOT_MATCH = 1;
        }
    }
    for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
        if (sysData.Door[i].COUNT_CATEGORY_1_ID != sysData.checkedSensor[i].COUNT_CATEGORY_1_ID) {
            sysData.sensorCheckStatus[i].SENSOR_CHECK_STATUS_FLAGS.COUNT_CATEGORY_1_ID_DOES_NOT_MATCH = 1;
        }
    }

    if (SYSTEM_PARAMETERS.SystemCountCategoryCount > 1) {
        for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
            if (sysData.Door[i].COUNT_CATEGORY_2_ID != sysData.checkedSensor[i].COUNT_CATEGORY_2_ID) {
                sysData.sensorCheckStatus[i].SENSOR_CHECK_STATUS_FLAGS.COUNT_CATEGORY_2_ID_DOES_NOT_MATCH = 1;
            }
        }
        for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
            if ((sysData.Door[i].COUNT_CATEGORY_1_PARAMETER_1 != sysData.checkedSensor[i].COUNT_CATEGORY_1_PARAMETER_1) ||
                    (sysData.Door[i].COUNT_CATEGORY_1_PARAMETER_2 != sysData.checkedSensor[i].COUNT_CATEGORY_1_PARAMETER_2)) {
                sysData.sensorCheckStatus[i].SENSOR_CHECK_STATUS_FLAGS.CAT_1_PARAMS_DOES_NOT_MATCH = 1;
            }
        }
        for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
            if ((sysData.Door[i].COUNT_CATEGORY_2_PARAMETER_1 != sysData.checkedSensor[i].COUNT_CATEGORY_2_PARAMETER_1) ||
                    (sysData.Door[i].COUNT_CATEGORY_2_PARAMETER_2 != sysData.checkedSensor[i].COUNT_CATEGORY_2_PARAMETER_2)) {
                sysData.sensorCheckStatus[i].SENSOR_CHECK_STATUS_FLAGS.CAT_2_PARAMS_DOES_NOT_MATCH = 1;
            }
        }
    }
}

void systemStartupCheck(volatile UART_DATA_TYPE* uartTransmit, volatile UART_DATA_TYPE* uartReceive, unsigned char uartType) {
    unsigned char count = 0;
    unsigned char faultIndicator = 0;

    checkAllSensorParameters();
    while (count < SYSTEM_PARAMETERS.SystemDoorCount) {
        if (sysData.sensorCheckStatus[count].sensorCheckStatusData != 0) {
            faultIndicator = 1;
            break;
        }
        ++count;
    }
    if (faultIndicator == 1) {
        addDataToBuffer(&uartTransmit->transmitDataBuffer, SYSTEM_PARAMETERS.SystemDoorCount, BUFFER_SIZE);
        unsigned int i = 0;
        for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
            addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (sysData.sensorCheckStatus[i].sensorCheckStatusData & 0x000000FF), BUFFER_SIZE);
        }
        uartTransmit->command = RSP_STARTUP_CHECK_PARAMETERS;
        prepareMessagePackage(uartTransmit->command, uartTransmit);
        addBufferToBuffer(&uartTransmit->messageBuffer, &uartTransmit->uartTransmitBuffer, BUFFER_SIZE);
        if (uartType == ETH_) {
            USART_1_StartTransmit();
        } else if (uartType == KIFI_) {
            USART_5_StartTransmit();
        } else if (uartType == BOTH_) {
            USART_1_StartTransmit();
            USART_5_StartTransmit();
        }
    }
}

void fakeInit(void) {
    unsigned char count = 0;

    i2cWriteBuffer[SYSTEM_DOOR_COUNT_EEADRESS] = 1;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_COUNT_EEADRESS] = 1;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_EEADRESS] = 0;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_EEADRESS] = 1;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS] = 0x02;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_1_EEADRESS + 1] = 0xBC;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS] = 0x0B;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_1_PARAM_2_EEADRESS + 1] = 0xB8;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS] = 0x02;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_1_EEADRESS + 1] = 0xBC;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS] = 0x0B;
    i2cWriteBuffer[SYSTEM_COUNT_CATEGORY_ID_2_PARAM_2_EEADRESS + 1] = 0xB8;
    i2cWriteBuffer[SENSOR_1_ADDRESS_EEADRESS] = 0x62;
    i2cWriteBuffer[SENSOR_1_ADDRESS_EEADRESS + 1] = 0xD7;
    i2cWriteBuffer[SENSOR_1_FA_EEADRESS] = 0x00;
    i2cWriteBuffer[SENSOR_1_FA_EEADRESS + 1] = 0x01;
    i2cWriteBuffer[INPUT_TYPES_EEPROM_ADDRESS] = 0xFF;

    eepromWrite(SYSTEM_PARAMETERS_EEPROM_START_ADDRESS, SYSTEM_PARAMETERS_EEPROM_SIZE, i2cWriteBuffer);
    eepromRead(SYSTEM_PARAMETERS_EEPROM_START_ADDRESS, SYSTEM_PARAMETERS_EEPROM_SIZE, i2cReadBuffer);

    count = 0;
    while (count < 128) {
        i2cWriteBuffer[count] = 0xFF;
        ++count;
    }
    eepromWrite(COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, COUNTING_DATA_INDEX_BUFFER_COUNT * COUNTING_DATA_INDEX_SIZE, i2cWriteBuffer);
    eepromRead(COUNTING_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, COUNTING_DATA_INDEX_BUFFER_COUNT * COUNTING_DATA_INDEX_SIZE, i2cReadBuffer);

    eepromWrite(STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, STATUS_DATA_INDEX_BUFFER_COUNT * STATUS_DATA_INDEX_SIZE, i2cWriteBuffer);
    eepromRead(STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, STATUS_DATA_INDEX_BUFFER_COUNT * STATUS_DATA_INDEX_SIZE, i2cReadBuffer);

    //    while (!i2cEepromReadWrite(WRITE, 128, 64, i2cWriteBuffer));
    //    while (!i2cEepromReadWrite(READ, 128, 64, i2cReadBuffer));
    //    while (!i2cEepromReadWrite(READ, 0, 128, i2cReadBuffer));

    //    eepromWrite(100, 80, i2cWriteBuffer);
    //    //        eepromWrite(STATUS_DATA_INDEX_EEPROM_AREA_START_EEADDRESS, STATUS_DATA_INDEX_BUFFER_COUNT * STATUS_DATA_INDEX_SIZE, i2cWriteBuffer);
    //    eepromRead(100, 80, i2cReadBuffer);
    //
    //    
    //    eepromWrite(124, 80, i2cWriteBuffer);
    //    eepromRead(124, 80, i2cReadBuffer);



}


/*******************************************************************************
 End of File
 */
