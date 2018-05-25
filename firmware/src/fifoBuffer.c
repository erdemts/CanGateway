
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdbool.h>
#include "fifoBuffer.h"



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

void addDataToBuffer(volatile BUFFER_TYPE* targetBuffer, unsigned char data, unsigned char bufferSize) {
	
    targetBuffer->buffer[targetBuffer->W] = data;
    
    ++targetBuffer->W;
    if (targetBuffer->W == bufferSize) {
        targetBuffer->W = 0;
    }
    if (targetBuffer->W == targetBuffer->R) {
        ++targetBuffer->R;
    }
    if (targetBuffer->R == bufferSize) {
        targetBuffer->R = 0;
    }
    ++targetBuffer->count;
    if (targetBuffer->count > bufferSize) {
        targetBuffer->count = bufferSize;
    }
}

unsigned char getDataFromBuffer(volatile BUFFER_TYPE* sourceBuffer, unsigned char bufferSize) {
    unsigned char value;

    value = sourceBuffer->buffer[sourceBuffer->R];
    ++sourceBuffer->R;
    if (sourceBuffer->R == bufferSize) {
        sourceBuffer->R = 0;
    }
    --sourceBuffer->count;
    if (sourceBuffer->count < 0) {
        sourceBuffer->count = 0;
    }
    return value;
}

void clearDataBuffer(volatile BUFFER_TYPE* targetBuffer, unsigned char bufferSize) {
   
    unsigned char count = 0; 
    targetBuffer->W = 0;
    targetBuffer->R = 0;
    targetBuffer->count = 0;
    
    while(count < bufferSize)
    {
    	targetBuffer->buffer[count] = 0;
    	++count;
	}
}

//bool copyBufferToBuffer(volatile BUFFER_TYPE* sourceBuffer, volatile BUFFER_TYPE* targetBuffer, unsigned char bufferSize) {
//
//    if (sourceBuffer->W != sourceBuffer->R) {
//        while (sourceBuffer->W != sourceBuffer->R) {
//            addDataToBuffer(targetBuffer, getDataFromBuffer(sourceBuffer, bufferSize), bufferSize);
//        }
//        return (1);
//    } else {
//        return (0);
//    }
//}

bool addBufferToBuffer(volatile BUFFER_TYPE* sourceBuffer, volatile BUFFER_TYPE* targetBuffer, unsigned char bufferSize) {

    if (sourceBuffer->W != sourceBuffer->R) {
        while (sourceBuffer->W != sourceBuffer->R) {
            addDataToBuffer(targetBuffer, getDataFromBuffer(sourceBuffer, bufferSize), bufferSize);
        }
        return (1);
    } else {
        return (0);
    }
}
/* *****************************************************************************
 End of File
 */
