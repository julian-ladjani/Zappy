/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.c
*/

#include "server_function.h"

static char *get_broadcast_msg(cmdparams_t *cmd)
{
	char *msg;

	if (!cmd || cmd->nb_args < 1) {
		return (NULL);
	}
	msg = strdup(cmd->args[0]);
	for (unsigned int i = 1; i < cmd->nb_args; ++i)
		str_append(msg, cmd->args[i]);
	return (msg);
}

uint8_t srv_cmd_broadcast(server_config_t *server,
				server_user_t *user, cmdparams_t *cmd)
{
	char *msg = get_broadcast_msg(cmd);
	char *graphic_msg;

	if (!msg) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	asprintf(&graphic_msg, "pbc %d %s\n", user->id, msg);
	send_msg_to_all_graphic(server, graphic_msg);
	free(graphic_msg);
	free(msg);
	return (0);
}
