/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	command_exec.c
*/

#include "server_function.h"

void exec_ai_command(server_config_t *server_config,
			server_user_t *user, cmdparams_t *cmdparams)
{
	(void)server_config;
	(void)user;
	(void)cmdparams;
}

void exec_graphic_command(server_config_t *server_config,
				server_user_t *user, cmdparams_t *cmdparams)
{
	(void)server_config;
	(void)user;
	(void)cmdparams;
}
	
void exec_pending_command(server_config_t *server_config,
				server_user_t *user)
{
	cmdparams_t *cmdparams = (cmdparams_t *)list_get_elem_at_pos(
					user->commands, LIST_FIRST);

	if (user->logged_state & ZAPPY_USER_NOT_CONNECTED)
		try_to_join_team(server_config, user, cmdparams);
	else if (user->logged_state & ZAPPY_USER_CONNECTED) {
		if (user->type == ZAPPY_USER_AI)
			exec_ai_command(server_config, user, cmdparams);
		if (user->type == ZAPPY_USER_GRAPHIC)
			exec_graphic_command(server_config, user, cmdparams);
	}
	user->commands = list_delete_at_pos(user->commands,
					    LIST_FIRST, &free_arguments);
}
