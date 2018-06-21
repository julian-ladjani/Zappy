/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** bct.c
*/

#include "server_struct.h"

uint8_t srv_cmd_bct(server_config_t *server,
	server_user_t *user, cmdparams_t *cmd)
{
	int x;
	int y;
	char *ressources;

	if (cmd->nb_args < 2) {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	x = atoi(cmd->args[0]);
	y = atoi(cmd->args[0]);
	if (x < 0 || y < 0 || x >= (int)server->map->width
		|| y >= (int)server->map->height) {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	ressources = tile_to_str_quantity(map_get_tile(server->map, x, y));
	dprintf(user->fd, "bct %d %d %s\n", x, y, ressources);
	free(ressources);
	return (0);
}
