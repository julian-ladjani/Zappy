/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** look.c
*/

#include <math.h>
#include "client.h"

#define GET_FRONTPOS(n) ((ssize_t) trunc(sqrt(n)))
#define GET_LATPOS(n, frontpos) (n - frontpos * frontpos + frontpos)

static tile_t *get_tile_from_look_index(clt_config_t *client, int i)
{
	ssize_t fpos = GET_FRONTPOS(i);
	ssize_t lpos = GET_LATPOS(i, fpos);

	switch (client->specs->orientation) {
		case EAST:
			return map_get_tile(client->map, fpos, -lpos);
		case SOUTH:
			return map_get_tile(client->map, -lpos, -fpos);
		case WEST:
			return map_get_tile(client->map, -fpos, lpos);
		default:
			return map_get_tile(client->map, lpos, fpos);
	}
}

static uint8_t clt_cmd_look_receiver(clt_config_t *client)
{
	cmdparams_t *cmdparams = parse_arguments(
		client->server->response_request, ",");
	tile_t *tile = get_tile_from_look_index(client, 0);

	str_to_tile(cmdparams->name, tile);
	for (unsigned int i = 0; i < cmdparams->nb_args; ++i) {
		tile = get_tile_from_look_index(client, i + 1);
		str_to_tile(cmdparams->args[i], tile);
		printf("{%s}\n", cmdparams->args[i]);
	}
	printf("-----\n");
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
