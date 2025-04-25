// File: src/bsw/rte/rte_signal_routing.c

#include "Rte_ApplicationSwc1.h" // Assuming an Application SWC interface
#include "Rte_ApplicationSwc2.h" // Assuming another Application SWC interface
#include "Com.h"                 // AUTOSAR Communication Stack Interface

// Static buffer to hold the received CL15_01 message
static PduInfoType CL15_01_RxBuffer;
static boolean CL15_01_received = FALSE;

// Callback function to be called when the CL15_01 message is received
void Com_RxIndication_CL15_01(PduIdType RxPduId, const PduInfoType* PduInfoPtr) {
  if (PduInfoPtr != NULL && PduInfoPtr->SduDataPtr != NULL && PduInfoPtr->SduLength > 0) {
    // Copy the received PDU data to the internal buffer
    CL15_01_RxBuffer.SduDataPtr = PduInfoPtr->SduDataPtr;
    CL15_01_RxBuffer.SduLength = PduInfoPtr->SduLength;
    CL15_01_received = TRUE;
    // Potentially trigger a task or event to process the signal
  } else {
    // Handle error: Received PDU is invalid
    // Log error or trigger error handling mechanism
  }
}

// Function to extract the CL15ON signal and provide it to Application SWCs
Std_ReturnType Rte_Read_CL15_01_CL15ON(boolean* data) {
  if (CL15_01_received) {
    // Assuming CL15ON is the first bit in the received message
    // This is a simplified example; the actual bit position and data type
    // would depend on the specific communication matrix and signal definition.
    uint8_t byte = CL15_01_RxBuffer.SduDataPtr[0];
    *data = (byte & 0x01) ? TRUE : FALSE;
    return RTE_E_OK;
  } else {
    // Handle case where the signal has not yet been received
    return RTE_E_NO_DATA;
  }
}

// Example of how Application SWCs might access the signal
void ApplicationSwc1_Runnable() {
  boolean cl15on_value;
  if (Rte_Read_CL15_01_CL15ON(&cl15on_value) == RTE_E_OK) {
    // Use the cl15on_value in Application SWC 1 logic
    if (cl15on_value) {
      // ... perform action when CL15 is ON ...
    } else {
      // ... perform action when CL15 is OFF ...
    }
  } else {
    // Handle the case where the signal is not yet available
  }
}

void ApplicationSwc2_Runnable() {
  boolean cl15on_value;
  if (Rte_Read_CL15_01_CL15ON(&cl15on_value) == RTE_E_OK) {
    // Use the cl15on_value in Application SWC 2 logic
    // ...
  }
}

//end
