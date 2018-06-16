/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.c
*/

#include "client.h"

static uint8_t clt_cmd_broadcast_receiver(clt_config_t *client, char *msg,
					va_list *av)
{
	(void) client;
	(void) av;
	(void) msg;
	return (1);
}

static uint8_t clt_cmd_broadcast(clt_config_t *client, char *msg, va_list *av)
{
	(void) client;
	(void) av;
	(void) msg;
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
