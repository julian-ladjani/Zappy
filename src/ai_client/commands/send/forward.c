/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** forward.c
*/

#include "client.h"

static void forward_user(clt_specs_t *client, map_t *map)
{
	switch (client->orientation) {
		case (NORTH):
			client->y = map_get_abs(client->y + 1, map->height);
			break;
		case (EAST):
			client->x = map_get_abs(client->x + 1, map->width);
			break;
		case (SOUTH):
			client->y = map_get_abs(client->y - 1, map->height);
			break;
		case (WEST):
			client->x = map_get_abs(client->x - 1, map->width);
			break;
	}
}

static uint8_t clt_cmd_forward_receiver(clt_config_t *client)
{
	if (ZAPPY_IS_OK(client->server->response_request))
		forward_user(client->specs, client->map);
	printf("forward\n");
	return (1);
}

static uint8_t clt_cmd_forward(clt_config_t *client)
{
	dprintf(client->server->pollfd->fd, "%s\n",
		client->server->active_request);
	return (1);
}

uint8_t clt_cmd_get_args_forward(clt_config_t *client, va_list *av, char sender)
{
	return (sender ? clt_cmd_forward(client) :
		clt_cmd_forward_receiver(client));
	(void) av;
}