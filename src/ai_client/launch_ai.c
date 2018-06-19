/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** launch_ai.c
*/

#include <client.h>

void launch_ai(clt_config_t *clt)
{
	while (clt->status != ZAPPY_CLT_DEAD) {
		send_request(LOOK, clt);
		print_map(clt->map);
		while ((*map_get_tile(clt->map, clt->specs->x, clt->specs->y))
			[FOOD] != 0)
			send_request(TAKE, clt, FOOD);
		print_map(clt->map);
		send_request(FORWARD, clt);
	}
}

