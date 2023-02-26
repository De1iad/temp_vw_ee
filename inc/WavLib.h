/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#ifndef WAVLIB_H
# define WAVLIB_H
# include <stdint.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include "../inc/FftLib.h"

# define WAVLIB_FMT ("WAVE")
# define WAVLIB_ONE_BYTE (1U)
# define WAVLIB_BYTE_BITS (8)
# define WAVLIB_STEREO_SAMPLE_MAX (44100)     // Number of Samples for stereo
# define WAVLIB_MONO_SAMPLE_MAX (16)      // Max number of Samples for Mono
# define WAVLIB_SOUND_DATA_BYTE_ADDR (44) // Start byte addr of wav Sound data
# define WAVLIB_CHANNEL_MONO (1)          // Wav file contains only one channel
# define WAVLIB_CHANNEL_STEREO (2)        // Wav file contains two channel

struct s_car;

typedef struct s_light_freqs
{
	uint16_t	Front_Lights;
	uint16_t	Parking_Lights;
	uint16_t	Blink_Lights;
	uint16_t	Brake_Lights;
	uint16_t	Reverse_Lights;
	uint16_t	Ambient_Lights;
	uint16_t	Fog_Lights;
	uint16_t	License_Light1;
	uint16_t	License_Light2;
	uint16_t	License_Light3;
	uint16_t	License_Light4;
	uint16_t	License_Light5;
} t_light_freqs;

typedef enum enWavLibReturnCode
{
    WAVLIB_ERR_FILE_OPEN = -127,
    WAVLIB_ERR_NULL_PTR,
    WAVLIB_ERR_STEREO_MUL_CHAN,   // Stereo Wav file with more than two channels
	WAVLIB_EOF,
    WAVLIB_SUCCESS = 0,

}   tenWavLibReturnCode;


typedef struct stWavLibSpecItem
{
    uint32_t    u32SpecData;
    uint32_t    u32EndAddrPos;
    uint8_t     u8ByteCnt;
    char *      strSpecName;
}   tstWavLibSpecItem;



typedef enum enWavSpecItem
{
    NumOfChannels = 0,   // 22 - 23 byte addr : Mono (1), stereo (2)
    SampleRate,          // 24 - 27 byte addr : eg 44100Hz
    ByteRate,            // 28 - 31 byte addr :
                         // sampleRate * NumOfchannels * BitsPerSampe/8
                         //                    
    BlockAlign,          // 32 - 33 byte addr : 
                         // NumOfSample * bitsPerSample / 8
                         //
    BitsPerSample,       // 34 -35 Byte addr : eg 8 or 16;
    SoundDataSize,       // 40 - 43 byte addr:
                         // NumOfSamples * NumOfChannels * BitsPerSample/8
                         //
    NumOfSamples         // To be computed after file opening
}   tenWavSpecItem;




/* Data structure to store raw data read from audio wav file */
typedef struct sSampleBufferHex
{
    int16_t i16StereoL[WAVLIB_STEREO_SAMPLE_MAX]; // left channel
    int16_t i16StereoR[WAVLIB_STEREO_SAMPLE_MAX]; // right channel
    int16_t i16Mono[WAVLIB_MONO_SAMPLE_MAX];      // Only one channel
}   tstSampleBufferHex;



/* Data structure to store corresponding sample data converted to float */
typedef struct sSampleBufferFloat
{
    float f32StereoL[WAVLIB_STEREO_SAMPLE_MAX]; // left channel
    float f32StereoR[WAVLIB_STEREO_SAMPLE_MAX]; // right channel
    float f32Mono[WAVLIB_MONO_SAMPLE_MAX];      // Only one channel
}   tstSampleBufferFloat;


/* Data structure to store corresponding sample data converted to float */
typedef struct sSampleBufferDouble
{
    double dStereoL[WAVLIB_STEREO_SAMPLE_MAX]; // left channel
    double dStereoR[WAVLIB_STEREO_SAMPLE_MAX]; // right channel
    double dMono[WAVLIB_MONO_SAMPLE_MAX];      // Only one channel
}   tstSampleBufferDouble;


/* Data structure to specify how samples are read from file depend in the 
    audio wav file specification
*/
typedef struct sWavReadConfig
{
    uint32_t u32FileSeekPosL;
    uint32_t u32FileSeekPosR;
    uint32_t u32Idx;
    uint32_t u32Offset;
    uint8_t  u8ByteCnt;
    uint8_t  u8NumOfChannel;   
}   tstWavReadConfig;



typedef enum eChannel
{
    CHAN_MONO,
    CHAN_STEREO_L,
    CHAN_STEREO_R
}   tChannel;

// data bytes are stored in little endian; would read off from right to left
static tstWavLibSpecItem wavSpec[] = 
{
    { 0, 23, 2, "NumOfChannels"},
    { 0, 27, 4, "SampleRate"   },
    { 0, 31, 4, "ByteRate"     },
    { 0, 33, 2, "BlockAlign"   },
    { 0, 35, 2, "BitsPerSample"},
    { 0, 43, 4, "SoundDataSize"},
    { 0, 00, 0, "NumOfSample"  }
};



/**
 * @brief 
 * This function reads data from src (fWavStream), given the number of bytes to
 * read (ByteCnt) and store the read data in the destination given.
 * 
 * @param fWavStream 
 * @param u32Pos 
 * @param pu32SpecData 
 * @param u8ByteCnt 
 * @return tenWavLibReturnCode 
 */
tenWavLibReturnCode WAVLIB_ReadByteFromStream(FILE *fWavStream,
                                              uint32_t u32Pos,
                                              void *pu32SpecData,
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
tenWavLibReturnCode    WAVLIB_LoadSpecData(FILE *fWavStream, 
                                           tstWavLibSpecItem *paWavSpec);



/**
 * @brief 
 * This functions prints out the required specification of the wav file
 * 
 * @param paWavSpec 
 */
void    WAVLIB_ShowWavSpec(tstWavLibSpecItem *paWavSpec);




void    WAVLIB_ReadConfigInit(tstWavReadConfig *tstReadConfig,
                                tstWavLibSpecItem *tstWavSpec);



tenWavLibReturnCode    WAVLIB_LoadSampleFromStreamToBuffer(FILE *fWavStream,
                                            tstWavReadConfig *tstReadConfig, 
                                           tstSampleBufferHex *tstBufferHex,
                                           tstWavLibSpecItem *paWavSpec);

/**
 * @brief 
 * This function loads raw sample data (hexadecimal) from the wav file
 * stream into the buffer (stereo left, stereo right, mono)
 * 
 * @param fWavStream        : file stream open in binary read mode
 * @param tstReadConfig     : struct to sample reading configuration
 * @param paBufferHex       : address to buffer to store read samples
 * @param tenChannel        : indicate the channel type mono, stereo L || R
 * @return tenWavLibReturnCode 
 */
tenWavLibReturnCode    WAVLIB_LoadSampleFromStreamToBufferChannel(
                               FILE *fWavStream,
                               tstWavReadConfig *tstReadConfig, 
                               int16_t *paBufferHex,
                                tChannel tenChannel);



/**
 * @brief 
 * This function converts the 16bit data in the hexbuffer to float and
 * store them in a float buffer for fft transform.
 * 
 * @param u16BufferHex 
 * @param BufferFloat 
 * @param u8BufferSize 
 * @return tenWavLibReturnCode 
 */
tenWavLibReturnCode    WAVLIB_ConvertSampleBufferToFloat(
                                            int16_t *u16BufferHex,
                                            float *BufferFloat,
                                            uint16_t const u16BufferSize);




/**
 * @brief 
 * todo Calls the function: WAVLIB_ConvertSampleBufferToFloat
 * This function converts the 16bit array buffer which stores the raw 
 * samples from the wav file stream to float by calling the function,
 * WAVLIB_ConvertSampleBufferToFloat. This operation is performed, 
 * considering the number channels (mono or stereo) of the wav samples
 *  
 * @param BufferHex 
 * @param BufferFloat 
 * @param ReadConfig 
 * @return tenWavLibReturnCode 
 */
tenWavLibReturnCode WAVLIB_ConvertSampleBufferToFloatByChannel(
                                tstSampleBufferHex * BufferHex,
                                tstSampleBufferFloat *BufferFloat,
                                tstWavReadConfig *ReadConfig);



tenWavLibReturnCode WAVLIB_TransformFloatSample(
                                            tstSampleBufferFloat *BufferFloat,
                                            tstSampleBufferDouble  *BufferFreq,
                                            tstWavReadConfig *ReadConfig);

typedef struct s_wav
{
	FILE *wavStream;
	struct sWavReadConfig wavReadConfig;
	struct sSampleBufferHex wavSampleBufferHex;
	struct sSampleBufferFloat wavSampleBufferFloatInp;
	struct sSampleBufferDouble wavSampleBufferFreq;
} t_wav;

int transform(struct s_car *car);
void	*transform_loop(void *car);
void fetch_amp_range(struct s_car *car);
time_t	get_time_in_ms(void);


#endif // WAVLIB

