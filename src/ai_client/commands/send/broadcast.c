/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.c
*/

#define _GNU_SOURCE
#include <stdio.h>
#include "client.h"

static uint8_t clt_cmd_broadcast_receiver(clt_config_t *client, char *msg,
					va_list *av)
{
	if (ZAPPY_DEBUG)
		printf("BROADCAST SENT !\n");
	return (1);
	(void) client;
	(void) msg;
	(void) av;
}

static uint8_t clt_cmd_broadcast(clt_config_t *client, char *msg, va_list *av)
{
	char *tmp = NULL;

	vasprintf(&tmp, msg, *av);
	if (!tmp)
		return (0);
	send_active_request(client, "%s:%d:%s", client->specs->team,
				client->specs->id, tmp);
	return (1);
}

uint8_t clt_cmd_get_args_broadcast(clt_config_t *client, va_list *av,
					char sender)
{
	if (sender)
		return (clt_cmd_broadcast(client, va_arg(*av, char *), av));
	else
		return (clt_cmd_broadcast_receiver(
			client, va_arg(*av, char *), av));
}
