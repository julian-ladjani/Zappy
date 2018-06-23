/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tile_ratio.c
*/

#include "math.h"
#include "client.h"

int get_food_ratio(tile_t *tile)
{
	return ((int) (*tile)[FOOD]);
}

int get_obj_ratio(clt_config_t *client, tile_t *tile)
{
	int ratio = 0;
	ssize_t tmp;

	for (int i = 1; i < 7; ++i) {
		if (INCANTATION_OBJ[client->specs->level][i] && (*tile)[i]) {
			tmp = INCANTATION_OBJ[client->specs->level][i]
				- client->specs->inventory[i];
			if ((ssize_t)(*tile)[i] > tmp || tmp > 0)
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

double get_tile_ratio(clt_config_t *client,
			double (* searcher)(clt_config_t *, ssize_t, ssize_t),
			ssize_t x, ssize_t y)
{
	return (searcher(client, x, y));
}