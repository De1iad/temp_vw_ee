/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fft_sample.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:28:51 by cudoh             #+#    #+#             */
/*   Updated: 2023/02/05 09:31:05 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fft_sample.h"


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



void fft_sample_1d(double *data, int N)
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
        in[i][0] = data[i];
        in[i][1] = 0.0;
    }

    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    /*
    for (i = 0; i < N; i++)
    {
        printf("%d %f\n", i, sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]));
    }
    */
    show_freq_spec(out, N);
    
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);
    return ;
}



void render_freq_bar(int freq)
{
    for (int x = 0; x < freq; x++)
    {
        write(1, "|", 1);
    }
    write(1, "\n", 1);
}



void show_freq_spec(fftw_complex *freq, int N)
{
    double magnitude = 0.0;
    
    for (int x = 0; x < N; x++)
    {
        magnitude = sqrt(freq[x][0] * freq[x][0] + freq[x][1] * freq[x][1]);
        render_freq_bar((int)magnitude);
    }
}