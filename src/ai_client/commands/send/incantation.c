/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "client.h"

uint8_t clt_cmd_incantation_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_incantation(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_incantation(clt_config_t *client, va_list *av)
{
	return (clt_cmd_incantation(client));
	(void) av;
}