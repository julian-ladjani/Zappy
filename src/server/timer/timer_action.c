/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	timer_action source file
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"
#include "server_const.h"

void timer_add_mili(struct timespec *timer, unsigned long mili)
{
	timer->tv_sec += mili / 1000;
	timer->tv_nsec += (mili - (timer->tv_sec * 1000)) * 1000000;
}

void timer_sup_mili(struct timespec *timer, unsigned long mili)
{
	timer->tv_sec -= mili / 1000;
	timer->tv_nsec -= (mili - (timer->tv_sec * 1000)) * 1000000;
}

unsigned long timer_calc_time_with_frequency(unsigned int frequency,
	unsigned int time_s)
{
	if (frequency == 0)
		return (0);
	return ((time_s * 1000) * (1 / frequency));
}

void timer_set_current_time(struct timespec *timer)
{
	if (timer == NULL)
		return;
	clock_gettime(CLOCK_REALTIME, timer);
}
