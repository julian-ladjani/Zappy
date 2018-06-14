/*
1;5002;0c** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	poll_loop source file
*/

#include "server_struct.h"

void parse_command(__attribute__((unused))server_config_t *server_config,
		   server_user_t *user)
{
	char *buf = NULL;
        long int sep = circbuf_strstr(user->circular_buffer, "\r\n");
	cmdparams_t *cmdparams;

	while (sep >= 0) {
		buf = circbuf_nbufferise(user->circular_buffer, sep);
		cmdparams = parse_arguments(buf, " ");
		if (!cmdparams)
                        return;
		if (list_size(user->commands) < 10
			|| (user->logged_state & ZAPPY_USER_CONNECTED
			&& user->type == ZAPPY_USER_GRAPHIC))
			list_add_elem_at_pos(user->commands,
						cmdparams, LIST_END);
		else
			free_arguments(cmdparams);
	        circbuf_free_nspace(user->circular_buffer, sep + 2);
		sep = circbuf_strstr(user->circular_buffer, "\r\n");
	}
}
