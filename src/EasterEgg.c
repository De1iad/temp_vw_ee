/*============================================================================*/
/*                        VW Easter Egg Project                               */
/*============================================================================*/

#include "../inc/EasterEgg.h"

extern inputsEE EasterEggLightsEE;
uint8_t EasterEggEnabled;
uint64_t EasterEggSequence;

void EasterEgg_Cyclic_10ms(void)
{

    static uint8_t RandomTimer1 = 0; //This is just a timer I'll use randomly when I need spacing between the cases;

    switch (EasterEggSequence)
    {
        case 0:
            EasterEggLightsEE.ParkingLightLeft = 1;
            EasterEggLightsEE.ParkingLightLeftPWM +=3;
            if (EasterEggLightsEE.ParkingLightLeftPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 1:
            EasterEggLightsEE.ParkingLightRight = 1;
            EasterEggLightsEE.ParkingLightRightPWM +=3;
            if (EasterEggLightsEE.ParkingLightRightPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 2:
            EasterEggLightsEE.BlinkLightLeft = 1;
            EasterEggLightsEE.BlinkLightLeftPWM +=3;
            if (EasterEggLightsEE.BlinkLightLeftPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 3:
            EasterEggLightsEE.BlinkLightRight = 1;
            EasterEggLightsEE.BlinkLightRightPWM +=3;
            if (EasterEggLightsEE.BlinkLightRightPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 4:
            EasterEggLightsEE.BrakeLights = 1;
            EasterEggLightsEE.BrakeLightsPWM +=3;
            if (EasterEggLightsEE.BrakeLightsPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 5:
            EasterEggLightsEE.ReverseLights = 1;
            EasterEggLightsEE.ReverseLightsPWM +=3;
            if (EasterEggLightsEE.ReverseLightsPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 6:
            EasterEggLightsEE.FogLights = 1;
            EasterEggLightsEE.FogLightsPWM +=3;
            if (EasterEggLightsEE.FogLightsPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 7:
            EasterEggLightsEE.LicensePlateLight1 = 1;
            EasterEggLightsEE.LicensePlateLight1PWM +=3;
            if (EasterEggLightsEE.LicensePlateLight1PWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 8:
            EasterEggLightsEE.LicensePlateLight2 = 1;
            EasterEggLightsEE.LicensePlateLight2PWM +=3;
            if (EasterEggLightsEE.LicensePlateLight2PWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 9:
            EasterEggLightsEE.LicensePlateLight3 = 1;
            EasterEggLightsEE.LicensePlateLight3PWM +=3;
            if (EasterEggLightsEE.LicensePlateLight3PWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 10:
            EasterEggLightsEE.LicensePlateLight4 = 1;
            EasterEggLightsEE.LicensePlateLight4PWM +=3;
            if (EasterEggLightsEE.LicensePlateLight4PWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 11:
            EasterEggLightsEE.LicensePlateLight5 = 1;
            EasterEggLightsEE.LicensePlateLight5PWM +=3;
            if (EasterEggLightsEE.LicensePlateLight5PWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 12:
            EasterEggLightsEE.AmbientLights = 1;
            EasterEggLightsEE.AmbientLightsPWM +=3;
            if (EasterEggLightsEE.AmbientLightsPWM > 900)
            {
            EasterEggSequence++;
            break;
            }
            break;
        case 13:
            EasterEggLightsEE.ParkingLightLeft = 1;
            EasterEggLightsEE.ParkingLightLeftPWM -=3;
            EasterEggLightsEE.ParkingLightRight = 1;
            EasterEggLightsEE.ParkingLightRightPWM -=3;
            EasterEggLightsEE.BlinkLightLeft = 1;
            EasterEggLightsEE.BlinkLightLeftPWM -=3;
            EasterEggLightsEE.BlinkLightRight = 1;
            EasterEggLightsEE.BlinkLightRightPWM -=3;
            EasterEggLightsEE.BrakeLights = 1;
            EasterEggLightsEE.BrakeLightsPWM -=3;
            EasterEggLightsEE.ReverseLights = 1;
            EasterEggLightsEE.ReverseLightsPWM -=3;
            EasterEggLightsEE.FogLights = 1;
            EasterEggLightsEE.FogLightsPWM -=3;
            EasterEggLightsEE.LicensePlateLight1 = 1;
            EasterEggLightsEE.LicensePlateLight1PWM -=3;
            EasterEggLightsEE.LicensePlateLight2 = 1;
            EasterEggLightsEE.LicensePlateLight2PWM -=3;
            EasterEggLightsEE.LicensePlateLight3 = 1;
            EasterEggLightsEE.LicensePlateLight3PWM -=3;
            EasterEggLightsEE.LicensePlateLight4 = 1;
            EasterEggLightsEE.LicensePlateLight4PWM -=3;
            EasterEggLightsEE.LicensePlateLight5 = 1;
            EasterEggLightsEE.LicensePlateLight5PWM -=3;
            EasterEggLightsEE.AmbientLights = 1;
            EasterEggLightsEE.AmbientLightsPWM -=3;
            if (EasterEggLightsEE.ParkingLightLeftPWM < 10)
            {
            EasterEggLightsEE.ParkingLightLeft = 0;
            EasterEggLightsEE.ParkingLightLeftPWM = 0;

            EasterEggLightsEE.ParkingLightRight = 0;
            EasterEggLightsEE.ParkingLightRightPWM = 0;

            EasterEggLightsEE.BlinkLightLeft = 0;
            EasterEggLightsEE.BlinkLightLeftPWM = 0;

            EasterEggLightsEE.BlinkLightRight = 0;
            EasterEggLightsEE.BlinkLightRightPWM = 0;

            EasterEggLightsEE.BrakeLights = 0;
            EasterEggLightsEE.BrakeLightsPWM = 0;

            EasterEggLightsEE.ReverseLights = 0;
            EasterEggLightsEE.ReverseLightsPWM = 0;

            EasterEggLightsEE.FogLights = 0;
            EasterEggLightsEE.FogLightsPWM = 0;

            EasterEggLightsEE.LicensePlateLight1 = 0;
            EasterEggLightsEE.LicensePlateLight1PWM = 0;

            EasterEggLightsEE.LicensePlateLight2 = 0;
            EasterEggLightsEE.LicensePlateLight2PWM = 0;

            EasterEggLightsEE.LicensePlateLight3 = 0;
            EasterEggLightsEE.LicensePlateLight3PWM = 0;

            EasterEggLightsEE.LicensePlateLight4 = 0;
            EasterEggLightsEE.LicensePlateLight4PWM = 0;

            EasterEggLightsEE.LicensePlateLight5 = 0;
            EasterEggLightsEE.LicensePlateLight5PWM = 0;

            EasterEggLightsEE.AmbientLights = 0;
            EasterEggLightsEE.AmbientLightsPWM = 0;

            EasterEggSequence++;
            break;
            }
            break;
        case 14:
                RandomTimer1++;
            if (RandomTimer1 > 200){
                RandomTimer1 = 0;
                EasterEggSequence = 0;
                break;
            }
            break;
    }
}



/* Notice: the file ends with a blank new line to avoid compiler warnings */
