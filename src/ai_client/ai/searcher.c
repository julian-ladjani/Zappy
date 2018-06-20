/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** searcher.c
*/

#include "client.h"

static void prepare_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	tile_t *ref = (tile_t *) (INCANTATION_OBJ + clt->specs->level);

	for (int i = 1; i < 7; ++i) {
		send_request(LOOK, clt);
		while ((*tile)[i] > (*ref)[i]) {
			tile = map_get_tile(clt->map,
					    clt->specs->x, clt->specs->y);
			send_request(TAKE, clt, i);
			print_map(clt->map);
		}
	}
	send_request(INCANTATION, clt);
}

int ai_searcher(clt_config_t *clt)
{
	tile_t *tile;

	send_request(LOOK, clt);
	print_map(clt->map);
	tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	while ((*tile)[FOOD] != 0)
		send_request(TAKE, clt, FOOD);
	if (tilecmp(tile, (tile_t *)
		(INCANTATION_OBJ + clt->specs->level)) >= 0) {
		prepare_incantation(clt);
	}
	print_map(clt->map);
	send_request(FORWARD, clt);
	return (ZAPPY_EXIT_SUCCESS);
}
