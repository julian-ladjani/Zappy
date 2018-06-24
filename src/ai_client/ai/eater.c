/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eater.c
*/

#include "client.h"

int ai_eater(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);

	send_request(LOOK, clt);
	for (int i = 0; (*tile)[FOOD] != 0 &&
			clt->specs->inventory[FOOD] < 20; ++i)
		send_request(TAKE, clt, FOOD);
	if (clt->specs->inventory[FOOD] >= 12) {
		clt->specs->ai_mode = LAST_MODE;
		clt->specs->target = clt->specs->last_target;
		return (ZAPPY_EXIT_SUCCESS);
	}
	if (clt->specs->y == clt->specs->target.y &&
		clt->specs->x == clt->specs->target.x)
		update_target_tile(clt, ratio_eater);
	move_player_to_target(clt);
	return (ZAPPY_EXIT_SUCCESS);
}