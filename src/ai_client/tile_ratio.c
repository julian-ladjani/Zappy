/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tile_ratio.c
*/

#include "math.h"
#include "client.h"

int get_food_ratio(clt_config_t *clt, tile_t *tile)
{
	return (0);
	(void) clt;
	(void) tile;
}

int get_obj_ratio(clt_config_t *client, tile_t *tile)
{
	int ratio = 0;
	ssize_t tmp;

	for (int i = 1; i < 7; ++i) {
		if (INCANTATION_OBJ[client->specs->level][i] && (*tile)[i]) {
			tmp = INCANTATION_OBJ[client->specs->level][i]
				- client->specs->inventory[i];
			if ((*tile)[i] > tmp || tmp > 0)
				ratio += tmp;
			else if (tmp > 0)
				ratio += (*tile)[i];
		}
	}
	return (ratio);
}

double get_distance_from_tile(clt_config_t *client, ssize_t x, ssize_t y)
{
	vec_t vec1 = {client->specs->x, client->specs->y};
	vec_t vec2 = {x, y};
	vec_t vec = map_get_dir(client->map, vec1, vec2);
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

double get_tile_ratio(clt_config_t *client, ssize_t y, ssize_t x)
{
	tile_t *tile = map_get_tile(client->map, x, y);
	int food_ratio = get_food_ratio(client, tile);
	int obj_ratio = get_obj_ratio(client, tile);
	double dist = get_distance_from_tile(client, x, y);

	if (dist > 1)
		return ((double)food_ratio
				+ ((double)obj_ratio / dist) * 10);
	else
		return (food_ratio + obj_ratio * 10);
}