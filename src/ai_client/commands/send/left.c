/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** left.c
*/

#include "client.h"

uint8_t clt_cmd_left(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_left(clt_config_t *client, va_list *av)
{
	return (clt_cmd_left(client));
	(void) av;
}