/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	timer_cleanup source file
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"

void cleanup_timer(struct timespec *timer)
{
	free(timer);
}

void cleanup_user_timer(user_timer_t *user_timer)
{
	cleanup_timer(user_timer->first_wait_timer);
	cleanup_timer(user_timer->timer);
	free(user_timer);
}