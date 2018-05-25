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

#ifndef _IRMA_H    /* Guard against multiple inclusion */
#define _IRMA_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdbool.h>


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    //#define _debug  
#define IRMA_COMMAND_RESPONSE_BUFFER_DATA_LENGHT    64

    //CAN Channel Definitions
#define CAN_TX_CHANNEL                  CAN_CHANNEL0
#define CAN_RX_CHANNEL                  CAN_CHANNEL1

#define PERSON                                      1
#define ALL_COUNT_CATEGORIES                        0xFF
#define SENSOR_READ_COUNT_DATA_DELAY                200 //10ms * 100 = 1s

#define WITH_RESET                                  1
#define WITHOUT_RESET                               0

    //Bu deger sensor haberlesmesinde sorun oldugunda haberlesmeyi tekrar deneme sayisidir.
#define MAX_GENERAL_TRY_COUNT                       5

    //Command Response Timeout Value Definition
#define COMMAND_RESPONSE_TIMEOUT_VALUE  20 // 20x10 ms = 200ms

    //Buffer size definitions
#define IRMA_CAN_TRANSMIT_BUFFER_SIZE   32
#define IRMA_CAN_RECEIVE_BUFFER_SIZE    32

    //----------------------Sensor Specific Definitions-----------------------------
    //IRMA Message Identifier Definitions
#define IRMA_MESSAGE_IDENTIFIER_TO_SENSOR           0x74
#define IRMA_MESSAGE_IDENTIFIER_FROM_SENSOR         0x75

    //IRMA Receiver Class Definitions
#define IRMA_RECEIVER_CLASS_SINGLE_SENSOR           0x01
#define IRMA_RECEIVER_CLASS_ALL_SENSORS             0x05
#define IRMA_RECEIVER_CLASS_HOST                    0x04

    //IRMA UIP LEVEL definitions    
#define IRMA_STACK_LEVEL_UIP                        0x01
#define IRMA_SERVICE_LEVEL_UIP                      0x02
#define IRMA_APPLICATION_LEVEL_UIP                  0x03

    //IRMA UIP Version Definition
#define UIP_Ver3    0x03

    //IRMA DK Definitions
#define IRMA_DK_COUNT_DATA                                  'C'
#define IRMA_DK_WORKING_MODE                                'U'
#define IRMA_DK_STATUS                                      'S'
#define IRMA_DK_CONFIGURATION                               'K'
#define IRMA_DK_FIRMWARE_RESET                              'W'
#define IRMA_DK_DEVICE_QUERY                                'c'     

    //IRMA CMD(subcommand) definitions (IRMA COMMANDS)
#define IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET                'g'
#define IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET_RESPONSE       'G'
#define IRMA_CMD_COUNT_DATA_RESET                           'r'    
#define IRMA_CMD_COUNT_DATA_RESET_RESPONSE                  'R'       
#define IRMA_CMD_COUNT_CATEGORY_QUERY                       'c'
#define IRMA_CMD_COUNT_CATEGORY_QUERY_RESPONSE              'C'
#define IRMA_CMD_START_COUNTING                             'e'
#define IRMA_CMD_START_COUNTING_RESPONSE                    'E'
#define IRMA_CMD_STOP_COUNTING                              'd'
#define IRMA_CMD_STOP_COUNTING_RESPONSE                     'D' 
#define IRMA_CMD_SENSOR_STATUS_QUERY                        'g'
#define IRMA_CMD_SENSOR_STATUS_QUERY_RESPONSE               'G'
#define IRMA_CMD_FUNCTION_AREA_STATUS_QUERY                 'g'
#define IRMA_CMD_FUNCTION_AREA_STATUS_QUERY_RESPONSE        'G'
#define IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY            'g'
#define IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE   'G'
#define IRMA_CMD_SENSOR_FIRMWARE_RESTART                    'r'
#define IRMA_CMD_SENSOR_FIRMWARE_RESTART_RESPONSE           'R'
#define IRMA_CMD_BROADCAST_SCAN                             'b'
#define IRMA_CMD_BROADCAST_SCAN_RESPONSE                    'B'

    //IRMA CMD(subcommand) Version Definitions
#define IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET_VER            0x60
#define IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET_RESPONSE_VER   0x60
#define IRMA_CMD_COUNT_DATA_RESET_VER                       0x60
#define IRMA_CMD_COUNT_DATA_RESET_RESPONSE_VER              0x60    
#define IRMA_CMD_COUNT_CATEGORY_QUERY_VER                   0x60
#define IRMA_CMD_COUNT_CATEGORY_QUERY_RESPONSE_VER          0x60    
#define IRMA_CMD_START_COUNTING_VER                         0x20
#define IRMA_CMD_START_COUNTING_RESPONSE_VER                0x20
#define IRMA_CMD_STOP_COUNTING_VER                          0x20
#define IRMA_CMD_STOP_COUNTING_RESPONSE_VER                 0x20
#define IRMA_CMD_SENSOR_STATUS_QUERY_VER                    0x30
#define IRMA_CMD_SENSOR_STATUS_QUERY_RESPONSE_VER           0x30
#define IRMA_CMD_FUNCTION_AREA_STATUS_QUERY_VER             0x31
#define IRMA_CMD_FUNCTION_AREA_STATUS_QUERY_RESPONSE_VER    0x31
#define IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY_VER        0x10
#define IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE_VER   0x10    
#define IRMA_CMD_SENSOR_FIRMWARE_RESTART_VER                0x10 
#define IRMA_CMD_SENSOR_FIRMWARE_RESTART_RESPONSE_VER       0x10
#define IRMA_CMD_BROADCAST_SCAN_VER                         0x10
#define IRMA_CMD_BROADCAST_SCAN_RESPONSE_VER                0x10

    //IRMA CMD(subcommand) UIP Level Definitions
#define IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET_UIP_LEVEL                IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET_RESPONSE_UIP_LEVEL       IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_COUNT_DATA_RESET_UIP_LEVEL                           IRMA_APPLICATION_LEVEL_UIP    
#define IRMA_CMD_COUNT_DATA_RESET_RESPONSE_UIP_LEVEL                  IRMA_APPLICATION_LEVEL_UIP       
#define IRMA_CMD_COUNT_CATEGORY_QUERY_UIP_LEVEL                       IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_COUNT_CATEGORY_QUERY_RESPONSE_UIP_LEVEL              IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_START_COUNTING_UIP_LEVEL                             IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_START_COUNTING_RESPONSE_UIP_LEVEL                    IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_STOP_COUNTING_UIP_LEVEL                              IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_STOP_COUNTING_RESPONSE_UIP_LEVEL                     IRMA_APPLICATION_LEVEL_UIP 
#define IRMA_CMD_SENSOR_STATUS_QUERY_UIP_LEVEL                        IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_SENSOR_STATUS_QUERY_RESPONSE_UIP_LEVEL               IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_FUNCTION_AREA_STATUS_QUERY_UIP_LEVEL                 IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_FUNCTION_AREA_STATUS_QUERY_RESPONSE_UIP_LEVEL        IRMA_APPLICATION_LEVEL_UIP
#define IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY_UIP_LEVEL            IRMA_SERVICE_LEVEL_UIP
#define IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE_UIP_LEVEL   IRMA_SERVICE_LEVEL_UIP
#define IRMA_CMD_SENSOR_FIRMWARE_RESTART_UIP_LEVEL                    IRMA_SERVICE_LEVEL_UIP
#define IRMA_CMD_SENSOR_FIRMWARE_RESTART_RESPONSE_UIP_LEVEL           IRMA_SERVICE_LEVEL_UIP
#define IRMA_CMD_BROADCAST_SCAN_UIP_LEVEL                             IRMA_STACK_LEVEL_UIP
#define IRMA_CMD_BROADCAST_SCAN_RESPONSE_UIP_LEVEL                    IRMA_STACK_LEVEL_UIP

    //IRMA Command Defines   
#define IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET                1
#define IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET_RESPONSE       2
#define IRMA_COMMAND_COUNT_DATA_RESET                           3   
#define IRMA_COMMAND_COUNT_DATA_RESET_RESPONSE                  4      
#define IRMA_COMMAND_COUNT_CATEGORY_QUERY                       5
#define IRMA_COMMAND_COUNT_CATEGORY_QUERY_RESPONSE              6
#define IRMA_COMMAND_START_COUNTING                             7
#define IRMA_COMMAND_START_COUNTING_RESPONSE                    8
#define IRMA_COMMAND_STOP_COUNTING                              9
#define IRMA_COMMAND_STOP_COUNTING_RESPONSE                     10 
#define IRMA_COMMAND_SENSOR_STATUS_QUERY                        11
#define IRMA_COMMAND_SENSOR_STATUS_QUERY_RESPONSE               12
#define IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY                 13
#define IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY_RESPONSE        14
#define IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY            15
#define IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE   16
#define IRMA_COMMAND_SENSOR_FIRMWARE_RESTART                    17
#define IRMA_COMMAND_SENSOR_FIRMWARE_RESTART_RESPONSE           18
#define IRMA_COMMAND_BROADCAST_SCAN                             19
#define IRMA_COMMAND_BROADCAST_SCAN_RESPONSE                    20

    //IRMA Commands Payload Count Definitions
#define IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET_PAYLOAD_SIZE       5
#define IRMA_COMMAND_COUNT_DATA_RESET_PAYLOAD_SIZE                  3    
#define IRMA_COMMAND_COUNT_CATEGORY_QUERY_PAYLOAD_SIZE              2
#define IRMA_COMMAND_START_COUNTING_PAYLOAD_SIZE                    0
#define IRMA_COMMAND_STOP_COUNTING_PAYLOAD_SIZE                     0
#define IRMA_COMMAND_SENSOR_STATUS_QUERY_PAYLOAD_SIZE               0
#define IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY_PAYLOAD_SIZE        0
#define IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY_PAYLOAD_SIZE   4    
#define IRMA_COMMAND_SENSOR_FIRMWARE_RESTART_PAYLOAD_SIZE           0    
#define IRMA_COMMAND_BROADCAST_SCAN_PAYLOAD_SIZE                    0

    //IRMA Check Command Status
#define WAIT_FIRST_CAN_FRAME                1
#define CHECK_FIRST_CAN_FRAME               2
#define START_COMMAND_PROCCESING            3
#define WAIT_NEXT_FRAME                     4
#define CHECK_CURRENT_CAN_FRAME             5    

    //Count category ID and description definitions
#define COUNT_CATEGORY_ID_ADULTS            0
#define COUNT_CATEGORY_ID_CHILDREN          1
#define COUNT_CATEGORY_DESCRIPTION_HUMAN    1

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef struct {
        unsigned irma_can_address : 19; /* IRMA CAN address of the Received CAN Message */
        unsigned irma_receiver_class : 3; /* IRMA receiver class of the Received CAN Message */
        unsigned irma_message_identifier : 7; /* IRMA message identifier of the Received CAN Message */
        unsigned unimplemented : 3; /* Unimplemented bit. Should be always 0. */
    } IRMA_CAN_IDENTIFIER_TYPE;

    typedef union {

        struct {
            IRMA_CAN_IDENTIFIER_TYPE irma_can_identifier; /* This is can identifier portion of the CAN Receive message */
            unsigned char dlc; /* This is the data DLC section of the received message */
            unsigned char data[8]; /* This is the data portion of the CAN Transmit message */
        };
        unsigned int can_identifier;
    } IRMA_CAN_MSG_BUFFER_TYPE;

    typedef union {

        struct {
            IRMA_CAN_IDENTIFIER_TYPE irma_can_identifier; /* This is can identifier portion of the received response*/
            unsigned char UIP_VERSION;
            unsigned char UIP_LEVEL;
            unsigned short DL; /* This is the data UIP DL of the response */
            unsigned char DK; /* This is the data DK section of the response */
            unsigned char VER; /* This is the data VER section of the response */
            unsigned char CMD; /* This is the data CMD section of the response */
            unsigned char dataCount; //For debug                    /* This is the data count section of the response */
            unsigned char data[IRMA_COMMAND_RESPONSE_BUFFER_DATA_LENGHT]; /* This is the data data section of the response */
        };
        unsigned int can_identifier;
    } IRMA_RESPONSE_BUFFER_TYPE;

    typedef struct //Bu yapidaki siranin degistirilmemesi gerekiyor. Aksi takdirde sensor status veFA status sorgular? hatali sonuc uretir.
    {
        unsigned Sabotage : 1; /*Selected diagnostic data to send server*/
        unsigned PrimaryConfigurationIsInvalid : 1; /*Selected diagnostic data to send server*/
        unsigned PrimaryConfigurationIsValid : 1; /*Selected diagnostic data to send server*/
        unsigned SensorCurrentlyRunningInServiceMode : 1; /*Selected diagnostic data to send server*/
        unsigned ConfigurationContainsOneOrMoreFaultyParameter : 1; /*Selected diagnostic data to send server*/
        unsigned ConfigurationIsInvalid : 1; /*Selected diagnostic data to send server*/
        unsigned MaxTemperatureWasExceededAtLastOnce : 1; /*Selected diagnostic data to send server*/
        unsigned MaxTemperatureIsCurrentlyExceeded : 1; /*Selected diagnostic data to send server*/
        unsigned FPGAWasRestarted : 1; /*Selected diagnostic data to send server*/
        unsigned UndervoltageWasdedected : 1; /*Selected diagnostic data to send server*/
        unsigned MISSING_SLAVE : 1; /* At least one slave is missing - for sensor groups */ /*Selected diagnostic data to send server*/
        unsigned FA_DOES_NOT_MATCH : 1; /*Selected diagnostic data to send server*/
        unsigned COUNT_CATEGORY_COUNT_DOES_NOT_MATCH : 1; /*Selected diagnostic data to send server*/
        unsigned COUNT_CATEGORY_1_ID_DOES_NOT_MATCH : 1; /*Selected diagnostic data to send server*/
        unsigned COUNT_CATEGORY_2_ID_DOES_NOT_MATCH : 1; /*Selected diagnostic data to send server*/
        unsigned CAN_NOT_COMMUNICATE_TO_SENSOR : 1; /*Selected diagnostic data to send server*/

        unsigned COUNT_DATA_TYPE_DOES_NOT_MATCH : 1;
        unsigned DOOR_IS_CLEAR : 1; /* Door is clear (door clear function is under development) */
        unsigned DOOR_IS_NOT_CLEAR : 1; /* Door is not clear (door is not clear function is under development) */
        unsigned NEW_COUNTING_RESULT_AVAIBLE : 1; /* New counting result availability flag */
        unsigned NEW_COUNT_DATA_FLAG : 1;
        //        unsigned NEW_SENSOR_STATUS_DATA_FLAG : 1;

        unsigned unimplemented : 11;

    } SENSOR_STATUS_FLAGS_TYPE;

    typedef union {

        struct {
            SENSOR_STATUS_FLAGS_TYPE SENSOR_STATUS_FLAGS; /* IRMA Sensor Status */
            unsigned int SENSOR_ADDRESS; /* IRMA Sensor Address */
            unsigned short FA; /* IRMA Sensor Function Area */
            unsigned short TEMP_CAT_1_IN_T; /* Temp Counting Category 1 IN Current Counter */
            unsigned short TEMP_CAT_1_OUT_T; /* Temp Counting Category 1 OUT Current Counter */
            unsigned short TEMP_CAT_2_IN_T; /* Temp Counting Category 2 IN Current Counter */
            unsigned short TEMP_CAT_2_OUT_T; /* Temp Counting Category 2 OUT Current Counter */
            unsigned short TEMP_CAT_1_IN_B; /* Temp Counting Category 1 IN Buffered Counter */
            unsigned short TEMP_CAT_1_OUT_B; /* Temp Counting Category 1 OUT Buffered Counter */
            unsigned short TEMP_CAT_2_IN_B; /* Temp Counting Category 2 IN Buffered Counter */
            unsigned short TEMP_CAT_2_OUT_B; /* Temp Counting Category 2 OUT Buffered Counter */
            unsigned short CAT_1_IN_T; /* Counting Category 1 IN Current Counter */
            unsigned short CAT_1_OUT_T; /* Counting Category 1 OUT Current Counter */
            unsigned short CAT_2_IN_T; /* Counting Category 2 IN Current Counter */
            unsigned short CAT_2_OUT_T; /* Counting Category 2 OUT Current Counter */
            unsigned short CAT_1_IN_B; /* Counting Category 1 IN Buffered Counter */
            unsigned short CAT_1_OUT_B; /* Counting Category 1 OUT Buffered Counter */
            unsigned short CAT_2_IN_B; /* Counting Category 2 IN Buffered Counter */
            unsigned short CAT_2_OUT_B; /* Counting Category 2 OUT Buffered Counter */
            unsigned char COUNT_CATEGORY_COUNT; /* IRMA Sensor Count Category Count - It will be max=2 */
            unsigned char COUNT_CATEGORY_1_ID; /* Counting Category 1 Category ID */
            unsigned char COUNT_CATEGORY_1_DESC; /* Counting Category 1 Category Description */
            unsigned short COUNT_CATEGORY_1_PARAMETER_1; /* Counting Category 1 Parameter_1 */
            unsigned short COUNT_CATEGORY_1_PARAMETER_2; /* Counting Category 1 Parameter_2 */
            unsigned char COUNT_CATEGORY_2_ID; /* Counting Category 2 Category ID */
            unsigned char COUNT_CATEGORY_2_DESC; /* Counting Category 2 Category Description */
            unsigned short COUNT_CATEGORY_2_PARAMETER_1; /* Counting Category 2 Parameter_1 */
            unsigned short COUNT_CATEGORY_2_PARAMETER_2; /* Counting Category 2 Parameter_2 */
            unsigned char SENSOR_STATE;
            time_t DOOR_OPEN_TIME;
            time_t DOOR_CLOSE_TIME;
        };
        unsigned int sensorStatus;
    } IRMA_SENSOR_TYPE;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    bool IRMA_Send_CAN_Channel_Receive_Buffer_To_IRMA_CAN_Receive_Buffer(CAN_CHANNEL channelNum, IRMA_CAN_MSG_BUFFER_TYPE* receiveBuffer, unsigned char* receiveBufferWriteIdentifier);
    bool IRMA_Send_IRMA_CAN_Transmit_Buffer_To_CAN_Channel_Transmit_Buffer(CAN_CHANNEL channelNum, IRMA_CAN_MSG_BUFFER_TYPE* transmitBuffer, unsigned char* transmitBufferReadIdentifier);
    void IRMA_Send_MSG_To_CAN_RX_TX_Buffer(IRMA_CAN_MSG_BUFFER_TYPE* msgBuffer, IRMA_CAN_MSG_BUFFER_TYPE* rxTxBuffer, unsigned char* bufferWriteIdentifier);
    unsigned int IRMA_Prepare_IRMA_CAN_Identifier(unsigned char messageIdentifier, unsigned char receiverClass, unsigned int sensorAddress);
    unsigned char IRMA_Get_UIP_LEVEL(unsigned char irmaCommand);
    unsigned char IRMA_Get_DK(unsigned char irmaCommand);
    unsigned char IRMA_Get_CDM_VER(unsigned char irmaCommand);
    unsigned char IRMA_Get_CMD(unsigned char irmaCommand);
    unsigned char IRMA_Get_PAYLOAD_SIZE(unsigned char irmaCommand);
    unsigned char IRMA_Get_RECEIVER_CLASS(unsigned char irmaCommand);
    void IRMA_Prepare_IRMA_CAN_Frames(unsigned char irmaCommand, unsigned char* payloadBuffer, unsigned int irmaAddress);
    void IRMA_Send_Command(void);

    void setCommandResponseTimeOut(unsigned char value); //Timeout Time= value * 10ms
    void IRMA_Get_CAN_Frame_From_IRMA_CAN_MSG_BUFFER(IRMA_CAN_MSG_BUFFER_TYPE* receiveBuffer, unsigned char* receiveBufferReadIdentifier, IRMA_CAN_MSG_BUFFER_TYPE* resultBuffer);
    void IRMA_Clear_IRMA_CAN_MSG_BUFFER(IRMA_CAN_MSG_BUFFER_TYPE* buffer);
    bool IRMA_Get_Response(IRMA_RESPONSE_BUFFER_TYPE* responseBuffer, IRMA_CAN_MSG_BUFFER_TYPE* receiveBuffer, unsigned char* receiveBufferWriteIdentifier, unsigned char* receiveBufferReadIdentifier, unsigned char timeOutValue);
    bool IRMA_Check_Response(unsigned char irmaCommand, IRMA_RESPONSE_BUFFER_TYPE* responseBuffer, unsigned int irmaAddress);
    void Irma_Add_Data_To_Irma_Response_Buffer(IRMA_RESPONSE_BUFFER_TYPE* responseBuffer, unsigned char* responseBufferWriteIdentifier, unsigned char data);
    unsigned char IRMA_getSensorNo(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors); //Sensor adresinden sensor numarasini verir. Tanimsiz adres icin 0 dondurur.


    void IRMA_Send_Command_Get_Count_Results_With_Optional_Reset(unsigned int irmaAddress, unsigned short FA, unsigned char resetFlag, unsigned char countDataType, unsigned char catogoryID);
    void IRMA_Send_Command_Reset_Counts(unsigned int irmaAddress, unsigned short FA, unsigned char countDataType);
    void IRMA_Send_Command_Get_Count_Catogory(unsigned int irmaAddress, unsigned short FA);
    void IRMA_Send_Command_Start_Counting(unsigned int irmaAddress);
    void IRMA_Send_Command_Stop_Counting(unsigned int irmaAddress);
    void IRMA_Send_Command_Get_Sensor_Status(unsigned int irmaAddress);
    void IRMA_Send_Command_Get_Function_Area_Status(unsigned int irmaAddress);
    void IRMA_Send_Command_Get_Active_Configuration_Data(unsigned int irmaAddress, unsigned short groupID, unsigned short parameterID);
    void IRMA_Send_Command_Sensor_Firmaware_Restart(unsigned int irmaAddress);
    void IRMA_Send_Command_Scan_Devices(void);

    bool IRMA_getCountResultsWithOptionalReset(unsigned int sensorAddress, unsigned short FA, unsigned char resetFlag, unsigned char countDataType, unsigned char catogoryID, volatile IRMA_SENSOR_TYPE* sensors);
    bool IRMA_resetCounts(unsigned int sensorAddress, unsigned short FA, unsigned char countDataType, volatile IRMA_SENSOR_TYPE* sensors);
    bool IRMA_getCountCatogory(unsigned int sensorAddress, unsigned short FA, volatile IRMA_SENSOR_TYPE* sensors);
    bool IRMA_startCounting(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors);
    bool IRMA_stopCounting(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors);
    bool IRMA_getSensorStatus(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors);
    bool IRMA_getFunctionAreaStatus(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors);
    void Clear_Configuration_Data_Buffer(unsigned char* configurationDataBuffer);
    bool IRMA_getActiveConfigurationData(unsigned int sensorAddress, unsigned short groupID, unsigned short parameterID, unsigned char* configurationDataBuffer, volatile IRMA_SENSOR_TYPE* sensors);
    bool IRMA_sensorFirmawareRestart(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors);
    /*TESTED*/ unsigned char IRMA_Scan_Sensors(unsigned int* sensorAddressList); //Ready for test
    bool IRMA_getSensorFA(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sourceSensors, volatile IRMA_SENSOR_TYPE* destinationSensors);
    bool IRMA_getSensorCountParameters(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sourceSensors, volatile IRMA_SENSOR_TYPE* destinationSensors);

    void IRMA_getAllSensorStatus(volatile IRMA_SENSOR_TYPE* sensors);
    void IRMA_getAllSensorsCountCatogory(volatile IRMA_SENSOR_TYPE* sensors);
    void checkAllSensorParameters(void); //Ramdaki ve sensorlerdeki parametreleri karsilastirir ve sonucu sysData.sensorCheckStatus[]'a yazar.



    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
