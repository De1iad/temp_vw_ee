
/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include "../inc/car.h"
#include "../inc/WavLib.h"
#include "../inc/TimeLib.h"
#include "../inc/EasterEgg.h"
#ifdef DEBUG
# include "../inc/PlaySong.h"
#endif
# define WAVFILE ("./encore.wav")

inputsEE EasterEggLightsEE;

/* Global variable for the playback sampling timer */
volatile sig_atomic_t alarm_snooze = 1;

/* function prototype for the timer SIGALARM handler */
void	SigAlarmHandler(int sig);

double **get_averages(tstSampleBufferDouble *sample_freqs)
{
	double **averages = calloc(sizeof(double *), 2);
	int j;

	averages[0] = calloc(sizeof(double), 15);
	averages[1] = calloc(sizeof(double), 15);
	j = 0;
	for (int i = 0; i < 2280; i++)
	{
		//mode
		if (sample_freqs->dStereoL[i] > averages[0][j]) // with 15 samples if max sample size of 2280 and pools of 152
			averages[0][j] = sample_freqs->dStereoL[i];
		if (sample_freqs->dStereoR[i] > averages[1][j])
			averages[1][j] = sample_freqs->dStereoR[i];
		if (i == 152 * (j + 1))
			j++;
		// //average
		// averages[0][j] += sample_freqs->dStereoL[i];
		// averages[1][j] += sample_freqs->dStereoR[i];
		// if (i == 1575 * (j + 1))
		// {
		// 	averages[0][j] /= 1575;
		// 	averages[1][j] /= 1575; //570 pools if 7980 total, 1575 if 22050 total. Assuming 14 samples.
		// 	j++;
		// }
	}
	return (averages);
}

void	set_light_variables(double **averages)
{
	for (int i = 0; i < 14; i++)
		printf("freq range %d-%d: %f\n", i * 152, (i + 1) * 152, averages[0][i]);
	// headlights
	if (averages[0][0] > 2000 && averages[1][0] > 2000)
	{
		EasterEggLightsEE.FrontLights = 1;
	}
	else
		EasterEggLightsEE.FrontLights = 0;

	// fog lights
	if (averages[0][1] > 400)
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (averages[0][1] / 400);
	}
	else if (averages[1][1] > 400)
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (averages[1][1] / 400);
	}
	else if (averages[0][1] < 350 && averages[1][1] < 350)
		EasterEggLightsEE.FogLights = 0;

	// brake lights
	if (averages[0][0] > 2000)
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (averages[0][0] / 2500);
	}
	else if (averages[1][0] > 2000)
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (averages[1][0] / 2500);
	}
	else if (averages[0][0] < 1700 && averages[1][0] < 1700)
		EasterEggLightsEE.BrakeLights = 0;

	// reverse lights
	if (averages[0][1] > 1)
	{
		EasterEggLightsEE.ReverseLights = 1;
		EasterEggLightsEE.ReverseLightsPWM = 1000 * (averages[0][1] / 500);
	}
	else if (averages[1][1] > 1)
	{
		EasterEggLightsEE.ReverseLights = 1;
		EasterEggLightsEE.ReverseLightsPWM = 1000 * (averages[1][1] / 500);
	}
	else
		EasterEggLightsEE.ReverseLights = 0;
	
	// blink lights
	if (averages[0][8] > 100)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (averages[0][8] / 100);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (averages[0][8] / 100);
	}
	else if (averages[1][8] > 100)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (averages[1][8] / 100);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (averages[1][8] / 100);
	}
	else
	{
		EasterEggLightsEE.BlinkLightLeft = 0;
		EasterEggLightsEE.BlinkLightRight = 0;
	}

	// parking lights
	if (averages[0][3] > 200)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (averages[0][3] / 200);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (averages[0][3] / 200);
	}
	else if (averages[1][3] > 200)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (averages[1][3] / 200);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (averages[1][3] / 200);
	}
	else
		EasterEggLightsEE.ParkingLightRight = 0;
	free(averages[0]);
	free(averages[1]);
	free(averages);
}

int	transform_loop(t_car *car)
{
	/* On timer alarm */            
	if (alarm_snooze == 1)
	{   
		alarm_snooze = 0;
		//printf("\n-----\n");
		// u32SigCounter++;
		// how many lights to turn on - number of samples
		// - load new set of samples to the buffer (hexbuffer)
		WAVLIB_LoadSampleFromStreamToBuffer(car->wav.wavStream,
														&car->wav.wavReadConfig, 
														&car->wav.wavSampleBufferHex,
														wavSpec);
		// if (wavReturnCode != WAVLIB_SUCCESS)
		// {
		// 	//printf("ERROR! >>> LoadSampleFromStreamToBuffer %d\n", wavReturnCode);
		// }
		// - update the number of samples remaining

		// - convert sample data to float
		WAVLIB_ConvertSampleBufferToFloatByChannel(
													&car->wav.wavSampleBufferHex,
													&car->wav.wavSampleBufferFloatInp,
													&car->wav.wavReadConfig);
		// if (wavReturnCode != WAVLIB_SUCCESS)
		// {
		// 	//printf("ERROR! >>> ConvertSampleBufferToFloatByChannel %d\n", wavReturnCode);
		// }


		// - perform transform - freq 
		WAVLIB_TransformFloatSample(
													&car->wav.wavSampleBufferFloatInp,
													&car->wav.wavSampleBufferFreq,
													&car->wav.wavReadConfig);

		// show spectrum on terminal
		// system("clear");
		// FFTLIB_ShowFreqSpectrum(wavSampleBufferFreq.dStereoL, 16);
		// FFTLIB_ShowFreqSpectrum(wavSampleBufferFreq.dStereoR, 16);
		// int enablelightbuff;
		// for (int i = 0; i < 8; i++)
		// {

		// }
		set_light_variables(get_averages(&car->wav.wavSampleBufferFreq));
		// if (wavSampleBufferFreq.dStereoL[0] > 0)
		// 	EasterEggLightsEE.FrontLightLeft = 1;
		// EasterEggLightsEE.FrontLightRight = wavSampleBufferFreq.dStereoR[0];
		// Adjust sample pos to next based on sampling rate
		car->wav.wavReadConfig.u32FileSeekPosL -= (car->wav.wavReadConfig.u32Offset * (44100 - 2205));
		car->wav.wavReadConfig.u32FileSeekPosR -= (car->wav.wavReadConfig.u32Offset * (44100 - 2205));

		// - map transform result to lights
		// - map the brightness to light using sample data (float) - pwm 
		// - hook the data to gui car to light up light images on car
	}
	return (0);
	
	// if (u32SigCounter == (21 * 206))
	// {
	//     break ;
	// }
}

int transform(t_car *car)
{
    /* Variable declaration */
    tenWavLibReturnCode     wavReturnCode;
    pthread_t               pxThreadPlaySong;

    /* Variable Initialisation */
    wavReturnCode = WAVLIB_ERR_FILE_OPEN;
    car->wav.wavStream = NULL;
    memset((void *)&car->wav.wavSampleBufferHex, 0, (sizeof(tstSampleBufferHex)));
    memset((void *)&car->wav.wavSampleBufferFloatInp, 0, (sizeof(tstSampleBufferFloat)));
    memset((void *)&car->wav.wavSampleBufferFreq, 0, (sizeof(tstSampleBufferHex)));
    memset((void *)&car->wav.wavReadConfig, 0, (sizeof(tstWavReadConfig)));

    /* Load wav file */
    car->wav.wavStream = fopen(WAVFILE, "rb");
    if (car->wav.wavStream == NULL)
    {
        printf("Error open file, %d\n", wavReturnCode);
        return (wavReturnCode);
    }

    /* Load wav file audio specification data */
    wavReturnCode = WAVLIB_LoadSpecData(car->wav.wavStream, wavSpec);
    if (wavReturnCode != WAVLIB_SUCCESS)
    {
        printf("Error load spec data, %d\n", wavReturnCode);
        fclose(car->wav.wavStream);
        return (wavReturnCode);
    }

    /* Display wav file audio specification data */
    WAVLIB_ShowWavSpec(wavSpec);

    /* Initialise the configuration for reading samples from wav file */
    WAVLIB_ReadConfigInit(&car->wav.wavReadConfig, wavSpec);
    printf("seekposL: %d, seekposR: %d, idx: %d, offset: %d, byteCnt: %d\n",
                                        car->wav.wavReadConfig.u32FileSeekPosL,
                                        car->wav.wavReadConfig.u32FileSeekPosR,
                                        car->wav.wavReadConfig.u32Idx,
                                        car->wav.wavReadConfig.u32Offset,
                                        car->wav.wavReadConfig.u8ByteCnt);




    /* Setup alarm signal handler */
    struct sigaction sa;    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_handler = SigAlarmHandler;
    if (sigaction (SIGALRM, &sa, NULL) == -1)
    {
        printf("Error Sigaction!");
        return (0);
    }

    /* create timer */
    uint32_t u32SigCounter = 0; 
    timer_t xTimerId;
    struct sigevent sigEvent;
    sigEvent.sigev_notify = SIGEV_SIGNAL;
    sigEvent.sigev_signo = SIGALRM;
    sigEvent.sigev_value.sival_ptr = &xTimerId;
    if (TIME_CreateTimer(&xTimerId, &sigEvent) == -1)
    {
        printf("Error! timer_create");
        return (-1);
    }
    printf("time id: %p\n", xTimerId);
    

    /* set a timer - 10msec - 192kbit/sec */
   time_t xPeriodNs = 1000000000 /21;
   //if (TIME_SetTimer(&xTimerId, xPeriod, TIME_TIMER_PERIODIC) == -1)
   int flags;
    struct itimerspec timespec_ns = {{0, 0}, {0, 0}};
    flags = 0;      /* the value.it_value is interpreted relative to the clock
                        value at the time of the call to timer_settime()
                    */
    
    
     /* arm the interval timer */
    timespec_ns.it_interval.tv_sec = (xPeriodNs / NSEC_PER_SEC) ;
    timespec_ns.it_interval.tv_nsec = ( xPeriodNs % NSEC_PER_SEC) ;
    timespec_ns.it_value.tv_sec = (xPeriodNs / NSEC_PER_SEC);
    timespec_ns.it_value.tv_nsec = (xPeriodNs % NSEC_PER_SEC);
   if (timer_settime(xTimerId, flags, &timespec_ns, NULL) == -1)
   {
        printf("Error! timer_settime\n");
        return (-1);
   }

   /* store the start time */
    printf("start time: %lf\n", TIME_GetTime(unit_sec));
    struct timespec stTimeStart = {0, 0};
    clock_gettime(CLOCK_MONOTONIC_RAW, &stTimeStart);

    /* Play sound if DEBUG flag is define */
    #ifdef DEBUG
        if (pthread_create(&pxThreadPlaySong, NULL, playSong, "DEBUG") != 0)
        {
            printf("Error! pthread_create.\n");
            return (PLAYSONG_THREAD_CREATE_ERR);
        }
    #endif

	return (0);

    // #ifdef DEBUG
    //     if (pthread_join(pxThreadPlaySong, NULL) != 0)
    //     {
    //         printf("Error! pthread_join.\n");
    //         return (PLAYSONG_THREAD_JOIN_ERR);
    //     }
    // #endif

    // // - disable timer if the number of sample to zero
    // TIME_DisableTimer(&xTimerId);
    // printf("run time: %lf\n", TIME_GetRuntime(&stTimeStart, unit_sec));

    /* show runtime of program */
    /*
    printf("start time: %lf\n", TIME_GetTime(unit_sec));
    for (int x=0; x<WAVLIB_STEREO_SAMPLE_MAX; x++)
    {
        printf("sample: %d -> L[%5d], R[%5d]\n", x+1, wavSampleBufferHex.i16StereoL[x],
                                                    wavSampleBufferHex.i16StereoR[x]);
    }

    for (int x=0; x<WAVLIB_STEREO_SAMPLE_MAX; x++)
    {
        printf("sample: %d -> L[%10f], R[%10f]\n", x+1, wavSampleBufferFloatInp.f32StereoL[x],
                                                      wavSampleBufferFloatInp.f32StereoR[x]);
    }
    */

    // testing
    // adding one thread to play the sound while lighting the gui car
    // fclose(wavStream);
    // exit(0);
    // return (0);
}



void	SigAlarmHandler(int sig)
{
	if (sig == SIGALRM)
    {
        alarm_snooze = 1;
	}
}
