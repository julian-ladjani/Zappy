/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	command_exec.c
*/

#include "server_function.h"

const server_command_t GRAPHIC_COMMANDS[10] = {
	{"msz", &srv_cmd_msz},
	{"bct", &srv_cmd_bct},
	{"mct", &srv_cmd_mct},
	{"tna", &srv_cmd_tna},
	{"ppo", &srv_cmd_ppo},
	{"plv", &srv_cmd_plv},
	{"pin", &srv_cmd_pin},
	{"sgt", &srv_cmd_sgt},
	{"sst", &srv_cmd_sst},
	{NULL, NULL}
};

void exec_graphic_command(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams)
{
	for (int i = 0; GRAPHIC_COMMANDS[i].name; ++i) {
		if (!strcasecmp(GRAPHIC_COMMANDS[i].name, cmdparams->name)) {
			GRAPHIC_COMMANDS[i].cmd(server_config, user, cmdparams);
			return;
		}
	}
	dprintf(user->fd, "suc\n");
}
