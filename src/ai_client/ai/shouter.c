/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** shouter.c
*/

#include <broadcast.h>
#include "client.h"

int check_others_broadcasts(clt_config_t *clt)
{

	clt_msg_t *msg = broadcast_search_for
		(clt, condition_search_incantation);

	if (!msg || msg->from > clt->specs->id)
		return (0);
	clt->specs->targeted_incantation_id = msg->from;
	clt->specs->ai_mode = FOLLOWER;
	return (1);
	return 0;
}

int ai_shouter(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	int lvl = clt->specs->level;

	send_request(LOOK, clt);
	//if (check_others_broadcasts(clt))
	if ((*tile)[PLAYER] != (size_t) INCANTATION_OBJ[lvl][PLAYER]) {
		send_request(BROADCAST, clt, "incantation:need_players:%d",
				lvl);
		tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
		if (tilecmp(tile, (tile_t *) (INCANTATION_OBJ + lvl)) != 0)
			clt->specs->ai_mode = SEARCHER;
		return (ZAPPY_EXIT_SUCCESS);
	}
	send_request(BROADCAST, clt, "incantation:start:%d", lvl);
	send_request(INCANTATION, clt);
	clt->specs->ai_mode = SEARCHER;
	return (ZAPPY_EXIT_SUCCESS);
}