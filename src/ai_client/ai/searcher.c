/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** searcher.c
*/

#include "client.h"
#include "broadcast.h"

static int check_obj_for_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	tile_t *ref = (tile_t *) (INCANTATION_OBJ + clt->specs->level);

	for (int i = 1; i < 7; ++i)
		if ((*tile)[i] + clt->specs->inventory[i] < (*ref)[i])
			return (0);
	return (1);
}

static void prepare_incantation(clt_config_t *clt)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	tile_t *ref = (tile_t *) (INCANTATION_OBJ + clt->specs->level);

	send_request(INVENTORY, clt);
	if (check_obj_for_incantation(clt)) {
		clear_tile_from_ref(clt, tile, ref);
		fill_tile_from_inv(clt, tile, ref);
	}
	if (condition_pre_incantation(clt)) {
		if ((*tile)[PLAYER] == (*ref)[PLAYER]) {
			send_request(BROADCAST, clt, "incantation:start:%d",
					clt->specs->level);
			send_request(INCANTATION, clt);
		} else
			clt->specs->ai_mode = SHOUTER;
	}
}

static int find_incantation(clt_config_t *clt)
{
	clt_msg_t *msg = broadcast_search_for
		(clt, condition_search_incantation);

	if (!msg)
		return (0);
	clt->specs->targeted_incantation_id = msg->from;
	clt->specs->ai_mode = FOLLOWER;
	return (1);
}

int ai_searcher(clt_config_t *clt)
{
	tile_t *tile;

	if (find_incantation(clt))
		return (ZAPPY_EXIT_SUCCESS);
	send_request(LOOK, clt);
	if (ZAPPY_DEBUG)
		print_map(clt->map);
	tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);
	for (int i = 0; i < 5 && (*tile)[FOOD] != 0; ++i)
		send_request(TAKE, clt, FOOD);
	take_obj_from_ref(clt, (tile_t *)(INCANTATION_OBJ + clt->specs->level));
	update_target_tile(clt);
	move_player_to_target(clt);
	if (find_incantation(clt))
		return (ZAPPY_EXIT_SUCCESS);
	prepare_incantation(clt);
	return (ZAPPY_EXIT_SUCCESS);
}