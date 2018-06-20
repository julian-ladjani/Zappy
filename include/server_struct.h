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

typedef struct server_team_s server_team_t;

typedef struct server_user_s {
	int id;
	circbuf_t *circular_buffer;
	user_type_t type;
	user_logged_state_t logged_state;
	int fd;
	server_team_t *team;
	list_t *commands;
	tile_t inventory;
	cardinal_dir_t orientation;
	vec_t pos;
	u_int64_t wait;
	unsigned int level;
} server_user_t;

struct server_team_s {
	char *name;
	list_t *users;
	int slots;
};

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
	char **team_names;
} server_argument_t;

typedef struct server_egg_s {
	vec_t pos;
	server_team_t *team;
	unsigned int id;
	u_int64_t wait;
} server_egg_t;

typedef struct server_config_s {
	server_argument_t *arguments;
	zappy_socket_t *master;
	server_state_t state;
	unsigned short port;
	list_t *users;
	list_t *teams;
	list_t *eggs;
	nfds_t nfds;
	struct pollfd poll_fd[ZAPPY_MAX_CLIENT + 1];
	map_t *map;
	struct timespec *cur_time;
	unsigned int frequency;
} server_config_t;

typedef struct server_command_s {
	char *name;
	uint8_t (*cmd)(server_config_t *, server_user_t *, cmdparams_t *);
} server_command_t;

#endif //PSU_ZAPPY_2017_SERVER_STRUCT_H
