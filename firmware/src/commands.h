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

#ifndef _COMMANDS_H    /* Guard against multiple inclusion */
#define _COMMANDS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#define STX                                             0xFE
#define ETX                                             0xFD
#define SEPERATOR                                       0xFC


    /*
     * 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * Data: Data bytes. Max 80 bytes lenght.
     * Lenght : Command + Data 
     * CRC : CCIT 16 XMODEM CRC. All bytes used to calculate CRC, exclude STX and ETX.
     * If any bytes are equal to STX, EXT or SEPERATOR in the data package, SEPERATOR comes before that byte.
     * <STX><Command><Lenght><"\"><0xFF><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * 
     */

    /*
     * 
     * <STX><Command><Lenght><Data><CRC_H><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * Data: Data bytes. Max 80 bytes lenght.
     * Lenght : Command + Data 
     * CRC : CCIT 16 XMODEM CRC. All bytes used to calculate CRC, exclude CRC_LENGHT,STX and ETX.
     * If any bytes are equal to STX, EXT or SEPERATOR in the data package, SEPERATOR comes before that byte.
     * <STX><Command><Lenght><"\"><0xFF><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * 
     */ /*                              COMMAND CODES                                 
     -----------------------------------------------------------------------------*/

    typedef enum {
        CMD_SET_DOOR_COUNT = 0x11,
        CMD_GET_DOOR_COUNT,
        CMD_SET_COUNT_CATEGORY_COUNT, //Max 2 count catagory avaible
        CMD_GET_COUNT_CATEGORY_COUNT, //For selected sensor 
        CMD_SET_COUNT_CATEGORY_ID,
        CMD_GET_COUNT_CATEGORY_ID,
        CMD_SET_DOOR_SENSOR_ADDRESS,
        CMD_GET_DOOR_SENSOR_ADDRESS,
        CMD_SET_DOOR_FA, //For selected door 
        CMD_GET_DOOR_FA,
        CMD_SET_COUNT_CATEGORY_PARAMETERS,
        CMD_GET_COUNT_CATEGORY_PARAMETERS,
        CMD_GET_SENSOR_STATUS,
        CMD_GET_COUNT_RESULT, //For selected door                
        CMD_GET_SYSTEM_STATUS,
        CMD_CHECK_SYSTEM_PARAMETERS,
        EVENT_COUNT_DATA,
        EVENT_STATUS_DATA,
        RSP_ACK,
        EVENT_SENSOR_STATUS,
        EVENT_CANBUS_STATUS,
        EVENT_SYSTEM_CHECK_STATUS,
        SET_LOCATION_AND_TIME,
        GET_LOCATION_AND_TIME,
        CMD_SET_DOOR_INPUT_TYPE,
        CMD_GET_DOOR_INPUT_TYPE
    } COMMANDS;

    /*                              RESPONSE CODES                                 
     -----------------------------------------------------------------------------*/
    typedef enum {
        RSP_DOOR_COUNT = 0x51,
        RSP_COUNT_CATEGORY_COUNT, //Max 2 count catagory avaible
        RSP_COUNT_CATEGORY_ID,
        RSP_DOOR_SENSOR_ADDRESS,
        RSP_DOOR_FA, //For selected door 
        RSP_COUNT_CATEGORY_PARAMETERS,
        RSP_SENSOR_STATUS,
        RSP_COUNT_RESULT, //For selected door
        RSP_CHECK_SYSTEM_PARAMETERS,
        RSP_STARTUP_CHECK_PARAMETERS,
        RSP_DOOR_INPUT_TYPE,
        RSP_LOCATION_AND_TIME,
        RSP_NACK
    } RESPONSES;





    /*------------------------COMMAND DESCRIPTIONS----------------------------------
     *------------------------------------------------------------------------------
     * 
     * COMMAND: SET_DOOR_COUNT 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * <STX><CMD_SET_DOOR_COUNT><0x02><DoorCount><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * DoorCount is 1 Byte 
     * Sample set:                                 
     * 
     * RESPONSE: 
     * <STX><RSP_ACK><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: GET_DOOR_COUNT 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><CMD_GET_DOOR_COUNT><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX> //No Data                                 
     * 
     * RESPONSE: 
     * <STX><RSP_DOOR_COUNT><0x02><DoorCount><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * DoorCount is 1 Byte
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: SET_COUNT_CATEGORY_COUNT 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><CMD_SET_COUNT_CATEGORY_COUNT><0x02><CountCategoryCount><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * CountCategoryCount is 1 Byte                                  
     * 
     * RESPONSE: 
     * <STX><RSP_ACK><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: GET_COUNT_CATEGORY_COUNT 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><GET_COUNT_CATEGORY_COUNT><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX> //No Data
     * CountCategoryCount is 1 Byte                                
     * 
     * RESPONSE: 
     * <STX><RSP_COUNT_CATEGORY_COUNT><0x02><CountCategoryCount><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * CountCategoryCount is 1 Byte
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: SET_COUNT_CATEGORY_ID 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><SET_COUNT_CATEGORY_ID><0x03><CategoryNumber(1 or 2)><CountCategoryID><CRC_LENGHT><CRC_H><CRC_L><ETX>  
     * CategoryNumber is 1 Byte
     * CountCategoryID is 1 Byte                               
     * 
     * RESPONSE:
     * <STX><RSP_ACK><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX>
     *
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: GET_COUNT_CATEGORY_ID 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><GET_COUNT_CATEGORY_ID><0x02><CategoryNumber(1 or 2)><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * CategoryNumber is 1 Byte                                 
     * 
     * RESPONSE: 
     * <STX><RSP_COUNT_CATEGORY_ID><0x02><CountCategoryID><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * CategoryNumber is 1 Byte
     * CountCategoryID is 1 Byte
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: SET_SENSOR_ADDRESS 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><SET_SENSOR_ADDRESS><0x06><DoorNumber><AddressByte_3><AddressByte_2><AddressByte_1><AddressByte_0><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * DoorNumber is 1 Byte
     * Address is 32 bit integer. (Big Endian)
     * AddressByte_3 is high byte of integer address - 1 Byte
     * AddressByte_2 is upper middle byte of integer address- 1 Byte
     * AddressByte_1 is lower middle byte of integer address- 1 Byte
     * AddressByte_0 is low byte of integer address - 1 Byte                             
     * 
     * RESPONSE: 
     * <STX><RSP_ACK><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     *
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: GET_SENSOR_ADDRESS 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><GET_SENSOR_ADDRESS><0x02><DoorNumber><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * DoorNumber is 1 Byte                                
     * 
     * RESPONSE: 
     * <STX><RSP_DOOR_SENSOR_ADDRESS><0x05><AddressByte_3><AddressByte_2><AddressByte_1><AddressByte_0><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * DoorNumber is 1 Byte
     * Address is 32 bit integer. (Big Endian)
     * AddressByte_3 is high byte of integer address - 1 Byte
     * AddressByte_2 is upper middle byte of integer address- 1 Byte
     * AddressByte_1 is lower middle byte of integer address- 1 Byte
     * AddressByte_0 is low byte of integer address - 1 Byte   
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: SET_DOOR_FA 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><SET_DOOR_FA><0x02><DoorNumber><FA_H><FA_L><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * DoorNumber is 1 Byte 
     * FA is 1 Byte                                
     * 
     * RESPONSE: 
     * <STX><RSP_ACK><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX>  
     * DoorNumber is 1 Byte 
     * FA is 1 Byte
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: GET_DOOR_FA 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><GET_DOOR_FA><0x02><DoorNumber><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * DoorNumber is 1 Byte                                 
     * 
     * RESPONSE: 
     * <STX><RSP_DOOR_FA><0x02><DoorNumber><FA><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * DoorNumber is 1 Byte 
     * FA is 1 Byte
     * 
     * -----------------------------------------------------------------------------
     * COMMAND: SET_COUNT_CATEGORY_PARAMETERS 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><SET_COUNT_CATEGORY_PARAMETERS><0x06><CategoryNumber(1 or 2)><Parameter1HighByte><Parameter1LowByte><Parameter2HighByte><Parameter2LowByte><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * CategoryNumber is 1 Byte
     * Parameter1 and Parameter2 are 16 bit shorts. (Big Endian)
     * Parameter1HighByte is high byte of short Parameter1 - 1 Byte
     * Parameter1LowByte is low byte of short Parameter1 - 1 Byte
     * Parameter2HighByte is high byte of short Parameter2 - 1 Byte
     * Parameter2LowByte is low byte of short Parameter2 - 1 Byte                                           
     * 
     * RESPONSE: 
     * <STX><RSP_ACK><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: GET_COUNT_CATEGORY_PARAMETERS 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><GET_COUNT_CATEGORY_PARAMETERS><0x02><CategoryNumber(1 or 2)><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * CategoryNumber is 1 Byte                                 
     * 
     * RESPONSE: 
     * <STX><RSP_COUNT_CATEGORY_PARAMETERS><0x06><CategoryNumber(1 or 2)><Parameter1HighByte><Parameter1LowByte><Parameter2HighByte><Parameter2LowByte><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * Parameter1 and Parameter2 are 16 bit shorts. (Big Endian)
     * Parameter1HighByte is high byte of short Parameter1 - 1 Byte
     * Parameter1LowByte is low byte of short Parameter1 - 1 Byte
     * Parameter2HighByte is high byte of short Parameter2 - 1 Byte
     * Parameter2LowByte is low byte of short Parameter2 - 1 Byte
     * 
     * -----------------------------------------------------------------------------
     * 
     * -----------------------------------------------------------------------------
     * 
     * COMMAND: GET_SENSOR_STATUS 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><GET_SENSOR_STATUS><0x02><DoorNo><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * SensorNo is 1 Byte                                 
     * 
     * RESPONSE: 
     * <STX><RSP_SENSOR_STATUS><0x03><StatusByteHigh><StatusByteLow><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * Status is 16 bit short. (Big Endian)
     * StatusByteHigh is high byte of short status - 1 Byte
     * StatusByteLow is high byte of short status - 1 Byte
     * 
     * 
     * STATUS BITS <b15><b14><b13><b12><b11><b10><b9><b8><b7><b6><b5><b4><b3><b2><b1><b0>
     * All status bit active when value=1. (eg. if Sabotage=1, sabotage occurred)
     * 
     * BIT 0    : Sabotage
     * BIT 1    : PrimaryConfigurationIsInvalid
     * BIT 2    : PrimaryConfigurationIsValid
     * BIT 3    : SensorCurrentlyRunningInServiceMode
     * BIT 4    : ConfigurationContainsOneOrMoreFaultyParameter
     * BIT 5    : ConfigurationIsInvalid
     * BIT 6    : MaxTemperatureWasExceededAtLastOnce
     * BIT 7    : MaxTemperatureIsCurrentlyExceeded
     * BIT 8    : FPGAWasRestarted
     * BIT 9    : UndervoltageWasdedected
     * BIT 10   : MISSING_SLAVE
     * BIT 11   : FA_DOES_NOT_MATCH
     * BIT 12   : COUNT_CATEGORY_COUNT_DOES_NOT_MATCH
     * BIT 13   : COUNT_CATEGORY_1_ID_DOES_NOT_MATCH
     * BIT 14   : COUNT_CATEGORY_2_ID_DOES_NOT_MATCH
     * BIT 15   : CAN_NOT_COMMUNICATE_TO_SENSOR
     * 
     * 
     * -----------------------------------------------------------------------------
     * 
     * 
     * COMMAND: CMD_GET_COUNT_RESULT 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><CMD_GET_COUNT_RESULT><0x02><DoorNo><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * DoorNumber is 1 Byte                                 
     * 
     * RESPONSE: 
     * <STX><RSP_COUNT_RESULT><0x05><Cat_1_In><Cat_1_Out><Cat_2_In><Cat_2_Out><CRC_LENGHT><CRC_H><CRC_L><ETX> 
     * 
     * DoorNo is door number - 1 Byte
     * In is boarding passenger count of sensor - 1 Byte
     * Out is descending passenger count of sensor - 1 Byte
     * 
     *  
     *----------------------------------------------------------------------------*/




    /*------------------------EVENT DESCRIPTIONS----------------------------------
     * 
     * EVENT: EVENT_COUNT_DATA 
     * <STX><Command><Lenght><Data><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * <STX><0x0D><EVENT_COUNT_DATA>
     * <DoorNo>
     * <openTime_3><openTime_2><openTime_1><openTime_0>
     * <closeTime_3>closeTime_2>closeTime_1>closeTime_0>
     * <cat_1_in><cat_1_out><cat_2_in><cat_2_out>
     * <CRC_LENGHT><CRC_H><CRC_L><ETX>
     * DoorCount is 1 Byte                                 
     * 
     * RESPONSE: 
     * <STX><RSP_ACK><0x01><CRC_LENGHT><CRC_H><CRC_L><ETX>
     * 
     * 
     * -----------------------------------------------------------------------------   
     * 
     * 
 
    
        /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */

