/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** follower.c
*/

#include <broadcast.h>
#include "client.h"

static vec_t get_tile_from_dir(ssize_t x, ssize_t y, int dir, cardinal_dir_t c)
{
	static const vec_t vecs[8] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1},
					{0, -1}, {1, -1}, {1, 0}, {1, 1}};
	int index = (8 - 2 * (c - 1) + dir) % 8;
	vec_t vec;

	if (index == 0)
		index = 8;
	--index;
	vec.x = vecs[index].x + x;
	vec.y = vecs[index].y + y;
	return (vec);
}

static void find_incantation(clt_config_t *clt)
{
	clt_msg_t *msg = broadcast_search_for
		(clt, condition_targeted_incantation);
	msg_infos_incantation_t *infos;

	if (!msg) {
		clt->incantation = 0;
		clt->specs->ai_mode = SEARCHER;
		return;
	}
	infos = (msg_infos_incantation_t *) msg->content;
	if (infos->state == START) {
		clt->incantation = 1;
		return;
	}
	if (msg->dir == 0)
		return;
	clt->specs->target = get_tile_from_dir(clt->specs->x, clt->specs->y,
				msg->dir, clt->specs->orientation);
	move_player_to_target(clt);
	return;
}

int wait_for_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	int lvl = clt->specs->level;
	clt_msg_t *msg = broadcast_search_for
		(clt, condition_targeted_incantation);
	msg_infos_incantation_t *infos;

	if (msg) {
		infos = (msg_infos_incantation_t *) msg->content;
		if (infos->state == CANCELED) {
			clt->specs->ai_mode = SEARCHER;
			clt->incantation = 0;
			return (ZAPPY_EXIT_SUCCESS);
		}
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
	for (int i = 0; i < 5 && (*tile)[FOOD] != 0; ++i)
		send_request(TAKE, clt, FOOD);
	send_request(INVENTORY, clt);
	if (clt->specs->inventory[FOOD] < 5) {
		printf("JE VEUX PASSER ENMDOE EATER !\n");
		clt->specs->ai_mode = EATER;
		return (ZAPPY_EXIT_SUCCESS);
	}
	manage_broadcast_timer(clt);
	send_request(LOOK, clt);
	find_incantation(clt);
	if (ZAPPY_DEBUG)
		print_map(clt->map);
	return (ZAPPY_EXIT_SUCCESS);
}