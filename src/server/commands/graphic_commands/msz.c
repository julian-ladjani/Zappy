/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** msz.c
*/

#include "server_struct.h"

uint8_t srv_cmd_msz(server_config_t *server, server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	dprintf(user->fd, "msz %lu %lu\n", server->map->width,
		server->map->height);
	return (0);
}
