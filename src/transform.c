
/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include "../inc/car.h"
#include "../inc/WavLib.h"
//#include "../inc/TimeLib.h"
#include "../inc/EasterEgg.h"
#ifdef DEBUG
# include "../inc/PlaySong.h"
#endif
# define WAVFILE ("./encore.wav")

inputsEE EasterEggLightsEE;

double g_max_amp[22050];

void	auto_assign_freqs(t_light_freqs *freqs)
{
	double	magnitude = 0;
	for (int i = 80; i < 100; i++)
	{
		if (g_max_amp[i] > magnitude)
		{
			freqs->Front_Lights = i;
			magnitude = g_max_amp[i];
			//break ;
		}
	}
	printf("front lights: %dhz\n", freqs->Front_Lights);
	magnitude = 0;
	for (int i = 10; i < 50; i++)
	{
		if (g_max_amp[i] > magnitude)
		{
			freqs->Fog_Lights = i;
			magnitude = g_max_amp[i];
		}
	}
	printf("fog lights: %dhz\n", freqs->Fog_Lights);
	magnitude = 0;
	for (int i = 400; i < 700; i++)
	{
		if (g_max_amp[i] > magnitude)
		{
			freqs->Blink_Lights = i;
			magnitude = g_max_amp[i];
		}
	}
	printf("blink lights: %dhz\n", freqs->Blink_Lights);
	magnitude = 0;
	for (int i = 40; i < 50; i++)
	{
		if (g_max_amp[i] > magnitude && freqs->Fog_Lights != i)
		{
			freqs->Ambient_Lights = i;
			magnitude = g_max_amp[i];
		}
	}
	printf("ambient lights: %dhz\n", freqs->Ambient_Lights);
	magnitude = 0;
	for (int i = 880; i < 900; i++)
	{
		if (g_max_amp[i] > magnitude)
		{
			freqs->License_Light1 = i;
			freqs->License_Light2 = i;
			magnitude = g_max_amp[i];
		}
	}
	printf("license lights 1-2: %dhz\n", freqs->License_Light1);
	magnitude = 0;
	for (int i = 2130; i < 2136; i++)
	{
		if (g_max_amp[i] > magnitude)
		{
			freqs->License_Light3 = i;
			freqs->License_Light4 = i;
			magnitude = g_max_amp[i];
		}
	}
	printf("license lights 3-4: %dhz\n", freqs->License_Light1);
}

void fetch_amp_range(t_car *car)
{
	int return_code = 0;
	
	memset(g_max_amp, 0, 22050 * sizeof(double));
    fseek(car->wav.wavStream, 45, SEEK_SET);
	//int total_samples = 0;
    while (return_code != WAVLIB_EOF) //total_samples < wavSpec[6].u32SpecData
	{
		return_code = WAVLIB_LoadSampleFromStreamToBuffer(car->wav.wavStream,
														&car->wav.wavReadConfig, 
														&car->wav.wavSampleBufferHex,
														wavSpec);

		// - convert sample data to float
		WAVLIB_ConvertSampleBufferToFloatByChannel(
													&car->wav.wavSampleBufferHex,
													&car->wav.wavSampleBufferFloatInp,
													&car->wav.wavReadConfig);


		// - perform transform - freq 
		WAVLIB_TransformFloatSample(
													&car->wav.wavSampleBufferFloatInp,
													&car->wav.wavSampleBufferFreq,
													&car->wav.wavReadConfig);
		for (int x=0; x < 22050; x++)
		{
		    if (car->wav.wavSampleBufferFreq.dStereoL[x] > g_max_amp[x])
		    {
		        g_max_amp[x] = car->wav.wavSampleBufferFreq.dStereoL[x];
		    }
		    if (car->wav.wavSampleBufferFreq.dStereoR[x] > g_max_amp[x])
		    {
		        g_max_amp[x] = car->wav.wavSampleBufferFreq.dStereoR[x];
		    }
		}
		car->wav.wavReadConfig.u32FileSeekPosL += (car->wav.wavReadConfig.u32Offset * 44100);
		car->wav.wavReadConfig.u32FileSeekPosR += (car->wav.wavReadConfig.u32Offset * 44100);
		//total_samples += 44100;
	}
	car->wav.wavReadConfig.u32FileSeekPosL = 45;
	car->wav.wavReadConfig.u32FileSeekPosR = 47;
	// for (int x=0; x < 150; x++)
		//printf("freq %d max: %f\n", x, g_max_amp[x]);
	printf("done\n");
	// exit(0);
}

double **get_averages(tstSampleBufferDouble *sample_freqs)
{
	double **averages = calloc(sizeof(double *), 2);
	int j;

	averages[0] = calloc(sizeof(double), 19);
	averages[1] = calloc(sizeof(double), 19);
	j = 0;
	for (int i = 0; i < 152; i++)
	{
		//max
		if (sample_freqs->dStereoL[i] > averages[0][j]) // with 15 samples if max sample size of 2280 and pools of 152
			averages[0][j] = sample_freqs->dStereoL[i]; // with 19 samples if max sample size of 152 and pools of 8
		if (sample_freqs->dStereoR[i] > averages[1][j])
			averages[1][j] = sample_freqs->dStereoR[i];
		if (i == 8 * (j + 1))
			j++;
		//mean
		// averages[0][j] += sample_freqs->dStereoL[i];
		// averages[1][j] += sample_freqs->dStereoR[i];
		// if (i == 152 * (j + 1))
		// {
		// 	averages[0][j] /= 152;
		// 	averages[1][j] /= 152; //570 pools if 7980 total, 1575 if 22050 total. Assuming 14 samples.
		// 	j++;
		// }
	}
	return (averages);
}

void	set_light_variables(tstSampleBufferDouble *sample_freqs, t_light_freqs *freqs)
{
	// double **averages = get_averages(sample_freqs);
	// for (int i = 0; i < 19; i++)
	// 	printf("freq range %d-%d: %f\n", i * 8, (i + 1) * 8, averages[0][i]);
	// free(averages);
	// headlights
	// printf("freq 150 value: %f\n", g_max_amp[150]);
	//printf("%f / 7 = %f, current freq L: %f, current freq R: %f\n", g_max_amp[93], g_max_amp[93] / 7, sample_freqs->dStereoL[93], sample_freqs->dStereoR[93]);
	printf("timestamp: %ld\n", get_time_in_ms());
	for (int i = 0; i < 22050; i++)
	{
		if ((sample_freqs->dStereoL[i] > g_max_amp[i] * 0.5 && sample_freqs->dStereoL[i] > 400) || (sample_freqs->dStereoR[i] > g_max_amp[i] * 0.5 && sample_freqs->dStereoR[i] > 400))
			printf("freq %d, left: %f, right: %f\n", i, sample_freqs->dStereoL[i], sample_freqs->dStereoR[i]);
	}
	//printf("%f\n", sample_freqs->dStereoL[freqs->Front_Lights]);
	if (sample_freqs->dStereoL[freqs->Front_Lights] > g_max_amp[freqs->Front_Lights] / 5 || sample_freqs->dStereoR[freqs->Front_Lights] > g_max_amp[freqs->Front_Lights] / 5) //old: sample_freqs->dStereoL[93] > g_max_amp[93] / 7 || sample_freqs->dStereoR[93] > g_max_amp[93] / 7
	{
		EasterEggLightsEE.FrontLights = 1;
	}
	else
		EasterEggLightsEE.FrontLights = 0;

	//fog lights
	if (sample_freqs->dStereoL[freqs->Fog_Lights] > g_max_amp[freqs->Fog_Lights] / 7) // old: sample_freqs->dStereoL[44] > g_max_amp[44] / 7
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (sample_freqs->dStereoL[freqs->Fog_Lights] / g_max_amp[freqs->Fog_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Fog_Lights] > g_max_amp[freqs->Fog_Lights] / 7)
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (sample_freqs->dStereoR[freqs->Fog_Lights] / g_max_amp[freqs->Fog_Lights]);
	}
	else
		EasterEggLightsEE.FogLights = 0;

	// parking lights
	if (sample_freqs->dStereoL[73] > g_max_amp[73] / 7)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (sample_freqs->dStereoL[73] / g_max_amp[73]);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (sample_freqs->dStereoL[73] / g_max_amp[73]);
	}
	else if (sample_freqs->dStereoR[73] > g_max_amp[73] / 7)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (sample_freqs->dStereoR[73] > g_max_amp[73]);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (sample_freqs->dStereoR[73] > g_max_amp[73]);
	}
	else
	{
		EasterEggLightsEE.ParkingLightLeft = 0;
		EasterEggLightsEE.ParkingLightRight = 0;
	}

	// blink lights
	if (sample_freqs->dStereoL[freqs->Blink_Lights] > g_max_amp[freqs->Blink_Lights] / 5) // old: sample_freqs->dStereoL[876] > g_max_amp[876] / 7
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoL[freqs->Blink_Lights] / g_max_amp[freqs->Blink_Lights]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoL[freqs->Blink_Lights] / g_max_amp[freqs->Blink_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Blink_Lights] > g_max_amp[freqs->Blink_Lights] / 5)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoR[freqs->Blink_Lights] / g_max_amp[freqs->Blink_Lights]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoR[freqs->Blink_Lights] / g_max_amp[freqs->Blink_Lights]);
	}
	else
	{
		EasterEggLightsEE.BlinkLightLeft = 0;
		EasterEggLightsEE.BlinkLightRight = 0;
	}

	// brake lights
	if (sample_freqs->dStereoL[556] > g_max_amp[556] / 7)
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (sample_freqs->dStereoL[556] / g_max_amp[556]);
	}
	else if (sample_freqs->dStereoR[1109] > g_max_amp[1109] / 7)
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (sample_freqs->dStereoR[1109] > g_max_amp[1109]);
	}
	else
		EasterEggLightsEE.BrakeLights = 0;

	// ambient lights
	if (sample_freqs->dStereoL[freqs->Ambient_Lights] > g_max_amp[freqs->Ambient_Lights] / 5)
	{
		EasterEggLightsEE.AmbientLights = 1;
		EasterEggLightsEE.AmbientLightsPWM = 1000 * (sample_freqs->dStereoL[freqs->Ambient_Lights] / g_max_amp[freqs->Ambient_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Ambient_Lights] > g_max_amp[freqs->Ambient_Lights] / 5)
	{
		EasterEggLightsEE.AmbientLights = 1;
		EasterEggLightsEE.AmbientLightsPWM = 1000 * (sample_freqs->dStereoR[freqs->Ambient_Lights] > g_max_amp[freqs->Ambient_Lights]);
	}
	else
		EasterEggLightsEE.AmbientLights = 0;
	
	// license lights 1-2
	if (sample_freqs->dStereoL[freqs->License_Light1] > g_max_amp[freqs->License_Light1] / 5)
	{
		EasterEggLightsEE.LicensePlateLight1 = 1;
		EasterEggLightsEE.LicensePlateLight1PWM = 1000 * (sample_freqs->dStereoL[freqs->License_Light1] / g_max_amp[freqs->License_Light1]);
		EasterEggLightsEE.LicensePlateLight2 = 1;
		EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;

	}
	else if (sample_freqs->dStereoR[freqs->License_Light1] > g_max_amp[freqs->License_Light1] / 5)
	{
		EasterEggLightsEE.LicensePlateLight1 = 1;
		EasterEggLightsEE.LicensePlateLight1PWM = 1000 * (sample_freqs->dStereoR[freqs->License_Light1] / g_max_amp[freqs->License_Light1]);
		EasterEggLightsEE.LicensePlateLight2 = 1;
		EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;
	}
	else
	{
		EasterEggLightsEE.LicensePlateLight1 = 0;
		EasterEggLightsEE.LicensePlateLight2 = 0;
	}

	// license lights 3-4
	if (sample_freqs->dStereoL[freqs->License_Light3] > g_max_amp[freqs->License_Light3] / 5)
	{
		EasterEggLightsEE.LicensePlateLight3 = 1;
		EasterEggLightsEE.LicensePlateLight3PWM = 1000 * (sample_freqs->dStereoL[freqs->License_Light3] / g_max_amp[freqs->License_Light3]);
		EasterEggLightsEE.LicensePlateLight4 = 1;
		EasterEggLightsEE.LicensePlateLight4PWM = EasterEggLightsEE.LicensePlateLight3PWM;

	}
	else if (sample_freqs->dStereoR[freqs->License_Light3] > g_max_amp[freqs->License_Light3] / 5)
	{
		EasterEggLightsEE.LicensePlateLight3 = 1;
		EasterEggLightsEE.LicensePlateLight3PWM = 1000 * (sample_freqs->dStereoR[freqs->License_Light3] / g_max_amp[freqs->License_Light3]);
		EasterEggLightsEE.LicensePlateLight4 = 1;
		EasterEggLightsEE.LicensePlateLight4PWM = EasterEggLightsEE.LicensePlateLight3PWM;
	}
	else
	{
		EasterEggLightsEE.LicensePlateLight3 = 0;
		EasterEggLightsEE.LicensePlateLight4 = 0;
	}

	// // reverse lights
	// if (averages[0][1] > 1)
	// {
	// 	EasterEggLightsEE.ReverseLights = 1;
	// 	EasterEggLightsEE.ReverseLightsPWM = 1000 * (averages[0][1] / 500);
	// }
	// else if (averages[1][1] > 1)
	// {
	// 	EasterEggLightsEE.ReverseLights = 1;
	// 	EasterEggLightsEE.ReverseLightsPWM = 1000 * (averages[1][1] / 500);
	// }
	// else
	// 	EasterEggLightsEE.ReverseLights = 0;
	

	// free(averages[0]);
	// free(averages[1]);
	// free(averages);
}

void	*transform_loop(void *car_void)
{
	/* On timer alarm */   
	t_car *car = car_void;   
	time_t current_time;
	time_t previous_time;
	time_t change_in_time;
	t_light_freqs freqs;
	pthread_t               pxThreadPlaySong;
	auto_assign_freqs(&freqs);
	#ifdef DEBUG
	if (pthread_create(&pxThreadPlaySong, NULL, playSong, "DEBUG") != 0)
	{
		printf("Error! pthread_create.\n");
		return (NULL);
	}
    #endif
	sleep(1);
	fseek(car->wav.wavStream, 45, SEEK_SET);
	previous_time = get_time_in_ms();    
	while (1)
	{  
		current_time = get_time_in_ms();
		change_in_time = current_time - previous_time;
		if (change_in_time >= 100)
		{
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
			// set_light_variables(get_averages(&car->wav.wavSampleBufferFreq), &car->wav.wavSampleBufferFreq);
			set_light_variables(&car->wav.wavSampleBufferFreq, &freqs);
			// if (wavSampleBufferFreq.dStereoL[0] > 0)
			// 	EasterEggLightsEE.FrontLightLeft = 1;
			// EasterEggLightsEE.FrontLightRight = wavSampleBufferFreq.dStereoR[0];
			// Adjust sample pos to next based on sampling rate
			double change_in_pos = 44100 - (change_in_time * 44.1);
			car->wav.wavReadConfig.u32FileSeekPosL -= (car->wav.wavReadConfig.u32Offset * (change_in_pos));
			car->wav.wavReadConfig.u32FileSeekPosR -= (car->wav.wavReadConfig.u32Offset * (change_in_pos));

			// - map transform result to lights
			// - map the brightness to light using sample data (float) - pwm 
			// - hook the data to gui car to light up light images on car
			previous_time = current_time;
		}
	}
	return (NULL);
	
	// if (u32SigCounter == (21 * 206))
	// {
	//     break ;
	// }
}

int transform(t_car *car)
{
    /* Variable declaration */
    tenWavLibReturnCode     wavReturnCode;
    // pthread_t               pxThreadPlaySong;

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
	if (!wavSpec[0].u32SpecData)
	{
		wavReturnCode = WAVLIB_LoadSpecData(car->wav.wavStream, wavSpec);
		if (wavReturnCode != WAVLIB_SUCCESS)
		{
			printf("Error load spec data, %d\n", wavReturnCode);
			fclose(car->wav.wavStream);
			return (wavReturnCode);
		}
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


	return (0);


    /* Setup alarm signal handler */
    // struct sigaction sa;    
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = SA_RESTART | SA_SIGINFO;
    // sa.sa_handler = SigAlarmHandler;
    // if (sigaction (SIGALRM, &sa, NULL) == -1)
    // {
    //     printf("Error Sigaction!");
    //     return (0);
    // }

    // /* create timer */
    // uint32_t u32SigCounter = 0; 
    // timer_t xTimerId;
    // struct sigevent sigEvent;
    // sigEvent.sigev_notify = SIGEV_SIGNAL;
    // sigEvent.sigev_signo = SIGALRM;
    // sigEvent.sigev_value.sival_ptr = &xTimerId;
    // if (TIME_CreateTimer(&xTimerId, &sigEvent) == -1)
    // {
    //     printf("Error! timer_create");
    //     return (-1);
    // }
    // printf("time id: %p\n", xTimerId);
    

    /* set a timer - 10msec - 192kbit/sec */
//    time_t xPeriodNs = 1000000000 /21;
//    //if (TIME_SetTimer(&xTimerId, xPeriod, TIME_TIMER_PERIODIC) == -1)
//    int flags;
//     struct itimerspec timespec_ns = {{0, 0}, {0, 0}};
//     flags = 0;      /* the value.it_value is interpreted relative to the clock
//                         value at the time of the call to timer_settime()
//                     */
    
    
//      /* arm the interval timer */
//     timespec_ns.it_interval.tv_sec = (xPeriodNs / NSEC_PER_SEC) ;
//     timespec_ns.it_interval.tv_nsec = ( xPeriodNs % NSEC_PER_SEC) ;
//     timespec_ns.it_value.tv_sec = (xPeriodNs / NSEC_PER_SEC);
//     timespec_ns.it_value.tv_nsec = (xPeriodNs % NSEC_PER_SEC);
//    if (timer_settime(xTimerId, flags, &timespec_ns, NULL) == -1)
//    {
//         printf("Error! timer_settime\n");
//         return (-1);
//    }

//    /* store the start time */
//     printf("start time: %lf\n", TIME_GetTime(unit_sec));
//     struct timespec stTimeStart = {0, 0};
//     clock_gettime(CLOCK_MONOTONIC_RAW, &stTimeStart);

    /* Play sound if DEBUG flag is define */
    // #ifdef DEBUG
    //     if (pthread_create(&pxThreadPlaySong, NULL, playSong, "DEBUG") != 0)
    //     {
    //         printf("Error! pthread_create.\n");
    //         return (PLAYSONG_THREAD_CREATE_ERR);
    //     }
    // #endif


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