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
