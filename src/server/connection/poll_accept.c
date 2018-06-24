/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	poll_accept source file
*/

#include <errno.h>
#include <sys/poll.h>
#include "server_struct.h"
#include "server_function.h"

static void accept_client(server_config_t *server_config, int fd)
{
	server_user_t *server_user = initialise_server_user(fd);

	if (server_user == NULL) {
		printf("Error when accept incoming connection - %d\n", fd);
		close(fd);
		return;
	}
	dprintf(fd, "WELCOME\n");
	printf("New incoming connection - %d\n", fd);
	server_config->poll_fd[server_config->nfds].fd = fd;
	server_config->poll_fd[server_config->nfds].events = POLLIN;
	server_config->users = list_add_elem_at_pos_releasably(
		server_config->users, server_user, LIST_FIRST,
		LIST_RELEASABLE);
	server_config->nfds++;
}

void poll_accept_client(server_config_t *server_config)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size = sizeof(s_in_client);
	int client_fd;

	do {
		client_fd = accept(server_config->master->fd,
			(struct sockaddr *) &s_in_client, &s_in_size);
		if (client_fd == -1 && errno != EWOULDBLOCK) {
			printf("Error: When Accept Incoming Connection\n");
		} else if (client_fd != -1)
			accept_client(server_config, client_fd);
	} while (client_fd != -1);
}
