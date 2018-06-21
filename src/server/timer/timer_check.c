/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	timer_check source file
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"
#include "server_const.h"

int timer_is_ended(struct timespec *timer, struct timespec *cur_time)
{
	if (timer->tv_sec == cur_time->tv_sec) {
		if (timer->tv_nsec < cur_time->tv_nsec)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	if (timer->tv_sec < cur_time->tv_sec)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

unsigned long timer_diff_mili(struct timespec *start,
	struct timespec *end)
{
	return ((unsigned long)
		((((double) end->tv_sec + 1.0e-9 * end->tv_nsec) -
			((double) start->tv_sec + 1.0e-9 * start->tv_nsec))
			* 1000));
}

unsigned int timer_get_nb_tick(unsigned long mili, unsigned int frequency)
{
	double hetz = (double) 1 / frequency;

	if ((unsigned int) (hetz * 1000) == 0)
		return (mili);
	return ((unsigned int) (mili / (hetz * 1000)));
}

unsigned long timer_get_tick_time_mili(unsigned int frequency)
{
	return ((unsigned long) (((((double) 1 / ((frequency))))
		* 1000)));
}

unsigned long timer_get_remain_time_mili(unsigned long mili,
	unsigned int frequency)
{
	unsigned long tick_time = timer_get_tick_time_mili(frequency);

	return (tick_time - (mili % tick_time));
}