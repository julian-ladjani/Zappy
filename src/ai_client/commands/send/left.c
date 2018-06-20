/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** left.c
*/

#include "client.h"

static uint8_t clt_cmd_left_receiver(clt_config_t *client)
{
	client->specs->forwarding = 0;
	client->specs->orientation -= 1;
	if (client->specs->orientation < NORTH)
		client->specs->orientation = WEST;
	return (1);
}

static uint8_t clt_cmd_left(clt_config_t *client)
{
	dprintf(client->server->pollfd->fd, "%s\n",
		client->server->active_request);
	return (1);
}

uint8_t clt_cmd_get_args_left(clt_config_t *client, va_list *av, char sender)
{
	return (sender ? clt_cmd_left(client) : clt_cmd_left_receiver(client));
	(void) av;
}