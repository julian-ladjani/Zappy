/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "server_function.h"

static char check_incantation_ressources(server_config_t *server,
	server_user_t *user)
{
	tile_t *tile = map_get_tile(server->map, user->pos.y, user->pos.x);

	if (user->level < 1 || user->level > 7)
		return (0);
	if (find_nb_user_at_pos_and_level(server, user->pos.x,
			user->pos.y, user->level)
		!= (int)INCANTATION_OBJ[user->level - 1][0])
		return (0);
	for (int i = LINEMATE; i <= THYSTAME; ++i)
		if (INCANTATION_OBJ[user->level - 1][i] != (*tile)[i])
			return (0);
	return (1);
}

uint8_t srv_cmd_incantation(server_config_t *server, server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	if (!check_incantation_ressources(server, user)) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	dprintf(user->fd, "Elevation underway\nCurrent level: %u\n",
		user->level);
	user->wait += 300;
	return (0);
}
