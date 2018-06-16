/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** rigth.c
*/

#include "client.h"

static uint8_t clt_cmd_right_receiver(clt_config_t *client)
{
	if (ZAPPY_IS_OK(client->server->response_request)) {
	}
	return (1);
}

static uint8_t clt_cmd_right(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_right(clt_config_t *client, va_list *av, char sender)
{
	return (sender ? clt_cmd_right(client) : clt_cmd_right_receiver(client));
	(void) av;
}
