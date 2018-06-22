/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** take.c
*/

#include "client.h"
#include "map.h"

static uint8_t clt_cmd_take_receiver(clt_config_t *client, object_t obj)
{
	tile_t *tile;

	tile = map_get_tile(client->map, client->specs->x,
				client->specs->y);
	if (ZAPPY_IS_OK(client->server->response_request)) {
		(*tile)[obj] -= 1;
		client->specs->inventory[obj] += 1;
	} else {
		(*tile)[obj] = 0;
		send_request(INVENTORY, client);
	}
	if (ZAPPY_DEBUG)
		print_cell(tile);
	return (1);
}

static uint8_t clt_cmd_take(clt_config_t *client, object_t obj)
{
	send_active_request(client, "%s", OBJ_NAMES[obj]);
	return (1);
}

uint8_t clt_cmd_get_args_take(clt_config_t *client, va_list *av, char sender)
{
	if (sender)
		return (clt_cmd_take(client, va_arg(*av, object_t)));
	else
		return (clt_cmd_take_receiver(client, va_arg(*av, object_t)));
}