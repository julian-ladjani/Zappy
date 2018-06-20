/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "client.h"

static uint8_t clt_cmd_incantation_wait_receiver(clt_config_t *client)
{
	if (ZAPPY_IS_OK(client->server->response_request))
		--client->specs->level;
	return (1);
	(void) client;
}

static uint8_t clt_cmd_incantation_wait(clt_config_t *client)
{
	return (1);
	(void) client;
}

uint8_t clt_cmd_get_args_incantation_wait(clt_config_t *client, va_list *av,
					char sender)
{
	if (sender)
		return (clt_cmd_incantation_wait(client));
	else
		return (clt_cmd_incantation_wait_receiver(client));
	(void) av;
}
