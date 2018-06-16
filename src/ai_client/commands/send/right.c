/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** rigth.c
*/

#include "client.h"

uint8_t clt_cmd_right_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_right(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_right(clt_config_t *client, va_list *av)
{
	return (clt_cmd_right(client));
	(void) av;
}
