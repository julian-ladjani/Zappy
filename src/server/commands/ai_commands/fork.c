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
	char *msg;

	asprintf(&msg, "pfk %d\nenw %d %d %u %u\n", user->id, -1,
		user->id, user->x, user->y);
	send_msg_to_all_graphic(server, msg);
	dprintf(user->fd, "ok\n");
	user->wait += 42;
	free(msg);
	return (1);
}
