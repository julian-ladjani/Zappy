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
	send(client->server->pollfd->fd, client->specs->team,
		strlen(client->specs->team), 0);
	send(client->server->pollfd->fd, "\n", 1, 0);
	return (ZAPPY_EXIT_SUCCESS);
}

int prerequest_map_size(clt_config_t *client)
{
	char *str = client->server->response_request;
	char *tmp = strchr(str, ' ');

	if (!str || !tmp || client->map || ZAPPY_IS_KO(str))
		return (ZAPPY_EXIT_FAILURE);
	*tmp = 0;
	if (!is_number(str) || !is_number(tmp + 1))
		return (ZAPPY_EXIT_FAILURE);
	client->map = map_create((size_t) atoi(str), (size_t) atoi(tmp + 1), 0);
	client->status = ZAPPY_CLT_READY;
	return (ZAPPY_EXIT_SUCCESS);
}

int prerequest_team_slots(clt_config_t *client)
{
	char *str = client->server->response_request;

	if (!str || ZAPPY_IS_KO(str))
		return (ZAPPY_EXIT_FAILURE);
	if (!is_number(str))
		return (ZAPPY_EXIT_FAILURE);
	client->slots = atoi(str);
	return (client->slots ? ZAPPY_EXIT_SUCCESS : ZAPPY_EXIT_FAILURE);
}