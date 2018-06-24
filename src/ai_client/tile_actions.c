/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tile_actions.c
*/

#include "client.h"

void clear_tile_from_ref(clt_config_t *clt, tile_t *tile, tile_t *ref)
{
	for (int i = 1; i < 7; ++i) {
		if ((*tile)[i] > (*ref)[i])
			send_request(LOOK, clt);
		while ((*tile)[i] > (*ref)[i])
			send_request(TAKE, clt, i);
	}
}

void fill_tile_from_inv(clt_config_t *clt, tile_t *tile, tile_t *ref)
{
	size_t tmp;

	send_request(INVENTORY, clt);
	for (int i = 1; i < 7; ++i) {
		send_request(LOOK, clt);
		tmp = (*tile)[i];
		while ((*tile)[i] < (*ref)[i] &&
			clt->specs->inventory[i] > 0) {
			send_request(SET, clt, i);
			if (tmp == (*tile)[i]) {
				send_request(INVENTORY, clt);
				send_request(LOOK, clt);
			}
			tmp = (*tile)[i];
		}
	}
}

void take_obj_from_ref(clt_config_t *clt, tile_t *ref)
{
	tile_t *tile = map_get_tile(clt->map, clt->specs->x, clt->specs->y);

	send_request(INVENTORY, clt);
	for (int i = 1; i < 7; ++i) {
		if ((*tile)[i] != 0 && clt->specs->inventory[i] < (*ref)[i])
			send_request(LOOK, clt);
		while ((*tile)[i] != 0 &&
			clt->specs->inventory[i] < (*ref)[i]) {
			send_request(TAKE, clt, i);
		}
	}
}