/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eject.c
*/

#include "client.h"

uint8_t clt_cmd_eject(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_eject(clt_config_t *client, ...)
{
	return (clt_cmd_eject(client));
}
