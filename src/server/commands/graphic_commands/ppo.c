/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ppo.c
*/

#include "server_function.h"

uint8_t srv_cmd_ppo(server_config_t *server,
	server_user_t *user, cmdparams_t *cmd)
{
	server_user_t *player;

	if (cmd->nb_args < 1 || cmd->args[0][0] != '#') {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	player = find_user_by_id(server, atoi(cmd->args[0] + 1));
	if (!player) {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	dprintf(user->fd, "ppo %d %lu %lu %d\n", player->id, player->pos.x,
		player->pos.y, player->orientation);
	return (0);
}
