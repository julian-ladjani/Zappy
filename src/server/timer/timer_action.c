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
	timer->tv_sec = mili / 1000;
	timer->tv_nsec = (mili - (timer->tv_sec * 1000)) * 1000000;
}

unsigned long timer_calc_time_with_frequency(unsigned int frequency,
	unsigned int time_s)
{
	if (frequency == 0)
		return (0);
	return ((time_s * 1000) * (1 / frequency));
}

int timer_is_ended(struct timespec *timer)
{

}

void timer_set_wait(struct timespec *timer, unsigned int frequency,
	unsigned int time_s)
{
	if (timer == NULL)
		return;
	clock_gettime(CLOCK_REALTIME, timer);
	timer_add_mili(timer, timer_calc_time_with_frequency(frequency,
		time_s));
}