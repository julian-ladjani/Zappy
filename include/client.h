/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.h
*/

#ifndef PSU_ZAPPY_2017_CLIENT_H
#define PSU_ZAPPY_2017_CLIENT_H

#include <sys/poll.h>
#include "map.h"
#include "zappy_socket.h"
#include "parser.h"
#include <stdarg.h>

typedef struct client_config_s clt_config_t;

typedef enum sendable_command {
	FORWARD,
	RIGHT,
	LEFT,
	LOOK,
	INVENTORY,
	BROADCAST,
	CONNECT,
	FORK,
	EJECT,
	TAKE,
	SET,
	INCANTATION
} send_cmd_t;

typedef struct request_s {
	send_cmd_t cmd_id;
	char *cmd_name;
	uint8_t  (*sender)(clt_config_t *client, va_list *av);
} request_t;

typedef struct client_socket_s {
	struct pollfd pollfd[1];
	zappy_socket_t *socket;
	char *active_request;
} clt_socket_t;

struct client_config_s {
	map_t *map;
	char *team;
	uint8_t dead;
	clt_socket_t *server;
	request_t send;
};

uint8_t clt_cmd_forward(clt_config_t *client);
uint8_t clt_cmd_right(clt_config_t *client);
uint8_t clt_cmd_left(clt_config_t *client);
uint8_t clt_cmd_look(clt_config_t *client);
uint8_t clt_cmd_inventory(clt_config_t *client);
uint8_t clt_cmd_broadcast(clt_config_t *client, char *str, va_list *);
uint8_t clt_cmd_connect_nbr(clt_config_t *client);
uint8_t clt_cmd_fork(clt_config_t *client);
uint8_t clt_cmd_eject(clt_config_t *client);
uint8_t clt_cmd_take(clt_config_t *client, object_t obj);
uint8_t clt_cmd_set(clt_config_t *client, object_t obj);
uint8_t clt_cmd_incantation(clt_config_t *client);

uint8_t clt_cmd_get_args_forward(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_right(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_left(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_look(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_inventory(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_broadcast(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_connect_nbr(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_fork(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_eject(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_take(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_set(clt_config_t *client, va_list *);
uint8_t clt_cmd_get_args_incantation(clt_config_t *client, va_list *);

void show_help();
int init_server(clt_config_t *client);

#endif /* PSU_ZAPPY_2017_CLIENT_H */