/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client_connection.h
*/

#ifndef PSU_ZAPPY_2017_CLIENT_CONNECTION_H
#define PSU_ZAPPY_2017_CLIENT_CONNECTION_H

#include <stdint.h>
#include "client.h"

const clt_func_t pre_requests[4] = {
	prerequest_welcome,
	prerequest_player_id,
	prerequest_map_size,
	NULL
};

typedef struct launcher_s
{
	char *flag;
	clt_func_t request;
} launcher_t;

const launcher_t srv_requests[3] = {
	{"dead", srvrequest_dead},
	{"message ", srvrequest_message},
	{NULL, NULL}
};

#endif /* PSU_ZAPPY_2017_CLIENT_CONNECTION_H */