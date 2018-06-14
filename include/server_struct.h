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
#include "parser.h"
#include "map.h"

typedef struct server_user_s {
	int id;
	char *name;
	char *password;
	char *nick;
	circbuf_t *circular_buffer;
	user_type_t type;
	user_logged_state_t logged_state;
	int fd;
	list_t *teams;
	list_t *commands;
	tile_t inventory;
	cardinal_dir orientation;
	unsigned int x;
	unsigned int y;
	unsigned int level;
} server_user_t;

typedef struct server_team_s {
	char *name;
	list_t *users;
} server_team_t;

typedef union server_port_u {
	uint8_t port_part[2];
	in_port_t port;
} server_port_t;

typedef struct server_argument_s {
	unsigned short port;
	unsigned int width;
	unsigned int height;
	size_t client_nb;
	unsigned int frequency;
} server_argument_t;

typedef struct server_config_s {
	server_argument_t *arguments;
	zappy_socket_t *master;
	server_state_t state;
	list_t *users;
	list_t *teams;
	nfds_t nfds;
	struct pollfd poll_fd[ZAPPY_MAX_CLIENT + 1];
	map_t *map;
} server_config_t;

#endif //PSU_ZAPPY_2017_SERVER_STRUCT_H
