/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** forward.c
*/

#include "server_struct.h"

uint8_t srv_cmd_forward(server_config_t *server,
			server_user_t *user,
			__attribute__((unused))cmdparams_t *cmd)
{
	switch (user->orientation) {
	case (NORTH):
		user->y = (user->y + 1) % server->map->width;
		break;
	case (EAST):
		user->x = (user->x + 1) % server->map->height;
		break;
	case (SOUTH):
		user->y = user->y == 0 ? server->map->width - 1 : user->y - 1;
		break;
	case (WEST):
		user->x = user->x == 0 ? server->map->height - 1 : user->x - 1;
		break;
	}
	dprintf(user->fd, "ok\n");
	user->wait += 7;
	return (0);
}
