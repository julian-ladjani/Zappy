/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** fork.c
*/

#include "client.h"

static uint8_t clt_cmd_fork_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

static uint8_t clt_cmd_fork(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_fork(clt_config_t *client, va_list *av, char sender)
{
	return (sender ? clt_cmd_fork(client) : clt_cmd_fork_receiver(client));
	(void) av;
}
