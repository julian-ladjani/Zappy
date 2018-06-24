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
	while ((*tile)[FOOD] != 0 && clt->specs->inventory[FOOD] <= 10)
		send_request(TAKE, clt, FOOD);
	if ((ssize_t) clt->specs->y == clt->specs->target.y &&
		(ssize_t) clt->specs->x == clt->specs->target.x)
		update_target_tile(clt, ratio_eater);
	move_player_to_target(clt);
	return (ZAPPY_EXIT_SUCCESS);
}