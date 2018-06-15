/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** set.c
*/

#include "server_function.h"

static int send_set_message(server_config_t *server,
				server_user_t *user, int ressource)
{
	char *msg;

	asprintf(&msg, "pdr %d %d", user->id, ressource);
	send_msg_to_all_graphic(server, msg);
	dprintf(user->fd, "ok\n");
	free(msg);
	return (0);
}

uint8_t srv_cmd_set(server_config_t *server,
			server_user_t *user, cmdparams_t *cmd)
{
	char *ressources[7] = {"food", "linemate", "deraumere", "sibur",
				"mendiane", "phiras", "thystame"};

	if (cmd->nb_args < 1) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	for (int i = FOOD; i <= THYSTAME; ++i) {
		if (!strcasecmp(ressources[i], cmd->args[0])
			&& ((i != FOOD && user->inventory[i] > 0)
			|| (i == FOOD && user->inventory[i] > 125))) {
			server->map->tiles[user->y][user->x][i] += 1;
			user->inventory[i] -= (i == FOOD ? 126 : 1);
			return (send_set_message(server, user, i));
		}
	}
	dprintf(user->fd, "ko\n");
	return (1);
}
