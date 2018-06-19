/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** take.c
*/

#include "server_function.h"

static int send_take_message(server_config_t *server,
	server_user_t *user, int ressource)
{
	char *msg;

	asprintf(&msg, "pgt %d %d", user->id, ressource);
	send_msg_to_all_graphic(server, msg);
	dprintf(user->fd, "ok\n");
	free(msg);
	return (0);
}

uint8_t srv_cmd_take(server_config_t *server,
	server_user_t *user, cmdparams_t *cmd)
{
	if (cmd->nb_args < 1) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	for (int i = FOOD; i <= THYSTAME; ++i) {
		if (!strcasecmp(obj_names[i], cmd->args[0])
			&&
			server->map->tiles[user->pos.y][user->pos.x][i] > 0) {
			server->map->tiles[user->pos.y][user->pos.x][i] -= 1;
			user->inventory[i] += (i == FOOD ? 126 : 1);
			user->wait += 7;
			return ((uint8_t) send_take_message(server, user, i));
		}
	}
	dprintf(user->fd, "ko\n");
	return (1);
}
