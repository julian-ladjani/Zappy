/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** find_player.c
*/

#include "server_struct.h"

server_user_t *find_player_by_id(server_config_t *server, int id)
{
	list_t *player_list = server->users;
	server_user_t *player;

	while (player_list) {
		player = player_list->elem;
		if (player && player->id == id)
			return (player);
		player_list = player_list->next;
	}
	return (NULL);
}
