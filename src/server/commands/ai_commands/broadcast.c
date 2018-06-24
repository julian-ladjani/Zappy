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
	for (unsigned int i = 1; i < cmd->nb_args; ++i) {
		msg = str_append(msg, " ");
		msg = str_append(msg, cmd->args[i]);
	}
	return (msg);
}

static void send_broadcast_to_other_ai(server_config_t *server,
	server_user_t *emitter, char *msg)
{
	list_t *user_list = server->users;
	server_user_t *user;
	vec_t pos = {emitter->pos.x, emitter->pos.y};
	vec_t user_pos;

	while (user_list) {
		user = user_list->elem;
		if (user && user != emitter && user->type == ZAPPY_USER_AI) {
			user_pos.x = user->pos.x;
			user_pos.y = user->pos.y;
			dprintf(user->fd, "message %u, %s\n",
				map_rotate_orientation(user->orientation,
					map_get_orientation(
						map_get_dir(server->map,
							user_pos, pos))),
				msg);
		}
		user_list = user_list->next;
	}
}

uint8_t srv_cmd_broadcast(server_config_t *server,
	server_user_t *user, cmdparams_t *cmd)
{
	char *msg = get_broadcast_msg(cmd);
	char *graphic_msg;

	user->wait += 7;
	if (!msg) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	asprintf(&graphic_msg, "pbc %d %s\n", user->id, msg);
	send_msg_to_all_graphic(server, graphic_msg);
	send_broadcast_to_other_ai(server, user, msg);
	dprintf(user->fd, "ok\n");
	free(graphic_msg);
	free(msg);
	return (0);
}
