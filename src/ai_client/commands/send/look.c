/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** look.c
*/

#include "client.h"

uint8_t clt_cmd_look(clt_config_t *client)
{
	send_active_request(client, "");
	return (1);
}

uint8_t clt_cmd_get_args_look(clt_config_t *client, va_list *av)
{
	return (clt_cmd_look(client));
	(void) av;
}
