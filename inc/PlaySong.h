/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#ifndef PLAYSONG_H
#define PLAYSONG_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

#define WAVE_FILE_PATH ("./Quantumania.wav")
#define ERR_FILE_LOAD_FAIL ("Error: Failed to load file\n")
#define NAME_SONG ("Numb Encore by JayZ and Linkin-Park\n")
#define STDERROR (2)
#define PLAYSONG_THREAD_CREATE_ERR -100
#define PLAYSONG_THREAD_JOIN_ERR -101


typedef struct s_AudioData
{
    uint8_t *pos;
    uint32_t length;
}   AudioData;

void    MyAudioCallBack(void *userData, uint8_t *stream, int streamLength);
void    *playSong(void *args);

#endif // PLAYSONG_H