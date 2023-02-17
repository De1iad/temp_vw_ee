/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WavLib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:06:43 by cudoh             #+#    #+#             */
/*   Updated: 2023/02/17 23:34:32 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/WavLib.h"


tenWavLibReturnCode    WAVLIB_OpenFile(char *strWaveFilePath, FILE *fWavStream)
{
    tenWavLibReturnCode = WAVLIB_ERR_FILE_OPEN;
    fWavStream = fopen(strWaveFilePath, "rb");
    if (fWavStreaam != NULL)
    {
        tenWavLibReturnCode = WAVLIB_SUCCESS;
    }
    return (tenWavLibReturnCode);
}




tenWavLibReturnCode WAVLIB_ReadByteFromStream(FILE *fWavStream,
                                              uint32_t u32Pos,
                                              void *dest,
                                              uint8_t u8ByteCnt)
{
    if (fWavStream == NULL || dest == NULL)
    {
        return (WAVLIB_ERR_NULL_PTR);
    }
    else
    {
        while (u8ByteCnt > 0)
        {
            fseek(fWavStream, u32Pos, SEEK_SET);
            fread(dest, u8ByteCnt, sizeof(uint8_t), fWavStream);
            u8ByteCnt--;
            u32Pos--;
            dest++;
        } 
    }
    return (WAVLIB_SUCCESS);                                          
}




tenWavLibReturnCode    WAVLIB_LoadSpecData(FILE *fWavStream, tstWavLibSpec *tstWavSpec)
{
    WAVLIB_ReadByteFromStream(fWavStream, WAVLIB_PosNumOfChannels,
                                          (void *)&(tstWavSpec->u16NumOfChannels),
                                          WAVLIB_ByteSzNumOfChannels);
                                          
    WAVLIB_ReadByteFromStream(fWavStream, WAVLIB_PosNumOfChannels,
                                          (void *)&(tstWavSpec->u16NumOfChannels),
                                          WAVLIB_ByteSzNumOfChannels);
                                          
    WAVLIB_ReadByteFromStream(fWavStream, WAVLIB_PosNumOfChannels,
                                          (void *)&(tstWavSpec->u16NumOfChannels),
                                          WAVLIB_ByteSzNumOfChannels);
                                          
    WAVLIB_ReadByteFromStream(fWavStream, WAVLIB_PosNumOfChannels,
                                          (void *)&(tstWavSpec->u16NumOfChannels),
                                          WAVLIB_ByteSzNumOfChannels);
                                          
    WAVLIB_ReadByteFromStream(fWavStream, WAVLIB_PosNumOfChannels,
                                          (void *)&(tstWavSpec->u16NumOfChannels),
                                          WAVLIB_ByteSzNumOfChannels);
                                          
    WAVLIB_ReadByteFromStream(fWavStream, WAVLIB_PosNumOfChannels,
                                          (void *)&(tstWavSpec->u16NumOfChannels),
                                          WAVLIB_ByteSzNumOfChannels);
    
}