/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** fork.c
*/

#include "server_struct.h"

uint8_t srv_cmd_fork(server_config_t *server, server_user_t *user,
			__attribute__((unused))cmdparams_t *cmd)
{
	(void)server;
	dprintf(user->fd, "ko\n");
	user->wait += 42;
	return (1);
}
