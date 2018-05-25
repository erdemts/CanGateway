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

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
volatile SYSTEM_DATA_TYPE sysData;
volatile SYSTEM_PARAMETERS_TYPE SYSTEM_PARAMETERS;

volatile TIMER_TYPE systemCheckTimer;
volatile TIMER_TYPE uart_1_DataSendTimeoutTimer;
volatile TIMER_TYPE uart_5_DataSendTimeoutTimer;
volatile TIMER_TYPE debounceTimer;
volatile TIMER_TYPE eepromTimeoutTimer;
volatile TIMER_TYPE eepromControlTimer;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
void setSensorPollingTimer10ms(unsigned char timerNo, unsigned int value) { //value * 10 ms delayTimer
    sysData.sensorPollingTimer[timerNo].timerCounter = value;
    sysData.sensorPollingTimer[timerNo].timeoutFlag = 0;
    sysData.sensorPollingTimer[timerNo].timerEnable = 1;
}

void disableSensorPollingTimer10ms(unsigned char timerNo) {
    sysData.sensorPollingTimer[timerNo].timeoutFlag = 0;
    sysData.sensorPollingTimer[timerNo].timerEnable = 0;
}

inline void sensorPollingTimer10msProcess(unsigned char timerNo) {
    if ((--sysData.sensorPollingTimer[timerNo].timerCounter == 0) && sysData.sensorPollingTimer[timerNo].timerEnable) {
        sysData.sensorPollingTimer[timerNo].timeoutFlag = 1;
    }
}

bool isSensorPollingTimer10msEnable1(unsigned char timerNo) {
    return (sysData.sensorPollingTimer[timerNo].timerEnable);
}

bool isSensorPollingTimer10msTimeoutOccured(unsigned char timerNo) {
    return ((sysData.sensorPollingTimer[timerNo].timeoutFlag) & (sysData.sensorPollingTimer[timerNo].timerEnable));
}




void setTimer10ms(volatile TIMER_TYPE* timer, unsigned int value) { //value * 10 ms delayTimer
    timer->timerCounter = value;
    timer->timeoutFlag = 0;
    timer->timerEnable = 1;
}

void disableTimer10ms(volatile TIMER_TYPE* timer) {
    timer->timeoutFlag = 0;
    timer->timerEnable = 0;
}

inline void timer10msProcess(volatile TIMER_TYPE* timer) {
    if ((--timer->timerCounter == 0) && timer->timerEnable) {
        timer->timeoutFlag = 1;
    }
}

bool isTimer10msEnable1(volatile TIMER_TYPE* timer) {
    return (timer->timerEnable);
}

bool isTimer10msTimeoutOccured(volatile TIMER_TYPE* timer) {
    return ((timer->timeoutFlag) & (timer->timerEnable));
}

/* *****************************************************************************
 End of File
 */
