/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** forward.c
*/

#include "client.h"

static uint8_t clt_cmd_forward_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

static uint8_t clt_cmd_forward(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_forward(clt_config_t *client, va_list *av, char sender)
{
	return (client ? clt_cmd_forward(client) :
		clt_cmd_forward_receiver(client));
	(void) av;
}