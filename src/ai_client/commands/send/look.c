/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** look.c
*/

#include <math.h>
#include "client.h"
#include "map.h"

static tile_t *get_tile_from_look_index(clt_config_t *client, int i)
{
	ssize_t fpos = GET_FRONTPOS(i);
	ssize_t lpos = GET_LATPOS(i, fpos);
	ssize_t x = client->specs->x;
	ssize_t y = client->specs->y;

	switch (client->specs->orientation) {
		case EAST:
			return map_get_tile(client->map, fpos + x, -lpos + y);
		case SOUTH:
			return map_get_tile(client->map, -lpos + x, -fpos + y);
		case WEST:
			return map_get_tile(client->map, -fpos + x, lpos + y);
		default:
			return map_get_tile(client->map, lpos + x, fpos + y);
	}
}

static void remove_players_from_map(map_t *map)
{
	for (size_t i = 0; i < map->width * map->height; ++i)
		(*map->tiles)[i][PLAYER] = 0;
}

static uint8_t clt_cmd_look_receiver(clt_config_t *client)
{
	cmdparams_t *cmdparams = parse_arguments(
		client->server->response_request, ",");
	tile_t *tile = get_tile_from_look_index(client, 0);

	remove_players_from_map(client->map);
	str_to_tile(cmdparams->name, tile);
	for (unsigned int i = 0; i < cmdparams->nb_args; ++i) {
		tile = get_tile_from_look_index(client, i + 1);
		str_to_tile(cmdparams->args[i], tile);
	}
	free_arguments(cmdparams);
	printf("LOOK\n");
	if (ZAPPY_DEBUG)
		print_map(client->map);
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
