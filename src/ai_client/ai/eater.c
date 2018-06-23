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

	for (int i = 0; (*tile)[FOOD] != 0 &&
			clt->specs->inventory[FOOD] < 12; ++i)
		send_request(TAKE, clt, FOOD);
	if (clt->specs->inventory[FOOD] >= 12) {
		clt->specs->ai_mode = LAST_MODE;
		return (ZAPPY_EXIT_SUCCESS);
	}
	update_target_tile(clt, ratio_eater);
	send_request(FORWARD, clt);
	return (ZAPPY_EXIT_SUCCESS);
}