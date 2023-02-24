/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include "../inc/PlaySong.h"

void    MyAudioCallBack(void *userData, uint8_t *stream, int streamLength)
{
    uint32_t length = (uint32_t)streamLength;
    AudioData *audio = (AudioData *)userData;
    if (audio->length == 0)
    {
        return ;
    }
    length = (length > audio->length ? audio->length : length);
    SDL_memcpy(stream, audio->pos, length);
    audio->pos += length;
    audio->length -= length;
}

void    *playSong(void *args)
{
	//sleep(1);
	SDL_Init(SDL_INIT_AUDIO);
	printf("\nPlaying %s: %s", NAME_SONG, (char *)args);
    
    SDL_AudioSpec   wavSpec;
    uint8_t         *wavStart;
    uint32_t        wavLength;

    /* Load sound */
    if (SDL_LoadWAV(WAVE_FILE_PATH, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        write(STDERROR, ERR_FILE_LOAD_FAIL, strlen(ERR_FILE_LOAD_FAIL));
        return (NULL);
    }
    
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
        return (NULL);
    }

    /* play sound */
    SDL_PauseAudioDevice(audioDevice, 0);
    
    while (audio.length > 0)
    {
        SDL_Delay(100);
    }

    /* close the audio device */
    SDL_CloseAudioDevice(audioDevice);

    /* free the memory where sound data is stored */
    SDL_FreeWAV(wavStart);

	SDL_Quit();
	return (NULL);
}
