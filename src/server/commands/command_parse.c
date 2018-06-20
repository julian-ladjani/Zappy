/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	poll_loop source file
*/

#include "server_struct.h"

static void add_command(server_user_t *user, cmdparams_t *cmdparams)
{
	if (list_size(user->commands) < 10
		|| (user->logged_state & ZAPPY_USER_CONNECTED
		&& user->type == ZAPPY_USER_GRAPHIC))
		user->commands = list_add_elem_at_pos(user->commands,
		cmdparams, LIST_END);
	else
		free_arguments(cmdparams);
}

void parse_command(__attribute__((unused))server_config_t *server_config,
	server_user_t *user)
{
	char *buf = NULL;
	long int sep = circbuf_strstr(user->circular_buffer, "\n");
	cmdparams_t *cmdparams;

	while (sep >= 0) {
		buf = circbuf_nbufferise(user->circular_buffer, sep);
		cmdparams = parse_arguments(buf, " ");
		if (!cmdparams)
			return;
		printf("Connection - %d Send Command %s\n", user->fd,
			cmdparams->name);
		add_command(user, cmdparams);
		free(buf);
		circbuf_free_nspace(user->circular_buffer, sep + 1);
		sep = circbuf_strstr(user->circular_buffer, "\n");
	}
}
