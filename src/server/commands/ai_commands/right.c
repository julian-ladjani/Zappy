/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** rigth.c
*/

#include "server_struct.h"

uint8_t srv_cmd_right(__attribute__((unused))server_config_t *server,
	server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	user->orientation += 1;
	if (user->orientation > WEST)
		user->orientation = NORTH;
	dprintf(user->fd, "ok\n");
	user->wait += 7;
	return (0);
}
