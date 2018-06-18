/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	command_exec.c
*/

#include "server_function.h"

static void exec_ai_command(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams)
{
	dprintf(user->fd, "ko\n");
	(void) server_config;
	(void) cmdparams;
}

static void exec_graphic_command(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams)
{
	dprintf(user->fd, "suc\n");
	(void) server_config;
	(void) cmdparams;
}

static void exec_client_command(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams)
{

	if (user->logged_state & ZAPPY_USER_NOT_CONNECTED)
		try_to_join_team(server_config, user, cmdparams);
	else if (user->logged_state & ZAPPY_USER_CONNECTED) {
		if (user->type == ZAPPY_USER_AI)
			exec_ai_command(server_config, user, cmdparams);
		if (user->type == ZAPPY_USER_GRAPHIC)
			exec_graphic_command(server_config, user, cmdparams);
	}
}

static void exec_user_pending_command(server_config_t *server_config,
	server_user_t *user)
{
	cmdparams_t *cmdparams;

	while (user->commands) {
		cmdparams = user->commands->elem;
		if (cmdparams)
			exec_client_command(server_config, user, cmdparams);
		user->commands = list_delete_at_pos(user->commands,
			LIST_FIRST, &free_arguments);
	}
}

void exec_pending_command(server_config_t *server_config)
{
	list_t *user_list = server_config->users;
	server_user_t *user;

	while (user_list) {
		user = user_list->elem;
		exec_user_pending_command(server_config, user);
		user_list = user_list->next;
	}
}
