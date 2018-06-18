/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** forward.c
*/

#include "server_struct.h"

static void forward_user(server_config_t *server, server_user_t *user)
{
	switch (user->orientation) {
		case (NORTH):
			user->pos.y = map_get_abs(user->pos.y + 1,
				server->map->height);
			break;
		case (EAST):
			user->pos.x = map_get_abs(user->pos.x + 1,
				server->map->width);
			break;
		case (SOUTH):
			user->pos.y = map_get_abs(user->pos.y - 1,
				server->map->height);
			break;
		case (WEST):
			user->pos.x = map_get_abs(user->pos.x - 1,
				server->map->width);
			break;
	}
}

uint8_t srv_cmd_forward(server_config_t *server,
	server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	forward_user(server, user);
	dprintf(user->fd, "ok\n");
	user->wait += 7;
	return (0);
}
