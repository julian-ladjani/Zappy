/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tna.c
*/

#include "server_struct.h"

uint8_t srv_cmd_tna(server_config_t *server, server_user_t *user,
		    __attribute__((unused))cmdparams_t *cmd)
{
	list_t *team_list = server->teams;
	server_team_t *team;

	while (team_list) {
		team = team_list->elem;
		if (team)
			dprintf(user->fd, "tna %s\n", team->name);
		team_list = team_list->next;
	}
	return (0);
}
