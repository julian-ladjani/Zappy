/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	poll_initialisation source file
*/

#include <poll.h>
#include "server_struct.h"
#include "server_const.h"

int initialise_socket_poll(server_config_t *server_config)
{
	memset(server_config->poll_fd, 0, sizeof(server_config->poll_fd));
	server_config->poll_fd[0].fd = server_config->master->fd;
	server_config->poll_fd[0].events = POLLIN;
	server_config->nfds = 1;
	return (ZAPPY_EXIT_SUCCESS);
}