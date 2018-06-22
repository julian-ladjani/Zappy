/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "client.h"

static uint8_t clt_cmd_incantation_receiver(clt_config_t *client)
{
	if (!ZAPPY_IS_KO(client->server->response_request))
		++client->specs->level;
	client->incantation = 0;
	return (1);
}

static uint8_t clt_cmd_incantation(clt_config_t *client)
{
	if (!strcmp(client->server->active_request, "Incantation"))
		dprintf(client->server->pollfd->fd, "%s\n",
			client->server->active_request);
	client->incantation = 1;
	return (1);
}

uint8_t clt_cmd_get_args_incantation(clt_config_t *client,
					va_list *av, char sender)
{
	return (sender ? clt_cmd_incantation(client) :
		clt_cmd_incantation_receiver(client));
	(void) av;
}
