/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "system_definitions.h"
#include "data_types.h"
#include "IRMA.h"

//#define _debug

// TODO: Cihazin kaç kategoride saymayi destekleyecegi ayarlanabilir olmali.
// TODO: Cihaza kurulumda sensör adreslerinin girilmesi için API hazirlanacak.
// TODO: Kaç adet sensör ile çalisacagi ayarlanabilmeli.
// TODO: Peryodik olarak sensör durumu sorgulanmali ve uyarilar merkeze gönderilmeli.
// TODO: Haberlesilemeyen sensörler merkeze bildirilecek.
// TODO: Kapi açik kaldi alarmi cihazda üretilecek. (belirlenen süreden uzun süre kapi açik kaldiysa)
// TODO: Cihaza enerji verildiginde bir uyari göndermesi faydali olabilir.
// TODO: Sadece irma sensorlerin gonderdigi mesajlarin alinacagi CAN filtresi eklenecek.
// TODO: Sistemin kac adet sensor destekleyecegi EEPROM'da tutulacak.
// TODO: Verilerin tüm kapilar kapandiktan sonra gönderilmesi degerlendirilecek.

// TODO: Power saving mode incelenecek.
// TODO: Birden fazla sensörün kullanildigi kapilar için nasil bir yol izlenecegi belirlenecek.
// TODO: Sensörün hangi modda çalistiginin tespit edilmesi gerekiyor. Eger sensör normal mode disinda çalisiyorsa, normal moda alinmasi gerekiyor.
// TODO: Self test hazirlanacak. Sensor adres,Category count, category id ve FA'lari kontrol edilecek.Hatali olmasi durumunda uyari verilecek.
// TODO: Door delay'in ne ise yaradigi IRIS'den ögrenilecek.
// TODO: Kapinin bir kanadinin açildigi durumlar için ne yapilabilecegi IRIS'den ögrenilecek.

// TODO: Kifi CAN Controller'a ulasamazsa merkeze bildirecek.

// TODO: Bootloader eklenecek.
// TODO: Aracin hareket ve hiz bilgisinin alinmasi incelenecek.
// TODO: Cihazda hatalarin loglanmasi icin EEPROM'da log alani olusturulacak.
// TODO: Can hattinda hicbir cihaz bagli degil ise ne yapilacagi belirlenecek.
// TODO: Kapi kontagi acik ve kapali durumlari icin voltaj seviyeleri ayarlanabilir olacak.
// TODO: Cihaza içindeki loglar? gormemizi saglayacak ozellikler eklenecek. Gonderilen al?nan ve islenen can frame sayilari gorulebilecek.

// Kullanilmasi gereken CAN konfigurasyonu 
//// *****************************************************************************
//// *****************************************************************************
//// Section: Instance 0 static driver functions
//// *****************************************************************************
//// *****************************************************************************
//void DRV_CAN0_Initialize(void)
//{
//    /* Switch the CAN module ON */
//    PLIB_CAN_Enable(CAN_ID_1);
//    /* Switch the CAN module to Configuration mode. Wait until the switch is complete */
//    PLIB_CAN_OperationModeSelect(CAN_ID_1, CAN_CONFIGURATION_MODE);
//    while(PLIB_CAN_OperationModeGet(CAN_ID_1) != CAN_CONFIGURATION_MODE);
//
//    PLIB_CAN_PhaseSegment2LengthFreelyProgrammableEnable(CAN_ID_1);
//
//    //Set the Baud rate to 125 kbps
//    PLIB_CAN_PropagationTimeSegmentSet(CAN_ID_1, 1-1);
//    PLIB_CAN_PhaseSegment1LengthSet(CAN_ID_1, 3-1);
//    PLIB_CAN_PhaseSegment2LengthSet(CAN_ID_1, 3-1);
//    PLIB_CAN_SyncJumpWidthSet(CAN_ID_1, 1-1);
//    PLIB_CAN_BaudRatePrescaleSet(CAN_ID_1, 39); // set to 1 higher then ECAN tool
//
//
//    /* Assign the buffer area to the CAN module.
//      In this case assign enough memory for 2
//      channels, each with 8 message buffers.*/
//    PLIB_CAN_MemoryBufferAssign(CAN_ID_1, can_message_buffer0);
//
//    /* Configure CAN_ID_1 Channel for CAN_TX_RTR_DISABLED operation. Allocate 1 message buffer, and assign low medium priority for transmissions. */
//    PLIB_CAN_ChannelForTransmitSet(CAN_ID_1, CAN_CHANNEL0, 8, CAN_TX_RTR_DISABLED, CAN_LOW_MEDIUM_PRIORITY);
//    /* Configure CAN_ID_1 Channel for CAN_RX_FULL_RECEIVE operation. Allocate 1 message buffer, and assign low medium priority for transmissions. */
//    PLIB_CAN_ChannelForReceiveSet(CAN_ID_1, CAN_CHANNEL1, 8, CAN_RX_FULL_RECEIVE);
//    PLIB_CAN_FilterToChannelLink(CAN_ID_1, CAN_FILTER0, CAN_FILTER_MASK0, CAN_CHANNEL1);
//    PLIB_CAN_ChannelEventEnable(CAN_ID_1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY|CAN_RX_CHANNEL_FULL);
//    PLIB_CAN_FilterConfigure(CAN_ID_1, CAN_FILTER0, 0x00000000, CAN_EID);
//    PLIB_CAN_FilterEnable(CAN_ID_1, CAN_FILTER0);
//
//    PLIB_CAN_FilterMaskConfigure(CAN_ID_1, CAN_FILTER_MASK0, 0x00000000, CAN_EID, CAN_FILTER_MASK_IDE_TYPE);
////    PLIB_CAN_TimeStampPrescalerSet(CAN_ID_1, 0x1F40);//Sets prescaler to 8000.  1\80000000 = 12.5ns. 8000 *12.5ns = .1ms per CAN timer tick
////    PLIB_CAN_TimeStampEnable(CAN_ID_1);
//
//    /* Switch the CAN module to Normal mode. Wait until the switch is complete */
//    PLIB_CAN_OperationModeSelect(CAN_ID_1, CAN_NORMAL_MODE);
//    while(PLIB_CAN_OperationModeGet(CAN_ID_1) != CAN_NORMAL_MODE);
//
//    PLIB_CAN_ModuleEventEnable(CAN_ID_1 , 0|CAN_RX_EVENT);
//
//
//
//
//    /* Setup CAN_ID_1 Interrupt */
//    PLIB_INT_SourceEnable(INT_ID_0,INT_SOURCE_CAN_1);
//    PLIB_INT_VectorPrioritySet(INT_ID_0,INT_VECTOR_CAN1, INT_PRIORITY_LEVEL1);
//    PLIB_INT_VectorSubPrioritySet(INT_ID_0,INT_VECTOR_CAN1, INT_SUBPRIORITY_LEVEL0);
//}

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

IRMA_CAN_MSG_BUFFER_TYPE irmaCanReceiveBuffer[IRMA_CAN_RECEIVE_BUFFER_SIZE];
unsigned char irmaCanReceiveBufferW = 0;
unsigned char irmaCanReceiveBufferR = 0;

IRMA_CAN_MSG_BUFFER_TYPE irmaCanTransmitBuffer[IRMA_CAN_TRANSMIT_BUFFER_SIZE];
unsigned char irmaCanTransmitBufferW = 0;
unsigned char irmaCanTransmitBufferR = 0;

unsigned char irmaConfigurationDataBuffer[IRMA_COMMAND_RESPONSE_BUFFER_DATA_LENGHT]; //irmaConfigurationDataBuffer lenght must equal IRMA_COMMAND_RESPONSE_BUFFER_DATA_LENGHT

volatile unsigned char commandResponseTimer = 0;
volatile unsigned char commandResponseTimerEnable = 0;
volatile unsigned char commandResponseTimeOutFlag = 0;

IRMA_RESPONSE_BUFFER_TYPE commandResponseBuffer;

unsigned int sensorAddressList[MAX_SUPPORTED_SENSOR_COUNT]; //unsigned int sensorAddressList[SYSTEM_SENSOR_COUNT];
IRMA_SENSOR_TYPE sensorList[MAX_SUPPORTED_SENSOR_COUNT]; //IRMA_SENSOR_LIST_TYPE sensorList[SYSTEM_SENSOR_COUNT];

extern SYSTEM_DATA_TYPE sysData;
extern SYSTEM_PARAMETERS_TYPE SYSTEM_PARAMETERS;

volatile unsigned int debugForReceivedCanFramesCount;
volatile unsigned int debugForProccessingCanFrameCount;
volatile unsigned int debugForTransmittedCanFramesCount;




/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

bool IRMA_Send_IRMA_CAN_Transmit_Buffer_To_CAN_Channel_Transmit_Buffer(CAN_CHANNEL channelNum, IRMA_CAN_MSG_BUFFER_TYPE* transmitBuffer, unsigned char* transmitBufferReadIdentifier) {
    CAN_TX_MSG_BUFFER* drv_Message1;
    int count = 0;
    if ((PLIB_CAN_ChannelEventGet(CAN_ID_1, channelNum) & CAN_TX_CHANNEL_NOT_FULL) == CAN_TX_CHANNEL_NOT_FULL) {
        //drv_Message0 = (CAN_TX_MSG_BUFFER *) &can_message_buffer0[channelNum];
        drv_Message1 = PLIB_CAN_TransmitBufferGet(CAN_ID_1, channelNum);

        /* Point correct buffer element */
        transmitBuffer = transmitBuffer + *transmitBufferReadIdentifier;

        /* Check the address whether it falls under SID or EID,
         * SID max limit is 0x7FF, so anything beyond that is EID */
        if (transmitBuffer->can_identifier > 0x7FF) {
            drv_Message1->msgSID.sid = (transmitBuffer->can_identifier >> 18);
            drv_Message1->msgEID.eid = (0x3FFFF)&(transmitBuffer->can_identifier);
            drv_Message1->msgEID.ide = 1;
        } else {
            drv_Message1->msgSID.sid = transmitBuffer->can_identifier;
            drv_Message1->msgEID.eid = 0;
            drv_Message1->msgEID.ide = 0;
        }

        if (transmitBuffer->dlc > 8) {
            transmitBuffer->dlc = 8;
        }

        drv_Message1->msgEID.data_length_code = transmitBuffer->dlc;
        while (count < transmitBuffer->dlc) {
            drv_Message1->data[count] = transmitBuffer->data[count];
            ++count;
        }
        ++*transmitBufferReadIdentifier;
        if (*transmitBufferReadIdentifier >= IRMA_CAN_TRANSMIT_BUFFER_SIZE) {
            *transmitBufferReadIdentifier = 0;
        }

        //Update CAN module and then transmit data on the bus;
        PLIB_CAN_ChannelUpdate(CAN_ID_1, channelNum);
        PLIB_CAN_TransmitChannelFlush(CAN_ID_1, channelNum);
        ++debugForTransmittedCanFramesCount; //For maintenance
        return (true);
    }
    return (false);
}

void IRMA_Send_MSG_To_CAN_RX_TX_Buffer(IRMA_CAN_MSG_BUFFER_TYPE* msgBuffer, IRMA_CAN_MSG_BUFFER_TYPE* rxTxBuffer, unsigned char* bufferWriteIdentifier) {
    IRMA_CAN_MSG_BUFFER_TYPE* msg;
    int count = 0;

    msg = msgBuffer;

    /* Point correct buffer element */
    rxTxBuffer = rxTxBuffer + *bufferWriteIdentifier;
    rxTxBuffer->irma_can_identifier = msg->irma_can_identifier;
    rxTxBuffer->dlc = msg->dlc;
    while (count < rxTxBuffer->dlc) {
        rxTxBuffer->data[count] = msg->data[count];
        count++;
    }
    ++*bufferWriteIdentifier;
    if (*bufferWriteIdentifier >= IRMA_CAN_TRANSMIT_BUFFER_SIZE) {
        *bufferWriteIdentifier = 0;
    }
}

bool IRMA_Send_CAN_Channel_Receive_Buffer_To_IRMA_CAN_Receive_Buffer(CAN_CHANNEL channelNum, IRMA_CAN_MSG_BUFFER_TYPE* receiveBuffer, unsigned char* receiveBufferWriteIdentifier) {
    CAN_RX_MSG_BUFFER *RxMessage;
    bool readStatus;
    CAN_CHANNEL_EVENT ChannelEvent;
    int EchoDLC = 0;

    /* Get the channel RX status */
    ChannelEvent = PLIB_CAN_ChannelEventGet(CAN_ID_1, channelNum);

    /* Check if there is a message available to read. */
    if ((ChannelEvent & CAN_RX_CHANNEL_NOT_EMPTY) == CAN_RX_CHANNEL_NOT_EMPTY) {
        /* There is a message available in the Channel FIFO. */

        /* Get a pointer to RX message buffer */
        RxMessage = (CAN_RX_MSG_BUFFER *) PLIB_CAN_ReceivedMessageGet(CAN_ID_1, channelNum);

        /* Point correct buffer element */
        receiveBuffer = receiveBuffer + *receiveBufferWriteIdentifier;
        /* get can identifier */
        receiveBuffer->can_identifier = 0;
        receiveBuffer->can_identifier = RxMessage->msgSID.sid;
        receiveBuffer->can_identifier = (receiveBuffer->can_identifier << 18);
        receiveBuffer->can_identifier |= (RxMessage->msgEID.eid & 0x0003FFFF);

        receiveBuffer->dlc = RxMessage->msgEID.data_length_code;

        if (RxMessage->msgEID.data_length_code > 0) {
            while (EchoDLC < RxMessage->msgEID.data_length_code) {
                receiveBuffer->data[EchoDLC] = RxMessage->data[EchoDLC];
                ++EchoDLC;
            }
        }
        /* Message processing is done, update the message buffer pointer. */
        PLIB_CAN_ChannelUpdate(CAN_ID_1, channelNum);

        ++*receiveBufferWriteIdentifier;
        if (*receiveBufferWriteIdentifier >= IRMA_CAN_RECEIVE_BUFFER_SIZE) {
            *receiveBufferWriteIdentifier = 0;
        }

        /* Message is processed successfully, so return true */
        readStatus = true;
        ++debugForReceivedCanFramesCount; //For maintenance            
    } else {
        /* There is no message to read ,so return false */
        readStatus = false;
    }

    return readStatus;
}

unsigned int IRMA_Prepare_IRMA_CAN_Identifier(unsigned char messageIdentifier, unsigned char receiverClass, unsigned int sensorAddress) {
    unsigned int temp = 0;
    //Prepare CAN Identifier
    temp = messageIdentifier;
    temp <<= 3;
    temp |= (receiverClass & 0x07);
    temp <<= 19;
    temp |= (sensorAddress & 0x0007FFFF);

    return (temp);
}

unsigned char IRMA_Get_UIP_LEVEL(unsigned char irmaCommand) {
    if ((irmaCommand == IRMA_COMMAND_BROADCAST_SCAN) || (irmaCommand == IRMA_COMMAND_BROADCAST_SCAN_RESPONSE)) {
        return (IRMA_STACK_LEVEL_UIP);
    } else if ((irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY) || (irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE) ||
            (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART) || (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART_RESPONSE)) {
        return (IRMA_SERVICE_LEVEL_UIP);
    } else if ((irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET) || (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET) ||
            (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY) || (irmaCommand == IRMA_COMMAND_START_COUNTING) ||
            (irmaCommand == IRMA_COMMAND_STOP_COUNTING) || (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY) ||
            (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY) ||
            (irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET_RESPONSE) || (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET_RESPONSE) ||
            (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY_RESPONSE) || (irmaCommand == IRMA_COMMAND_START_COUNTING_RESPONSE) ||
            (irmaCommand == IRMA_COMMAND_STOP_COUNTING_RESPONSE) || (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY_RESPONSE) ||
            (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY_RESPONSE)) {
        return (IRMA_APPLICATION_LEVEL_UIP);
    } else return (0);
}

unsigned char IRMA_Get_DK(unsigned char irmaCommand) {
    if ((irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET) || (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET) ||
            (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY) ||
            (irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET_RESPONSE) || (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET_RESPONSE) ||
            (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY_RESPONSE)) {
        return (IRMA_DK_COUNT_DATA);
    } else if ((irmaCommand == IRMA_COMMAND_START_COUNTING) || (irmaCommand == IRMA_COMMAND_STOP_COUNTING) ||
            (irmaCommand == IRMA_COMMAND_START_COUNTING_RESPONSE) || (irmaCommand == IRMA_COMMAND_STOP_COUNTING_RESPONSE)) {
        return (IRMA_DK_WORKING_MODE);
    } else if ((irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY) || (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY) ||
            (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY_RESPONSE) || (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY_RESPONSE)) {
        return (IRMA_DK_STATUS);
    } else if ((irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY) || (irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE)) {
        return (IRMA_DK_CONFIGURATION);
    } else if ((irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART) || (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART_RESPONSE)) {
        return (IRMA_DK_FIRMWARE_RESET);
    } else if ((irmaCommand == IRMA_COMMAND_BROADCAST_SCAN) || (irmaCommand == IRMA_COMMAND_BROADCAST_SCAN_RESPONSE)) {
        return (IRMA_DK_DEVICE_QUERY);
    } else return (0);
}

unsigned char IRMA_Get_CDM_VER(unsigned char irmaCommand) {
    if ((irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET) || (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET) ||
            (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY) ||
            (irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET_RESPONSE) || (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET_RESPONSE) ||
            (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY_RESPONSE)) {
        return (IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET_VER);
    } else if ((irmaCommand == IRMA_COMMAND_START_COUNTING) || (irmaCommand == IRMA_COMMAND_STOP_COUNTING) ||
            (irmaCommand == IRMA_COMMAND_START_COUNTING_RESPONSE) || (irmaCommand == IRMA_COMMAND_STOP_COUNTING_RESPONSE)) {
        return (IRMA_CMD_START_COUNTING_VER);
    } else if ((irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY) || (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY_RESPONSE)) {
        return (IRMA_CMD_SENSOR_STATUS_QUERY_VER);
    } else if ((irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY) || (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY_RESPONSE)) {
        return (IRMA_CMD_FUNCTION_AREA_STATUS_QUERY_VER);
    } else if ((irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY) || (irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE)) {
        return (IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY_VER);
    } else if ((irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART) || (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART_RESPONSE)) {
        return (IRMA_CMD_SENSOR_FIRMWARE_RESTART_VER);
    } else if ((irmaCommand == IRMA_COMMAND_BROADCAST_SCAN) || (irmaCommand == IRMA_COMMAND_BROADCAST_SCAN_RESPONSE)) {
        return (IRMA_CMD_BROADCAST_SCAN_VER);
    } else return (0);
}

unsigned char IRMA_Get_CMD(unsigned char irmaCommand) {
    if (irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET) {
        return (IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET) {
        return (IRMA_CMD_COUNT_DATA_RESET);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY) {
        return (IRMA_CMD_COUNT_CATEGORY_QUERY);
    } else if (irmaCommand == IRMA_COMMAND_START_COUNTING) {
        return (IRMA_CMD_START_COUNTING);
    } else if (irmaCommand == IRMA_COMMAND_STOP_COUNTING) {
        return (IRMA_CMD_STOP_COUNTING);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY) {
        return (IRMA_CMD_SENSOR_STATUS_QUERY);
    } else if (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY) {
        return (IRMA_CMD_FUNCTION_AREA_STATUS_QUERY);
    } else if (irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY) {
        return (IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART) {
        return (IRMA_CMD_SENSOR_FIRMWARE_RESTART);
    } else if (irmaCommand == IRMA_COMMAND_BROADCAST_SCAN) {
        return (IRMA_CMD_BROADCAST_SCAN);
    }

    if (irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET_RESPONSE) {
        return (IRMA_CMD_COUNT_DATA_QUERY_WITH_RESET_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET_RESPONSE) {
        return (IRMA_CMD_COUNT_DATA_RESET_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY_RESPONSE) {
        return (IRMA_CMD_COUNT_CATEGORY_QUERY_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_START_COUNTING_RESPONSE) {
        return (IRMA_CMD_START_COUNTING_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_STOP_COUNTING_RESPONSE) {
        return (IRMA_CMD_STOP_COUNTING_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY_RESPONSE) {
        return (IRMA_CMD_SENSOR_STATUS_QUERY_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY_RESPONSE) {
        return (IRMA_CMD_FUNCTION_AREA_STATUS_QUERY_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE) {
        return (IRMA_CMD_ACTIVE_CONFIGURATION_DATA_QUERY_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART_RESPONSE) {
        return (IRMA_CMD_SENSOR_FIRMWARE_RESTART_RESPONSE);
    } else if (irmaCommand == IRMA_COMMAND_BROADCAST_SCAN_RESPONSE) {
        return (IRMA_CMD_BROADCAST_SCAN_RESPONSE);
    } else return (0);
}

unsigned char IRMA_Get_PAYLOAD_SIZE(unsigned char irmaCommand) {
    if (irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET) {
        return (IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET) {
        return (IRMA_COMMAND_COUNT_DATA_RESET_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY) {
        return (IRMA_COMMAND_COUNT_CATEGORY_QUERY_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_START_COUNTING) {
        return (IRMA_COMMAND_START_COUNTING_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_STOP_COUNTING) {
        return (IRMA_COMMAND_STOP_COUNTING_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY) {
        return (IRMA_COMMAND_SENSOR_STATUS_QUERY_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY) {
        return (IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY) {
        return (IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART) {
        return (IRMA_COMMAND_SENSOR_FIRMWARE_RESTART_PAYLOAD_SIZE);
    } else if (irmaCommand == IRMA_COMMAND_BROADCAST_SCAN) {
        return (IRMA_COMMAND_BROADCAST_SCAN_PAYLOAD_SIZE);
    } else return (0);
}

unsigned char IRMA_Get_RECEIVER_CLASS(unsigned char irmaCommand) {
    if (irmaCommand == IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_DATA_RESET) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_COUNT_CATEGORY_QUERY) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_START_COUNTING) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_STOP_COUNTING) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_STATUS_QUERY) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_SENSOR_FIRMWARE_RESTART) {
        return (IRMA_RECEIVER_CLASS_SINGLE_SENSOR);
    } else if (irmaCommand == IRMA_COMMAND_BROADCAST_SCAN) {
        return (IRMA_RECEIVER_CLASS_ALL_SENSORS);
    } else return (0);
}

void IRMA_Prepare_IRMA_CAN_Frames(unsigned char irmaCommand, unsigned char* payloadBuffer, unsigned int irmaAddress) {
    IRMA_CAN_MSG_BUFFER_TYPE msgBuffer;
    unsigned char count = 0;
    unsigned short tempDL = 0;

    msgBuffer.can_identifier = IRMA_Prepare_IRMA_CAN_Identifier(IRMA_MESSAGE_IDENTIFIER_TO_SENSOR, IRMA_Get_RECEIVER_CLASS(irmaCommand), irmaAddress);
    msgBuffer.dlc = 7; //default Can frame DLC value for payloadCount=0

    //Clear data buffer
    while (count < 8) //DL - DK(1Byte) - VER(1Byte) - CMD(1Byte) - PAYLOAD1(1Byte)
    {
        msgBuffer.data[count] = 0;
        ++count;
    }

    //UIP Part Number
    msgBuffer.data[0] = 0x01;
    //UIP Version Number
    msgBuffer.data[1] = UIP_Ver3;
    msgBuffer.data[1] <<= 4;
    //UIP Level
    msgBuffer.data[1] |= (IRMA_Get_UIP_LEVEL(irmaCommand) & 0x0F);
    //Prepare DL
    tempDL = IRMA_Get_PAYLOAD_SIZE(irmaCommand) + 3; //PayloadCount + DK(1Byte) + VER(1Byte) + CMD(1Byte)
    //DL <0-7>
    msgBuffer.data[2] = (unsigned char) (tempDL & 0x00FF);
    //R
    msgBuffer.data[3] &= 0x7F; //R is MSB of data[3] and R=0;
    //DL <8-14>
    msgBuffer.data[3] |= (unsigned char) ((tempDL & 0x7F00) >> 8);
    //DK
    msgBuffer.data[4] = IRMA_Get_DK(irmaCommand);
    //VER (CMD Version) 
    msgBuffer.data[5] = IRMA_Get_CDM_VER(irmaCommand);
    //CMD
    msgBuffer.data[6] = IRMA_Get_CMD(irmaCommand);

    if (IRMA_Get_PAYLOAD_SIZE(irmaCommand) > 0) {
        //modified first CAN message's DLC
        msgBuffer.dlc = 8;
        msgBuffer.data[7] = payloadBuffer[0];
        IRMA_Send_MSG_To_CAN_RX_TX_Buffer(&msgBuffer, irmaCanTransmitBuffer, &irmaCanTransmitBufferW);
        //Second CAN message's DLC
        msgBuffer.dlc = IRMA_Get_PAYLOAD_SIZE(irmaCommand);
        //Clear data buffer
        while (count < 8) //DL - DK(1Byte) - VER(1Byte) - CMD(1Byte) - PAYLOAD1(1Byte)
        {
            msgBuffer.data[count] = 0;
            ++count;
        }
        //Second CAN Frame's UIP Part Number
        msgBuffer.data[0] = 0x02;
        count = 0;
        while (count < tempDL - 4) //DL - DK(1Byte) - VER(1Byte) - CMD(1Byte) - PAYLOAD1(1Byte)
        {
            msgBuffer.data[count + 1] = payloadBuffer[count + 1];
            count++;
        }
    }
    //send package to CAN Transmit Buffer
    IRMA_Send_MSG_To_CAN_RX_TX_Buffer(&msgBuffer, irmaCanTransmitBuffer, &irmaCanTransmitBufferW);
}

void IRMA_Send_Command(void) {
    unsigned char count = MAX_GENERAL_TRY_COUNT;

    sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_CABLE_ERROR = 0;

    while (irmaCanTransmitBufferR != irmaCanTransmitBufferW) {
        while ((IRMA_Send_IRMA_CAN_Transmit_Buffer_To_CAN_Channel_Transmit_Buffer(CAN_TX_CHANNEL, irmaCanTransmitBuffer, &irmaCanTransmitBufferR) == false) && (count > 0)) {
            --count;
        }
        if (count == 0) {
            sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_CABLE_ERROR = 1;
        }
        if (sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_CABLE_ERROR == 1) {
            break;
        } else {
            sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_CABLE_ERROR = 0;
        }
    }
    PLIB_CAN_ChannelEventEnable(CAN_ID_1, CAN_TX_CHANNEL, 0 | CAN_TX_CHANNEL_EMPTY);
}

void setCommandResponseTimeOut(unsigned char value) //Timeout Time= value * 10ms
{
    commandResponseTimer = value;
    commandResponseTimerEnable = 1;
    commandResponseTimeOutFlag = 0;
}

void IRMA_Get_CAN_Frame_From_IRMA_CAN_MSG_BUFFER(IRMA_CAN_MSG_BUFFER_TYPE* receiveBuffer, unsigned char* receiveBufferReadIdentifier, IRMA_CAN_MSG_BUFFER_TYPE* resultBuffer) {
    unsigned char count = 0;

    /* Point correct buffer element */
    receiveBuffer = receiveBuffer + *receiveBufferReadIdentifier;

    IRMA_Clear_IRMA_CAN_MSG_BUFFER(resultBuffer);
    resultBuffer->irma_can_identifier = receiveBuffer->irma_can_identifier;
    resultBuffer->dlc = receiveBuffer->dlc;

    while (count < receiveBuffer->dlc) {
        resultBuffer->data[count] = receiveBuffer->data[count];
        ++count;
    }
    ++*receiveBufferReadIdentifier;
    if (*receiveBufferReadIdentifier == IRMA_CAN_RECEIVE_BUFFER_SIZE) {
        *receiveBufferReadIdentifier = 0;
    }
}

void IRMA_Clear_IRMA_CAN_MSG_BUFFER(IRMA_CAN_MSG_BUFFER_TYPE* buffer) {
    unsigned char count = 0;

    buffer->can_identifier = 0;
    buffer->dlc = 0;
    while (count < 8) {
        buffer->data[count] = 0;
        ++count;
    }
}

bool IRMA_Get_Response(IRMA_RESPONSE_BUFFER_TYPE* responseBuffer, IRMA_CAN_MSG_BUFFER_TYPE* receiveBuffer, unsigned char* receiveBufferWriteIdentifier, unsigned char* receiveBufferReadIdentifier, unsigned char timeOutValue) {
    unsigned char status = 0;
    IRMA_CAN_MSG_BUFFER_TYPE frameBuffer;
    unsigned char totalUIPDatagramCount = 0;
    unsigned char currentFrameUIPDatagramPartNumber = 1;
    unsigned char count = 0;
    unsigned char dataCount = 0;

    setCommandResponseTimeOut(timeOutValue); //set (value x 10ms) timeout
    status = WAIT_FIRST_CAN_FRAME;

    //Clear Response Buffer
    responseBuffer->can_identifier = 0;
    responseBuffer->UIP_LEVEL = 0;
    responseBuffer->DL = 0;
    responseBuffer->DK = 0;
    responseBuffer->VER = 0;
    responseBuffer->CMD = 0;
    responseBuffer->dataCount = 0;
    count = 0;
    while (count < 64) //DL - DK(1Byte) - VER(1Byte) - CMD(1Byte) - PAYLOAD1(1Byte)
    {
        responseBuffer->data[count] = 0;
        ++count;
    }

    while (1) {
        if (status == WAIT_FIRST_CAN_FRAME) {
            if (*receiveBufferWriteIdentifier != *receiveBufferReadIdentifier) {
                IRMA_Get_CAN_Frame_From_IRMA_CAN_MSG_BUFFER(irmaCanReceiveBuffer, &irmaCanReceiveBufferR, &frameBuffer);
                status = CHECK_FIRST_CAN_FRAME;

                ++debugForProccessingCanFrameCount;

            }
        } else if (status == CHECK_FIRST_CAN_FRAME) {
            //gelen frame'in message identifier'i bir sensore ait olup olmadigina bakilir. 
            if (frameBuffer.irma_can_identifier.irma_message_identifier != IRMA_MESSAGE_IDENTIFIER_FROM_SENSOR) {
                //Message identifier bir sensore ait degil.
                status = WAIT_FIRST_CAN_FRAME;
            } else {
                //gelen frame'in UIP paket numarasi 1 mi? Gelen frame'in bir mesajin baslangic frame'mi olup olmadigina bakilir
                if (frameBuffer.data[0] != currentFrameUIPDatagramPartNumber) {
                    //beklenen frame degil
                    status = WAIT_FIRST_CAN_FRAME;
                } else {
                    status = START_COMMAND_PROCCESING; //gelen can frame'in beklenen frame oldugu anlasildi.
                }
            }

        } else if (status == START_COMMAND_PROCCESING) {
            responseBuffer->irma_can_identifier = frameBuffer.irma_can_identifier;
            responseBuffer->UIP_VERSION = (frameBuffer.data[1] & 0xF0) >> 4;
            responseBuffer->UIP_LEVEL = frameBuffer.data[1] & 0x0F;
            responseBuffer->DL = 0;
            responseBuffer->DL = (frameBuffer.data[3] & 0x7F);
            responseBuffer->DL <<= 8;
            responseBuffer->DL |= frameBuffer.data[2];
            responseBuffer->DK = frameBuffer.data[4];
            responseBuffer->VER = frameBuffer.data[5];
            responseBuffer->CMD = frameBuffer.data[6];

            if ((responseBuffer->DL - 3) > 1) {
                //Gelen mesaj birden fazla can frame'inden olusuyor.
                Irma_Add_Data_To_Irma_Response_Buffer(responseBuffer, &dataCount, frameBuffer.data[7]);
                //Kac frame daha gelecegi hesaplanir. 
                totalUIPDatagramCount = (responseBuffer->DL - 4) / 7;
                if ((responseBuffer->DL - 4) % 7) {
                    ++totalUIPDatagramCount;
                }
                ++totalUIPDatagramCount; //add first frame

                //Siradaki frame'in UIP paket numaras? belirlenir.
                ++currentFrameUIPDatagramPartNumber;
                status = WAIT_NEXT_FRAME;
            } else {
                //Gelen mesaj tek can frame'inden olusuyor.
                //DL = 4 ise data[7] response buffer'a eklenir.
                if (responseBuffer->DL == 4) {
                    Irma_Add_Data_To_Irma_Response_Buffer(responseBuffer, &dataCount, frameBuffer.data[7]);
                }
                return (1);
            }
        } else if (status == WAIT_NEXT_FRAME) {
            if (*receiveBufferWriteIdentifier != *receiveBufferReadIdentifier) {
                IRMA_Get_CAN_Frame_From_IRMA_CAN_MSG_BUFFER(irmaCanReceiveBuffer, &irmaCanReceiveBufferR, &frameBuffer);
                status = CHECK_CURRENT_CAN_FRAME;
                ++debugForProccessingCanFrameCount;
            }
        } else if (status == CHECK_CURRENT_CAN_FRAME) {
            //Is IRMA sensor address correct?
            if (responseBuffer->irma_can_identifier.irma_can_address != frameBuffer.irma_can_identifier.irma_can_address) {
                //IRMA sensor address is not correct.
                status = WAIT_FIRST_CAN_FRAME;
            }
            //Is IRMA Message identifier correct?
            if (responseBuffer->irma_can_identifier.irma_message_identifier != frameBuffer.irma_can_identifier.irma_message_identifier) {
                //IRMA Message Identifier is not correct.
                status = WAIT_FIRST_CAN_FRAME;
            }
            //Is IRMA Receiver Class correct?
            if (responseBuffer->irma_can_identifier.irma_receiver_class != frameBuffer.irma_can_identifier.irma_receiver_class) {
                //IRMA Receiver Class is not correct.
                status = WAIT_FIRST_CAN_FRAME;
            }
            //Is UIP datagram number correct?
            if (frameBuffer.data[0] != currentFrameUIPDatagramPartNumber) {
                //UIP datagram number is not correct.
                status = WAIT_FIRST_CAN_FRAME;
            }
            //gelen frame'deki data miktari beklenenle ayni mi?
            //Is it last frame?
            if (currentFrameUIPDatagramPartNumber != totalUIPDatagramCount) {
                count = 0;
                while (count < 7) //DL - DK(1Byte) - VER(1Byte) - CMD(1Byte) - PAYLOAD1(1Byte)
                {
                    Irma_Add_Data_To_Irma_Response_Buffer(responseBuffer, &dataCount, frameBuffer.data[count + 1]);
                    count++;
                }
                ++currentFrameUIPDatagramPartNumber;
                status = WAIT_NEXT_FRAME;
            } else if (currentFrameUIPDatagramPartNumber == totalUIPDatagramCount) {
                count = 0;
                while (count < ((responseBuffer->DL - 4) - ((currentFrameUIPDatagramPartNumber - 2) * 7))) {
                    Irma_Add_Data_To_Irma_Response_Buffer(responseBuffer, &dataCount, frameBuffer.data[count + 1]);
                    count++;
                }
                return (1);
            }
        }
        if (commandResponseTimeOutFlag)//check timeout
        {
            commandResponseTimeOutFlag = 0; //Clear Timeout Flag
            //Clear Response Buffer
            responseBuffer->can_identifier = 0;
            responseBuffer->UIP_LEVEL = 0;
            responseBuffer->DL = 0;
            responseBuffer->DK = 0;
            responseBuffer->VER = 0;
            responseBuffer->CMD = 0;
            count = 0;
            while (count < 64) //DL - DK(1Byte) - VER(1Byte) - CMD(1Byte) - PAYLOAD1(1Byte)
            {
                responseBuffer->data[count] = 0;
                ++count;
            }
            return (0);
        }
    }
}

bool IRMA_Check_Response(unsigned char irmaCommand, IRMA_RESPONSE_BUFFER_TYPE* responseBuffer, unsigned int irmaAddress) {
    unsigned char result = 0;

    result = IRMA_Get_Response(&commandResponseBuffer, irmaCanReceiveBuffer, &irmaCanReceiveBufferW, &irmaCanReceiveBufferR, COMMAND_RESPONSE_TIMEOUT_VALUE);
    if (!result) {
        return (0);
    }
    //Check sensor address
    if (irmaAddress)//Check sensor address
    {
        if (responseBuffer->irma_can_identifier.irma_can_address != irmaAddress) {
            return (0);
        }
    }
    //Check message identifier
    if (responseBuffer->irma_can_identifier.irma_message_identifier != IRMA_MESSAGE_IDENTIFIER_FROM_SENSOR) {
        return (0);
    }
    //Check Receiver Class
    if (responseBuffer->irma_can_identifier.irma_receiver_class != IRMA_RECEIVER_CLASS_HOST) {
        return (0);
    }
    //Check UIP Version
    if (responseBuffer->UIP_VERSION != 3) {
        return (0);
    }
    //Check UIP Level
    if (responseBuffer->UIP_LEVEL != IRMA_Get_UIP_LEVEL(irmaCommand + 1)) //irmaCommand + 1 = irmaCommandResponse
    {
        return (0);
    }
    //Check DK
    if (responseBuffer->DK != IRMA_Get_DK(irmaCommand + 1)) //irmaCommand + 1 = irmaCommandResponse
    {
        return (0);
    }
    //Check VER
    if (responseBuffer->VER != IRMA_Get_CDM_VER(irmaCommand + 1)) //irmaCommand + 1 = irmaCommandResponse
    {
        return (0);
    }
    //Check CMD
    if (responseBuffer->CMD != IRMA_Get_CMD(irmaCommand + 1)) //irmaCommand + 1 = irmaCommandResponse
    {
        return (0);
    }
    //Everything ok
    return (1);
}

void Irma_Add_Data_To_Irma_Response_Buffer(IRMA_RESPONSE_BUFFER_TYPE* responseBuffer, unsigned char* responseBufferWriteIdentifier, unsigned char data) {
    responseBuffer->data[*responseBufferWriteIdentifier] = data;
    ++responseBuffer->dataCount;
    ++*responseBufferWriteIdentifier;
}

unsigned char IRMA_getSensorNo(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors)//Sensor adresinden sensor numarasini verir. Tanimsiz adres icin 0 dondurur.
{
    unsigned char sensorNo = 0;

    if (sensorAddress == sensors[0].SENSOR_ADDRESS) {
        sensorNo = 0;
    } else if (sensorAddress == sensors[1].SENSOR_ADDRESS) {
        sensorNo = 1;
    } else if (sensorAddress == sensors[2].SENSOR_ADDRESS) {
        sensorNo = 2;
    } else if (sensorAddress == sensors[3].SENSOR_ADDRESS) {
        sensorNo = 3;
    } else if (sensorAddress == sensors[4].SENSOR_ADDRESS) {
        sensorNo = 4;
    } else if (sensorAddress == sensors[5].SENSOR_ADDRESS) {
        sensorNo = 5;
    } else if (sensorAddress == sensors[6].SENSOR_ADDRESS) {
        sensorNo = 6;
    } else if (sensorAddress == sensors[7].SENSOR_ADDRESS) {
        sensorNo = 7;
    }
    return (sensorNo);
}

void IRMA_Send_Command_Get_Count_Results_With_Optional_Reset(unsigned int irmaAddress, unsigned short FA, unsigned char resetFlag, unsigned char countDataType, unsigned char catogoryID) {
    unsigned char payloadBuffer[5];

    payloadBuffer[0] = (unsigned char) (FA & 0x00FF);
    payloadBuffer[1] = (unsigned char) (FA >> 8) & 0x00FF;
    payloadBuffer[2] = resetFlag;
    payloadBuffer[3] = countDataType;
    payloadBuffer[4] = catogoryID;

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Reset_Counts(unsigned int irmaAddress, unsigned short FA, unsigned char countDataType) {
    unsigned char payloadBuffer[5];

    payloadBuffer[0] = (unsigned char) (FA & 0x00FF);
    payloadBuffer[1] = (unsigned char) (FA >> 8) & 0x00FF;
    payloadBuffer[2] = countDataType;

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_COUNT_DATA_RESET, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Get_Count_Catogory(unsigned int irmaAddress, unsigned short FA) {
    unsigned char payloadBuffer[5];

    payloadBuffer[0] = (unsigned char) (FA & 0x00FF);
    payloadBuffer[1] = (unsigned char) (FA >> 8) & 0x00FF;

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_COUNT_CATEGORY_QUERY, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Start_Counting(unsigned int irmaAddress) {
    unsigned char payloadBuffer[5];

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_START_COUNTING, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Stop_Counting(unsigned int irmaAddress) {
    unsigned char payloadBuffer[5];

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_STOP_COUNTING, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Get_Sensor_Status(unsigned int irmaAddress) {
    unsigned char payloadBuffer[5];

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_SENSOR_STATUS_QUERY, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Get_Function_Area_Status(unsigned int irmaAddress) {
    unsigned char payloadBuffer[5];

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Get_Active_Configuration_Data(unsigned int irmaAddress, unsigned short groupID, unsigned short parameterID) {
    unsigned char payloadBuffer[5];

    payloadBuffer[0] = (unsigned char) (groupID & 0x00FF);
    payloadBuffer[1] = (unsigned char) (groupID >> 8) & 0x00FF;
    payloadBuffer[2] = (unsigned char) (parameterID & 0x00FF);
    payloadBuffer[3] = (unsigned char) (parameterID >> 8) & 0x00FF;

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Sensor_Firmaware_Restart(unsigned int irmaAddress) {
    unsigned char payloadBuffer[5];

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_SENSOR_FIRMWARE_RESTART, payloadBuffer, irmaAddress);
    IRMA_Send_Command();
}

void IRMA_Send_Command_Scan_Devices(void) {
    unsigned char payloadBuffer[5];

    IRMA_Prepare_IRMA_CAN_Frames(IRMA_COMMAND_BROADCAST_SCAN, payloadBuffer, 0);
    IRMA_Send_Command();
    // TODO: 100ms içinde cevabin gelmesi beklenecek. Cevap gelmezse ne yapilacak?     
}

bool IRMA_getCountResultsWithOptionalReset(unsigned int sensorAddress, unsigned short FA, unsigned char resetFlag, unsigned char countDataType, unsigned char catogoryID, volatile IRMA_SENSOR_TYPE* sensors) {
    unsigned char sensorNo = 0;

    //Get sensor no
    sensorNo = IRMA_getSensorNo(sensorAddress, sensors);

    IRMA_Send_Command_Get_Count_Results_With_Optional_Reset(sensorAddress, FA, resetFlag, countDataType, catogoryID);
    if (IRMA_Check_Response(IRMA_COMMAND_COUNT_DATA_QUERY_WITH_RESET, &commandResponseBuffer, sensorAddress)) {
        //Check FA
        if (toShort(commandResponseBuffer.data[1], commandResponseBuffer.data[0]) != sensors[sensorNo].FA) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.FA_DOES_NOT_MATCH = 1;
            return (0);
        }
        //Check Count Data Type
        if (commandResponseBuffer.data[3] != countDataType) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.COUNT_DATA_TYPE_DOES_NOT_MATCH = 1;
            return (0);
        }
        if (commandResponseBuffer.data[4] != SYSTEM_PARAMETERS.SystemCountCategoryCount) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.COUNT_CATEGORY_COUNT_DOES_NOT_MATCH = 1;
            return (0);
        }
        if (commandResponseBuffer.data[5] != SYSTEM_PARAMETERS.SystemCountCategory_ID_1) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.COUNT_CATEGORY_1_ID_DOES_NOT_MATCH = 1;
            return (0);
        }
        //Update Counter
        if (countDataType == 'T') {
            sensors[sensorNo].TEMP_CAT_1_IN_T = toShort(commandResponseBuffer.data[7], commandResponseBuffer.data[6]);
            sensors[sensorNo].TEMP_CAT_1_OUT_T = toShort(commandResponseBuffer.data[9], commandResponseBuffer.data[8]);
        } else if (countDataType == 'B') {
            sensors[sensorNo].TEMP_CAT_1_IN_B = toShort(commandResponseBuffer.data[7], commandResponseBuffer.data[6]);
            sensors[sensorNo].TEMP_CAT_1_OUT_B = toShort(commandResponseBuffer.data[9], commandResponseBuffer.data[8]);
        }
        //Check, count category count more than one(CountCategoryCount = 0xFF)
        if ((catogoryID == ALL_COUNT_CATEGORIES) && (SYSTEM_PARAMETERS.SystemCountCategoryCount == 2)) {
            //Check second count category result
            if (commandResponseBuffer.data[10] != SYSTEM_PARAMETERS.SystemCountCategory_ID_2) {
                sensors[sensorNo].SENSOR_STATUS_FLAGS.COUNT_CATEGORY_2_ID_DOES_NOT_MATCH = 1;
                return (0);
            }
            //Update Counter
            if (countDataType == 'T') {
                sensors[sensorNo].TEMP_CAT_2_IN_T = toShort(commandResponseBuffer.data[12], commandResponseBuffer.data[11]);
                sensors[sensorNo].TEMP_CAT_2_OUT_T = toShort(commandResponseBuffer.data[14], commandResponseBuffer.data[13]);
            } else if (countDataType == 'B') {
                sensors[sensorNo].TEMP_CAT_2_IN_B = toShort(commandResponseBuffer.data[12], commandResponseBuffer.data[11]);
                sensors[sensorNo].TEMP_CAT_2_OUT_B = toShort(commandResponseBuffer.data[14], commandResponseBuffer.data[13]);
            }
        }
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
        return (1);
    } else {
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

bool IRMA_resetCounts(unsigned int sensorAddress, unsigned short FA, unsigned char countDataType, volatile IRMA_SENSOR_TYPE* sensors) {
    unsigned char sensorNo = 0;

    //Get sensor no
    sensorNo = IRMA_getSensorNo(sensorAddress, sensors);

    IRMA_Send_Command_Reset_Counts(sensorAddress, FA, countDataType);

    if (IRMA_Check_Response(IRMA_COMMAND_COUNT_DATA_RESET, &commandResponseBuffer, sensorAddress)) {
        //Check FA
        if (toShort(commandResponseBuffer.data[1], commandResponseBuffer.data[0]) != sensors[sensorNo].FA) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.FA_DOES_NOT_MATCH = 1;
            return (0);
        }
        if (countDataType == commandResponseBuffer.data[2]) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
            return (1);
        } else {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.COUNT_DATA_TYPE_DOES_NOT_MATCH = 1;
            return (0);
        }
    } else {
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
        return (0);
    }
}

bool IRMA_getCountCatogory(unsigned int sensorAddress, unsigned short FA, volatile IRMA_SENSOR_TYPE* sensors) {
    unsigned char count = 0;
    unsigned char sensorNo = 0;

    sensorNo = IRMA_getSensorNo(sensorAddress, sensors);

    IRMA_Send_Command_Get_Count_Catogory(sensorAddress, FA);
    if (IRMA_Check_Response(IRMA_COMMAND_COUNT_CATEGORY_QUERY, &commandResponseBuffer, sensorAddress)) {
        if (sensors[sensorNo].FA != toShort(commandResponseBuffer.data[1], commandResponseBuffer.data[0])) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.FA_DOES_NOT_MATCH = 1;
            return (0);
        }
        if (commandResponseBuffer.data[2] != SYSTEM_PARAMETERS.SystemCountCategoryCount) {
            sensors[sensorNo].SENSOR_STATUS_FLAGS.COUNT_CATEGORY_COUNT_DOES_NOT_MATCH = 1;
            return (0);
        }
        sensors[sensorNo].COUNT_CATEGORY_COUNT = commandResponseBuffer.data[2];
        sensors[sensorNo].COUNT_CATEGORY_1_ID = commandResponseBuffer.data[3];
        sensors[sensorNo].COUNT_CATEGORY_1_DESC = commandResponseBuffer.data[4];
        sensors[sensorNo].COUNT_CATEGORY_1_PARAMETER_1 = toShort(commandResponseBuffer.data[6], commandResponseBuffer.data[5]);
        sensors[sensorNo].COUNT_CATEGORY_1_PARAMETER_2 = toShort(commandResponseBuffer.data[8], commandResponseBuffer.data[7]);

        if (commandResponseBuffer.data[2] > 1) {
            sensors[count].COUNT_CATEGORY_2_ID = commandResponseBuffer.data[13];
            sensors[count].COUNT_CATEGORY_2_DESC = commandResponseBuffer.data[14];
            sensors[count].COUNT_CATEGORY_2_PARAMETER_1 = toShort(commandResponseBuffer.data[16], commandResponseBuffer.data[15]);
            sensors[count].COUNT_CATEGORY_2_PARAMETER_2 = toShort(commandResponseBuffer.data[18], commandResponseBuffer.data[17]);
        }
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
        sensors[sensorNo].SENSOR_STATUS_FLAGS.COUNT_CATEGORY_COUNT_DOES_NOT_MATCH = 0;
        sensors[sensorNo].SENSOR_STATUS_FLAGS.FA_DOES_NOT_MATCH = 0;
        return (1);
    } else {
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

bool IRMA_startCounting(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors) {
    IRMA_Send_Command_Start_Counting(sensorAddress);
    if (IRMA_Check_Response(IRMA_COMMAND_START_COUNTING, &commandResponseBuffer, sensorAddress)) {
        sensors[IRMA_getSensorNo(sensorAddress, sensors)].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
        return (1);
    } else {
        sensors[IRMA_getSensorNo(sensorAddress, sensors)].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

bool IRMA_stopCounting(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors) {
    IRMA_Send_Command_Stop_Counting(sensorAddress);
    if (IRMA_Check_Response(IRMA_COMMAND_STOP_COUNTING, &commandResponseBuffer, sensorAddress)) {
        sensors[IRMA_getSensorNo(sensorAddress, sensors)].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
        return (1);
    } else {
        sensors[IRMA_getSensorNo(sensorAddress, sensors)].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

bool IRMA_getSensorStatus(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors) {
    unsigned char count = 0;
    unsigned char sensorNo = 0;

    sensorNo = IRMA_getSensorNo(sensorAddress, sensors);

    IRMA_Send_Command_Get_Sensor_Status(sensorAddress);
    if (IRMA_Check_Response(IRMA_COMMAND_SENSOR_STATUS_QUERY, &commandResponseBuffer, sensorAddress)) {
        if (commandResponseBuffer.data[0] && commandResponseBuffer.data[0] <= 10) {
            while (count < commandResponseBuffer.data[0]) {
                switch (commandResponseBuffer.data[count + 1]) {
                    case 1:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.Sabotage = 1;
                        break;
                    case 2:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.PrimaryConfigurationIsInvalid = 1;
                        break;
                    case 3:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.PrimaryConfigurationIsValid = 1;
                        break;
                    case 4:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.SensorCurrentlyRunningInServiceMode = 1;
                        break;
                    case 5:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.ConfigurationContainsOneOrMoreFaultyParameter = 1;
                        break;
                    case 6:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.ConfigurationIsInvalid = 1;
                        break;
                    case 7:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.MaxTemperatureWasExceededAtLastOnce = 1;
                        break;
                    case 8:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.MaxTemperatureIsCurrentlyExceeded = 1;
                        break;
                    case 9:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.FPGAWasRestarted = 1;
                        break;
                    case 10:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.UndervoltageWasdedected = 1;
                        break;
                    default:
                        break;
                }
                ++count;
            }
            sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
            return (1);
        } else {
            return (0);
        }
    } else {
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

bool IRMA_getFunctionAreaStatus(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors) {
    unsigned char count = 0;
    unsigned char sensorNo = 0;

    sensorNo = IRMA_getSensorNo(sensorAddress, sensors);

    IRMA_Send_Command_Get_Function_Area_Status(sensorAddress);
    if (IRMA_Check_Response(IRMA_COMMAND_FUNCTION_AREA_STATUS_QUERY, &commandResponseBuffer, sensorAddress)) {
        if (commandResponseBuffer.data[0] && commandResponseBuffer.data[0] <= 4) {
            while (count < commandResponseBuffer.data[0]) {
                if (sensors[sensorNo].FA != toShort(commandResponseBuffer.data[3 * count + 2], commandResponseBuffer.data[3 * count + 1])) {
                    sensors[sensorNo].SENSOR_STATUS_FLAGS.FA_DOES_NOT_MATCH = 1;
                    return (0);
                }
                switch (commandResponseBuffer.data[count * 3 + 3]) {
                    case 1:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.NEW_COUNTING_RESULT_AVAIBLE = 1;
                        break;
                    case 2:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.MISSING_SLAVE = 1;
                        break;
                    case 3:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.DOOR_IS_CLEAR = 1;
                        break;
                    case 4:
                        sensors[sensorNo].SENSOR_STATUS_FLAGS.DOOR_IS_NOT_CLEAR = 1;
                        break;
                    default:
                        break;
                }
                ++count;
            }
            sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
            return (1);
        } else {
            return (0);
        }
    } else {
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

void Clear_Configuration_Data_Buffer(unsigned char* configurationDataBuffer) {
    unsigned char count = 0;

    while (count < IRMA_COMMAND_RESPONSE_BUFFER_DATA_LENGHT) {
        configurationDataBuffer[count] = 0;
        ++count;
    }
}

bool IRMA_getActiveConfigurationData(unsigned int sensorAddress, unsigned short groupID, unsigned short parameterID, unsigned char* configurationDataBuffer, volatile IRMA_SENSOR_TYPE* sensors) {
    unsigned char sensorNo = 0;
    unsigned char lenght = 0;
    unsigned char count = 0;

    Clear_Configuration_Data_Buffer(configurationDataBuffer);

    sensorNo = IRMA_getSensorNo(sensorAddress, sensors);

    IRMA_Send_Command_Get_Active_Configuration_Data(sensorAddress, groupID, parameterID);
    if (IRMA_Check_Response(IRMA_COMMAND_ACTIVE_CONFIGURATION_DATA_QUERY, &commandResponseBuffer, sensorAddress)) {
        if (groupID != toShort(commandResponseBuffer.data[1], commandResponseBuffer.data[0])) {
            return (0);
        }
        if (parameterID != toShort(commandResponseBuffer.data[3], commandResponseBuffer.data[2])) {
            return (0);
        }

        lenght = toShort(commandResponseBuffer.data[5], commandResponseBuffer.data[4]);
        if (lenght > IRMA_COMMAND_RESPONSE_BUFFER_DATA_LENGHT) {
            return (0);
        } else {
            while (count < lenght) {
                configurationDataBuffer[count] = commandResponseBuffer.data[count + 6];
                --count;
            }
        }
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
        return (1);
    } else {
        sensors[sensorNo].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

bool IRMA_sensorFirmawareRestart(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sensors) {
    IRMA_Send_Command_Sensor_Firmaware_Restart(sensorAddress);

    if (IRMA_Check_Response(IRMA_COMMAND_SENSOR_FIRMWARE_RESTART, &commandResponseBuffer, sensorAddress)) {
        sensors[IRMA_getSensorNo(sensorAddress, sensors)].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 0;
        return (1);
    } else {
        sensors[IRMA_getSensorNo(sensorAddress, sensors)].SENSOR_STATUS_FLAGS.CAN_NOT_COMMUNICATE_TO_SENSOR = 1;
        return (0);
    }
}

unsigned char IRMA_Scan_Sensors(unsigned int* sensorAddressList) {
    unsigned char count = 0;
    unsigned char sensorCount = 0;

    //clear sensorAddresses buffer
    count = 0;
    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        sensorAddressList[count] = 0;
        ++count;
    }

    IRMA_Send_Command_Scan_Devices();
    count = 0;
    while (count < MAX_SUPPORTED_SENSOR_COUNT) {
        if (IRMA_Check_Response(IRMA_COMMAND_BROADCAST_SCAN, &commandResponseBuffer, 0)) {
            sensorAddressList[count] = commandResponseBuffer.irma_can_identifier.irma_can_address;
            ++sensorCount;
        }
        ++count;
    }
    return (sensorCount);
}


bool IRMA_getSensorFA(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sourceSensors, volatile IRMA_SENSOR_TYPE* destinationSensors) {
    unsigned char sensorNo = 0;
    
    sensorNo = IRMA_getSensorNo(sensorAddress, sourceSensors);
    if (IRMA_getActiveConfigurationData(sourceSensors[sensorNo].SENSOR_ADDRESS, 0x0700, 0x0100, irmaConfigurationDataBuffer, sourceSensors)) {
        destinationSensors[sensorNo].FA = irmaConfigurationDataBuffer[1];
        destinationSensors[sensorNo].FA <<= 8;
        destinationSensors[sensorNo].FA = irmaConfigurationDataBuffer[0];
        return (1);
    } else {
        return (0);
    }
}


bool IRMA_getSensorCountParameters(unsigned int sensorAddress, volatile IRMA_SENSOR_TYPE* sourceSensors, volatile IRMA_SENSOR_TYPE* destinationSensors) 
{
    unsigned char sensorNo = 0;

    sensorNo = IRMA_getSensorNo(sensorAddress, sourceSensors);

    IRMA_Send_Command_Get_Count_Catogory(sourceSensors[sensorNo].SENSOR_ADDRESS, sourceSensors[sensorNo].FA);
    if (IRMA_Check_Response(IRMA_COMMAND_COUNT_CATEGORY_QUERY, &commandResponseBuffer, sourceSensors[sensorNo].SENSOR_ADDRESS)) {
        destinationSensors[sensorNo].COUNT_CATEGORY_COUNT = commandResponseBuffer.data[2]; //TODO: Sistemde tanimlanandan daha fazla Count Category olmasi durumunda uyari verilecek. Bunun nasil yapilacagi belirlenecek.
        destinationSensors[sensorNo].COUNT_CATEGORY_1_ID = commandResponseBuffer.data[3];
        destinationSensors[sensorNo].COUNT_CATEGORY_1_DESC = commandResponseBuffer.data[4];
        destinationSensors[sensorNo].COUNT_CATEGORY_1_PARAMETER_1 = toShort(commandResponseBuffer.data[6], commandResponseBuffer.data[5]);
        destinationSensors[sensorNo].COUNT_CATEGORY_1_PARAMETER_2 = toShort(commandResponseBuffer.data[8], commandResponseBuffer.data[7]);

        if (destinationSensors[sensorNo].COUNT_CATEGORY_COUNT > 1) {
            destinationSensors[sensorNo].COUNT_CATEGORY_2_ID = commandResponseBuffer.data[13];
            destinationSensors[sensorNo].COUNT_CATEGORY_2_DESC = commandResponseBuffer.data[14];
            destinationSensors[sensorNo].COUNT_CATEGORY_2_PARAMETER_1 = toShort(commandResponseBuffer.data[16], commandResponseBuffer.data[15]);
            destinationSensors[sensorNo].COUNT_CATEGORY_2_PARAMETER_2 = toShort(commandResponseBuffer.data[18], commandResponseBuffer.data[17]);
        }

        return (1);
    } else
        return (0);
}

void IRMA_getAllSensorStatus(volatile IRMA_SENSOR_TYPE* sensors) // TODO: Ornek veriler ile kontrol edilecek
{
    unsigned char count = 0;
    unsigned char count1 = 0;
    unsigned char response = 0;

    for (count = 0; count < SYSTEM_PARAMETERS.SystemDoorCount; ++count) {
        IRMA_Send_Command_Get_Sensor_Status(sensors[count].SENSOR_ADDRESS);
        response = IRMA_Check_Response(IRMA_COMMAND_SENSOR_STATUS_QUERY, &commandResponseBuffer, sensors[count].SENSOR_ADDRESS);

        if (response) {
            count1 = 0;
            while (count1 < commandResponseBuffer.data[0]) {
                switch (commandResponseBuffer.data[count1 + 1]) {
                    case 1: //1.	SABOTAGE
                        sensors[count].SENSOR_STATUS_FLAGS.Sabotage = 1;
                        break;
                    case 2: //2.	PRIMARY CONFIGURATION IS INVALID. SENSOR IS RUNNING ON SECONDARY (BACKUP) CONFIGURATION
                        sensors[count].SENSOR_STATUS_FLAGS.PrimaryConfigurationIsInvalid = 1;
                        break;
                    case 3: //3.	PRIMARY CONFIGURATION IS VALID, BUT THE SECONDARY (BACKUP) CONFIGURATION IS MISSING OR INVALID
                        sensors[count].SENSOR_STATUS_FLAGS.PrimaryConfigurationIsValid = 1;
                        break;
                    case 4: //4.	THE SENSOR IS CURRENTLY RUNNING IN SERVICE MODE
                        sensors[count].SENSOR_STATUS_FLAGS.SensorCurrentlyRunningInServiceMode = 1;
                        break;
                    case 5: //5.	THE CONFIGURATION CONTAINS ONE OR MORE PARAMETERS WITH VALUE THAT DOES NOT CONFORM TO THE RESPECTIVE CONSTRAINTS
                        sensors[count].SENSOR_STATUS_FLAGS.ConfigurationContainsOneOrMoreFaultyParameter = 1;
                        break;
                    case 6: //6.	THE CONFIGURATION IS INVALID (PRIMARY AND SECONDARY)
                        sensors[count].SENSOR_STATUS_FLAGS.ConfigurationIsInvalid = 1;
                        break;
                    case 7: //7.	THE MAXIMUM TEMPERATURE WAS EXCEEDED AT LEAST ONCE
                        sensors[count].SENSOR_STATUS_FLAGS.MaxTemperatureWasExceededAtLastOnce = 1;
                        break;
                    case 8: //8.	THE MAXIMUM TEMPERATURE IS CURRENTLY EXCEEDED
                        sensors[count].SENSOR_STATUS_FLAGS.MaxTemperatureIsCurrentlyExceeded = 1;
                        break;
                    case 9: //9.	THE FPGA WAS RESTARTED
                        sensors[count].SENSOR_STATUS_FLAGS.FPGAWasRestarted = 1;
                        break;
                    case 10: //10.	UNDERVOLTAGE WAS DETECTED
                        sensors[count].SENSOR_STATUS_FLAGS.UndervoltageWasdedected = 1;
                        break;
                    default: //
                        break;
                }
                ++count1;
            }
        }
    }
}

//Tum sensorlerin count category'lerini sorgular ve IRMA_SENSOR_LIST_TYPE tipinde buffer'a kaydeder.
void IRMA_getAllSensorsCountCatogory(volatile IRMA_SENSOR_TYPE* sensors) {
    unsigned char count = 0;
    unsigned char response = 0;

    for (count = 0; count < SYSTEM_PARAMETERS.SystemDoorCount; ++count) {
        IRMA_Send_Command_Get_Count_Catogory(sensors[count].SENSOR_ADDRESS, sensors[count].FA);
        response = IRMA_Check_Response(IRMA_COMMAND_COUNT_CATEGORY_QUERY, &commandResponseBuffer, sensors[count].SENSOR_ADDRESS);

        if (response) {
            if (sensors[count].FA == toShort(commandResponseBuffer.data[1], commandResponseBuffer.data[0])) {
                sensors[count].COUNT_CATEGORY_COUNT = commandResponseBuffer.data[2]; //TODO: Sistemde tanimlanandan daha fazla Count Category olmasi durumunda uyari verilecek. Bunun nasil yapilacagi belirlenecek.
                sensors[count].COUNT_CATEGORY_1_ID = commandResponseBuffer.data[3];
                sensors[count].COUNT_CATEGORY_1_DESC = commandResponseBuffer.data[4];
                sensors[count].COUNT_CATEGORY_1_PARAMETER_1 = toShort(commandResponseBuffer.data[6], commandResponseBuffer.data[5]);
                sensors[count].COUNT_CATEGORY_1_PARAMETER_2 = toShort(commandResponseBuffer.data[8], commandResponseBuffer.data[7]);

                if (sensors[count].COUNT_CATEGORY_COUNT > 1) {
                    sensors[count].COUNT_CATEGORY_2_ID = commandResponseBuffer.data[13];
                    sensors[count].COUNT_CATEGORY_2_DESC = commandResponseBuffer.data[14];
                    sensors[count].COUNT_CATEGORY_2_PARAMETER_1 = toShort(commandResponseBuffer.data[16], commandResponseBuffer.data[15]);
                    sensors[count].COUNT_CATEGORY_2_PARAMETER_2 = toShort(commandResponseBuffer.data[18], commandResponseBuffer.data[17]);
                }
            } else {
                sensors[count].SENSOR_STATUS_FLAGS.FA_DOES_NOT_MATCH = 0; // TODO: Bu hata icin ne yapilacagi belirlenecek
            }
        }
    }
}