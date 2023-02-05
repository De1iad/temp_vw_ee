
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <unistd.h>
#include "fft_sample.h"

#define WAVE_FILE_PATH ("/home/mexes/Music/encore.wav")
#define ERR_FILE_LOAD_FAIL ("Error: Failed to load file\n")
#define NAME_SONG ("Numb Encore by JayZ and Linkin-Park\n")
#define STDERROR (2)

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
    fft_sample_1d(audio->pos, 512);
    system("clear");
    audio->pos += length;
    audio->length -= length;
}


void    read_file_header(void)
{
    FILE *f = fopen(WAVE_FILE_PATH, "rb");

    if (f == NULL)
    {
        write(STDERROR, ERR_FILE_LOAD_FAIL, strlen(ERR_FILE_LOAD_FAIL));
        return (1);
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
    printf("audio length : %d", wavLength);
    //read_file_header();
#if 1
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
    SDL_PauseAudioDevice(audioDevice, 0);

    while (audio.length > 0)
    {
        SDL_Delay(100);
        //fft_sample_1d(audio.pos, length);
    }

    /* close the audio device */
    SDL_CloseAudioDevice(audioDevice);

    /* free the memory where sound data is stored */
    SDL_FreeWAV(wavStart);

	SDL_Quit();
#endif
	return 0;
}
