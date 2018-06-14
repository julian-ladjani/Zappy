/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** mct.c
*/

#include "server_struct.h"

uint8_t srv_cmd_mct(server_config_t *server, server_user_t *user,
			__attribute__((unused))cmdparams_t *cmd)
{
	char *ressources;

	for (unsigned int y = 0; y < server->map->height; ++y) {
		for (unsigned int x = 0; x < server->map->width; ++x) {
			ressources = tile_to_str_quantity(
				server->map->tiles[y][x]);
			dprintf(user->fd, "bct %u %u %s\n", x, y, ressources);
			if (ressources)
				free(ressources);
		}
	}
	return (0);
}
