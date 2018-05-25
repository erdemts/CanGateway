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
#include "data_types.h"
#include "app.h"
#include "uart.h"
#include "commands.h"
#include "uart_protocol_handler.h"


extern volatile SYSTEM_DATA_TYPE sysData;
extern volatile SYSTEM_PARAMETERS_TYPE SYSTEM_PARAMETERS;
extern struct tm *sysTime_str;



/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */


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
void prepareMessagePackage(unsigned char command, volatile UART_DATA_TYPE* uartData) {
    unsigned short crc = 0;
    unsigned char count = 0;
    unsigned char dataLenghtWithSeperators = 0;
    unsigned char crcLenght = 2;

    uartData->messageBuffer.W = 0;
    uartData->messageBuffer.R = 0;

    addDataToBuffer(&uartData->messageBuffer, STX, BUFFER_SIZE); //STX of message package
    addDataToBuffer(&uartData->messageBuffer, command, BUFFER_SIZE); //Command of message package
    crc = UpdateCrc(command, crc);

    //Calculate message lenght
    while (count < (uartData->transmitDataBuffer.W - uartData->transmitDataBuffer.R)) //Data bytes of message package
    {
        if (uartData->transmitDataBuffer.buffer[count] == STX || uartData->transmitDataBuffer.buffer[count] == ETX || uartData->transmitDataBuffer.buffer[count] == SEPERATOR) {
            ++dataLenghtWithSeperators;
        }
        ++dataLenghtWithSeperators;
        ++count;
    }
    addDataToBuffer(&uartData->messageBuffer, dataLenghtWithSeperators + 1, BUFFER_SIZE); //Lenght of message package. dataLenghtWithSeperators + 1(for command byte))
    crc = UpdateCrc(dataLenghtWithSeperators + 1, crc);

    count = 0;
    while (count < (uartData->transmitDataBuffer.W - uartData->transmitDataBuffer.R)) //Data bytes of message package
    {
        if (uartData->transmitDataBuffer.buffer[count] == STX || uartData->transmitDataBuffer.buffer[count] == ETX || uartData->transmitDataBuffer.buffer[count] == SEPERATOR) {
            addDataToBuffer(&uartData->messageBuffer, SEPERATOR, BUFFER_SIZE);
            crc = UpdateCrc(SEPERATOR, crc);
        }
        addDataToBuffer(&uartData->messageBuffer, uartData->transmitDataBuffer.buffer[count], BUFFER_SIZE);
        crc = UpdateCrc(uartData->transmitDataBuffer.buffer[count], crc);
        ++count;
    }
    if ((hibyte(crc) == STX) || (hibyte(crc) == ETX) || (hibyte(crc) == SEPERATOR)) {
        ++crcLenght;
    }
    if ((lobyte(crc) == STX) || (lobyte(crc) == ETX) || (lobyte(crc) == SEPERATOR)) {
        ++crcLenght;
    }
    addDataToBuffer(&uartData->messageBuffer, crcLenght, BUFFER_SIZE);

    if ((hibyte(crc) == STX) || (hibyte(crc) == ETX) || (hibyte(crc) == SEPERATOR)) {
        addDataToBuffer(&uartData->messageBuffer, SEPERATOR, BUFFER_SIZE);
    }
    addDataToBuffer(&uartData->messageBuffer, hibyte(crc), BUFFER_SIZE);
    if ((lobyte(crc) == STX) || (lobyte(crc) == ETX) || (lobyte(crc) == SEPERATOR)) {
        addDataToBuffer(&uartData->messageBuffer, SEPERATOR, BUFFER_SIZE);
    }
    addDataToBuffer(&uartData->messageBuffer, lobyte(crc), BUFFER_SIZE);
    addDataToBuffer(&uartData->messageBuffer, ETX, BUFFER_SIZE);
}

void uartCommandHandler(volatile UART_DATA_TYPE* uartData) {

    unsigned char dataTemp = 0;

    if (uartData->uartReceiveBuffer.W != uartData->uartReceiveBuffer.R) {
        dataTemp = getDataFromBuffer(&uartData->uartReceiveBuffer, BUFFER_SIZE);
        switch (uartData->commandHandlerState) {
            case WAIT_STX:
                if ((dataTemp == STX) && (uartData->oldData != SEPERATOR)) {
                    uartData->commandHandlerState = WAIT_COMMAND;
                    uartData->receivedCRC = 0;
                    uartData->calculatedCRC = 0;
                }
                break;
            case WAIT_COMMAND:
                uartData->command = 0;
                if ((dataTemp != STX) && (dataTemp != ETX) && (dataTemp != SEPERATOR) && (uartData->oldData != SEPERATOR)) {
                    uartData->command = dataTemp;
                    uartData->calculatedCRC = UpdateCrc(dataTemp, uartData->calculatedCRC);
                    uartData->commandHandlerState = WAIT_LENGHT;
                } else {
                    uartData->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_LENGHT:
                uartData->lenght = 0;
                if ((dataTemp != STX) && (dataTemp != ETX) && (dataTemp != SEPERATOR) && (uartData->oldData != SEPERATOR)) {
                    uartData->lenght = dataTemp;
                    clearDataBuffer(&uartData->receivedDataBuffer, BUFFER_SIZE);
                    uartData->calculatedCRC = UpdateCrc(dataTemp, uartData->calculatedCRC);
                    uartData->dataCount = uartData->lenght - 1;
                    if (uartData->dataCount) //data sayisi 0 ise WAIT_CRC_H beklenir.
                    {
                        uartData->commandHandlerState = WAIT_DATA;
                    } else {
                        uartData->commandHandlerState = WAIT_CRC_LENGHT;
                    }
                } else {
                    uartData->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_DATA:
                if (uartData->dataCount > 0) {
                    if ((dataTemp == STX) || (dataTemp == ETX) || (dataTemp == SEPERATOR)) {
                        if (uartData->oldData == SEPERATOR) {
                            addDataToBuffer(&uartData->receivedDataBuffer, dataTemp, BUFFER_SIZE);
                            uartData->calculatedCRC = UpdateCrc(dataTemp, uartData->calculatedCRC);
                        } else {
                            if (dataTemp == SEPERATOR) {
                                uartData->calculatedCRC = UpdateCrc(dataTemp, uartData->calculatedCRC);
                            } else {
                                uartData->commandHandlerState = WAIT_STX;
                            }
                        }
                    } else {
                        addDataToBuffer(&uartData->receivedDataBuffer, dataTemp, BUFFER_SIZE);
                        uartData->calculatedCRC = UpdateCrc(dataTemp, uartData->calculatedCRC);
                    }
                    --uartData->dataCount;
                    if (uartData->dataCount == 0) {
                        uartData->commandHandlerState = WAIT_CRC_LENGHT;
                    }
                }
                break;
            case WAIT_CRC_LENGHT:
                if (dataTemp <= 4) {
                    uartData->crcLenght = dataTemp;
                    uartData->commandHandlerState = WAIT_CRC_H;
                } else {
                    uartData->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_CRC_H:
                if (uartData->crcLenght <= 4) {
                    if ((dataTemp == STX) || (dataTemp == ETX) || (dataTemp == SEPERATOR)) {
                        if (uartData->oldData == SEPERATOR) {
                            uartData->receivedCRC = dataTemp;
                            uartData->commandHandlerState = WAIT_CRC_L;
                        }
                    } else {
                        if (uartData->oldData == SEPERATOR) {
                            uartData->commandHandlerState = WAIT_STX;
                        } else {
                            uartData->receivedCRC = dataTemp;
                            uartData->commandHandlerState = WAIT_CRC_L;
                        }
                    }
                    --uartData->crcLenght;
                } else {
                    uartData->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_CRC_L:
                if (uartData->crcLenght <= 4) {
                    if ((dataTemp == STX) || (dataTemp == ETX) || (dataTemp == SEPERATOR)) {
                        if (uartData->oldData == SEPERATOR) {
                            uartData->receivedCRC <<= 8;
                            uartData->receivedCRC |= dataTemp;
                            uartData->commandHandlerState = WAIT_ETX;
                        }
                    } else {
                        if (uartData->oldData == SEPERATOR) {
                            uartData->commandHandlerState = WAIT_STX;
                        } else {
                            uartData->receivedCRC <<= 8;
                            uartData->receivedCRC |= dataTemp;
                            uartData->commandHandlerState = WAIT_ETX;
                        }
                    }
                    --uartData->crcLenght;
                } else {
                    uartData->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_ETX:
                if (dataTemp == ETX) {
                    uartData->commandHandlerState = RUN_COMMAND;
                } else {
                    uartData->commandHandlerState = WAIT_STX;
                }
                break;
            default:
                break;
        }
        uartData->oldData = dataTemp;
        if (uartData->commandHandlerState == RUN_COMMAND) {
            if (uartData->calculatedCRC == uartData->receivedCRC) {
                uartProcessCommand(uartData);
                uartData->commandHandlerState = WAIT_STX;
            } else//Hatali CRC Durumu
            {
                uartData->commandHandlerState = WAIT_STX;
            }
        }
    }
}

void uartProcessCommand(volatile UART_DATA_TYPE* uartData) {

    unsigned char count = 0;
    bool commandSendEnable = 0;

    clearDataBuffer(&uartData->transmitDataBuffer, BUFFER_SIZE);

    switch (uartData->command) {
        case CMD_SET_DOOR_COUNT:
            if (uartData->receivedDataBuffer.buffer[0] > 0 && uartData->receivedDataBuffer.buffer[0] <= MAX_SUPPORTED_SENSOR_COUNT) {
                SYSTEM_PARAMETERS.SystemDoorCount = uartData->receivedDataBuffer.buffer[0];
                recordSystemParametersToEEprom();
                uartData->command = RSP_ACK;
                commandSendEnable = 1;
            }//TODO: Else için ne yap?laca??na karar verilecek
            break;
        case CMD_GET_DOOR_COUNT:
            addDataToBuffer(&uartData->transmitDataBuffer, SYSTEM_PARAMETERS.SystemDoorCount, BUFFER_SIZE);
            uartData->command = RSP_DOOR_COUNT;
            commandSendEnable = 1;
            break;
        case CMD_SET_COUNT_CATEGORY_COUNT:
            if (uartData->receivedDataBuffer.buffer[0] > 0 && uartData->receivedDataBuffer.buffer[0] <= 2) {
                SYSTEM_PARAMETERS.SystemCountCategoryCount = uartData->receivedDataBuffer.buffer[0];
                recordSystemParametersToEEprom();
                uartData->command = RSP_ACK;
                commandSendEnable = 1;
            }//TODO: Else için ne yap?laca??na karar verilecek
            break;
        case CMD_GET_COUNT_CATEGORY_COUNT:
            addDataToBuffer(&uartData->transmitDataBuffer, SYSTEM_PARAMETERS.SystemCountCategoryCount, BUFFER_SIZE);
            uartData->command = RSP_COUNT_CATEGORY_COUNT;
            commandSendEnable = 1;
            break;
        case CMD_SET_COUNT_CATEGORY_ID:
            if (uartData->receivedDataBuffer.buffer[0] == 1) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1 = uartData->receivedDataBuffer.buffer[1];
                recordSystemParametersToEEprom();
            } else if (uartData->receivedDataBuffer.buffer[0] == 2) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2 = uartData->receivedDataBuffer.buffer[1];
                recordSystemParametersToEEprom();
            }
            uartData->command = RSP_ACK;
            commandSendEnable = 1;
            break;
        case CMD_GET_COUNT_CATEGORY_ID:
            if (uartData->receivedDataBuffer.buffer[0] == 1) {
                addDataToBuffer(&uartData->transmitDataBuffer, SYSTEM_PARAMETERS.SystemCountCategory_ID_1, BUFFER_SIZE);
            } else if (uartData->receivedDataBuffer.buffer[0] == 2) {
                addDataToBuffer(&uartData->transmitDataBuffer, SYSTEM_PARAMETERS.SystemCountCategory_ID_2, BUFFER_SIZE);
            }
            uartData->command = RSP_COUNT_CATEGORY_ID;
            commandSendEnable = 1;
            break;
        case CMD_SET_DOOR_SENSOR_ADDRESS:
            if (uartData->receivedDataBuffer.buffer[0] > 0 && uartData->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS = uartData->receivedDataBuffer.buffer[1];
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS <<= 8;
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS |= uartData->receivedDataBuffer.buffer[2];
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS <<= 8;
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS |= uartData->receivedDataBuffer.buffer[3];
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS <<= 8;
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS |= uartData->receivedDataBuffer.buffer[4];
                recordSystemParametersToEEprom();
            }
            uartData->command = RSP_ACK;
            commandSendEnable = 1;
            break;
        case CMD_GET_DOOR_SENSOR_ADDRESS:
            if (uartData->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS >> 24) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS >> 16) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS >> 8) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS & 0x000000FF), BUFFER_SIZE);
            }
            uartData->command = RSP_DOOR_SENSOR_ADDRESS;
            commandSendEnable = 1;
            break;
        case CMD_SET_DOOR_FA:
            if (uartData->receivedDataBuffer.buffer[0] > 0 && uartData->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].FA = uartData->receivedDataBuffer.buffer[1];
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].FA <<= 8;
                sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].FA |= uartData->receivedDataBuffer.buffer[2];
                recordSystemParametersToEEprom();
            }
            uartData->command = RSP_ACK;
            commandSendEnable = 1;
            break;
        case CMD_GET_DOOR_FA:
            if (uartData->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].FA >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].FA & 0x00FF), BUFFER_SIZE);
            }
            uartData->command = RSP_DOOR_FA;
            commandSendEnable = 1;
            break;
        case CMD_SET_COUNT_CATEGORY_PARAMETERS:
            if (uartData->receivedDataBuffer.buffer[0] == 1) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 = uartData->receivedDataBuffer.buffer[1];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 |= uartData->receivedDataBuffer.buffer[2];

                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 = uartData->receivedDataBuffer.buffer[3];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 |= uartData->receivedDataBuffer.buffer[4];
                recordSystemParametersToEEprom();

            } else if (uartData->receivedDataBuffer.buffer[0] == 2) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 = uartData->receivedDataBuffer.buffer[1];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 |= uartData->receivedDataBuffer.buffer[2];

                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 = uartData->receivedDataBuffer.buffer[3];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 |= uartData->receivedDataBuffer.buffer[4];
                recordSystemParametersToEEprom();

            }
            uartData->command = RSP_ACK;
            commandSendEnable = 1;
            break;
        case CMD_GET_COUNT_CATEGORY_PARAMETERS:
            if (uartData->receivedDataBuffer.buffer[0] == 1) {
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 & 0x00FF), BUFFER_SIZE);
            } else if (uartData->receivedDataBuffer.buffer[0] == 2) {
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 & 0x00FF), BUFFER_SIZE);
            }
            uartData->command = RSP_COUNT_CATEGORY_PARAMETERS;
            commandSendEnable = 1;
            break;
        case CMD_GET_SENSOR_STATUS:
            addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].sensorStatus >> 8) & 0x000000FF), BUFFER_SIZE);
            addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].sensorStatus & 0x000000FF), BUFFER_SIZE);
            uartData->command = RSP_SENSOR_STATUS;
            commandSendEnable = 1;
            break;
        case CMD_GET_COUNT_RESULT://TODO:kapi no gelmese de sonuc gönderiyor. Duzeltilecek.
            addDataToBuffer(&uartData->transmitDataBuffer, sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].CAT_1_IN_B, BUFFER_SIZE);
            addDataToBuffer(&uartData->transmitDataBuffer, sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].CAT_1_OUT_B, BUFFER_SIZE);
            addDataToBuffer(&uartData->transmitDataBuffer, sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].CAT_2_IN_B, BUFFER_SIZE);
            addDataToBuffer(&uartData->transmitDataBuffer, sysData.Door[uartData->receivedDataBuffer.buffer[0] - 1].CAT_2_OUT_B, BUFFER_SIZE);
            uartData->command = RSP_COUNT_RESULT;
            commandSendEnable = 1;
            break;
        case CMD_CHECK_SYSTEM_PARAMETERS:

            checkAllSensorParameters();

            unsigned int i = 0;
            for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[i].sensorStatus >> 24) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[i].sensorStatus >> 16) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) ((sysData.Door[i].sensorStatus >> 8) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartData->transmitDataBuffer, (unsigned char) (sysData.Door[i].sensorStatus & 0x000000FF), BUFFER_SIZE);
            }
            uartData->command = RSP_CHECK_SYSTEM_PARAMETERS;
            commandSendEnable = 1;
            break;
        case CMD_SET_DOOR_INPUT_TYPE:
            SYSTEM_PARAMETERS.INPUT_TYPES.input_types = uartData->receivedDataBuffer.buffer[0];
            recordSystemParametersToEEprom();
            uartData->command = RSP_ACK;
            commandSendEnable = 1;
            break;
        case CMD_GET_DOOR_INPUT_TYPE:
            addDataToBuffer(&uartData->transmitDataBuffer, SYSTEM_PARAMETERS.INPUT_TYPES.input_types, BUFFER_SIZE);
            uartData->command = RSP_DOOR_INPUT_TYPE;
            commandSendEnable = 1;
            break;
        default://TODO: Gelen komutun gecerli bir komut olup olmadigi kontrol edilmeli
            commandSendEnable = 0;
            count = 0;
            clearDataBuffer(&uartData->commandDataBuffer, BUFFER_SIZE);
            uartData->receivedCommand = uartData->command;
            while (count < (uartData->receivedDataBuffer.W - uartData->receivedDataBuffer.R)) {
                addDataToBuffer(&uartData->transmitDataBuffer, uartData->receivedDataBuffer.buffer[count], BUFFER_SIZE);
                ++count;
            }
            sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 1;
            break;
    }
    if (commandSendEnable) {
        commandSendEnable = 0;
        sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
        prepareMessagePackage(uartData->command, uartData);
        addBufferToBuffer(&uartData->messageBuffer, &uartData->uartTransmitBuffer, BUFFER_SIZE);
        USART_1_StartTransmit();
    }
}

void uartCommandHandlerGeneral(volatile UART_DATA_TYPE* uartTransmit, volatile UART_DATA_TYPE* uartReceive, unsigned char uartType) {

    unsigned char dataTemp = 0;

    if (uartReceive->uartReceiveBuffer.W != uartReceive->uartReceiveBuffer.R) {
        dataTemp = getDataFromBuffer(&uartReceive->uartReceiveBuffer, BUFFER_SIZE);
        switch (uartReceive->commandHandlerState) {
            case WAIT_STX:
                if ((dataTemp == STX) && (uartReceive->oldData != SEPERATOR)) {
                    uartReceive->commandHandlerState = WAIT_COMMAND;
                    uartReceive->receivedCRC = 0;
                    uartReceive->calculatedCRC = 0;
                }
                break;
            case WAIT_COMMAND:
                uartReceive->command = 0;
                if ((dataTemp != STX) && (dataTemp != ETX) && (dataTemp != SEPERATOR) && (uartReceive->oldData != SEPERATOR)) {
                    uartReceive->command = dataTemp;
                    uartReceive->calculatedCRC = UpdateCrc(dataTemp, uartReceive->calculatedCRC);
                    uartReceive->commandHandlerState = WAIT_LENGHT;
                } else {
                    uartReceive->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_LENGHT:
                uartReceive->lenght = 0;
                if ((dataTemp != STX) && (dataTemp != ETX) && (dataTemp != SEPERATOR) && (uartReceive->oldData != SEPERATOR)) {
                    uartReceive->lenght = dataTemp;
                    clearDataBuffer(&uartReceive->receivedDataBuffer, BUFFER_SIZE);
                    uartReceive->calculatedCRC = UpdateCrc(dataTemp, uartReceive->calculatedCRC);
                    uartReceive->dataCount = uartReceive->lenght - 1;
                    if (uartReceive->dataCount) //data sayisi 0 ise WAIT_CRC_H beklenir.
                    {
                        uartReceive->commandHandlerState = WAIT_DATA;
                    } else {
                        uartReceive->commandHandlerState = WAIT_CRC_LENGHT;
                    }
                } else {
                    uartReceive->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_DATA:
                if (uartReceive->dataCount > 0) {
                    if ((dataTemp == STX) || (dataTemp == ETX) || (dataTemp == SEPERATOR)) {
                        if (uartReceive->oldData == SEPERATOR) {
                            addDataToBuffer(&uartReceive->receivedDataBuffer, dataTemp, BUFFER_SIZE);
                            uartReceive->calculatedCRC = UpdateCrc(dataTemp, uartReceive->calculatedCRC);
                        } else {
                            if (dataTemp == SEPERATOR) {
                                uartReceive->calculatedCRC = UpdateCrc(dataTemp, uartReceive->calculatedCRC);
                            } else {
                                uartReceive->commandHandlerState = WAIT_STX;
                            }
                        }
                    } else {
                        addDataToBuffer(&uartReceive->receivedDataBuffer, dataTemp, BUFFER_SIZE);
                        uartReceive->calculatedCRC = UpdateCrc(dataTemp, uartReceive->calculatedCRC);
                    }
                    --uartReceive->dataCount;
                    if (uartReceive->dataCount == 0) {
                        uartReceive->commandHandlerState = WAIT_CRC_LENGHT;
                    }
                }
                break;
            case WAIT_CRC_LENGHT:
                if (dataTemp <= 4) {
                    uartReceive->crcLenght = dataTemp;
                    uartReceive->commandHandlerState = WAIT_CRC_H;
                } else {
                    uartReceive->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_CRC_H:
                if (uartReceive->crcLenght <= 4) {
                    if ((dataTemp == STX) || (dataTemp == ETX) || (dataTemp == SEPERATOR)) {
                        if (uartReceive->oldData == SEPERATOR) {
                            uartReceive->receivedCRC = dataTemp;
                            uartReceive->commandHandlerState = WAIT_CRC_L;
                        }
                    } else {
                        if (uartReceive->oldData == SEPERATOR) {
                            uartReceive->commandHandlerState = WAIT_STX;
                        } else {
                            uartReceive->receivedCRC = dataTemp;
                            uartReceive->commandHandlerState = WAIT_CRC_L;
                        }
                    }
                    --uartReceive->crcLenght;
                } else {
                    uartReceive->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_CRC_L:
                if (uartReceive->crcLenght <= 4) {
                    if ((dataTemp == STX) || (dataTemp == ETX) || (dataTemp == SEPERATOR)) {
                        if (uartReceive->oldData == SEPERATOR) {
                            uartReceive->receivedCRC <<= 8;
                            uartReceive->receivedCRC |= dataTemp;
                            uartReceive->commandHandlerState = WAIT_ETX;
                        }
                    } else {
                        if (uartReceive->oldData == SEPERATOR) {
                            uartReceive->commandHandlerState = WAIT_STX;
                        } else {
                            uartReceive->receivedCRC <<= 8;
                            uartReceive->receivedCRC |= dataTemp;
                            uartReceive->commandHandlerState = WAIT_ETX;
                        }
                    }
                    --uartReceive->crcLenght;
                } else {
                    uartReceive->commandHandlerState = WAIT_STX;
                }
                break;
            case WAIT_ETX:
                if (dataTemp == ETX) {
                    uartReceive->commandHandlerState = RUN_COMMAND;
                } else {
                    uartReceive->commandHandlerState = WAIT_STX;
                }
                break;
            default:
                break;
        }
        uartReceive->oldData = dataTemp;
        if (uartReceive->commandHandlerState == RUN_COMMAND) {
            if (uartReceive->calculatedCRC == uartReceive->receivedCRC) {
                uartProcessCommandGeneral(uartTransmit, uartReceive, uartType);
                uartReceive->commandHandlerState = WAIT_STX;
            } else//Hatali CRC Durumu
            {
                uartReceive->commandHandlerState = WAIT_STX;
            }
        }
    }
}

void uartProcessCommandGeneral(volatile UART_DATA_TYPE* uartTransmit, volatile UART_DATA_TYPE* uartReceive, unsigned char uartType) {
//TODO:Tüm komutlar test edilecek
    unsigned char count = 0;
    bool commandSendEnable = 0;

    clearDataBuffer(&uartTransmit->transmitDataBuffer, BUFFER_SIZE);

    switch (uartReceive->command) {
        case CMD_SET_DOOR_COUNT:
            if (uartReceive->receivedDataBuffer.buffer[0] > 0 && uartReceive->receivedDataBuffer.buffer[0] <= MAX_SUPPORTED_SENSOR_COUNT) {
                SYSTEM_PARAMETERS.SystemDoorCount = uartReceive->receivedDataBuffer.buffer[0];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            }
            else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_DOOR_COUNT:
            addDataToBuffer(&uartTransmit->transmitDataBuffer, SYSTEM_PARAMETERS.SystemDoorCount, BUFFER_SIZE);
            uartTransmit->command = RSP_DOOR_COUNT;
            commandSendEnable = 1;
            break;
        case CMD_SET_COUNT_CATEGORY_COUNT:
            if (uartReceive->receivedDataBuffer.buffer[0] > 0 && uartReceive->receivedDataBuffer.buffer[0] <= 2) {
                SYSTEM_PARAMETERS.SystemCountCategoryCount = uartReceive->receivedDataBuffer.buffer[0];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            }
            else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_COUNT_CATEGORY_COUNT:
            addDataToBuffer(&uartTransmit->transmitDataBuffer, SYSTEM_PARAMETERS.SystemCountCategoryCount, BUFFER_SIZE);
            uartTransmit->command = RSP_COUNT_CATEGORY_COUNT;
            commandSendEnable = 1;
            break;
        case CMD_SET_COUNT_CATEGORY_ID:
            if (uartReceive->receivedDataBuffer.buffer[0] == 1) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1 = uartReceive->receivedDataBuffer.buffer[1];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            } else if (uartReceive->receivedDataBuffer.buffer[0] == 2) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2 = uartReceive->receivedDataBuffer.buffer[1];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_COUNT_CATEGORY_ID:
            if (uartReceive->receivedDataBuffer.buffer[0] == 1) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, SYSTEM_PARAMETERS.SystemCountCategory_ID_1, BUFFER_SIZE);
                uartTransmit->command = RSP_COUNT_CATEGORY_ID;
                commandSendEnable = 1;
            } else if (uartReceive->receivedDataBuffer.buffer[0] == 2) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, SYSTEM_PARAMETERS.SystemCountCategory_ID_2, BUFFER_SIZE);
                uartTransmit->command = RSP_COUNT_CATEGORY_ID;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_SET_DOOR_SENSOR_ADDRESS:
            if (uartReceive->receivedDataBuffer.buffer[0] > 0 && uartReceive->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS = uartReceive->receivedDataBuffer.buffer[1];
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS <<= 8;
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS |= uartReceive->receivedDataBuffer.buffer[2];
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS <<= 8;
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS |= uartReceive->receivedDataBuffer.buffer[3];
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS <<= 8;
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS |= uartReceive->receivedDataBuffer.buffer[4];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_DOOR_SENSOR_ADDRESS:
            if (uartReceive->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS >> 24) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS >> 16) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS >> 8) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].SENSOR_ADDRESS & 0x000000FF), BUFFER_SIZE);
                uartTransmit->command = RSP_DOOR_SENSOR_ADDRESS;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_SET_DOOR_FA:
            if (uartReceive->receivedDataBuffer.buffer[0] > 0 && uartReceive->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].FA = uartReceive->receivedDataBuffer.buffer[1];
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].FA <<= 8;
                sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].FA |= uartReceive->receivedDataBuffer.buffer[2];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_DOOR_FA:
            if (uartReceive->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].FA >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].FA & 0x00FF), BUFFER_SIZE);
                uartTransmit->command = RSP_DOOR_FA;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_SET_COUNT_CATEGORY_PARAMETERS:
            if (uartReceive->receivedDataBuffer.buffer[0] == 1) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 = uartReceive->receivedDataBuffer.buffer[1];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 |= uartReceive->receivedDataBuffer.buffer[2];

                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 = uartReceive->receivedDataBuffer.buffer[3];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 |= uartReceive->receivedDataBuffer.buffer[4];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            } else if (uartReceive->receivedDataBuffer.buffer[0] == 2) {
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 = uartReceive->receivedDataBuffer.buffer[1];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 |= uartReceive->receivedDataBuffer.buffer[2];

                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 = uartReceive->receivedDataBuffer.buffer[3];
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 <<= 8;
                SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 |= uartReceive->receivedDataBuffer.buffer[4];
                recordSystemParametersToEEprom();
                uartTransmit->command = RSP_ACK;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_COUNT_CATEGORY_PARAMETERS:
            if (uartReceive->receivedDataBuffer.buffer[0] == 1) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_1 & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_1_Param_2 & 0x00FF), BUFFER_SIZE);
                uartTransmit->command = RSP_COUNT_CATEGORY_PARAMETERS;
                commandSendEnable = 1;
            } else if (uartReceive->receivedDataBuffer.buffer[0] == 2) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_1 & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 >> 8) & 0x00FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (SYSTEM_PARAMETERS.SystemCountCategory_ID_2_Param_2 & 0x00FF), BUFFER_SIZE);
                uartTransmit->command = RSP_COUNT_CATEGORY_PARAMETERS;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_SENSOR_STATUS:
            if (uartReceive->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) ((sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].sensorStatus >> 8) & 0x000000FF), BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].sensorStatus & 0x000000FF), BUFFER_SIZE);
                uartTransmit->command = RSP_SENSOR_STATUS;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_GET_COUNT_RESULT:
            if (uartReceive->receivedDataBuffer.buffer[0] <= SYSTEM_PARAMETERS.SystemDoorCount) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].CAT_1_IN_B, BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].CAT_1_OUT_B, BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].CAT_2_IN_B, BUFFER_SIZE);
                addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.Door[uartReceive->receivedDataBuffer.buffer[0] - 1].CAT_2_OUT_B, BUFFER_SIZE);
                uartTransmit->command = RSP_COUNT_RESULT;
                commandSendEnable = 1;
            } else {
                uartTransmit->command = RSP_NACK;
                commandSendEnable = 1;
            }
            break;
        case CMD_CHECK_SYSTEM_PARAMETERS:
            checkAllSensorParameters();
            addDataToBuffer(&uartTransmit->transmitDataBuffer, SYSTEM_PARAMETERS.SystemDoorCount, BUFFER_SIZE);
            unsigned int i = 0;
            for (i = 0; i < SYSTEM_PARAMETERS.SystemDoorCount; i++) {
                addDataToBuffer(&uartTransmit->transmitDataBuffer, (unsigned char) (sysData.sensorCheckStatus[i].sensorCheckStatusData & 0x000000FF), BUFFER_SIZE);
            }
            uartTransmit->command = RSP_CHECK_SYSTEM_PARAMETERS;
            commandSendEnable = 1;
            break;
        case CMD_SET_DOOR_INPUT_TYPE:
            SYSTEM_PARAMETERS.INPUT_TYPES.input_types = uartTransmit->receivedDataBuffer.buffer[0];
            recordSystemParametersToEEprom();
            uartTransmit->command = RSP_ACK;
            commandSendEnable = 1;
            break;
        case CMD_GET_DOOR_INPUT_TYPE:
            addDataToBuffer(&uartTransmit->transmitDataBuffer, SYSTEM_PARAMETERS.INPUT_TYPES.input_types, BUFFER_SIZE);
            uartTransmit->command = RSP_DOOR_INPUT_TYPE;
            commandSendEnable = 1;
            break;
        case SET_LOCATION_AND_TIME:
            updateSystemTime(uartReceive->receivedDataBuffer.buffer[0], uartReceive->receivedDataBuffer.buffer[1], uartReceive->receivedDataBuffer.buffer[2],
                    uartReceive->receivedDataBuffer.buffer[3], uartReceive->receivedDataBuffer.buffer[4], uartReceive->receivedDataBuffer.buffer[5]);
            sysData.LATITUDE.Lat0 = uartReceive->receivedDataBuffer.buffer[6];
            sysData.LATITUDE.Lat1 = uartReceive->receivedDataBuffer.buffer[7];
            sysData.LATITUDE.Lat2 = uartReceive->receivedDataBuffer.buffer[8];
            sysData.LATITUDE.Lat3 = uartReceive->receivedDataBuffer.buffer[9];
            sysData.LONGITUDE.Lon0 = uartReceive->receivedDataBuffer.buffer[10];
            sysData.LONGITUDE.Lon1 = uartReceive->receivedDataBuffer.buffer[11];
            sysData.LONGITUDE.Lon2 = uartReceive->receivedDataBuffer.buffer[12];
            sysData.LONGITUDE.Lon3 = uartReceive->receivedDataBuffer.buffer[13];
            uartTransmit->command = RSP_ACK;
            commandSendEnable = 0;
            break;
        case GET_LOCATION_AND_TIME:
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysTime_str->tm_mday, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysTime_str->tm_mon + 1, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysTime_str->tm_year - 100, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysTime_str->tm_hour, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysTime_str->tm_min, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysTime_str->tm_sec, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LATITUDE.Lat0, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LATITUDE.Lat1, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LATITUDE.Lat2, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LATITUDE.Lat3, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LONGITUDE.Lon0, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LONGITUDE.Lon1, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LONGITUDE.Lon2, BUFFER_SIZE);
            addDataToBuffer(&uartTransmit->transmitDataBuffer, sysData.LONGITUDE.Lon3, BUFFER_SIZE);
            uartTransmit->command = RSP_LOCATION_AND_TIME;
            commandSendEnable = 0;
            break;
        case RSP_ACK:
            commandSendEnable = 0;
            count = 0;
            clearDataBuffer(&uartReceive->commandDataBuffer, BUFFER_SIZE);
            uartReceive->receivedCommand = uartReceive->command;
            while (count < (uartReceive->receivedDataBuffer.W - uartReceive->receivedDataBuffer.R)) {
                addDataToBuffer(&uartReceive->commandDataBuffer, uartReceive->receivedDataBuffer.buffer[count], BUFFER_SIZE);
                ++count;
            }
            sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 1;
            break;
        default://Unknown command
            uartTransmit->command = RSP_NACK;
            commandSendEnable = 1;
            break;
    }
    if (commandSendEnable) {
        commandSendEnable = 0;
        sysData.SYSTEM_STATUS.SYSTEM_STATUS_FLAGS.NEW_COMMAND_AVAIBLE = 0;
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

/* *****************************************************************************
 End of File
 */
