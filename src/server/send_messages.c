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

	while (user_list) {
		user = user_list->elem;
		if (user && user->type == ZAPPY_USER_GRAPHIC)
			dprintf(user->fd, msg);
		user_list = user_list->next;
	}
}