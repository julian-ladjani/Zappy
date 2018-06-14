/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.c
*/

#include "client.h"

uint8_t clt_cmd_broadcast(clt_config_t *client, char *msg, va_list *av)
{
	(void) client;
	(void) av;
	return (1);
}

uint8_t clt_cmd_get_args_broadcast(clt_config_t *client, va_list *av)
{
	return (clt_cmd_broadcast(client, va_arg(*av, char*), av));
}
