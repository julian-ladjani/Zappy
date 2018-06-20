/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include "client.h"

static uint8_t clt_cmd_inventory_receiver(clt_config_t *client)
{
	char *str = client->server->response_request;
	char *tmp;
	int quantity;

	if (ZAPPY_DEBUG)
		printf("\nINVENTORY\n");
	for (size_t i = 0; OBJ_NAMES[i]; ++i) {
		tmp = strstr(str, OBJ_NAMES[i]);
		if (!tmp)
			client->specs->inventory[i] = 0;
		else {
			quantity = atoi(tmp + strlen(OBJ_NAMES[i]) + 1);
			client->specs->inventory[i] = (size_t) quantity;
		}
		if (ZAPPY_DEBUG)
			printf("%-10s: %ld\n", OBJ_NAMES[i],
				client->specs->inventory[i]);
	}
	return (1);
}

static uint8_t clt_cmd_inventory(clt_config_t *client)
{
	dprintf(client->server->pollfd->fd, "%s\n",
		client->server->active_request);
	return (1);
}

uint8_t clt_cmd_get_args_inventory(clt_config_t *client,
					va_list *av, char sender)
{
	return (sender ? clt_cmd_inventory(client) :
		clt_cmd_inventory_receiver(client));
	(void) av;
}
