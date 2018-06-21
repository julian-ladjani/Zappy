/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** searcher.c
*/

#include "client.h"

static void clear_tile_from_ref(clt_config_t *clt, tile_t *tile, tile_t *ref)
{
	for (int i = 1; i < 7; ++i) {
		send_request(LOOK, clt);
		while ((*tile)[i] > (*ref)[i]) {
			send_request(TAKE, clt, i);
			if (ZAPPY_DEBUG)
				print_map(clt->map);
		}
	}
}

static void fill_tile_from_inv(clt_config_t *clt, tile_t *tile, tile_t *ref)
{
	send_request(INVENTORY, clt);
	for (int i = 1; i < 7; ++i) {
		send_request(LOOK, clt);
		while ((*tile)[i] < (*ref)[i] && clt->specs->inventory[i] > 0) {
			send_request(SET, clt, i);
			if (ZAPPY_DEBUG)
				print_map(clt->map);
		}
	}
}

static void prepare_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	tile_t *ref = (tile_t *) (INCANTATION_OBJ + clt->specs->level);

	send_request(INVENTORY, clt);
	if (condition_pre_incantation(clt)) {
		if ((*tile)[PLAYER] == (*ref)[PLAYER]) {
			send_request(BROADCAST, clt, "incantation:start:%d",
					clt->specs->level);
			send_request(INCANTATION, clt);
		} else
			clt->specs->ai_mode = SHOUTER;
	}
	clear_tile_from_ref(clt, tile, ref);
}

int ai_searcher(clt_config_t *clt)
{
	tile_t *tile;

	send_request(LOOK, clt);
	tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	for (int i = 0; i < 5 && (*tile)[FOOD] != 0; ++i)
		send_request(TAKE, clt, FOOD);
	if (tilecmp(tile, (tile_t *)
		(INCANTATION_OBJ + clt->specs->level)) >= 0) {
		prepare_incantation(clt);
		return (ZAPPY_EXIT_SUCCESS);
	}
	update_target_tile(clt);
	move_player_to_target(clt);
	if (ZAPPY_DEBUG)
		print_map(clt->map);
	return (ZAPPY_EXIT_SUCCESS);
}