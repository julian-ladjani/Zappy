/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include "client.h"

static uint8_t clt_cmd_inventory_receiver(clt_config_t *client)
{
	(void) client;
	return (1);
}

static uint8_t clt_cmd_inventory(clt_config_t *client)
{
	(void) client;
	return (1);
}

uint8_t clt_cmd_get_args_inventory(clt_config_t *client, va_list *av, char sender)
{
	return (sender ? clt_cmd_inventory(client) :
		clt_cmd_inventory_receiver(client));
	(void) av;
}