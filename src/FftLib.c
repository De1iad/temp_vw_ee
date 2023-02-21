/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FftLib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:28:51 by cudoh             #+#    #+#             */
/*   Updated: 2023/02/21 05:17:59 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/FftLib.h"


void fft_sample(int8_t *data, int N)
{
    //fftw_complex in[N], out[N];
    fftw_complex *in  = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out  = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);

    fftw_plan p;
    int i;

    for (i = 0; i < N; i++)
    {
        //in[i][0] = cos(2 * PI * i / N);
        in[i][0] = data[i];
        in[i][1] = 0;
    }

    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    for (i = 0; i < N; i++)
    {
        printf("%d %f\n", i, sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]) / N);
    }
    
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);
    return ;
}



void FFTLIB_Transform(double *dDataOutput, float *fdataInput, int N)
{
    //fftw_complex in[N], out[N];
    fftw_complex *in  = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out  = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);

    fftw_plan p;
    int i;
    double magnitude = 0.0;

    for (i = 0; i < N; i++)
    {
        //in[i][0] = cos(2 * PI * i / N);
        in[i][0] = fdataInput[i];
        //printf("%f\n", data[i]);
        in[i][1] = 0.0;
    }

    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);


    FFTLIB_ComputeMagnitude(dDataOutput, out, N);
    //show_freq_spec(out, N);
    
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);
    return ;
}


void    FFTLIB_ShowFreqSpectrum(double *dBufferFreqSpectrum, uint32_t u32SampleSize)
{
    uint32_t u32Idx = 0;
    
    for (; u32Idx < u32SampleSize; u32Idx++)
    {
        for (int x = 0; x < ((int)(dBufferFreqSpectrum[u32Idx])); x++)
        {
            write(1, "|", 1);
        }
        write(1, "\n", 1);
    }
}



void FFTLIB_ComputeMagnitude(double *dDataOutput, fftw_complex *freq, int N)
{
    for (int x = 0; x < N; x++)
    {
        dDataOutput[x] = (sqrt((freq[x][0] * freq[x][0]) + 
                              (freq[x][1] * freq[x][1]))) *10;
        //printf("Magnitude %d: %f\n", x, dDataOutput[x]);
        //render_freq_bar((int)magnitude);
    }
}


/*
void fft_sample__read_chan(double *samples, int8_t *data, \
                                            uint32_t *pu32Idx, \
                                            int N, \
                                            uint32_t u32AudioLength, \
                                            enum eChannel chan)
{
    uint32_t    u32IdxSample;
    uint32_t    u32Offset;
    uint32_t    u32DataLength;

    u32Offset = 2;
    u32IdxSample = 0;
    memset((void *)samples, 0, sizeof(double) * N);
    switch (chan)
    {
    case CHAN_STEREO_RIGHT:
    {
//        u32Idx = 2;
        u32Offset = 4;
        u32DataLength = N * 2;
        break;
    }
    case CHAN_STEREO_LEFT:
    {
        //(*pu32Idx) = ((*pu32Idx) == 0) ? 0 : (*pu32Idx);
        u32Offset = 4;
        u32DataLength = (*pu32Idx) + (N * 4);
        while ((*pu32Idx) < u32DataLength && ((*pu32Idx) < u32AudioLength))
        {
            samples[u32IdxSample] = fft_sample__read_sample(data, pu32Idx);
            //printf("wavidx%d, sample_val: %lf\n", *pu32Idx, samples[u32IdxSample]);
            (*pu32Idx) += u32Offset;
            u32IdxSample++;
        }
        break;
    }
    case CHAN_STEREO_LR:
    {
        *pu32Idx = 0;
        u32Offset = 4;
        u32DataLength = N * 2;
        break ;
    }
    default:
    {
        //
        break ;
    }
    }
    return ;
}

double fft_sample__read_sample(uint8_t *data, uint32_t *pu32Idx)
{
    int16_t i32SampleVal = 0;



    //printf("init_int16: %x\n", i32SampleVal);

    
    i32SampleVal = ((data[(*pu32Idx) + 1]) << BYTE);
    //printf("first_byte_: %x, shift_left_int16: %x\n", 
            //(data[(*pu32Idx) + 1]), i32SampleVal);

            
    i32SampleVal |= ((data[(*pu32Idx)]));
    //printf("second_byte_: %x, shift_right_int16: %x; dec: %d\n\n", 
            //(data[(*pu32Idx)]), i32SampleVal, i32SampleVal);
    return (((float)(i32SampleVal))/ (float)INT16_MAX);
}


*/