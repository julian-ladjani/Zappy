/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** connect_nbr.c
*/

#include "client.h"

static uint8_t clt_cmd_connect_nbr_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

static uint8_t clt_cmd_connect_nbr(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_connect_nbr(clt_config_t *client, va_list *av,
					char sender)
{
	return ((sender) ? clt_cmd_connect_nbr(client) :
		clt_cmd_connect_nbr_receiver(client));
	(void)(av);
}