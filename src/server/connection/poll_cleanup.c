/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** 	poll_cleanup source file
*/

#include <poll.h>
#include "server_struct.h"
#include "server_const.h"
#include "server_function.h"

void cleanup_socket_poll(struct pollfd *poll_fd)
{
	for (int i = 0; i <= MYIRC_MAX_CLIENT; i++) {
		if (poll_fd->fd > 0)
			close(poll_fd->fd);
	}
}

void compress_socket_poll(server_config_t *server_config)
{
	for (int i = 0; i < (int) server_config->nfds; i++) {
		if (server_config->poll_fd[i].fd == -1) {
			for (int j = i; j < (int) server_config->nfds; j++) {
				server_config->poll_fd[j].fd =
					server_config->poll_fd[j + 1].fd;
			}
			i--;
			server_config->nfds--;
		}
	}
}

void close_socket_poll(server_config_t *server_config, int index)
{
	list_t *user = list_get_elem_by_search(server_config->users,
		&(server_config->poll_fd[index].fd), user_fd_search_criteria);

	if (user != NULL && user->elem != NULL &&
		((server_user_t *) user->elem)->logged_state !=
			MYIRC_USER_QUIT)
		user_quit(server_config, user->elem, "Connection Closed");
	printf("A Client Left Server - %d\n",
		server_config->poll_fd[index].fd);
	server_config->users = list_delete_elem(user, cleanup_user_list_elem);
	if (server_config->poll_fd[index].fd != -1)
		close(server_config->poll_fd[index].fd);
	server_config->poll_fd[index].fd = -1;
}