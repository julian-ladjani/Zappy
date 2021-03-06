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
	while ((*tile)[FOOD] != 0 && clt->specs->inventory[FOOD] <= 10)
		send_request(TAKE, clt, FOOD);
	if (clt->specs->inventory[FOOD] >= 10) {
		clt->specs->ai_mode = LAST_MODE;
		clt->specs->target = clt->specs->last_target;
		return (ZAPPY_EXIT_SUCCESS);
	}
	update_target_tile(clt, ratio_eater);
	while ((ssize_t) clt->specs->y != clt->specs->target.y ||
		(ssize_t) clt->specs->x != clt->specs->target.x)
		move_player_to_target(clt);
	return (ZAPPY_EXIT_SUCCESS);
}