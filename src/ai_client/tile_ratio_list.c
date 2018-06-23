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

	return ((double)food_ratio / (dist > 1 ? dist : 1));
}

double ratio_searcher(clt_config_t *client, ssize_t x, ssize_t y)
{
	tile_t *tile = map_get_tile(client->map, x, y);
	int obj_ratio = get_obj_ratio(client, tile);
	double dist = get_distance_from_tile(client, x, y);

	if (dist > 1)
		return (((double)obj_ratio / dist) * 10
			  * ((*tile)[PLAYER] == 0));
	else
		return (obj_ratio * 10 * ((*tile)[PLAYER] == 0));
}