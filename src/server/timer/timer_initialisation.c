/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	time_initialisation source file
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"
#include "server_function.h"

struct timespec *initialise_timer(void)
{
	struct timespec *timer = malloc(sizeof(*timer));

	if (timer == NULL)
		return (NULL);
	clock_gettime(CLOCK_REALTIME, timer);
	return (timer);
}