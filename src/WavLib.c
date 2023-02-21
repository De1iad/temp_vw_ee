/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include "../inc/WavLib.h"


tenWavLibReturnCode WAVLIB_ReadByteFromStream(FILE *fWavStream,
                                              uint32_t u32Pos,
                                              void *pu32SpecData,
                                              uint8_t u8ByteCnt)
{
    uint8_t u8ByteData = 0;
    
    //printf("stream addr: %p; specDataAddr: %p\n", fWavStream, pu32SpecData);
    if (fWavStream == NULL || pu32SpecData == NULL)
    {
        return (WAVLIB_ERR_NULL_PTR);
    }
    else
    {
        while (u8ByteCnt > 0)
        {
            //printf("Bytecntdown: %d; data: %d\n", u8ByteCnt, *pu32SpecData);
            *((uint32_t *)pu32SpecData) <<= WAVLIB_BYTE_BITS;
            fseek(fWavStream, u32Pos, SEEK_SET);
            fread((void *)&(u8ByteData), WAVLIB_ONE_BYTE, sizeof(uint8_t), fWavStream);
            u8ByteCnt--;
            u32Pos--;
            *((uint32_t *)pu32SpecData) |= (u8ByteData & 0x000000FF);
            //printf("value: %d\n", *pu32SpecData);
        } 
    }
    return (WAVLIB_SUCCESS);                                          
}




tenWavLibReturnCode    WAVLIB_LoadSpecData(FILE *fWavStream,
                                           tstWavLibSpecItem *paWavSpec)
{
    tenWavLibReturnCode tenReturnCode;
    uint8_t u8Idx = 0;
    uint8_t u8NumOfSpecItems;
    
    /* Get number of spec items required */
    u8NumOfSpecItems = sizeof(wavSpec) / sizeof(tstWavLibSpecItem);
    
    /* Load Wav file spec data from stream to array of spec items */
    for (;u8Idx < u8NumOfSpecItems; u8Idx++) 
    {
        tenReturnCode = WAVLIB_ReadByteFromStream(fWavStream,
                                                  paWavSpec[u8Idx].u32EndAddrPos,
                                                  &(paWavSpec[u8Idx].u32SpecData),
                                                  paWavSpec[u8Idx].u8ByteCnt);
        if (tenReturnCode != WAVLIB_SUCCESS)
        {
            break ;
        }
    }

    /* compute NumOfSamples */
    paWavSpec[NumOfSamples].u32SpecData = paWavSpec[SoundDataSize].u32SpecData /
                                         (paWavSpec[NumOfChannels].u32SpecData *
                                          paWavSpec[BitsPerSample].u32SpecData /
                                          8); 
    return (tenReturnCode);
}



void    WAVLIB_ShowWavSpec(tstWavLibSpecItem *paWavSpec)
{
    int8_t u8Idx = 0;
    int8_t u8NumOfSpecItems;
    
    /* Get number of spec items required */
    u8NumOfSpecItems = sizeof(wavSpec) / sizeof(tstWavLibSpecItem);
    for (; u8Idx < u8NumOfSpecItems; u8Idx++)
    {
        printf("%14s: %d\n", paWavSpec[u8Idx].strSpecName,
                             paWavSpec[u8Idx].u32SpecData);
    }
}





void    WAVLIB_ReadConfigInit(tstWavReadConfig *tstReadConfig, 
                                tstWavLibSpecItem *tstWavSpec)
{
    //tstReadConfig->u32FileCurPos = tstWavSpec[NumOfSamples].u32SpecData;

    /* initialise offset based on wav specfication */
    tstReadConfig->u8ByteCnt = (uint8_t) (tstWavSpec[BitsPerSample].u32SpecData / 
                                         WAVLIB_BYTE_BITS);
    tstReadConfig->u32Offset = (tstReadConfig->u8ByteCnt * 
                                  tstWavSpec[NumOfChannels].u32SpecData);
    
    /* set seekpos to last byte of sample */
    tstReadConfig->u32FileSeekPosL = WAVLIB_SOUND_DATA_BYTE_ADDR + 
                                    tstReadConfig->u8ByteCnt - 1;
    tstReadConfig->u32FileSeekPosR = (tstReadConfig->u32FileSeekPosL) + 
                                     (tstReadConfig->u8ByteCnt);
    tstReadConfig->u8NumOfChannel = (uint8_t)(tstWavSpec[NumOfChannels].u32SpecData);

}

tenWavLibReturnCode    WAVLIB_LoadSampleFromStreamToBufferChannel(FILE *fWavStream,
                                                tstWavReadConfig *tstReadConfig, 
                                                int16_t *paBufferHex,
                                                tChannel tenChannel)
{
    tenWavLibReturnCode tenReturnCode;
    uint32_t *pu32FileSeekPos = &(tstReadConfig->u32FileSeekPosL);
    uint32_t u32MaxSampleCnt = WAVLIB_MONO_SAMPLE_MAX;

    /* select the right sample length for the channel and seekpos variable */
    if (tenChannel != CHAN_MONO)
    {
        u32MaxSampleCnt = WAVLIB_STEREO_SAMPLE_MAX;
        if (tenChannel == CHAN_STEREO_R)
        {
            pu32FileSeekPos = &(tstReadConfig->u32FileSeekPosR);
        }
    }

    tstReadConfig->u32Idx = 0; // reset the index
    memset((void *)paBufferHex, 0, (sizeof(tstSampleBufferHex)));
    while (tstReadConfig->u32Idx < u32MaxSampleCnt)
    {
        tenReturnCode = WAVLIB_ReadByteFromStream(fWavStream,
                                    *pu32FileSeekPos,
                                    (void *)&(paBufferHex[tstReadConfig->u32Idx]),
                                    tstReadConfig->u8ByteCnt);
        
        /* check if byte read was successful */
        if (tenReturnCode != WAVLIB_SUCCESS)
        {
            break ;
        }
        //paBufferHex[tstReadConfig->u32Idx] = (int32_t)(paBufferHex[tstReadConfig->u32Idx]);
        (tstReadConfig->u32Idx)++;                                     // increment
        (*pu32FileSeekPos) += (tstReadConfig->u32Offset); // update seekpos
    }

    return (tenReturnCode);
}


tenWavLibReturnCode    WAVLIB_LoadSampleFromStreamToBuffer(FILE *fWavStream,
                                                tstWavReadConfig *tstReadConfig, 
                                                tstSampleBufferHex *tstBufferHex,
                                                tstWavLibSpecItem *paWavSpec)
{
    tenWavLibReturnCode tenReturnCode;

    switch (paWavSpec[NumOfChannels].u32SpecData)
    {
        case WAVLIB_CHANNEL_MONO:
        {
            /* filled mono hex buffer with samples from wav stream file*/
            tenReturnCode = WAVLIB_LoadSampleFromStreamToBufferChannel(fWavStream,
                                                       tstReadConfig, 
                                                       tstBufferHex->i16Mono,
                                                       CHAN_MONO);
            break;
        }
        case WAVLIB_CHANNEL_STEREO:
        {
            /* filled left hex buffer with samples from wav stream file*/
            tenReturnCode = WAVLIB_LoadSampleFromStreamToBufferChannel(fWavStream,
                                                       tstReadConfig, 
                                                       tstBufferHex->i16StereoL,
                                                       CHAN_STEREO_L);

            /* filled right hex buffer with samples from wav stream file*/
            tenReturnCode = WAVLIB_LoadSampleFromStreamToBufferChannel(fWavStream,
                                                       tstReadConfig, 
                                                       tstBufferHex->i16StereoR,
                                                       CHAN_STEREO_R);
            
            break ;
        }
        default:
        {
            tenReturnCode = WAVLIB_ERR_STEREO_MUL_CHAN;
        }
    }
    return (tenReturnCode);
}


tenWavLibReturnCode    WAVLIB_ConvertSampleBufferToFloat(
                                                   int16_t *u16BufferHex,
                                                   float *BufferFloat,
                                                   uint8_t const u8BufferSize)
{
    tenWavLibReturnCode tenReturnCode = WAVLIB_ERR_NULL_PTR;
    uint8_t u8Idx = 0;

    if (BufferFloat == NULL || (BufferFloat == NULL))
    {
        return (tenReturnCode);
    }
    {
        for (;u8Idx < u8BufferSize; u8Idx++)
        {
            BufferFloat[u8Idx] = ((float)(u16BufferHex[u8Idx])) / ((float) INT16_MAX);
        }
    }
    return (tenReturnCode);
}                                    

tenWavLibReturnCode WAVLIB_ConvertSampleBufferToFloatByChannel(
                                            tstSampleBufferHex * BufferHex,
                                            tstSampleBufferFloat *BufferFloat,
                                            tstWavReadConfig *ReadConfig)
{
    tenWavLibReturnCode tenReturnCode = WAVLIB_ERR_NULL_PTR;
    if ((BufferFloat == NULL) || (BufferHex == NULL) || (ReadConfig == NULL))
    {
        return (tenReturnCode);
    }
    switch (ReadConfig->u8NumOfChannel)
    {
        case WAVLIB_CHANNEL_STEREO: // conversion for stereo wav
        {
            tenReturnCode = WAVLIB_ConvertSampleBufferToFloat(
                                                        BufferHex->i16StereoL,
                                                        BufferFloat->f32StereoL,
                                                        WAVLIB_STEREO_SAMPLE_MAX);
            tenReturnCode = WAVLIB_ConvertSampleBufferToFloat(
                                                        BufferHex->i16StereoR,
                                                        BufferFloat->f32StereoR,
                                                        WAVLIB_STEREO_SAMPLE_MAX);
            break ;
        }
        default:                    // conversion for mono wav
        {
            tenReturnCode = WAVLIB_ConvertSampleBufferToFloat(
                                                        BufferHex->i16Mono,
                                                        BufferFloat->f32Mono,
                                                        WAVLIB_MONO_SAMPLE_MAX);
            break ;
        }
    }
    return (tenReturnCode);
}



tenWavLibReturnCode WAVLIB_TransformFloatSample(
                                            tstSampleBufferFloat *BufferFloat,
                                            tstSampleBufferDouble  *BufferFreq,
                                            tstWavReadConfig *ReadConfig)
{
    tenWavLibReturnCode tenReturnCode = WAVLIB_ERR_NULL_PTR;
    if ((BufferFloat == NULL) || (BufferFreq == NULL) || (ReadConfig == NULL))
    {
        return (tenReturnCode);
    }
    switch (ReadConfig->u8NumOfChannel)
    {
        case WAVLIB_CHANNEL_STEREO: // transform for stereo wav
        {
            FFTLIB_Transform(BufferFreq->dStereoL, BufferFloat->f32StereoL,
                                                   WAVLIB_STEREO_SAMPLE_MAX);

            FFTLIB_Transform(BufferFreq->dStereoR, BufferFloat->f32StereoR,
                                                   WAVLIB_STEREO_SAMPLE_MAX);
            break ;
        }
        default:                    // transform for mono wav
        {
            FFTLIB_Transform(BufferFreq->dMono, BufferFloat->f32Mono,
                                                WAVLIB_MONO_SAMPLE_MAX);
            break ;
        }
    }
    return (tenReturnCode);
}