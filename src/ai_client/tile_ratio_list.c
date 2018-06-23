/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tile_ratio_list.c
*/

#include <client.h>

double ratio_searcher(clt_config_t *client, ssize_t x, ssize_t y)
{
	tile_t *tile = map_get_tile(client->map, x, y);
	int food_ratio = get_food_ratio(client, tile);
	int obj_ratio = get_obj_ratio(client, tile);
	double dist = get_distance_from_tile(client, x, y);

	if (dist > 1)
		return ((double)food_ratio
			+ ((double)obj_ratio / dist) * 10
			* ((*tile)[PLAYER] == 0));
	else
		return (food_ratio + obj_ratio * 10 * ((*tile)[PLAYER] == 0));
}