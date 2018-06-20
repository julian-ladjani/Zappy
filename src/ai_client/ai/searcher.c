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

void update_target_tile(clt_config_t *clt)
{
	double ratio = -1;
	int max_ratio = 0;

	for (ssize_t y = 0; y < clt->map->height; ++y) {
		for (ssize_t x = 0; x < clt->map->width; ++x) {
			ratio = get_tile_ratio(clt, y, x);
			if (ratio >= max_ratio) {
				ratio = max_ratio;
				clt->specs->target.y = y;
				clt->specs->target.x = x;
			}
		}
	}
	if (ratio == -1) {
		clt->specs->target.y = clt->specs->y;
		clt->specs->target.x = clt->specs->x;
	}
}

void turn_player_to_target(clt_config_t *clt)
{
	if (clt->specs->y != clt->specs->target.y)
		while ((clt->specs->y - clt->specs->target.y > 0 &&
			clt->specs->orientation == SOUTH) ||
		       (clt->specs->y - clt->specs->target.y < 0 &&
			clt->specs->orientation == NORTH))
			send_request(RIGHT, clt);
	else
		while ((clt->specs->x - clt->specs->target.x > 0 &&
			clt->specs->orientation == WEST) ||
		       (clt->specs->x - clt->specs->target.x < 0 &&
			clt->specs->orientation == EAST))
			send_request(RIGHT, clt);
}

void move_player_to_target(clt_config_t *clt)
{
	if (clt->specs->y == clt->specs->target.y &&
		clt->specs->target.x == clt->specs->x) {
		if (clt->specs->forwarding >= clt->map->width) {
			send_request(RIGHT, clt);
			send_request(FORWARD, clt);
			send_request(FORWARD, clt);
			send_request(LEFT, clt);
		}
		send_request(FORWARD, clt);
		return;
	}
	turn_player_to_target(clt);
	send_request(FORWARD, clt);
}

int ai_searcher(clt_config_t *clt)
{
	tile_t *tile;

	send_request(LOOK, clt);
	if (ZAPPY_DEBUG)
		print_map(clt->map);
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