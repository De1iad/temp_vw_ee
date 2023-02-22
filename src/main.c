
/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */


#include "../inc/WavLib.h"
#include "../inc/TimeLib.h"
#ifdef DEBUG
# include "../inc/PlaySong.h"
#endif
# define WAVFILE ("./encore.wav")

/* Global variable for the playback sampling timer */
volatile sig_atomic_t alarm_snooze = 1;

/* function prototype for the timer SIGALARM handler */
void	SigAlarmHandler(int sig);

int main(void)
{
    /* Variable declaration */
    tenWavLibReturnCode     wavReturnCode;
    FILE                    *wavStream;
    tstSampleBufferHex      wavSampleBufferHex;
    tstSampleBufferFloat    wavSampleBufferFloatInp;
    tstSampleBufferDouble   wavSampleBufferFreq;
    tstWavReadConfig        wavReadConfig;
    pthread_t               pxThreadPlaySong;

    /* Variable Initialisation */
    wavReturnCode = WAVLIB_ERR_FILE_OPEN;
    wavStream = NULL;
    memset((void *)&wavSampleBufferHex, 0, (sizeof(tstSampleBufferHex)));
    memset((void *)&wavSampleBufferFloatInp, 0, (sizeof(tstSampleBufferFloat)));
    memset((void *)&wavSampleBufferFreq, 0, (sizeof(tstSampleBufferHex)));
    memset((void *)&wavReadConfig, 0, (sizeof(tstWavReadConfig)));

    /* Load wav file */
    wavStream = fopen(WAVFILE, "rb");
    if (wavStream == NULL)
    {
        printf("Error open file, %d\n", wavReturnCode);
        return (wavReturnCode);
    }

    /* Load wav file audio specification data */
    wavReturnCode = WAVLIB_LoadSpecData(wavStream, wavSpec);
    if (wavReturnCode != WAVLIB_SUCCESS)
    {
        printf("Error load spec data, %d\n", wavReturnCode);
        fclose(wavStream);
        return (wavReturnCode);
    }

    /* Display wav file audio specification data */
    WAVLIB_ShowWavSpec(wavSpec);

    /* Initialise the configuration for reading samples from wav file */
    WAVLIB_ReadConfigInit(&wavReadConfig, wavSpec);
    printf("seekposL: %d, seekposR: %d, idx: %d, offset: %d, byteCnt: %d\n",
                                        wavReadConfig.u32FileSeekPosL,
                                        wavReadConfig.u32FileSeekPosR,
                                        wavReadConfig.u32Idx,
                                        wavReadConfig.u32Offset,
                                        wavReadConfig.u8ByteCnt);




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



    while (1)
    {
        /* On timer alarm */            
        if (alarm_snooze == 1)
        {   
            alarm_snooze = 0;
		    printf("\n-----\n");
            u32SigCounter++;
            // how many lights to turn on - number of samples
            // - load new set of samples to the buffer (hexbuffer)
            wavReturnCode = WAVLIB_LoadSampleFromStreamToBuffer(wavStream,
                                                            &wavReadConfig, 
                                                            &wavSampleBufferHex,
                                                            wavSpec);
            if (wavReturnCode != WAVLIB_SUCCESS)
            {
                //printf("ERROR! >>> LoadSampleFromStreamToBuffer %d\n", wavReturnCode);
            }
            // - update the number of samples remaining

            // - convert sample data to float
            wavReturnCode = WAVLIB_ConvertSampleBufferToFloatByChannel(
                                                        &wavSampleBufferHex,
                                                        &wavSampleBufferFloatInp,
                                                        &wavReadConfig);
            if (wavReturnCode != WAVLIB_SUCCESS)
            {
                //printf("ERROR! >>> ConvertSampleBufferToFloatByChannel %d\n", wavReturnCode);
            }


            // - perform transform - freq 
            wavReturnCode = WAVLIB_TransformFloatSample(
                                                        &wavSampleBufferFloatInp,
                                                        &wavSampleBufferFreq,
                                                        &wavReadConfig);

            // show spectrum on terminal
            system("clear");
            FFTLIB_ShowFreqSpectrum(wavSampleBufferFreq.dStereoL, 8);
            FFTLIB_ShowFreqSpectrum(wavSampleBufferFreq.dStereoR, 8);

            // Adjust sample pos to next based on sampling rate
            wavReadConfig.u32FileSeekPosL += (wavReadConfig.u32Offset * 44100/21);
            wavReadConfig.u32FileSeekPosR += (wavReadConfig.u32Offset * 44100/21);

            // - map transform result to lights
            // - map the brightness to light using sample data (float) - pwm 
            // - hook the data to gui car to light up light images on car
        }
        
        if (u32SigCounter == (21 * 206))
        {
            break ;
        }
        sleep(10);
    }
    #ifdef DEBUG
        if (pthread_join(pxThreadPlaySong, NULL) != 0)
        {
            printf("Error! pthread_join.\n");
            return (PLAYSONG_THREAD_JOIN_ERR);
        }
    #endif

    // - disable timer if the number of sample to zero
    TIME_DisableTimer(&xTimerId);
    printf("run time: %lf\n", TIME_GetRuntime(&stTimeStart, unit_sec));

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
    fclose(wavStream);
    exit(0);
    return (0);
}



void	SigAlarmHandler(int sig)
{
	if (sig == SIGALRM)
    {
        alarm_snooze = 1;
	}
}
