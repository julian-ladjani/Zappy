/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** follower.c
*/

#include <broadcast.h>
#include "client.h"

int ai_test(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);

	send_request(LOOK, clt);
	for (int i = 0; (*tile)[FOOD] != 0; ++i)
		send_request(TAKE, clt, FOOD);
	if ((ssize_t) clt->specs->y == clt->specs->target.y &&
	    (ssize_t) clt->specs->x == clt->specs->target.x) {
		update_target_tile(clt, ratio_eater);
		tile = map_get_tile(clt->map, clt->specs->target.x,
					clt->specs->target.y);
		print_map(clt->map);
		print_cell(tile);
	}
	move_player_to_target(clt);
	return (ZAPPY_EXIT_SUCCESS);
}