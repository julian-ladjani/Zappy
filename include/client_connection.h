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

typedef int (* pre_requests_t)(clt_config_t *);

const pre_requests_t pre_requests[4] = {
	prerequest_welcome,
	prerequest_player_id,
	prerequest_map_size,
	NULL
};

#endif /* PSU_ZAPPY_2017_CLIENT_CONNECTION_H */