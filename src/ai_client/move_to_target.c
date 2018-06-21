/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** move_to_target.c
*/

#include "client.h"

static void turn_player_to_dir(clt_config_t *clt, cardinal_dir_t dir)
{
	while (clt->specs->orientation != dir)
		send_request(RIGHT, clt);
}

static void turn_player_to_target(clt_config_t *clt)
{
	ssize_t dif;

	if ((ssize_t) clt->specs->y != clt->specs->target.y) {
		dif = (ssize_t) clt->specs->y - clt->specs->target.y;
		turn_player_to_dir(clt, dif > 0 ? SOUTH : NORTH);
	} else {
		dif = (ssize_t)clt->specs->x - clt->specs->target.x;
		turn_player_to_dir(clt, dif > 0 ? WEST : EAST);
	}

}

void move_player_to_target(clt_config_t *clt)
{
	if ((ssize_t)clt->specs->y == clt->specs->target.y &&
	    clt->specs->target.x == (ssize_t)clt->specs->x) {
		if (clt->specs->forwarding >= (int)clt->map->width) {
			send_request(RIGHT, clt);
			send_request(FORWARD, clt);
			send_request(FORWARD, clt);
			send_request(LEFT, clt);
		}
		send_request(FORWARD, clt);
		return;
	}
	turn_player_to_target(clt);
	if ((ssize_t)clt->specs->y != clt->specs->target.y ||
	    clt->specs->target.x != (ssize_t)clt->specs->x)
		send_request(FORWARD, clt);
}