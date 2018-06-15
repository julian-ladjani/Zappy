/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** pre_requests.c
*/

#include "client.h"

int prerequest_welcome(clt_config_t *client)
{
	if (!client->server->response_request)
		return (ZAPPY_EXIT_FAILURE);
	if (strcmp(client->server->response_request, "WELCOME") != 0)
		return (ZAPPY_EXIT_FAILURE);
	send(client->server->pollfd->fd, client->team, strlen(client->team), 0);
	send(client->server->pollfd->fd, "\n", 1, 0);
	return (ZAPPY_EXIT_SUCCESS);
}

int prerequest_map_size(clt_config_t *client)
{
	char *str = client->server->response_request;
	char *tmp = strchr(str, ' ');

	if (!str || !tmp || client->map || !strcmp(str, "ko"))
		return (ZAPPY_EXIT_FAILURE);
	*tmp = 0;
	if (!is_number(str) || !is_number(tmp + 1))
		return (ZAPPY_EXIT_FAILURE);
	client->map = map_create((size_t) atoi(str), (size_t) atoi(tmp + 1));
	client->id = atoi(client->server->response_request);
	return (ZAPPY_EXIT_SUCCESS);
}

int prerequest_player_id(clt_config_t *client)
{
	char *str = client->server->response_request;

	if (!str || !strcmp(str, "ko"))
		return (ZAPPY_EXIT_FAILURE);
	if (!is_number(str))
		return (ZAPPY_EXIT_FAILURE);
	client->id = atoi(str);
	return (ZAPPY_EXIT_SUCCESS);
}