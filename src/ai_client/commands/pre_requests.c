/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** pre_requests.c
*/

#include "client.h"

uint8_t prerequest_welcome(clt_config_t *client)
{
	if (!client->server->active_request)
		return (0);
	if (strcmp(client->server->active_request, "WELCOME") != 0)
		return (0);
	send(client->server->pollfd->fd, client->team, strlen(client->team), 0);
	send(client->server->pollfd->fd, "\n", 1, 0);
	return (1);
}

uint8_t prerequest_map_size(clt_config_t *client)
{
	char *str = client->server->active_request;
	char *tmp = strchr(str, ' ');

	if (!client->server->active_request)
		return (0);
	if (!tmp || client->map)
		return (0);
	*tmp = 0;
	if (!is_number(str) || !is_number(tmp + 1))
		return (0);
	client->map = map_create((size_t) atoi(str), (size_t) atoi(tmp + 1));
	client->id = atoi(client->server->active_request);
	return (1);
}

uint8_t prerequest_player_id(clt_config_t *client)
{
	if (!client->server->active_request)
		return (0);
	if (!is_number(client->server->active_request))
		return (0);
	client->id = atoi(client->server->active_request);
	return (1);
}