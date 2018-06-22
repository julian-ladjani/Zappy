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
	vec_t vecs[8] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1},
				{1, 0}, {1, 1}};
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

	printf("1\n");
	if (!msg)
		return;
	infos = (msg_infos_incantation_t *) msg->content;
	printf("2\n");
	if (infos->state == CANCELED) {
		clt->specs->ai_mode = SEARCHER;
		return;
	}
	printf("3\n");
	if (infos->state == START) {
		send_request(INCANTATION_WAIT, clt);
		clt->specs->ai_mode = SEARCHER;
		return;
	}
	printf("4\n");
	msg->dir;
	clt->specs->target = get_tile_from_dir(clt->specs->x, clt->specs->y,
				msg->dir, clt->specs->orientation);
	return;
}

int ai_follower(clt_config_t *clt)
{
	printf("FOLLOWER\n");

	find_incantation(clt);
	move_player_to_target(clt);
	print_map(clt->map);
	return (ZAPPY_EXIT_SUCCESS);
}