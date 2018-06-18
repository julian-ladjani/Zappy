/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "server_struct.h"

uint8_t srv_cmd_incantation(server_config_t *server, server_user_t *user,
				__attribute__((unused))cmdparams_t *cmd)
{
	(void)server;
	dprintf(user->fd, "ko\n");
	user->wait += 300;
	return (1);
}
