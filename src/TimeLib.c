/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */



#include "../inc/TimeLib.h"


int TIME_CreateTimer(timer_t *xTimerId, struct sigevent *sigEvent)
{
    return (timer_create(CLOCK_REALTIME, sigEvent, xTimerId));
}


//void Sequencer(int id);



int TIME_SetTimer(timer_t *xTimerId, time_t period_ns, int reset)
{
    int flags;
    struct itimerspec timespec_ns = {{0, 0}, {0, 0}};

    flags = 0;      /* the value.it_value is interpreted relative to the clock
                        value at the time of the call to timer_settime()
                    */
    
    
     /* arm the interval timer */
    timespec_ns.it_interval.tv_sec = 
            ((reset == TIME_TIMER_PERIODIC)? (period_ns / NSEC_PER_SEC) : 0);
    timespec_ns.it_interval.tv_nsec =
             ((reset == TIME_TIMER_PERIODIC)? (period_ns % NSEC_PER_SEC) : 0);
    timespec_ns.it_value.tv_sec = (period_ns / NSEC_PER_SEC);
    timespec_ns.it_value.tv_nsec = (period_ns % NSEC_PER_SEC);
    //printf("time set value : %ld\n" , timespec_ns.it_interval.tv_sec);
    
    timer_settime(*xTimerId, flags, &timespec_ns, NULL);
    return (-1);
}



int TIME_DisableTimer(timer_t *xTimerId)
{
    int flags;
    struct itimerspec timespec_ns;

    flags = 0;
    
    // disable interval timer by setting all value to zero
    timespec_ns.it_interval.tv_sec = 0;
    timespec_ns.it_interval.tv_nsec = 0;
    timespec_ns.it_value.tv_sec = 0;
    timespec_ns.it_value.tv_nsec = 0;
    
    return (timer_settime(*xTimerId, flags, &timespec_ns, NULL));
}




/* set up to signal SIGALRM if timer expires */

//  signal(SIGALRM, (void(*)()) Sequencer);






double  TIME_ConvToSec(struct timespec *pTime)
{
    return ((double)(pTime->tv_sec) + (((double)pTime->tv_nsec)/TIME_F_NSEC_PER_SEC));
}



double  TIME_ConvToMsec(struct timespec *pTime)
{
    return ((double)(pTime->tv_sec) + (((double)pTime->tv_nsec)/TIME_F_MSEC_PER_SEC));
}




double  TIME_ConvToUsec(struct timespec *pTime)
{
    return ((double)(pTime->tv_sec) + (((double)pTime->tv_nsec)/TIME_F_USEC_PER_SEC));
}



double  TIME_ConvToNsec(struct timespec *pTime)
{
    return ((double)((pTime->tv_sec) * TIME_F_NSEC_PER_SEC) + (((double)pTime->tv_nsec)));
}



double  TIME_ConvToUnit(struct timespec *pTime, t_timeunits unit)
{
    double dTime = 0.0;

    switch(unit)
    {
        case unit_sec:
            dTime = TIME_ConvToSec(pTime);
            break ;
        case unit_msec:
            dTime = TIME_ConvToMsec(pTime);
            break ;
        case unit_usec:
            dTime = TIME_ConvToUsec(pTime);
            break ;
        default:
            dTime = TIME_ConvToNsec(pTime);
            break ;
    }
    return (dTime);
}




double TIME_GetTime(t_timeunits unit)
{
    struct timespec stTimeCurrent = {0, 0};

    clock_gettime(CLOCK_MONOTONIC_RAW, &stTimeCurrent);
    return (TIME_ConvToUnit(&stTimeCurrent, unit));
}




double TIME_GetRuntime(struct timespec *pstTimeStart, t_timeunits unit)
{
    double dTimeStart = TIME_ConvToUnit(pstTimeStart, unit);
    double dTimeNow = TIME_GetTime(unit);
    return (dTimeNow - dTimeStart);
}


/*
clock_gettime(MY_CLOCK_TYPE, &current_time_val); current_realtime=realtime(&current_time_val);
        syslog(LOG_CRIT, "S4 5 Hz on core %d for release %llu @ sec=%6.9lf\n", sched_getcpu(), S4Cnt, current_realtime-start_realtime);
*/

