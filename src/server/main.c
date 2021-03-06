/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	main source file_dir
*/

#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"
#include "server_function.h"
#include "server_const.h"
#include "ressources_str.h"

static server_config_t *initialisation(server_argument_t *server_argument)
{
	server_config_t *server_config;

	server_config = initialise_server(server_argument);
	if (server_config == NULL)
		return (NULL);
	server_config->users = NULL;
	server_config->master = initialise_socket(
		server_config->arguments->port);
	if (server_config->master == NULL ||
		initialise_socket_poll(server_config) == ZAPPY_EXIT_FAILURE) {
		cleanup_server(server_config);
		return (NULL);
	}
	return (server_config);
}

int main(int ac, char **av)
{
	server_config_t *server_config;
	server_argument_t *server_argument;

	if (ac < 2) {
		printf("Error: Too few arguments\n");
		exit(ZAPPY_EXIT_FAILURE);
	}
	server_argument = parse_server_argument(ac, av);
	if (server_argument == NULL)
		exit(ZAPPY_EXIT_FAILURE);
	server_config = initialisation(server_argument);
	if (server_config == NULL)
		exit(ZAPPY_EXIT_FAILURE);
	server_main_loop(server_config);
	cleanup_server_exit(server_config, ZAPPY_EXIT_SUCCESS);
}
