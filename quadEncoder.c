/*
 * quadEncoder.c
 *
 *  Created on: 30.03.2017
 *  Author: david s
 */

#include "quadEncoder.h"
#include "driverlib/gpio.h"


//------------------------------------------
// Initialize Pins for Encoder
//------------------------------------------
void setupEncoderHardware(EncoderStatus_t *EncoderStatus, uint8_t Direction, uint32_t Port_A, uint32_t Port_B, uint32_t A, uint32_t B, int32_t *EncoderCounts)
{
    EncoderStatus->Encoder_A_Pin = A;
    EncoderStatus->Encoder_B_Pin = B;
    EncoderStatus->EncoderPort_A = Port_A;
    EncoderStatus->EncoderPort_B = Port_B;
    EncoderStatus->EncoderCounts = EncoderCounts;
    EncoderStatus->Direction = Direction;

    ENCODER_SETUP_HARDWARE(Port_A, Port_B, A, B);
}

//------------------------------------------
// Interrupt handler for the timer
//------------------------------------------
void decodeEncoder_FromISR(EncoderStatus_t *EncoderStatus)
{
    int32_t new;

    new = 0;

    if( (GPIOPinRead(EncoderStatus->EncoderPort_A, EncoderStatus->Encoder_A_Pin) & EncoderStatus->Encoder_A_Pin) ) new = 3;
    if( (GPIOPinRead(EncoderStatus->EncoderPort_B, EncoderStatus->Encoder_B_Pin) & EncoderStatus->Encoder_B_Pin) ) new ^= 1;	// convert gray to binary

    EncoderStatus->diffVal = EncoderStatus->newVal - new;             					// difference last - new
    if( EncoderStatus->diffVal & 1 ) {                                       			// bit 0 = value (1)

        EncoderStatus->newVal = new;                                                 	// store new as next last

        if( EncoderStatus->Direction == ENCODER_VEHICLE_COUNT_UP)
        {
            *EncoderStatus->EncoderCounts += (EncoderStatus->diffVal & 2) - 1;    		// bit 1 = direction (+/-)
        }
        else
        {
            *EncoderStatus->EncoderCounts -= (EncoderStatus->diffVal & 2) - 1;     		// bit 1 = direction (+/-)
        }
    }
}


