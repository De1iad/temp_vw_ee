
/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include "../inc/car.h"
#include "../inc/WavLib.h"
#include "../inc/EasterEgg.h"
#ifdef DEBUG
# include "../inc/PlaySong.h"
#endif
# define WAVFILE ("./encore.wav")

inputsEE EasterEggLightsEE;

double **get_averages(tstSampleBufferDouble *sample_freqs);

void	manual_assign_freqs(t_light_freqs *freqs)
{
	freqs->Ambient_Lights = 0;
	freqs->Blink_Lights = 0;
	freqs->Brake_Lights = 0;
	freqs->Fog_Lights = 0;
	freqs->Front_Lights = 0;
	freqs->License_Light1 = 0;
	freqs->License_Light2 = 0;
	freqs->License_Light3 = 0;
	freqs->License_Light4 = 0;
	freqs->License_Light5 = 0;
	freqs->Parking_Lights = 0;
	freqs->Reverse_Lights = 0;
}

void	auto_assign_freqs(t_light_freqs *freqs, double *max_amp)
{
	double	magnitude = 0;
	for (int i = 80; i < 100; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->Front_Lights = i;
			magnitude = max_amp[i];
		}
	}
	printf("front lights: %dhz\n", freqs->Front_Lights);
	magnitude = 0;
	for (int i = 10; i < 50; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->Fog_Lights = i;
			magnitude = max_amp[i];
		}
	}
	printf("fog lights: %dhz\n", freqs->Fog_Lights);
	magnitude = 0;
	for (int i = 400; i < 700; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->Blink_Lights = i;
			magnitude = max_amp[i];
		}
	}
	printf("blink lights: %dhz\n", freqs->Blink_Lights);
	magnitude = 0;
	for (int i = 40; i < 50; i++)
	{
		if (max_amp[i] > magnitude && freqs->Fog_Lights != i)
		{
			freqs->Ambient_Lights = i;
			magnitude = max_amp[i];
		}
	}
	printf("ambient lights: %dhz\n", freqs->Ambient_Lights);
	magnitude = 0;
	for (int i = 880; i < 900; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->License_Light1 = i;
			freqs->License_Light2 = i;
			magnitude = max_amp[i];
		}
	}
	printf("license lights 1-2: %dhz\n", freqs->License_Light1);
	magnitude = 0;
	for (int i = 2130; i < 2136; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->License_Light3 = i;
			freqs->License_Light4 = i;
			magnitude = max_amp[i];
		}
	}
	printf("license lights 3-4: %dhz\n", freqs->License_Light1);
}


void	set_light_variables(tstSampleBufferDouble *sample_freqs, t_light_freqs *freqs, double *max_amp)
{
	// double **averages = get_averages(sample_freqs);
	// for (int i = 0; i < 19; i++)
	// 	printf("freq range %d-%d: %f\n", i * 8, (i + 1) * 8, averages[0][i]);
	// free(averages);

	//printf("%f / 7 = %f, current freq L: %f, current freq R: %f\n", max_amp[freqs->Front_Lights], max_amp[freqs->Front_Lights] / 7, sample_freqs->dStereoL[freqs->Front_Lights], sample_freqs->dStereoR[freqs->Front_Lights]);
	printf("timestamp: %ld\n", get_time_in_ms());
	for (int i = 0; i < 22050; i++)
	{
		if ((sample_freqs->dStereoL[i] > 1000) || (sample_freqs->dStereoR[i] > 1000))
			printf("freq %d, left: %f, right: %f, max_amp: %f\n", i, sample_freqs->dStereoL[i], sample_freqs->dStereoR[i], max_amp[i]);
	}

	// headlights
	if (sample_freqs->dStereoL[freqs->Front_Lights] > max_amp[freqs->Front_Lights] / 3 || sample_freqs->dStereoR[freqs->Front_Lights] > max_amp[freqs->Front_Lights] / 3 ||  sample_freqs->dStereoL[622] > max_amp[622] / 3 || sample_freqs->dStereoR[622] > max_amp[622] / 3)
	{
		EasterEggLightsEE.FrontLights = 1;
	}
	else
		EasterEggLightsEE.FrontLights = 0;

	// fog lights
	if (sample_freqs->dStereoL[freqs->Fog_Lights] > max_amp[freqs->Fog_Lights] / 7)
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (sample_freqs->dStereoL[freqs->Fog_Lights] / max_amp[freqs->Fog_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Fog_Lights] > max_amp[freqs->Fog_Lights] / 7)
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (sample_freqs->dStereoR[freqs->Fog_Lights] / max_amp[freqs->Fog_Lights]);
	}
	else
		EasterEggLightsEE.FogLights = 0;

	// parking lights
	if (sample_freqs->dStereoL[73] > max_amp[73] / 7)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (sample_freqs->dStereoL[73] / max_amp[73]);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (sample_freqs->dStereoL[73] / max_amp[73]);
	}
	else if (sample_freqs->dStereoR[73] > max_amp[73] / 7)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (sample_freqs->dStereoR[73] > max_amp[73]);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (sample_freqs->dStereoR[73] > max_amp[73]);
	}
	else
	{
		EasterEggLightsEE.ParkingLightLeft = 0;
		EasterEggLightsEE.ParkingLightRight = 0;
	}

	// blink lights
	if (sample_freqs->dStereoL[freqs->Blink_Lights] > max_amp[freqs->Blink_Lights] / 5) // old: sample_freqs->dStereoL[876] > max_amp[876] / 7
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoL[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoL[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Blink_Lights] > max_amp[freqs->Blink_Lights] / 5)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoR[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoR[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
	}
	else if (sample_freqs->dStereoL[700] > max_amp[700] / 5)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoL[700] / max_amp[700]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoL[700] / max_amp[700]);
	}
	else if (sample_freqs->dStereoR[700] > max_amp[700] / 5)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoR[700] / max_amp[700]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoR[700] / max_amp[700]);
	}
	else
	{
		EasterEggLightsEE.BlinkLightLeft = 0;
		EasterEggLightsEE.BlinkLightRight = 0;
	}

	// brake lights
	if (sample_freqs->dStereoL[2365] > max_amp[2365] / 5) //556
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (sample_freqs->dStereoL[2365] / max_amp[2365]);
	}
	else if (sample_freqs->dStereoR[2365] > max_amp[2365] / 5)
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (sample_freqs->dStereoR[2365] > max_amp[2365]);
	}
	else
		EasterEggLightsEE.BrakeLights = 0;

	// ambient lights
	if (sample_freqs->dStereoL[freqs->Ambient_Lights] > max_amp[freqs->Ambient_Lights] / 5)
	{
		EasterEggLightsEE.AmbientLights = 1;
		EasterEggLightsEE.AmbientLightsPWM = 1000 * (sample_freqs->dStereoL[freqs->Ambient_Lights] / max_amp[freqs->Ambient_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Ambient_Lights] > max_amp[freqs->Ambient_Lights] / 5)
	{
		EasterEggLightsEE.AmbientLights = 1;
		EasterEggLightsEE.AmbientLightsPWM = 1000 * (sample_freqs->dStereoR[freqs->Ambient_Lights] > max_amp[freqs->Ambient_Lights]);
	}
	else
		EasterEggLightsEE.AmbientLights = 0;
	
	// license lights 1-2
	if (sample_freqs->dStereoL[freqs->License_Light1] > max_amp[freqs->License_Light1] / 5)
	{
		EasterEggLightsEE.LicensePlateLight1 = 1;
		EasterEggLightsEE.LicensePlateLight1PWM = 1000 * (sample_freqs->dStereoL[freqs->License_Light1] / max_amp[freqs->License_Light1]);
		EasterEggLightsEE.LicensePlateLight2 = 1;
		EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;

	}
	else if (sample_freqs->dStereoR[freqs->License_Light1] > max_amp[freqs->License_Light1] / 5)
	{
		EasterEggLightsEE.LicensePlateLight1 = 1;
		EasterEggLightsEE.LicensePlateLight1PWM = 1000 * (sample_freqs->dStereoR[freqs->License_Light1] / max_amp[freqs->License_Light1]);
		EasterEggLightsEE.LicensePlateLight2 = 1;
		EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;
	}
	else
	{
		EasterEggLightsEE.LicensePlateLight1 = 0;
		EasterEggLightsEE.LicensePlateLight2 = 0;
	}

	// license lights 3-4
	if (sample_freqs->dStereoL[freqs->License_Light3] > max_amp[freqs->License_Light3] / 5)
	{
		EasterEggLightsEE.LicensePlateLight3 = 1;
		EasterEggLightsEE.LicensePlateLight3PWM = 1000 * (sample_freqs->dStereoL[freqs->License_Light3] / max_amp[freqs->License_Light3]);
		EasterEggLightsEE.LicensePlateLight4 = 1;
		EasterEggLightsEE.LicensePlateLight4PWM = EasterEggLightsEE.LicensePlateLight3PWM;

	}
	else if (sample_freqs->dStereoR[freqs->License_Light3] > max_amp[freqs->License_Light3] / 5)
	{
		EasterEggLightsEE.LicensePlateLight3 = 1;
		EasterEggLightsEE.LicensePlateLight3PWM = 1000 * (sample_freqs->dStereoR[freqs->License_Light3] / max_amp[freqs->License_Light3]);
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
	t_car			*car = car_void;   
	time_t			current_time;
	time_t			previous_time;
	time_t			change_in_time;
	time_t			linked_time;
	double			change_in_pos;
	t_light_freqs	freqs;
	pthread_t		pxThreadPlaySong;

	linked_time = car->previous_time;
	//manual_assign_freqs(&freqs);
	auto_assign_freqs(&freqs, car->max_amp);
	fseek(car->wav.wavStream, car->wav.wavReadConfig.u32FileSeekPosL, SEEK_SET);
	current_time = get_time_in_ms();
	#ifdef DEBUG
	if (pthread_create(&pxThreadPlaySong, NULL, playSong, &linked_time) != 0)
	{
		printf("Error! pthread_create.\n");
		return (NULL);
	}
    #endif
	while (current_time - linked_time < 50000)
	{
		current_time = get_time_in_ms();
	}
	printf("trans current_time: %ld, prev_time: %ld\n", current_time, linked_time);
	previous_time = get_time_in_ms();    
	while (1)
	{  
		current_time = get_time_in_ms();
		change_in_time = current_time - previous_time;
		if (change_in_time >= 100)
		{
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

			set_light_variables(&car->wav.wavSampleBufferFreq, &freqs, car->max_amp);

			change_in_pos = 44100 - (change_in_time * 44.1);
			car->wav.wavReadConfig.u32FileSeekPosL -= (car->wav.wavReadConfig.u32Offset * (change_in_pos));
			car->wav.wavReadConfig.u32FileSeekPosR -= (car->wav.wavReadConfig.u32Offset * (change_in_pos));

			previous_time = current_time;
		}
	}
	return (NULL);
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
}

void fetch_amp_range(t_car *car)
{
	int return_code = 0;
	long i = 0;

    for (int i = 0; i < 22050; i++)
		car->max_amp[i] = 0;
	fseek(car->wav.wavStream, car->wav.wavReadConfig.u32FileSeekPosL, SEEK_SET);
	//int total_samples = 0;
    while (return_code != WAVLIB_EOF) //total_samples < wavSpec[6].u32SpecData
	{
		i++;
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
		    if (car->wav.wavSampleBufferFreq.dStereoL[x] > car->max_amp[x])
		    {
		        car->max_amp[x] = car->wav.wavSampleBufferFreq.dStereoL[x];
		    }
		    if (car->wav.wavSampleBufferFreq.dStereoR[x] > car->max_amp[x])
		    {
		        car->max_amp[x] = car->wav.wavSampleBufferFreq.dStereoR[x];
		    }
		}
		car->wav.wavReadConfig.u32FileSeekPosL -= (car->wav.wavReadConfig.u32Offset * (44100 - 4410));
		car->wav.wavReadConfig.u32FileSeekPosR -= (car->wav.wavReadConfig.u32Offset * (44100 - 4410));
	}
	printf("loops: %ld\n", i);
	printf("done\n");
	// for (int x=0; x < 22050; x++)
	// {
	// 	if (car->max_amp[x] > 200)
	// 		printf("freq %d max: %f\n", x, car->max_amp[x]);
	// }
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