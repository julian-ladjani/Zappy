/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	global_initialisation source file_dir
*/

#include <unistd.h>
#include <stdio.h>
#include "server_function.h"
#include "server_struct.h"
#include "server_const.h"
#include "map.h"

static server_config_t *initialise_server_configuration(
	server_argument_t *server_argument)
{
	server_config_t *server_config = malloc(sizeof(server_config_t));

	printf("Info: Initialise Server Configuration\n");
	if (server_config == NULL) {
		printf("Error: Server Configuration Initialisation Problem\n");
		return (NULL);
	}
	server_config->users = NULL;
	server_config->master = NULL;
	server_config->arguments = server_argument;
	server_config->teams = NULL;
	server_config->map = NULL;
	server_config->frequency = server_argument->frequency;
	server_config->eggs = NULL;
	server_config->state = ZAPPY_SERVER_STOP;
	return (server_config);
}

server_config_t *initialise_server(server_argument_t *server_argument)
{
	server_config_t *server_config;

	if (server_argument->port < 1) {
		printf("Error: Wrong port\n");
		return (NULL);
	}
	server_config = initialise_server_configuration(server_argument);
	if (server_config == NULL)
		return (NULL);
	server_config->map = map_create
		(server_argument->width, server_argument->height, 1);
	server_config->start_loop_time = initialise_timer();
	server_config->end_loop_time = initialise_timer();
	server_config->teams = initialise_server_teams(server_config);
	memset(server_config->poll_fd, 0, sizeof(server_config->poll_fd));
	return (server_config);
}
