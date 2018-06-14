/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	poll_loop source file
*/

#include "server_struct.h"

static void connect_user(server_config_t *server_config,
			server_user_t *user, server_team_t *team)
{
	user->logged_state = ZAPPY_USER_CONNECTED;
	if (team) {
		user->type = ZAPPY_USER_AI;
		list_add_elem_at_pos(team->users, user, LIST_END);
	} else {
		user->type = ZAPPY_USER_GRAPHIC;
	}
}

static void try_to_connect_user(server_config_t *server_config,
				server_user_t *user, cmdparams_t *cmdparams)
{
	list_t *team_list = server_config->teams;
	server_team_t *team;

	while (team_list) {
		team = (server_team_t *)list_get_elem_at_pos(team_list,
								LIST_FIRST);
		if (team && !strcmp(team->name, cmdparams->name))
			connect_user(server_config, user, team);
		team_list = team_list->next;
	}
	if (!strcmp(ZAPPY_GRAPHIC_TEAM_NAME, cmdparams->name))
		connect_user(server_config, user, NULL);
}

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
		try_to_connect_user(server_config, user, cmdparams);
	else if (user->logged_state & ZAPPY_USER_CONNECTED) {
		if (user->type == ZAPPY_USER_AI)
			exec_ai_command(server_config, user, cmdparams);
		if (user->type == ZAPPY_USER_GRAPHIC)
			exec_graphic_command(server_config, user, cmdparams);
	}
	user->commands = list_delete_at_pos(user->commands,
					    LIST_FIRST, &free_arguments);
}
