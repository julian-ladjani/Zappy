/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** send_messages.c
*/

#include "server_struct.h"

void send_msg_to_all_graphic(server_config_t *server, char *msg)
{
	list_t *user_list = server->users;
	server_user_t *user;

	if (!msg)
		return;
	while (user_list) {
		user = user_list->elem;
		if (user && user->type == ZAPPY_USER_GRAPHIC)
			dprintf(user->fd, "%s", msg);
		user_list = user_list->next;
	}
}

void send_player_list_to_user(server_config_t *server,
	server_user_t *user)
{
	list_t *player_list = server->users;
	server_user_t *player;

	while (player_list) {
		player = player_list->elem;
		if (player && player->type == ZAPPY_USER_AI) {
			dprintf(user->fd, "pnw #%d %lu %lu %d %u %s\n",
				player->id, player->pos.x, player->pos.y,
				player->orientation, player->level,
				player->team->name);
		}
		player_list = player_list->next;
	}
}
