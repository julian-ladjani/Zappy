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
