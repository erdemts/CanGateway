
#ifndef _FIFOBUFFER_H    /* Guard against multiple inclusion */
#define _FIFOBUFFER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */
#define BUFFER_SIZE                                     200



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef struct {
        unsigned char buffer[BUFFER_SIZE];
        unsigned char R;
        unsigned char W;
        signed char count;

    } BUFFER_TYPE;




    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

void addDataToBuffer(volatile BUFFER_TYPE* targetBuffer, unsigned char data, unsigned char bufferSize);
unsigned char getDataFromBuffer(volatile BUFFER_TYPE* sourceBuffer, unsigned char bufferSize);
void clearDataBuffer(volatile BUFFER_TYPE* targetBuffer, unsigned char bufferSize);
bool addBufferToBuffer(volatile BUFFER_TYPE* sourceBuffer, volatile BUFFER_TYPE* targetBuffer, unsigned char bufferSize) ;

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
