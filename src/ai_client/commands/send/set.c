/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** set.c
*/

#include "client.h"

static uint8_t clt_cmd_set_receiver(clt_config_t *client, object_t obj)
{
	tile_t *tile;

	if (ZAPPY_IS_OK(client->server->response_request)) {
		tile = map_get_tile(client->map, client->specs->x,
					client->specs->y);
		(*tile)[obj] += 1;
		client->specs->inventory[obj] -= 1;
	}
	return (1);
}

static uint8_t clt_cmd_set(clt_config_t *client, object_t obj)
{
	send_active_request(client, "%s", OBJ_NAMES[obj]);
	return (1);
}

uint8_t clt_cmd_get_args_set(clt_config_t *client, va_list *av, char sender)
{
	if (sender)
		return (clt_cmd_set(client, va_arg(*av, object_t)));
	else
		return (clt_cmd_set_receiver(client, va_arg(*av, object_t)));
}
