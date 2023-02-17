/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WavFile.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:59:58 by cudoh             #+#    #+#             */
/*   Updated: 2023/02/17 21:01: by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WAVLIB_H
# define WAVLIB_H
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>

# define WAVLIB_FMT ("WAVE")

typedef struct stWavLibSpecItem
{
    uint32_t    u32SpecData;
    uint32_t    u32EndAddrPos;
    uint8_t     u8ByteCnt;
}   tstWavLibSpecItem;



typedef enum enWavSpecItem
{
    u16NumOfChannels = 0,   // 22 - 23 byte addr : Mono (1), stereo (2)
    u32SampleRate,          // 24 - 27 byte addr : eg 44100Hz
    u32ByteRate,            // 28 - 31 byte addr :
                            // sampleRate * NumOfchannels * BitsPerSampe/8
                            //                    
    u16BlockAlign,          // 32 - 33 byte addr : 
                            // NumOfSample * bitsPerSample / 8
                            //
    u16BitsPerSample,       // 34 -35 Byte addr : eg 8 or 16;
    u32SoundDataSize,       // 40 - 43 byte addr:
                            // NumOfSamples * NumOfChannels * BitsPerSample/8
                            //
    u32NumOfSamples         // To be computed after file opening
}   tenWavSpecItem;



// data bytes are stored in little endian; would read off from right to left
tstWavLibSpecItem wavSpec[] = 
{
    { 0, 23, 2},
    { 0, 27, 4},
    { 0, 31, 4},
    { 0, 33, 2},
    { 0, 35, 2},
    { 0, 43, 4},
    { 0, 00, 0},
}



typedef enum enWavLibReturnCode
{
    WAVLIB_ERR_FILE_OPEN = -127,
    WAVLIB_ERR_NULL_PTR,

    WAVLIB_SUCCESS = 0,

}   tenWavLibReturnCode;




/**
 * @brief 
 * This function opens a wav file in binary read mode and stores the file
 * stream address in the pointer passed in.
 * 
 * @param strWaveFilePath 
 * @param fWavStream 
 * @return tenWavLibReturnCode 
 */
tenWavLibReturnCode    WAVLIB_OpenFile(char *strWaveFilePath, FILE *fWavStream);




/**
 * @brief 
 * This function reads data from src (fWavStream), given the number of bytes to
 * read (ByteCnt) and store the read data in the destination given.
 * 
 * @param fWavStream 
 * @param u32Pos 
 * @param dest 
 * @param u8ByteCnt 
 * @return tenWavLibReturnCode 
 */
tenWavLibReturnCode WAVLIB_ReadByteFromStream(FILE *fWavStream,
                                              uint32_t u32Pos,
                                              void *dest,
                                              uint8_t u8ByteCnt);



/**
 * @brief 
 * This function loads the wav file specification data to the given struct
 * type passed in as a pointer.
 * 
 * @param fWavSteam 
 * @param tstWavSpec 
 * @return tenWavLibReturnCode 
 */
tenWavLibReturnCode    WAVLIB_LoadSpecData(FILE *fWavStream, tstWavLibSpec *tstWavSpec);

#endif // WAVLIB