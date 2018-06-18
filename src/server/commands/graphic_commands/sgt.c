/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sgt.c
*/

#include "server_struct.h"

uint8_t srv_cmd_sgt(server_config_t *server, server_user_t *user,
		    __attribute__((unused))cmdparams_t *cmd)
{
	dprintf(user->fd, "sgt %u\n", server->frequency);
	return (0);
}
