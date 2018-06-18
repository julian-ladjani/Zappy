/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sst.c
*/

#include "server_function.h"

uint8_t srv_cmd_sst(server_config_t *server,
	server_user_t *user, cmdparams_t *cmd)
{
	char *msg;
	unsigned int frequency;

	if (cmd->nb_args < 1) {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	frequency = (uint8_t) atoi(cmd->args[0]);
	if (frequency <= 0) {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	server->frequency = frequency;
	asprintf(&msg, "sst %u\n", frequency);
	send_msg_to_all_graphic(server, msg);
	free(msg);
	return (0);
}
