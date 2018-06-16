/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** set.c
*/

#include "client.h"

static uint8_t clt_cmd_set_receiver(clt_config_t *client, object_t obj)
{
	(void) client;
	(void) obj;
	return (1);
}

static uint8_t clt_cmd_set(clt_config_t *client, object_t obj)
{
	(void) client;
	(void) obj;
	return (1);
}

uint8_t clt_cmd_get_args_set(clt_config_t *client, va_list *av, char sender)
{
	if (sender)
		return (clt_cmd_set(client, va_arg(*av, object_t)));
	else
		return (clt_cmd_set_receiver(client, va_arg(*av, object_t)));
}