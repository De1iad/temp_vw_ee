
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <unistd.h>
#include "fft_sample.h"
#include <time.h>
#include <syslog.h>
#include "TimeLib.h"

#define WAVE_FILE_PATH ("/home/mexes/Music/encore.wav")
#define ERR_FILE_LOAD_FAIL ("Error: Failed to load file\n")
#define NAME_SONG ("Numb Encore by JayZ and Linkin-Park\n")
#define STDERROR (2)

struct timespec stTimePeriodicStart = {0, 0};

typedef struct s_AudioData
{
    uint8_t *pos;
    uint32_t length;
}   AudioData;

void    MyAudioCallBack(void *userData, uint8_t *stream, int streamLength)
{
    uint32_t length = (uint32_t)streamLength;
    AudioData *audio = (AudioData *)userData;
    if (audio->length == 0)
    {
        return ;
    }
    length = (length > audio->length ? audio->length : length);
    /*
    printf("wave start : %p %x %x %x %x %x %x %x %x - %x %x %d\n", 
                        (audio->pos), *(audio->pos), 
                        *((audio->pos)+1), *((audio->pos)+2),
                        *((audio->pos)+3), *((audio->pos)+4),
                        *((audio->pos)+5), *((audio->pos)+6),
                        *((audio->pos)+7), *((audio->pos)+8),
                        *((audio->pos)+9), 
                         length);
    */

    SDL_memcpy(stream, audio->pos, length);
    
    syslog(LOG_INFO, "Sample time: %lf\n", 
                    TIME_GetRuntime(&stTimePeriodicStart, unit_sec));
    clock_gettime(CLOCK_MONOTONIC_RAW, &stTimePeriodicStart);
    //printf("time: %ld\n", time(NULL));
    #if 0
    uint32_t u32Idx = 0;
    double samples[64];
    fft_sample__read_chan(samples, audio->pos, &u32Idx, 64, audio->length, 
                                                        CHAN_STEREO_LEFT);
    fft_sample_1d(samples, 64);
    #endif
    audio->pos += length;
    audio->length -= length;
}


void    read_file_header(void)
{
    FILE *f = fopen(WAVE_FILE_PATH, "rb");

    if (f == NULL)
    {
        write(STDERROR, ERR_FILE_LOAD_FAIL, strlen(ERR_FILE_LOAD_FAIL));
        return ;
    }
    uint8_t byte[44];
    fread((void *)&byte, sizeof(uint8_t), 44, f);
    for (int x=0; x<44; x++)
    {
        printf("%d: %x \n", x, byte[x]);

        if ((x+1)%4 == 0) printf("----\n");
    }
    fclose(f);
}

int main(void)
{
	SDL_Init(SDL_INIT_AUDIO);
	printf("\nPlaying %s", NAME_SONG);
    
    SDL_AudioSpec   wavSpec;
    uint8_t         *wavStart;
    uint32_t        wavLength;

    /* Load sound */
    if (SDL_LoadWAV(WAVE_FILE_PATH, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        write(STDERROR, ERR_FILE_LOAD_FAIL, strlen(ERR_FILE_LOAD_FAIL));
        return 1;
    }
    printf("audio length : %d\n", wavLength);
    //read_file_header();
    /* setup audio data and call back function */
    AudioData audio;
    audio.pos = wavStart;
    audio.length = wavLength;

    wavSpec.callback = MyAudioCallBack;
    wavSpec.userdata = &audio;


    /* open audio device */
    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, \
                                                    SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (audioDevice == 0)
    {
        write(STDERROR, SDL_GetError(), strlen(SDL_GetError()));
        return (2);
    }

    /* play sound */
    clock_gettime(CLOCK_MONOTONIC_RAW, &stTimePeriodicStart);
    SDL_PauseAudioDevice(audioDevice, 0);
    
/*
    useconds_t timers = 22;
    uint32_t N = 10;
    double *samples = (double *)malloc(sizeof(double) * N);
    uint32_t u32IdxWav = 0;
*/
    while (audio.length > 0)
    {
        SDL_Delay(100);
        /*

        fft_sample__read_chan(samples, wavStart, &u32IdxWav, N, \
                                                 wavLength, \
                                                 CHAN_STEREO_LEFT);
        fft_sample_1d(samples, N);
        usleep(timers * N);
        */
        //system("clear");
    }

//    free(samples);
    /* close the audio device */
    SDL_CloseAudioDevice(audioDevice);

    /* free the memory where sound data is stored */
    SDL_FreeWAV(wavStart);

	SDL_Quit();
//#endif
	return 0;
}
