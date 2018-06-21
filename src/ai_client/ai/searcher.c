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

static void set_player_target_forward(clt_config_t *client)
{
	clt_specs_t *specs = client->specs;

	specs->target.y = (ssize_t) specs->y;
	specs->target.x = (ssize_t) specs->x;
	switch (specs->orientation) {
		case (NORTH):
			specs->target.y = map_get_abs
				(specs->target.y + 1, client->map->height);
			break;
		case (EAST):
			specs->target.x = map_get_abs
				(specs->target.x + 1, client->map->width);
			break;
		case (SOUTH):
			specs->target.y = map_get_abs
				(specs->target.y - 1, client->map->height);
			break;
		case (WEST):
			specs->target.x = map_get_abs
				(specs->target.x - 1, client->map->width);
			break;
	}
}

void update_target_tile(clt_config_t *clt)
{
	double ratio;
	double max_ratio = -1;

	for (ssize_t y = 0; y < (ssize_t) clt->map->height; ++y) {
		for (ssize_t x = 0; x < (ssize_t) clt->map->width; ++x) {
			ratio = get_tile_ratio(clt, y, x);
			if (ratio >= max_ratio && ratio > 0) {
				max_ratio = ratio;
				clt->specs->target.y = y;
				clt->specs->target.x = x;
			}
		}
	}
	if (max_ratio == -1)
		set_player_target_forward(clt);
	printf("ratio : %lf\npos %ld %ld\n",
	       max_ratio, clt->specs->target.y, clt->specs->target.x);
	tile_t *tile = map_get_tile(clt->map, clt->specs->target.x,
				    clt->specs->target.y);
	for (int i = 0; i < 9; ++i) {
		printf("%s : %ld\n", OBJ_NAMES[i],
		       (*tile)[i]);
	}
	printf("%lf\n", get_distance_from_tile(clt, clt->specs->target.x,
					       clt->specs->target.y));
}

static void turn_player_to_dir(clt_config_t *clt, cardinal_dir_t dir)
{
	while (clt->specs->orientation != dir) {
		printf("JE TOURNE PUTAIN § § § \n");
		send_request(RIGHT, clt);
	}
}

static void turn_player_to_target(clt_config_t *clt)
{
	ssize_t dif;

	if ((ssize_t) clt->specs->y != clt->specs->target.y) {
		dif = (ssize_t) clt->specs->y - clt->specs->target.y;
		turn_player_to_dir(clt, dif > 0 ? SOUTH : NORTH);
	} else {
		dif = (ssize_t)clt->specs->x - clt->specs->target.x;
		turn_player_to_dir(clt, dif > 0 ? WEST : EAST);
	}

}

void move_player_to_target(clt_config_t *clt)
{
	if ((ssize_t)clt->specs->y == clt->specs->target.y &&
		clt->specs->target.x == (ssize_t)clt->specs->x) {
		if (clt->specs->forwarding >= (int)clt->map->width) {
			send_request(RIGHT, clt);
			send_request(FORWARD, clt);
			send_request(FORWARD, clt);
			send_request(LEFT, clt);
		}
		send_request(FORWARD, clt);
		return;
	}
	turn_player_to_target(clt);
	if ((ssize_t)clt->specs->y != clt->specs->target.y ||
		clt->specs->target.x != (ssize_t)clt->specs->x)
		send_request(FORWARD, clt);
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