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
	int lvl = clt->specs->level;

	send_request(LOOK, clt);
	if ((*tile)[PLAYER] != (size_t) INCANTATION_OBJ[lvl][PLAYER]) {
		send_request(BROADCAST, clt, "incantation:need_players:%d",
				lvl);
		tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
		if (tilecmp(tile, (tile_t *) (INCANTATION_OBJ + lvl)) != 0)
			clt->specs->ai_mode = SEARCHER;
		return (ZAPPY_EXIT_SUCCESS);
	}
	send_request(INCANTATION, clt);
	clt->specs->ai_mode = SEARCHER;
	return (ZAPPY_EXIT_SUCCESS);
}