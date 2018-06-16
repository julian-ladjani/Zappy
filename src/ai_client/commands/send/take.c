/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** take.c
*/

#include "client.h"

static uint8_t clt_cmd_take_receiver(clt_config_t *client, object_t obj)
{
	(void) client;
	(void) obj;
	return (1);
}

static uint8_t clt_cmd_take(clt_config_t *client, object_t obj)
{
	(void) client;
	(void) obj;
	return (1);
}

uint8_t clt_cmd_get_args_take(clt_config_t *client, va_list *av, char sender)
{
	if (sender)
		return (clt_cmd_take(client, va_arg(*av, object_t)));
	else
		return (clt_cmd_take_receiver(client, va_arg(*av, object_t)));
}