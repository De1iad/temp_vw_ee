
/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#ifndef TIMELIB_H
# define TIMELIB_H
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <bits/types.h> 

#define USEC_PER_SEC 1000000    // CONVERT 1SEC TO USEC
#define NSEC_PER_SEC 1000000000 // CONVERT 1SEC TO NSEC
#define TIME_F_NSEC_PER_SEC 1000000000.0f // CONVERT 1SEC TO NSEC
#define TIME_F_MSEC_PER_SEC 1000000.0f    // CONVERT 1SEC TO MSEC
#define TIME_F_USEC_PER_SEC 1000.0f       // CONVERT 1SEC TO USEC
#define TIME_PERIOD 1000000 //usec
#define TIME_TIMER_PERIODIC 1
#define TIME_TIMER_ONCE 0
//#define _POSIX_C_SOURCE = 199309L


typedef struct timespec t_timespec_ns;
//typedef struct timeval t_timespec_us;

typedef enum e_timeunits
{
    unit_sec,
    unit_msec,
    unit_usec,
    unit_nsec
}   t_timeunits;

int     TIME_CreateTimer(timer_t *xTimerId, struct sigevent *sigEvent);
int     TIME_SetTimer(timer_t *xTimerId, time_t period_ns, int reset);
int     TIME_DisableTimer(timer_t *xTimerId);
double  TIME_ConvToSec(struct timespec *pTime);
double  TIME_ConvToMsec(struct timespec *pTime);
double  TIME_ConvToUsec(struct timespec *pTime);
double  TIME_ConvToNsec(struct timespec *pTime);
double  TIME_ConvToUnit(struct timespec *pTime, t_timeunits unit);
double  TIME_GetTime(t_timeunits unit);
double  TIME_GetRuntime(struct timespec *pstTimeStart, t_timeunits unit);

#endif