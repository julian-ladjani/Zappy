/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "client.h"

uint8_t clt_cmd_incantation(client_config_t *client, char *msg, ...)
{
	(void) client;
	return (1);
}

uint8_t clt_get_args_cmd_incantation(client_config_t *client, ...)
{
	va_list args;
	char buf[1000];
	va_start(args, client);
	vsnprintf(buf, sizeof(buf), client, args );
	va_end(args);
	return (1);
}
