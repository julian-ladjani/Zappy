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

static void take_obj_from_ref(clt_config_t *clt, tile_t *ref)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);

	send_request(INVENTORY, clt);
	for (int i = 1; i < 7; ++i) {
		send_request(LOOK, clt);
		while ((*tile)[i] != 0 &&
			clt->specs->inventory[i] < (*ref)[i]) {
			send_request(TAKE, clt, i);
			if (ZAPPY_DEBUG)
				print_map(clt->map);
		}
	}
}

static int check_obj_for_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	tile_t *ref = (tile_t *) (INCANTATION_OBJ + clt->specs->level);

	for (int i = 1; i < 7; ++i) {
		if ((*tile)[i] + clt->specs->inventory[i] < (*ref)[i]) {
			printf("%s : Inv %ld / Tile : %ld / Needed : %ld",
			       OBJ_NAMES[i],
			       clt->specs->inventory[i], (*tile)[i], (*ref)[i]);
			return (0);
		}
	}
	return (1);
}

static void prepare_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	tile_t *ref = (tile_t *) (INCANTATION_OBJ + clt->specs->level);

	send_request(INVENTORY, clt);
	if (check_obj_for_incantation(clt)) {
		print_map(clt->map);
		clear_tile_from_ref(clt, tile, ref);
		fill_tile_from_inv(clt, tile, ref);
		print_map(clt->map);
	}
	if (condition_pre_incantation(clt)) {
		if ((*tile)[PLAYER] == (*ref)[PLAYER]) {
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
	tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	for (int i = 0; i < 5 && (*tile)[FOOD] != 0; ++i)
		send_request(TAKE, clt, FOOD);
	take_obj_from_ref(clt, (tile_t *)(INCANTATION_OBJ + clt->specs->level));
	update_target_tile(clt);
	move_player_to_target(clt);
	prepare_incantation(clt);
	if (ZAPPY_DEBUG)
		print_map(clt->map);
	return (ZAPPY_EXIT_SUCCESS);
}