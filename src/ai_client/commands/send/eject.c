/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eject.c
*/

#include "client.h"

int srvrequest_eject(clt_config_t *client)
{
	int i = atoi(client->server->response_request + 7);
	vec_t vec;

	vec = get_tile_from_dir(client->specs->x, client->specs->y,
				(i + 3) % 8 + 1, client->specs->orientation);
	client->specs->x = (size_t) vec.x;
	client->specs->y = (size_t) vec.y;
	return (ZAPPY_EXIT_FAILURE);
}

static uint8_t clt_cmd_eject_receiver(clt_config_t *client)
{
	return (1);
}

static uint8_t clt_cmd_eject(clt_config_t *client)
{
	dprintf(client->server->pollfd->fd, "%s\n",
		client->server->active_request);
	return (1);
}

uint8_t clt_cmd_get_args_eject(clt_config_t *client, va_list *av, char sender)
{
	return (sender ? clt_cmd_eject(client) :
		clt_cmd_eject_receiver(client));
	(void) av;
}
