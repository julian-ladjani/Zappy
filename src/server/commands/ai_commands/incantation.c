/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "server_function.h"

char check_incantation_ressources(server_config_t *server, server_user_t *user)
{
	tile_t *tile = map_get_tile(server->map, user->pos.x, user->pos.y);

	if (user->level < 1 || user->level > 7)
		return (0);
	if (find_nb_user_at_pos_and_level(server, user->pos.x,
			user->pos.y, user->level)
		!= (int)INCANTATION_OBJ[user->level - 1][PLAYER])
		return (0);
	for (int i = LINEMATE; i <= THYSTAME; ++i)
		if (INCANTATION_OBJ[user->level - 1][i] != (*tile)[i])
			return (0);
	return (1);
}

static void send_incantation_message(server_config_t *server,
	server_user_t *user)
{
	list_t *player_list = server->users;
	server_user_t *player;
	char *msg;
	char *players = NULL;

	while (player_list) {
		player = player_list->elem;
		if (player && player->type == ZAPPY_USER_AI
			&& player->pos.x == user->pos.x
			&& player->pos.y == user->pos.y) {
			players = str_append(players, " ");
			players = str_append_number(players, player->id);
		}
		player_list = player_list->next;
	}
	asprintf(&msg, "pic %lu %lu %d%s\n", user->pos.x, user->pos.y,
		user->level, players);
	send_msg_to_all_graphic(server, msg);
	free(msg);
	free(players);
}

uint8_t srv_cmd_incantation(server_config_t *server, server_user_t *user,
	__attribute__((unused))cmdparams_t *cmd)
{
	char *msg;

	if (!check_incantation_ressources(server, user)) {
		dprintf(user->fd, "ko\n");
		return (1);
	}
	asprintf(&msg, "Elevation underway\n");
	send_to_player_in_incantation(server, user, msg);
	free(msg);
	send_incantation_message(server, user);
	user->wait += 300;
	return (0);
}
