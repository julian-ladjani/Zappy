/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_timer source file
*/

#include "server_function.h"
#include "server_struct.h"

void server_timer_start(server_config_t *server)
{
	timer_set_current_time(server->start_loop_time);
}

static void server_timer_end_loop(server_config_t *server,
	unsigned int nb_tick)
{
	user_action_sup_wait(server, nb_tick);
	user_action_egg_sup_wait(server, nb_tick);
}

void server_timer_end(server_config_t *server)
{
	unsigned long time_diff;
	unsigned long remain_time;
	unsigned long frequency_time;
	unsigned int nb_tick;

	timer_set_current_time(server->end_loop_time);
	time_diff = timer_diff_mili(server->start_loop_time,
		server->end_loop_time);
	nb_tick = timer_get_nb_tick(time_diff, server->frequency);
	remain_time = timer_get_remain_time_mili(time_diff,
		server->frequency);
	frequency_time = timer_get_tick_time_mili(server->frequency);
	if (remain_time != frequency_time || nb_tick == 0)
		nb_tick++;
	usleep((useconds_t) remain_time * 1000);
	server_timer_start(server);
	server_timer_end_loop(server, nb_tick);
}