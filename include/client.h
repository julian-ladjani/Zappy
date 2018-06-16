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
#include "circbuff.h"
#include "linked_list.h"
#include <stdarg.h>

#define ZAPPY_EXIT_FAILURE (2)
#define ZAPPY_EXIT_NOTHING (0)
#define ZAPPY_EXIT_SUCCESS (1)

#define ZAPPY_CLT_DEAD (1)
#define ZAPPY_CLT_READY (2)
#define ZAPPY_CLT_WAITING (0)

#define ZAPPY_IS_KO(s) (strcmp("ko", s) == 0)
#define ZAPPY_IS_OK(s) (strcmp("ok", s) == 0)

typedef struct client_config_s clt_config_t;

typedef struct client_parameters_s {
	int port;
	char *machine;
	char *team;
} clt_params_t;

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
	uint8_t (*sender)(clt_config_t *client, va_list *av);
	uint8_t (*receiver)(clt_config_t *client);
} request_t;

typedef struct client_socket_s {
	struct pollfd pollfd[1];
	zappy_socket_t *socket;
	circbuf_t *buf;
	char *active_request;
	char *response_request;
	list_t *broadcasts_queue;
} clt_socket_t;

struct client_config_s {
	char *team;
	int id;
	map_t *map;
	int status;
	clt_socket_t *server;
	request_t send;
};

int prerequest_welcome(clt_config_t *client);
int prerequest_map_size(clt_config_t *client);
int prerequest_player_id(clt_config_t *client);

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

void show_help_client(void);
int init_server(clt_config_t *client);
int handle_poll(clt_config_t *client);
void launch_ai(clt_config_t *clt);
clt_params_t *client_parse_arguments(int ac, char **av);

void send_active_request(clt_config_t *client, char *msg, ...);
void vsend_active_request(clt_config_t *client, char *msg, va_list *av);
int send_request(send_cmd_t request_id, clt_config_t *client, ...);

#endif /* PSU_ZAPPY_2017_CLIENT_H */