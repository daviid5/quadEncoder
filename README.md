# quadEncoder
Encoding quadrature Encoder

developed for an TI TM4C micocontroller

should be useable with little changed with every other microcontroller

### setup
```C
//ENCODER
#define ENCODER_FL_PORT_A     GPIO_PORTD_BASE
#define ENCODER_FL_PORT_B     GPIO_PORTD_BASE
#define ENCODER_FL_A          GPIO_PIN_2
#define ENCODER_FL_B          GPIO_PIN_3

EncoderStatus_t               EncoderStatus[4];

setupEncoderHardware(&EncoderStatus[0], ENCODER_VEHICLE_COUNT_DOWN,   ENCODER_FL_PORT_A, ENCODER_FL_PORT_B, ENCODER_FL_A, ENCODER_FL_B, &ECU_Internal.wheelFL_c);
```

```&ECU_Internal.wheelFL_c``` is an pointer to an ```int32_t``` variable where the counts of the encoder are stored


### readout
```C
// has to be called to readout the encoder status
// has to be called with an adequate sampling frequency, regarding the maximum encoder 'speed'
// for example from an timer ISR
decodeEncoder_FromISR(&EncoderStatus[0]);
```

To readout the counts since the last readout, just use the value in ```ECU_Internal.wheelFL_c```.
After each readout ```ECU_Internal.wheelFL_c``` should be set to zero
