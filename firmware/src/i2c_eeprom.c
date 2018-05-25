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

#include "i2c_eeprom.h"
#include "bsp.h"
#include "data_types.h"



/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
static uint8_t ackData = 0;
volatile I2C_DATA i2cData;
uint32_t i;
unsigned short I2C_24FC1025_Control_Byte = 0;
volatile unsigned char i2cWriteBuffer[128];
volatile unsigned char i2cReadBuffer[128];
static unsigned char bufferTemp[140];
unsigned char count = 0;

extern volatile SYSTEM_DATA_TYPE sysData;
extern volatile TIMER_TYPE eepromTimeoutTimer;
extern volatile TIMER_TYPE eepromControlTimer;


///* ************************************************************************** */
///* ************************************************************************** */
//// Section: Local Functions                                                   */
///* ************************************************************************** */
///* ************************************************************************** */
//

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_I2CEventHandler(DRV_I2C_BUFFER_EVENT event,
        DRV_I2C_BUFFER_HANDLE bufferHandle,
        uintptr_t context) {
    /* Checks for valid buffer handle */
    if (0 == bufferHandle || DRV_I2C_BUFFER_HANDLE_INVALID == bufferHandle) {
        return;
    }
    /* Decides current state based on previous state */
    switch (i2cData.previousState) {
        case I2C_STATE_READY:
            /* EEPROM is ready, start transmitting the data */
            if (DRV_I2C_BUFFER_EVENT_COMPLETE == event) {
                i2cData.currentState = I2C_STATE_DATA_TRANSMIT;
            }/* EEPROM is not ready, Error!!!*/
            else {
                i2cData.currentState = I2C_STATE_ERROR;
            }
            break;
        case I2C_STATE_DATA_TRANSMIT:
            /* Transmission of the data to EEPROM is done successfully. 
             * Start Acknowledge polling to know 
             * if EEPROM has completed its write cycle. */
            if (DRV_I2C_BUFFER_EVENT_COMPLETE == event) {
                i2cData.currentState = I2C_STATE_SUCCESS;
            }/* Transmission was not successful, Error!!!*/
            else {
                i2cData.currentState = I2C_STATE_ERROR;
            }
            break;
        default:
            i2cData.currentState = I2C_STATE_ERROR;
            break;
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */
unsigned char i2cEepromReadWrite(bool rW, unsigned int address, unsigned char dataLenght, volatile unsigned char* buffer) {
    i2cData.currentState = I2C_STATE_INIT;
    i2cData.previousState = I2C_STATE_INIT;
    setTimer10ms(&eepromTimeoutTimer, EEPROM_TIMEOUT_DELAY);
    while ((i2cData.currentState != I2C_STATE_SUCCESS) && (i2cData.currentState != I2C_STATE_ERROR)) {
        switch (i2cData.currentState) {
            case I2C_STATE_INIT:
                i2cData.drvI2CHandle = DRV_HANDLE_INVALID;
                i2cData.hReadyBuffer = DRV_I2C_BUFFER_HANDLE_INVALID;
                i2cData.hTxBuffer = DRV_I2C_BUFFER_HANDLE_INVALID;
                i2cData.hAckBuffer = DRV_I2C_BUFFER_HANDLE_INVALID;
                i2cData.hRxBuffer = DRV_I2C_BUFFER_HANDLE_INVALID;
                if (rW) {
                    I2C_24FC1025_Control_Byte = I2C_24FC1025_DEVICE_CODE;
                    I2C_24FC1025_Control_Byte |= (unsigned short) (address >> 15) & 0x0000000E; //bit 0 = 0. it's R/W bit    
                    bufferTemp[0] = (unsigned char) (address >> 8) & 0x000000FF;
                    bufferTemp[1] = (unsigned char) address & 0x000000FF;
                } else {
                    I2C_24FC1025_Control_Byte = I2C_24FC1025_DEVICE_CODE;
                    I2C_24FC1025_Control_Byte |= (unsigned short) (address >> 15) & 0x0000000E; //bit 0 = 0. it's R/W bit    
                    bufferTemp[0] = (unsigned char) (address >> 8) & 0x000000FF;
                    bufferTemp[1] = (unsigned char) address & 0x000000FF;
                    count = 0;
                    while (count < dataLenght) {
                        bufferTemp[count + 2] = buffer[count];
                        ++count;
                    }
                }
                /* Open the I2C Driver */
                i2cData.drvI2CHandle = DRV_I2C_Open(DRV_I2C_INDEX_0, (DRV_IO_INTENT_READWRITE | DRV_IO_INTENT_NONBLOCKING));
                DRV_I2C_QueueFlush(i2cData.drvI2CHandle);
                if (DRV_HANDLE_INVALID == i2cData.drvI2CHandle) {
                    return;
                }
                /* Register the I2C Driver event Handler */
                DRV_I2C_BufferEventHandlerSet(i2cData.drvI2CHandle, APP_I2CEventHandler, (uintptr_t) NULL);
                i2cData.previousState = I2C_STATE_INIT;
                i2cData.currentState = I2C_STATE_READY;
                break;
            case I2C_STATE_READY:
                /* Add a transmit request to verify whether EEPROM is ready */
                i2cData.hReadyBuffer = DRV_I2C_Transmit(i2cData.drvI2CHandle, I2C_24FC1025_Control_Byte,
                        (void *) &ackData, I2C_ACK_DATA_LENGTH, (void *) NULL);
                if (DRV_I2C_BUFFER_HANDLE_INVALID == i2cData.hReadyBuffer) {
                    i2cData.currentState = I2C_STATE_ERROR;
                }
                i2cData.previousState = I2C_STATE_READY;
                i2cData.currentState = I2C_STATE_DONE;
                break;
            case I2C_STATE_DATA_TRANSMIT:
                if (rW) {
                    i2cData.hTxBuffer = DRV_I2C_TransmitThenReceive(i2cData.drvI2CHandle,
                            I2C_24FC1025_Control_Byte, (void *) &bufferTemp[0], 2,
                            (void *) &buffer[0], dataLenght, (void *) NULL);
                } else {
                    /* Add a request to transmit the application data */
                    i2cData.hTxBuffer = DRV_I2C_Transmit(i2cData.drvI2CHandle, I2C_24FC1025_Control_Byte,
                            (void *) &bufferTemp[0], dataLenght + 2, (void *) NULL);
                }
                if (DRV_I2C_BUFFER_HANDLE_INVALID == i2cData.hTxBuffer) {
                    i2cData.currentState = I2C_STATE_ERROR;
                }
                i2cData.previousState = I2C_STATE_DATA_TRANSMIT;
                i2cData.currentState = I2C_STATE_DONE;
                break;
            default:
                break;
        }
        if (isTimer10msTimeoutOccured(&eepromTimeoutTimer)) {
            disableTimer10ms(&eepromTimeoutTimer);
            return 0;
        }
    }
    disableTimer10ms(&eepromTimeoutTimer);
    if (i2cData.currentState == I2C_STATE_SUCCESS) {
        DRV_I2C_Close(i2cData.drvI2CHandle);
        return 1;
    } else //if(i2cData.currentState == I2C_STATE_ERROR)
    {
        DRV_I2C_Close(i2cData.drvI2CHandle);
        return 0;
    }
}

void eepromWrite(unsigned int address, unsigned char length, volatile unsigned char* Data_Buffer) {

    unsigned int firstPageLimit = EEPROM_PAGE_SIZE - (address % EEPROM_PAGE_SIZE);

    if (length > firstPageLimit) {
        unsigned int lastAddress = address + length;
        unsigned int secondPageSize = lastAddress % EEPROM_PAGE_SIZE;
        unsigned int firstPageSize = firstPageLimit;
        unsigned char Data_Buffer_1_[firstPageSize];
        unsigned char Data_Buffer_2_[secondPageSize];
        unsigned int a;
        for (a = 0; a < firstPageSize; a++) {
            Data_Buffer_1_[a] = Data_Buffer[a];
        }
        setTimer10ms(&eepromControlTimer, EEPROM_TIMEOUT_DELAY);
        while (!i2cEepromReadWrite(WRITE, address, firstPageSize, Data_Buffer_1_));
        disableTimer10ms(&eepromControlTimer);
        address = address + firstPageSize;
        unsigned int b;
        for (b = 0; b < secondPageSize; b++) {
            Data_Buffer_2_[b] = Data_Buffer[firstPageSize + b];
        }
        setTimer10ms(&eepromControlTimer, EEPROM_TIMEOUT_DELAY);
        while (!i2cEepromReadWrite(WRITE, address, secondPageSize, Data_Buffer_2_));
        disableTimer10ms(&eepromControlTimer);

    } else {
        setTimer10ms(&eepromControlTimer, EEPROM_TIMEOUT_DELAY);
        while (!i2cEepromReadWrite(WRITE, address, length, Data_Buffer));
        disableTimer10ms(&eepromControlTimer);
    }
}

#define adressLimit     65535
void eepromRead(unsigned int address, unsigned char length, volatile unsigned char* Data_Buffer) {
    unsigned int lastAddress = (address & 0X0000FFFF) + length;

    if (lastAddress > adressLimit) {
        int overFlow = (lastAddress - adressLimit) - 1;
        int part1Length = length - overFlow;
        int part2Length = overFlow;
        int part1LastAddress = address;
        int part2LastAddress = address + part1Length;
        volatile unsigned char Data_Buffer_1_[part1Length];
        volatile unsigned char Data_Buffer_2_[part2Length];
        setTimer10ms(&eepromControlTimer, EEPROM_TIMEOUT_DELAY);
        while (!i2cEepromReadWrite(READ, part1LastAddress, part1Length, Data_Buffer) && !isTimer10msTimeoutOccured(&eepromControlTimer));
        disableTimer10ms(&eepromControlTimer);
        int a;
        for (a = 0; a < part1Length; a++) {
            Data_Buffer_1_[a] = Data_Buffer[a];
        }
        setTimer10ms(&eepromControlTimer, EEPROM_TIMEOUT_DELAY);
        while (!i2cEepromReadWrite(READ, part2LastAddress, part2Length, Data_Buffer) && !isTimer10msTimeoutOccured(&eepromControlTimer));
        disableTimer10ms(&eepromControlTimer);
        int b;
        for (b = 0; b < part2Length; b++) {
            Data_Buffer_2_[b] = Data_Buffer[part1Length + b];
        }
        int c;
        for (c = 0; c < part1Length; c++) {
            Data_Buffer[c] = Data_Buffer_1_[c];
        }

        for (; c < part1Length + part2Length; c++) {
            Data_Buffer[c] = Data_Buffer_2_[c];
        }

    } else {
        setTimer10ms(&eepromControlTimer, EEPROM_TIMEOUT_DELAY);
        while (!i2cEepromReadWrite(READ, address, length, Data_Buffer) && !isTimer10msTimeoutOccured(&eepromControlTimer));
        disableTimer10ms(&eepromControlTimer);
    }
}

///* *****************************************************************************

// End of File
// */
