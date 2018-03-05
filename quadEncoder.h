/*
 * quadEncoder.h
 *
 *  Created on: 30.03.2017
 *  Author: david s
 */

#ifndef LIB_QUADENCODER_H_
#define LIB_QUADENCODER_H_


#define DIRECTION_CW            0
#define DIRECTION_CCW           1

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint32_t EncoderPort_A;
    uint32_t EncoderPort_B;
    uint8_t Encoder_A_Pin;
    uint8_t Encoder_B_Pin;
    uint8_t Direction;

    int32_t newVal;
    int32_t diffVal;
    int32_t *EncoderCounts;
} EncoderStatus_t;


#define ENCODER_VEHICLE_COUNT_UP            0
#define ENCODER_VEHICLE_COUNT_DOWN          1

#define ENCODER_SETUP_HARDWARE(Port_A, Port_B, A, B)    {   GPIOPinTypeGPIOInput(Port_A, A );   \
                                                            GPIOPinTypeGPIOInput(Port_B, B );   }


#define ENCODER_SETUP_HARDWARE_PULLUP_EN(Port_A, Port_B, A, B)   {     GPIOPinTypeGPIOInput(Port_A, A); \
                                                                        GPIOPinTypeGPIOInput(Port_B, B); \
                                                                        GPIOPadConfigSet(Port_A, A, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); \
                                                                        GPIOPadConfigSet(Port_B, B, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); }




void setupEncoderHardware(EncoderStatus_t *EncoderStatus, uint8_t Direction, uint32_t Port_A, uint32_t Port_B, uint32_t A, uint32_t B, int32_t *EncoderCounts);      // Initialize Pins for Encoder
void decodeEncoder_FromISR(EncoderStatus_t *EncoderStatus);






#endif /* LIB_QUADENCODER_H_ */
