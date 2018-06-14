/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** set.c
*/

#include "client.h"

uint8_t clt_cmd_set(clt_config_t *client, object_t obj)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_set(clt_config_t *client, ...)
{
	uint8_t r_value;

	va_list args;
	va_start(args, client);
	r_value = clt_cmd_set(client, va_arg(args, object_t));
	va_end(args);
	return (r_value);
}