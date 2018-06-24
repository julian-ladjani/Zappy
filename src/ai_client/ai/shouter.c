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
	list_t *elem = clt->server->broadcasts_queue;
	clt_msg_t *msg = NULL;
	clt_msg_t *ref = NULL;
	msg_infos_incantation_t *infos;

	while (elem) {
		msg = (clt_msg_t *) elem->elem;
		if (msg && msg->type == MSG_INCANTATION) {
			infos = (msg_infos_incantation_t *) msg->content;
			if (infos->level == (int) clt->specs->level &&
				infos->state == NEED_HELP &&
				(!ref || msg->from > ref->from))
				ref = msg;
		}
		elem = elem->next;
	}
	if (ref)
		printf("From : %d | Je susi : %ld\n", ref->from, clt->specs->id);
	if (!ref || (size_t) ref->from < clt->specs->id)
		return (0);
	printf("BON BAH JE PARS\n");
	clt->specs->targeted_incantation_id = ref->from;
	clt->specs->ai_mode = FOLLOWER;
	return (1);
}

void shout_status(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	int lvl = clt->specs->level;

	send_request(LOOK, clt);
	if (check_others_broadcasts(clt))
		return;
	if ((*tile)[PLAYER] != (size_t) INCANTATION_OBJ[lvl][PLAYER]) {
		send_request(BROADCAST, clt, "incantation:need_players:%d",
			     lvl);
		tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
		if (tilecmp(tile, (tile_t *) (INCANTATION_OBJ + lvl)) != 0)
			clt->specs->ai_mode = SEARCHER;
		return;
	}
	send_request(BROADCAST, clt, "incantation:start:%d", lvl);
	send_request(INCANTATION, clt);
	clt->specs->ai_mode = SEARCHER;
}

int ai_shouter(clt_config_t *clt)
{
	send_request(INVENTORY, clt);
	if (clt->specs->inventory[FOOD] < 5) {
		clt->specs->ai_mode = EATER;
		clt->specs->last_target = clt->specs->target;
		return (ZAPPY_EXIT_SUCCESS);
	}
	if (!condition_pre_incantation(clt)) {
		if ((ssize_t) clt->specs->y == clt->specs->target.y &&
			(ssize_t) clt->specs->x == clt->specs->target.x) {
			clt->specs->ai_mode = SEARCHER;
			return (ZAPPY_EXIT_SUCCESS);
		}
		move_player_to_target(clt);
	} else
		shout_status(clt);
	return (ZAPPY_EXIT_SUCCESS);
}