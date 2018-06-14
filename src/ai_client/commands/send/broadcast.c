/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.c
*/

#include "client.h"

uint8_t clt_cmd_broadcast(clt_config_t *client, char *msg, ...)
{
	(void) client;
	return (1);
}

uint8_t clt_get_args_cmd_broadcast(clt_config_t *client, ...)
{
	uint8_t r_value;
	va_list va;

	va_start(va, client);
	r_value = clt_cmd_broadcast(client, va_arg(va, char*), va);
	va_end(va);
	return (r_value);
}
