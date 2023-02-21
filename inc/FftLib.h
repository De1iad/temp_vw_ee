/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FftLib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:32:09 by cudoh             #+#    #+#             */
/*   Updated: 2023/02/20 18:34:39 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FFTLIB_H
#define FFTLIB_H
#include <stdio.h>
#include <fftw3.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>


//#define N 9182
#define PI 3.14159265358979323846
#define BYTE (8)


void fft_sample(int8_t *data, int N);
void fft_sample_1d(double *data, int N);
void render_freq_bar(int freq);
void    FFTLIB_Transform(double *dDataOutput, float *fdataInput, int N);
void    FFTLIB_ComputeMagnitude(double *dDataOutput, 
                                fftw_complex *freq, int N);

void    FFTLIB_ShowFreqSpectrum(double *dBufferFreqSpectrum,
                               uint32_t u32SampleSize);

void show_freq_spec(fftw_complex *freq, int N);
/*
void fft_sample__read_chan(double *samples, int8_t *data, \
                                                uint32_t *pu32Idx, \
                                                int N, \
                                                uint32_t u32AudioLength, \
                                                enum eChannel chan);
double fft_sample__read_sample(uint8_t *data, uint32_t *pu32Idx);
*/
#endif