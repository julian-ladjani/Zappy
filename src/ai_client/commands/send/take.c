/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** take.c
*/

#include "client.h"

uint8_t clt_cmd_take(clt_config_t *client, object_t obj)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_take(clt_config_t *client, va_list *av)
{
	return (clt_cmd_set(client, va_arg(*av, object_t)));
}