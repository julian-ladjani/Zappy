/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation_end.c
*/

#include "server_function.h"

void send_to_player_in_incantation(server_config_t *server,
	server_user_t *user, char *msg)
{
	list_t *player_list = server->users;
	server_user_t *player;

	while (player_list) {
		player = player_list->elem;
		if (player && user->type == ZAPPY_USER_AI
			&& player->pos.x == user->pos.x
			&& player->pos.y == user->pos.y)
			dprintf(user->fd, "%s", msg);
		player_list = player_list->next;
	}
}

static void incantation_level_up(server_config_t *server, server_user_t *user)
{
	list_t *player_list = server->users;
	server_user_t *player;

	while (player_list) {
		player = player_list->elem;
		if (player && user->type == ZAPPY_USER_AI
			&& player->pos.x == user->pos.x
			&& player->pos.y == user->pos.y)
			player->level += 1;
		player_list = player_list->next;
	}
}

uint8_t incantation_end(server_config_t *server, server_user_t *user)
{
	char *msg;
	tile_t *tile = map_get_tile(server->map, user->pos.x, user->pos.y);

	if (!check_incantation_ressources(server, user)) {
		send_to_player_in_incantation(server, user, "ko\n");
		asprintf(&msg, "pie %lu %lu ko\n", user->pos.x, user->pos.y);
		send_msg_to_all_graphic(server, msg);
		free(msg);
		return (1);
	}
	incantation_level_up(server, user);
	user->incanting = 0;
	empty_tile(tile, (*tile)[FOOD]);
	asprintf(&msg, "Current level: %u\n", user->level);
	send_to_player_in_incantation(server, user, msg);
	free(msg);
	asprintf(&msg, "pie %lu %lu ok\n", user->pos.x, user->pos.y);
	send_msg_to_all_graphic(server, msg);
	free(msg);
	return (0);
}
