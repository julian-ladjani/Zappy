/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** follower.c
*/

#include <broadcast.h>
#include "client.h"

static void *go_search_mode(clt_config_t *clt, ai_mode_t mode)
{
	send_request(BROADCAST, clt, "incantation:stop_helping:%ld",
		clt->specs->level);
	clt->specs->ai_mode = mode;
	return (NULL);
}

static msg_infos_inc_t * check_need_to_leave(clt_config_t *clt, clt_msg_t *msg)
{
	msg_infos_inc_t *infos;

	send_request(LOOK, clt);
	list_dump(clt->server->broadcasts_queue, dump_broadcast);
	if (!msg) {
		clt->incantation = 0;
		return (go_search_mode(clt, SEARCHER));
	}
	printf("LOCKED TO : %d\n", msg->from);
	infos = (msg_infos_inc_t *) msg->content;
	if (infos->state == NEED_STOP_HELPING) {
		go_search_mode(clt, SEARCHER);
		send_request(FORWARD, clt);
		return (NULL);
	}
	return (infos);
}

static void find_incantation(clt_config_t *clt)
{
	clt_msg_t *msg = broadcast_search_for
		(clt, condition_targeted_incantation);
	msg_infos_inc_t *infos = check_need_to_leave(clt, msg);

	if (!infos || infos->state == START) {
		clt->incantation = (!infos) ? clt->incantation : 1;
		return;
	}
	if (msg->dir == 0)
		return;
	clt->specs->target = get_tile_from_dir
		(clt->specs->x, clt->specs->y, msg->dir,
		clt->specs->orientation);
	if ((*map_get_tile(clt->map, clt->specs->target.x,
				clt->specs->target.y))[PLAYER] <
		INCANTATION_OBJ[clt->specs->level][PLAYER])
		move_player_to_target(clt);
}

int wait_for_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	int lvl = clt->specs->level;
	clt_msg_t *msg = broadcast_search_for
		(clt, condition_targeted_incantation);

	if (msg && ((msg_infos_inc_t *)msg->content)->state == CANCELED) {
		clt->specs->ai_mode = SEARCHER;
		clt->incantation = 0;
		return (ZAPPY_EXIT_SUCCESS);
	}
	send_request(LOOK, clt);
	if ((*tile)[PLAYER] != (size_t) INCANTATION_OBJ[lvl][PLAYER] ||
		!condition_pre_incantation(clt)) {
		clt->incantation = 0;
		return (ZAPPY_EXIT_SUCCESS);
	}
	manage_broadcast_timer(clt);
	return (ZAPPY_EXIT_SUCCESS);
}

int ai_follower(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);

	if (clt->incantation == 1)
		return (wait_for_incantation(clt));
	for (int i = 0; i < 5 && (*tile)[FOOD] != 0; ++i) {
		send_request(TAKE, clt, FOOD);
		send_request(LOOK, clt);
	}
	send_request(INVENTORY, clt);
	if (clt->specs->inventory[FOOD] < 5 && !go_search_mode(clt, EATER))
		return (ZAPPY_EXIT_SUCCESS);
	send_request(BROADCAST, clt, "incantation:helping:%ld",
		clt->specs->level);
	manage_broadcast_timer(clt);
	find_incantation(clt);
	if (ZAPPY_DEBUG)
		print_map(clt->map);
	return (ZAPPY_EXIT_SUCCESS);
}