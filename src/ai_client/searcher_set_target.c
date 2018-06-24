/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** searcher_set_target.c
*/

#include "client.h"

static void set_player_target_forward(clt_config_t *client)
{
	clt_specs_t *specs = client->specs;

	specs->target.y = (ssize_t) specs->y;
	specs->target.x = (ssize_t) specs->x;
	if (specs->orientation == NORTH)
		specs->target.y = map_get_abs
			(specs->target.y + 1, client->map->height);
	if (specs->orientation == EAST)
		specs->target.x = map_get_abs
			(specs->target.x + 1, client->map->width);
	if (specs->orientation == SOUTH)
		specs->target.y = map_get_abs
			(specs->target.y - 1, client->map->height);
	if (specs->orientation == WEST)
		specs->target.x = map_get_abs
			(specs->target.x - 1, client->map->width);
}

void update_target_tile(clt_config_t *clt,
	double (*ratio_finder)
		(clt_config_t *, ssize_t, ssize_t))
{
	double ratio;
	double max_ratio = -1;

	for (ssize_t y = 0; y < (ssize_t) clt->map->height; ++y) {
		for (ssize_t x = 0; x < (ssize_t) clt->map->width; ++x) {
			ratio = get_tile_ratio(clt, ratio_finder, x, y);
			if (ratio >= max_ratio && ratio > 0) {
				max_ratio = ratio;
				clt->specs->target.y = map_get_abs
					(y, clt->map->height);
				clt->specs->target.x = map_get_abs
					(x, clt->map->width);
			}
		}
	}
	if (max_ratio == -1)
		set_player_target_forward(clt);
}