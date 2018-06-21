/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** shouter.c
*/

#include "client.h"

int ai_shouter(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);

	while ((*tile)[PLAYER] != (size_t) INCANTATION_OBJ[PLAYER]) {
		send_request(BROADCAST, clt, "incantation;need_players;%d",
				clt->specs->level);
		send_request(LOOK, clt);
		tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
		if (tilecmp(tile, (tile_t *)
			(INCANTATION_OBJ + clt->specs->level)) != 0)
			clt->specs->ai_mode = SEARCHER;
	}

	return (ZAPPY_EXIT_SUCCESS);
}