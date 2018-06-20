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

user_timer_t *initialise_user_timer(void)
{
	user_timer_t *user_timer = malloc(sizeof(user_timer_t));

	if (user_timer == NULL)
		return (NULL);
	user_timer->wait = 0;
	user_timer->timer = initialise_timer();
	user_timer->first_wait_timer = initialise_timer();
	if (user_timer->timer != NULL || user_timer->first_wait_timer != NULL)
		return (user_timer);
	cleanup_user_timer(user_timer);
	return (NULL);
}