/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	poll_loop source file
*/

#include <errno.h>
#include <sys/poll.h>
#include "server_struct.h"
#include "server_function.h"
#include "circbuff.h"

static ssize_t poll_exec_loop(server_config_t *server_config,
	server_user_t *user)
{
	ssize_t nb_read = 0;

	nb_read = user->circular_buffer->recv(user->fd,
		user->circular_buffer, 512);
	if (nb_read > 0) {
		//parse_command(server_config, user);
	}
	return (nb_read);
}

int poll_exec(server_config_t *server_config, int poll_index)
{
	server_user_t *user;

	if (server_config == NULL)
		return (ZAPPY_EXIT_FAILURE);
	user = get_user_by_fd(server_config,
		server_config->poll_fd[poll_index].fd);
	if (user == NULL) {
		close_socket_poll(server_config, poll_index);
		return (ZAPPY_EXIT_FAILURE);
	}
	if (poll_exec_loop(server_config, user) < 0 ||
		user->logged_state == ZAPPY_USER_QUIT) {
		close_socket_poll(server_config, poll_index);
		return (ZAPPY_EXIT_SUCCESS);
	}
	return (ZAPPY_EXIT_SUCCESS);
}

int poll_loop(server_config_t *server_config)
{
	for (int i = 0; i < (int) server_config->nfds; i++) {
		if (server_config->poll_fd[i].revents == 0)
			continue;
		if (server_config->poll_fd[i].revents != POLLIN)
			cleanup_server_exit(server_config,
				ZAPPY_EXIT_FAILURE);
		if (server_config->poll_fd[i].fd ==
			server_config->master->fd)
			poll_accept_client(server_config);
		else
			poll_exec(server_config, i);
	}
	compress_socket_poll(server_config);
	return (ZAPPY_EXIT_SUCCESS);
}
