/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** look.c
*/

#include "server_function.h"

static void send_tile_content(server_config_t *server, server_user_t *user,
				unsigned int x, unsigned int y)
{
	int nb_player = find_nb_user_at_pos(server, x, y);
	char *tile_ressources = tile_to_str(*map_get_tile(server->map, x, y));
	char *tile_content = NULL;

	for (int i = 0; i < nb_player; ++i) {
		tile_content = str_append(tile_content,
					tile_content ? " " : "");
		tile_content = str_append(tile_content, "player");
	}
	if (tile_content && tile_ressources)
		str_append(tile_content, " ");
	str_append(tile_content, tile_ressources);
	if (tile_content)
		dprintf(user->fd, tile_content);
	free(tile_ressources);
	free(tile_content);
}

static void select_tile_to_look(server_config_t *server, server_user_t *user,
				unsigned int level, int i)
{
	switch (user->orientation) {
	case (NORTH):
		send_tile_content(server, user, user->x + i, user->y + level);
		break;
	case (EAST):
		send_tile_content(server, user, user->x + level, user->y - i);
		break;
	case (SOUTH):
		send_tile_content(server, user, user->x - i, user->y - level);
		break;
	case (WEST):
		send_tile_content(server, user, user->x - level, user->y + i);
		break;
	}
}

uint8_t srv_cmd_look(server_config_t *server, server_user_t *user,
			__attribute__((unused))cmdparams_t *cmd)
{
	dprintf(user->fd, "[");
	send_tile_content(server, user, user->x, user->y);
	for (int l = 1; l <= (int)user->level; ++l) {
		for (int i = -l; i <= l; ++i) {
			select_tile_to_look(server, user, l, i);
			dprintf(user->fd, ", ");
		}
	}
	dprintf(user->fd, "]\n");
	user->wait += 7;
	return (0);
}
