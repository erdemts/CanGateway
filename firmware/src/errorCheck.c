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
#include "driver/can/drv_can_static.h"
#include "data_types.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

extern SYSTEM_DATA_TYPE sysData;




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


void checkCanbusErrors(void) {
    unsigned int transmitErrorCount = 0;
    unsigned int receiveErrorCount = 0;
    CAN_ERROR_STATE canErrorState;

    transmitErrorCount = PLIB_CAN_TransmitErrorCountGet(CAN_ID_1);
    if (transmitErrorCount > 200) {
        // This error count is high.
        // Do some diagnostics.
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_TRANSMIT_ERROR_COUNT_HIGH_FLAG = 1;
    }
    receiveErrorCount = PLIB_CAN_ReceiveErrorCountGet(CAN_ID_1);
    if (receiveErrorCount > 200) {
        // This error count is high.
        // Do some diagnostics.
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_RECEIVE_ERROR_COUNT_HIGH_FLAG = 1;
    }
    canErrorState = PLIB_CAN_ErrorStateGet(CAN_ID_1);
    if ((canErrorState & CAN_TX_RX_WARNING_STATE) != 0) {
        // CAN_ID_1 is in either  Transmit or Receive warning state.
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_TX_RX_WARNING_STATE_FLAG = 1;
    }
    if ((canErrorState & CAN_RX_WARNING_STATE) != 0) {
        // CAN_ID_1 is in either  Transmit or Receive warning state.
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_RX_WARNING_STATE_FLAG = 1;
    }
    if ((canErrorState & CAN_TX_WARNING_STATE) != 0) {
        // CAN_ID_1 is in either  Transmit or Receive warning state.
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_TX_WARNING_STATE_FLAG = 1;
    }
    if ((canErrorState & CAN_RX_BUS_PASSIVE_STATE) != 0) {
        // CAN_ID_1 is in either  Transmit or Receive warning state.
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_RX_BUS_PASSIVE_STATE_FLAG = 1;
    }
    if ((canErrorState & CAN_TX_BUS_PASSIVE_STATE) != 0) {
        // CAN_ID_1 is in either  Transmit or Receive warning state.
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_TX_BUS_PASSIVE_STATE_FLAG = 1;
    }
    if ((canErrorState & CAN_TX_BUS_OFF_STATE) != 0) {
        // CAN_ID_1 is in either  Transmit or Receive warning state.
        DRV_CAN0_Deinitialize();
        sysData.CAN_ERRORS.can_1_Errors = 0;
        DRV_CAN0_Initialize();
        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_TX_BUS_OFF_STATE_FLAG = 1;
    }
//    if (sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_BUS_ERROR_EVENT_FLAG) {
//        DRV_CAN0_Deinitialize();
//        sysData.CAN_ERRORS.can_1_Errors = 0;
//        DRV_CAN0_Initialize();
//        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_BUS_ERROR_EVENT_FLAG = 0;
//    }
//    if (sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_SYSTEM_ERROR_EVENT_FLAG) {
//        DRV_CAN0_Deinitialize();
//        sysData.CAN_ERRORS.can_1_Errors = 0;
//        DRV_CAN0_Initialize();
//        sysData.CAN_ERRORS.CAN_1_ERROR_FLAGS.CAN_SYSTEM_ERROR_EVENT_FLAG = 0;
//    }
}

/* *****************************************************************************
 End of File
 */

