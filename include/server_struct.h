/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_struct header file_dir
*/

#ifndef PSU_ZAPPY_2017_SERVER_STRUCT_H
#define PSU_ZAPPY_2017_SERVER_STRUCT_H

#define _GNU_SOURCE

#include <sys/poll.h>
#include <ctype.h>
#include <stdio.h>
#include <netinet/in.h>
#include "circbuff.h"
#include "linked_list.h"
#include "server_const.h"
#include "zappy_socket.h"

typedef struct server_user_s {
	char *name;
	char *password;
	char *nick;
	circbuf_t *circular_buffer;
	user_logged_state_t logged_state;
	int fd;
	list_t *channels;
} server_user_t;

typedef struct server_team_s {
	char *name;
	list_t *users;
} server_team_t;

typedef union server_port_u {
	uint8_t port_part[2];
	in_port_t port;
} server_port_t;

typedef struct server_config_s {
	unsigned short port;
	zappy_socket_t *master;
	server_state_t state;
	list_t *users;
	list_t *channels;
	nfds_t nfds;
	struct pollfd poll_fd[ZAPPY_MAX_CLIENT + 1];
} server_config_t;

#endif //PSU_ZAPPY_2017_SERVER_STRUCT_H
