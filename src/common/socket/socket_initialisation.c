/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	initialise_socket source file
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "zappy_socket.h"
#include "server_struct.h"
#include "server_const.h"

static zappy_socket_t *initialisation_error(zappy_socket_t *master)
{
	printf("Error: Cannot Initialise Socket\n");
	free(master);
	return (NULL);
}

static struct sockaddr_in init_sockaddr(int port)
{
	struct sockaddr_in s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	return (s_in);
}

static int bind_socket_to_port(zappy_socket_t *master, int port)
{
	struct sockaddr_in s_in;
	int true = 1;
	int ret;

	if (port != 0)
		printf("Info: Bind port %d to socket\n", port);
	else
		printf("Info: Bind random port to socket\n");
	s_in = init_sockaddr(port);
	setsockopt(master->fd, SOL_SOCKET, SO_REUSEADDR, &true,
		sizeof(int));
	ret = bind(master->fd, (const struct sockaddr *) &s_in, sizeof(s_in));
	if (ret == -1) {
		printf("Error: Cannot Bind Port\n");
		close(master->fd);
		return (ZAPPY_EXIT_FAILURE);
	}
	master->port = s_in.sin_port;
	master->ip = inet_ntoa(s_in.sin_addr);
	return (ZAPPY_EXIT_SUCCESS);
}

static int set_socket_non_blocking(int fd)
{
	int true = 1;

	if (ioctl(fd, FIONBIO, (char *) &true) < 0) {
		printf("Error: Cannot Set Socket No Blocking\n");
		return (ZAPPY_EXIT_FAILURE);
	}
	return (ZAPPY_EXIT_SUCCESS);
}

zappy_socket_t *initialise_socket(int port)
{
	struct protoent *pe = getprotobyname("TCP");
	zappy_socket_t *master = malloc(sizeof(zappy_socket_t));

	printf("Info: Initialise Socket\n");
	if (master == NULL)
		return (NULL);
	if (pe == NULL) {
		printf("Error: Cannot Get Proto By Name TCP\n");
		return (initialisation_error(master));
	}
	master->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (master->fd == -1) {
		printf("Error: Cannot Initialise Socket FD\n");
		return (initialisation_error(master));
	}
	if (set_socket_non_blocking(master->fd) == ZAPPY_EXIT_FAILURE)
		return (initialisation_error(master));
	if (bind_socket_to_port(master, port) == ZAPPY_EXIT_FAILURE)
		return (initialisation_error(master));
	return (master);
}