/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	cleanup source file_dir
*/

#include <unistd.h>
#include "server_struct.h"
#include "server_function.h"

void cleanup_server(server_config_t *server_config)
{
	printf("Info: Cleanup Server\n");
	if (server_config == NULL)
		return;
	if (server_config->users != NULL)
		cleanup_users(server_config->users);
	if (server_config->teams != NULL)
		cleanup_teams(server_config->teams);
	if (server_config->master != NULL)
		cleanup_socket(server_config->master);
	cleanup_socket_poll(server_config->poll_fd);
	free(server_config);
}

void cleanup_server_exit(server_config_t *server_config,
	unsigned int exit_status)
{
	cleanup_server(server_config);
	exit(exit_status);
}