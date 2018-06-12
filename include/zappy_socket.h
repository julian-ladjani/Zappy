/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	socket header file
*/

#ifndef PSU_ZAPPY_2017_SOCKET_H
#define PSU_ZAPPY_2017_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct zappy_socket_s {
	int fd;
	in_port_t port;
	char *ip;
} zappy_socket_t;

void cleanup_socket(zappy_socket_t *master);
zappy_socket_t *initialise_socket(int port);

#endif //PSU_ZAPPY_2017_SOCKET_H
