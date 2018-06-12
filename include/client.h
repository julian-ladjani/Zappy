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

typedef struct client_config_s {
	unsigned short port;
	struct pollfd server[1];
	zappy_socket_t *server_socket;
	map_t *map;
} client_config_t;

uint8_t clt_cmd_forward(client_config_t *client, void *params);
uint8_t clt_cmd_right(client_config_t *client, void *params);
uint8_t clt_cmd_left(client_config_t *client, void *params);
uint8_t clt_cmd_look(client_config_t *client, void *params);
uint8_t clt_cmd_inventory(client_config_t *client, void *params);
uint8_t clt_cmd_broadcast(client_config_t *client, void *params);
uint8_t clt_cmd_connect_nbr(client_config_t *client, void *params);
uint8_t clt_cmd_fork(client_config_t *client, void *params);
uint8_t clt_cmd_eject(client_config_t *client, void *params);
uint8_t clt_cmd_take(client_config_t *client, void *params);
uint8_t clt_cmd_set(client_config_t *client, void *params);
uint8_t clt_cmd_incantation(client_config_t *client, void *params);

#endif /* PSU_ZAPPY_2017_CLIENT_H */