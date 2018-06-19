/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
**	command_exec.c
*/

#include "server_function.h"

const server_command_t AI_COMMANDS[13] = {
	{"forward", &srv_cmd_forward},
	{"right", &srv_cmd_right},
	{"left", &srv_cmd_left},
	{"look", &srv_cmd_look},
	{"inventory", &srv_cmd_inventory},
	{"broadcast", &srv_cmd_broadcast},
	{"connect_nbr", &srv_cmd_connect_nbr},
	{"fork", &srv_cmd_fork},
	{"eject", &srv_cmd_eject},
	{"take", &srv_cmd_take},
	{"set", &srv_cmd_set},
	{"incantation", &srv_cmd_incantation},
	{NULL, NULL}
};

void exec_ai_command(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams)
{
	for (int i = 0; AI_COMMANDS[i].name; ++i) {
		if (!strcasecmp(AI_COMMANDS[i].name, cmdparams->name)) {
			AI_COMMANDS[i].cmd(server_config, user, cmdparams);
			return;
		}
	}
	dprintf(user->fd, "ko\n");
}
