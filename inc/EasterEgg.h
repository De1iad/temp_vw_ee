
#ifndef EASTEREGG
#define EASTEREGG

#include <stdint.h>
//#include "Platform_Types.h"
//#include "ComStack_Types.h"

extern void EasterEgg_Cyclic_10ms(void);

extern uint8_t EasterEggEnabled; //This variable will either enable or disable the EasterEggLights. Currently only set through the debugger, I'll decide later on what will trigger its activation from the car itself (probably a combination of button presses).
extern uint64_t EasterEggSequence;

typedef struct
{
       uint8_t FrontLights;
       uint8_t ParkingLightLeft; //The normal variables will either enable or disable the selected light with the intensity set through the PWM value
       uint16_t ParkingLightLeftPWM; //The PWM values stand for Pulse Width Modulation and can be set to any value from 0 to 1000, representing the intensity of the light
       uint8_t ParkingLightRight;
       uint16_t ParkingLightRightPWM;
       uint8_t BlinkLightLeft;
       uint16_t BlinkLightLeftPWM;
       uint8_t BlinkLightRight;
       uint16_t BlinkLightRightPWM;
       uint8_t BrakeLights;
       uint16_t BrakeLightsPWM;
       uint8_t ReverseLights;
       uint16_t ReverseLightsPWM;
       uint8_t AmbientLights;
       uint16_t AmbientLightsPWM;
       uint8_t FogLights;
       uint16_t FogLightsPWM;
       uint8_t LicensePlateLight1;
       uint16_t LicensePlateLight1PWM;
       uint8_t LicensePlateLight2;
       uint16_t LicensePlateLight2PWM;
       uint8_t LicensePlateLight3;
       uint16_t LicensePlateLight3PWM;
       uint8_t LicensePlateLight4;
       uint16_t LicensePlateLight4PWM;
       uint8_t LicensePlateLight5;
       uint16_t LicensePlateLight5PWM;

}inputsEE;






#endif // end of EASTEREGG application
