
#ifndef _TIMERDEFINITIONS_H    /* Guard against multiple inclusion */
#define _TIMERDEFINITIONS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    
    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */
#define DEBOUNCE_DELAY                              (5)     //5x10ms
#define DATA_SEND_DELAY_TIME                        (200)   //200x10ms 
#define RECORDED_DATA_CHECK_DELAY_TIME              (1000)   //1000x10ms
#define EEPROM_TIMEOUT_DELAY                        (100)


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef struct {
        unsigned int timerCounter;
        bool timerEnable;
        bool timeoutFlag;
    } TIMER_TYPE;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    void setSensorPollingTimer10ms(unsigned char timerNo, unsigned int value); //value * 10 ms delayTimer
    void disableSensorPollingTimer10ms(unsigned char timerNo);
    inline void sensorPollingTimer10msProcess(unsigned char timerNo);
    bool isSensorPollingTimer10msEnable1(unsigned char timerNo);
    bool isSensorPollingTimer10msTimeoutOccured(unsigned char timerNo);
    
    void setTimer10ms(volatile TIMER_TYPE* timer, unsigned int value); //value * 10 ms delayTimer
    void disableTimer10ms(volatile TIMER_TYPE* timer);
    inline void timer10msProcess(volatile TIMER_TYPE* timer);
    bool isTimer10msEnable1(volatile TIMER_TYPE* timer);
    bool isTimer10msTimeoutOccured(volatile TIMER_TYPE* timer);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
