/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** set.c
*/

#include "client.h"

uint8_t clt_cmd_set_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_set(clt_config_t *client, object_t obj)
{
	(void) client;
	(void) obj;
	return (1);
}

uint8_t clt_cmd_get_args_set(clt_config_t *client, va_list *av)
{
	return (clt_cmd_set(client, va_arg(*av, object_t)));
}