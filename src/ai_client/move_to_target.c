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

	printf("%ld %ld\n", clt->specs->y, clt->specs->target.y);
	if (clt->specs->y != clt->specs->target.y) {
		dif = get_shortest(clt->specs->y, clt->specs->target.y,
					clt->map->height);
		printf("TURNING NORTH : %ld\n", dif);
		turn_player_to_dir(clt, dif > 0 ? SOUTH : NORTH);
	} else {
		printf("TURNING EAST\n");
		dif = get_shortest(clt->specs->x, clt->specs->target.x,
					clt->map->width);
		turn_player_to_dir(clt, dif > 0 ? WEST : EAST);
	}

}

void move_player_to_target(clt_config_t *clt)
{
	if (clt->specs->forwarding >= (int)clt->map->width) {
		send_request(RIGHT, clt);
		send_request(FORWARD, clt);
		send_request(FORWARD, clt);
		send_request(LEFT, clt);
	}
	if ((ssize_t)clt->specs->y == clt->specs->target.y &&
	    clt->specs->target.x == (ssize_t)clt->specs->x)
		return;
	turn_player_to_target(clt);
	send_request(FORWARD, clt);
}