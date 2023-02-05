/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fft_sample.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:32:09 by cudoh             #+#    #+#             */
/*   Updated: 2023/02/05 09:59:06 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FFT_SAMPLE_H
#define FFT_SAMPLE_H
#include <stdio.h>
#include <fftw3.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>


//#define N 9182
#define PI 3.14159265358979323846

void fft_sample(int8_t *data, int N);
void fft_sample_1d(double *data, int N);
void render_freq_bar(int freq);
void show_freq_spec(fftw_complex *freq, int N);
void fft_sample__conv_left_chan()
#endif