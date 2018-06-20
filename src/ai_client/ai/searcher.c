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
			if (ZAPPY_DEBUG)
				print_map(clt->map);
		}
	}
	printf("Incantation ?\n");
	send_request(INVENTORY, clt);
	if (condition_pre_incantation(clt)) {
		printf("Incantation ? 2\n");
		if ((*tile)[PLAYER] == (*ref)[PLAYER]) {
			printf("Incantation ! 3\n");
			send_request(BROADCAST, clt, "incantation:start:%d",
					clt->specs->level);
			send_request(INCANTATION, clt);
		} else
			clt->specs->ai_mode = SHOUTER;
	}
}

int ai_searcher(clt_config_t *clt)
{
	tile_t *tile;

	send_request(LOOK, clt);
	if (ZAPPY_DEBUG)
		print_map(clt->map);
	tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	while ((*tile)[FOOD] != 0)
		send_request(TAKE, clt, FOOD);
	if (tilecmp(tile, (tile_t *)
		(INCANTATION_OBJ + clt->specs->level)) >= 0) {
		printf("IF\n");
		prepare_incantation(clt);
		return (ZAPPY_EXIT_SUCCESS);
	}
	if (ZAPPY_DEBUG)
		print_map(clt->map);
	if (clt->specs->forwarding >= clt->map->width) {
		send_request(RIGHT, clt);
		send_request(FORWARD, clt);
		send_request(FORWARD, clt);
		send_request(LEFT, clt);
	}
	send_request(FORWARD, clt);
	return (ZAPPY_EXIT_SUCCESS);
}
