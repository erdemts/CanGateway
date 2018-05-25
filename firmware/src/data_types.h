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

#ifndef _DATA_TYPES_H    /* Guard against multiple inclusion */
#define _DATA_TYPES_H




/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system/tmr/sys_tmr.h"
#include "app.h"
#include <time.h>
#include "IRMA.h"
#include "timerDefinitions.h"


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
typedef union {
        struct {
            unsigned char Lat0;
            unsigned char Lat1;
            unsigned char Lat2;
            unsigned char Lat3;
        };
        unsigned int latitude;
    } LATITUDE_TYPE;

    typedef union {
        struct {
            unsigned char Lon0;
            unsigned char Lon1;
            unsigned char Lon2;
            unsigned char Lon3;
        };
        unsigned int longitude;
    } LONGITUDE_TYPE;
    
    typedef struct {
        unsigned DOOR_1_STATE : 1;
        unsigned DOOR_2_STATE : 1;
        unsigned DOOR_3_STATE : 1;
        unsigned DOOR_4_STATE : 1;
        unsigned DOOR_5_STATE : 1;
        unsigned DOOR_6_STATE : 1;
        unsigned DOOR_7_STATE : 1;
        unsigned DOOR_8_STATE : 1;
        /* Unimplemented bit. Should be always 0. */
        unsigned unimplemented : 24;
    } DOOR_FLAGS_TYPE;

    typedef union {

        struct {
            /* This is can identifier portion of the CAN Receive message */
            DOOR_FLAGS_TYPE DOOR_STATES_FLAGS;
        };
        unsigned int door_states;
    } DOOR_STATES_TYPE;

    typedef struct {
        unsigned INPUT_1_STATE : 1;
        unsigned INPUT_2_STATE : 1;
        unsigned INPUT_3_STATE : 1;
        unsigned INPUT_4_STATE : 1;
        unsigned INPUT_5_STATE : 1;
        /* Unimplemented bit. Should be always 0. */
        unsigned unimplemented : 27;
    } INPUT_STATES_FLAGS_TYPE;

    typedef union {

        struct {
            /* This is can identifier portion of the CAN Receive message */
            INPUT_STATES_FLAGS_TYPE INPUT_STATES_FLAGS;
        };
        unsigned short input_states;
    } INPUT_STATES_TYPE;

    typedef struct {
        unsigned NEW_COMMAND_AVAIBLE : 1;
        unsigned CHECK_IO : 1;

        /* Unimplemented bit. Should be always 0. */
        unsigned unimplemented : 31;
    } SYSTEM_STATUS_FLAGS_TYPE;

    typedef union {

        struct {
            /* This is can identifier portion of the CAN Receive message */
            SYSTEM_STATUS_FLAGS_TYPE SYSTEM_STATUS_FLAGS;
        };
        unsigned int system_status;
    } SYSTEM_STATUS_TYPE;

    typedef struct {
        SYS_TMR_HANDLE pollingTimerHandle;
        bool POLLING_TIMER_EN;
    } SYSTEM_POLLING_TIMER_DATA_TYPE;

    typedef struct {
        unsigned INPUT_1_TYPE : 1;
        unsigned INPUT_2_TYPE : 1;
        unsigned INPUT_3_TYPE : 1;
        unsigned INPUT_4_TYPE : 1;
        unsigned INPUT_5_TYPE : 1;
        unsigned INPUT_6_TYPE : 1;
        unsigned INPUT_7_TYPE : 1;
        unsigned INPUT_8_TYPE : 1;

        /* Unimplemented bit. Should be always 0. */
        unsigned unimplemented : 24;
    } INPUT_TYPES_FLAGS_TYPE;

    typedef union {

        struct {
            /* This is can identifier portion of the CAN Receive message */
            INPUT_TYPES_FLAGS_TYPE INPUT_TYPES_FLAGS;
        };
        unsigned short input_types;
    } INPUT_TYPES_TYPE;

    typedef struct { //TODO: Hangi bayraklarin gonderilecegi daha sonra netlestirilecek.
        unsigned CAN_SYSTEM_ERROR_EVENT_FLAG : 1;
        unsigned CAN_BUS_ERROR_EVENT_FLAG : 1;
        unsigned CAN_TX_BUS_OFF_STATE_FLAG : 1;
        unsigned CAN_TX_RX_WARNING_STATE_FLAG : 1;
        unsigned CAN_RX_WARNING_STATE_FLAG : 1;
        unsigned CAN_TX_WARNING_STATE_FLAG : 1;
        unsigned CAN_RX_BUS_PASSIVE_STATE_FLAG : 1;
        unsigned CAN_TX_BUS_PASSIVE_STATE_FLAG : 1;

        unsigned CAN_RX_OVERFLOW_EVENT_FLAG : 1;
        unsigned CAN_TRANSMIT_ERROR_COUNT_HIGH_FLAG : 1;
        unsigned CAN_RECEIVE_ERROR_COUNT_HIGH_FLAG : 1;
        unsigned CAN_CABLE_ERROR : 1;
        unsigned CAN_INVALID_RX_MESSAGE_EVENT_FLAG : 1;

        unsigned unimplemented : 19;
    } CAN_ERROR_FLAGS_TYPE;

    
    typedef union {

        struct {
            CAN_ERROR_FLAGS_TYPE CAN_1_ERROR_FLAGS;
        };
        unsigned int can_1_Errors;
    } CAN_ERROR_TYPE;

    typedef struct {
        unsigned CAN_NOT_COMMUNICATE_TO_SENSOR : 1;
        unsigned FA_DOES_NOT_MATCH : 1;
        unsigned COUNT_CATEGORY_COUNT_DOES_NOT_MATCH : 1;
        unsigned COUNT_CATEGORY_1_ID_DOES_NOT_MATCH : 1;
        unsigned COUNT_CATEGORY_2_ID_DOES_NOT_MATCH : 1;
        unsigned CAT_1_PARAMS_DOES_NOT_MATCH : 1;
        unsigned CAT_2_PARAMS_DOES_NOT_MATCH : 1;

        unsigned unimplemented : 25;
    }
    SENSOR_CHECK_STATUS_FLAGS_TYPE;

    typedef union {

        struct {
            SENSOR_CHECK_STATUS_FLAGS_TYPE SENSOR_CHECK_STATUS_FLAGS;
        };
        unsigned int sensorCheckStatusData;
    } SENSOR_CHECK_STATUS_TYPE;

    typedef struct {
        SYSTEM_STATUS_TYPE SYSTEM_STATUS;
        CAN_ERROR_TYPE CAN_ERRORS;
        CAN_ERROR_TYPE OLD_CAN_ERRORS;
        INPUT_STATES_TYPE CURRENT_INPUT_STATES;
        INPUT_STATES_TYPE OLD_INPUT_STATES;
        DOOR_STATES_TYPE CURRENT_DOOR_STATES;
        LATITUDE_TYPE LATITUDE;
        LONGITUDE_TYPE LONGITUDE;
        unsigned short CAT_1_IN_TOTAL;
        unsigned short CAT_1_OUT_TOTAL;
        unsigned short CAT_2_IN_TOTAL;
        unsigned short CAT_2_OUT_TOTAL;
        unsigned short countDataLogWriteIndex;
        unsigned short countDataLogReadIndex;
        unsigned char countDataIndex;
        unsigned short statusDataLogWriteIndex;
        unsigned short statusDataLogReadIndex;
        unsigned char statusDataIndex;
        unsigned char dataProcessCurrentState;

        TIMER_TYPE sensorPollingTimer[MAX_SUPPORTED_SENSOR_COUNT];
        SYSTEM_POLLING_TIMER_DATA_TYPE eepromTimeoutTimer;
        
        IRMA_SENSOR_TYPE Door[MAX_SUPPORTED_SENSOR_COUNT];
        IRMA_SENSOR_TYPE checkedSensor[MAX_SUPPORTED_SENSOR_COUNT]; //check sensor isleminde kullan?lan degiskendir
        SENSOR_CHECK_STATUS_TYPE sensorCheckStatus[MAX_SUPPORTED_SENSOR_COUNT];
    } SYSTEM_DATA_TYPE;

    typedef struct {
        unsigned char SystemDoorCount;
        unsigned char SystemCountCategoryCount;
        unsigned char SystemCountCategory_ID_1;
        unsigned char SystemCountCategory_ID_2;
        unsigned short SystemCountCategory_ID_1_Param_1;
        unsigned short SystemCountCategory_ID_1_Param_2;
        unsigned short SystemCountCategory_ID_2_Param_1;
        unsigned short SystemCountCategory_ID_2_Param_2;
        INPUT_TYPES_TYPE INPUT_TYPES;
    } SYSTEM_PARAMETERS_TYPE;

    typedef struct {
        unsigned char doorNo;
        time_t openTime;
        time_t closeTime;
        unsigned char Cat_1_In;
        unsigned char Cat_1_Out;
        unsigned char Cat_2_In;
        unsigned char Cat_2_Out;
    } COUNT_DATA_BUFFER_TYPE;

    typedef struct {
        time_t currentTime;
        unsigned char statusType;
        unsigned char doorNo;
        unsigned short status;
    } STATUS_DATA_BUFFER_TYPE;



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************




    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
