/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** connect_nbr.c
*/

#include "server_function.h"

uint8_t srv_cmd_connect_nbr(server_config_t *server, server_user_t *user,
				__attribute__((unused))cmdparams_t *cmd)
{
	dprintf(user->fd, "%d\n",
		get_team_free_slots(find_team_by_user(server, user)));
	return (0);
}
