/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_timer_action source file
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"
#include "server_const.h"
#include "server_function.h"

void user_timer_set_wait(user_timer_t *timer,
	server_config_t *server, unsigned int time_s)
{
	if (timer == NULL)
		return;
	timer->first_wait_timer->tv_sec = server->cur_time->tv_sec;
	timer->first_wait_timer->tv_nsec = server->cur_time->tv_nsec;
	timer->timer->tv_sec = server->cur_time->tv_sec;
	timer->timer->tv_nsec = server->cur_time->tv_nsec;
	timer->wait = time_s;
	timer_add_mili(timer->timer, timer_calc_time_with_frequency(
		server->frequency, time_s));
}

void user_timer_sup_wait(user_timer_t *timer,
	server_config_t *server, unsigned int time_s)
{
	if (timer == NULL)
		return;
	timer->first_wait_timer->tv_sec = server->cur_time->tv_sec;
	timer->first_wait_timer->tv_nsec = server->cur_time->tv_nsec;
	timer->timer->tv_sec = server->cur_time->tv_sec;
	timer->timer->tv_nsec = server->cur_time->tv_nsec;
	timer->wait -= time_s;
	timer_sup_mili(timer->timer, timer_calc_time_with_frequency(
		server->frequency, time_s));
}

void user_timer_add_wait(user_timer_t *timer,
	server_config_t *server, unsigned int time_s)
{
	if (timer == NULL)
		return;
	if (timer->wait == 0)
		return (user_timer_set_wait(timer, server, time_s));
	timer->wait += time_s;
	timer_add_mili(timer->timer, timer_calc_time_with_frequency(
		server->frequency, time_s));
}
