/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** look.c
*/

#include "client.h"

static uint8_t clt_cmd_look_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

static uint8_t clt_cmd_look(clt_config_t *client)
{
	send_active_request(client, "");
	return (1);
}

uint8_t clt_cmd_get_args_look(clt_config_t *client, va_list *av, char sender)
{
	return (sender ? clt_cmd_look(client) : clt_cmd_look_receiver(client));
	(void) av;
}
