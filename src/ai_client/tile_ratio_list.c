/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tile_ratio_list.c
*/

#include <client.h>

double ratio_eater(clt_config_t *client, ssize_t x, ssize_t y)
{
	tile_t *tile = map_get_tile(client->map, x, y);
	int food_ratio = get_food_ratio(tile);
	double dist = get_distance_from_tile(client, x, y);

	return ((double) food_ratio / (dist > 1 ? dist : 1));
}

double ratio_searcher(clt_config_t *client, ssize_t x, ssize_t y)
{
	tile_t *tile = map_get_tile(client->map, x, y);
	int obj_ratio = get_obj_ratio(client, tile);
	double dist = get_distance_from_tile(client, x, y);

	if (dist > 1)
		return (((double) obj_ratio / dist) * 10
			* ((*tile)[PLAYER] == 0));
	else
		return (obj_ratio * 10 * ((*tile)[PLAYER] == 0));
}

vec_t get_tile_from_dir(ssize_t x, ssize_t y, int dir, cardinal_dir_t c)
{
	static const vec_t vecs[8] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1},
		{0, -1}, {1, -1}, {1, 0}, {1, 1}};
	int index = (8 - 2 * (c - 1) + dir) % 8;
	vec_t vec;

	if (index == 0)
		index = 8;
	--index;
	vec.x = vecs[index].x + x;
	vec.y = vecs[index].y + y;
	return (vec);
}