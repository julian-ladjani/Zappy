/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_action source file
*/

#include "server_struct.h"

void user_send_message(server_user_t *user, char *message)
{
	if (user == NULL || message == NULL)
		return;
	dprintf(user->fd, "%s\r\n", message);
}

void user_send_message_users_same_team(server_config_t *server_config,
	server_user_t *user, char *message)
{
	list_t *users;
	server_user_t *o_user;

	if (server_config == NULL || user == NULL || message == NULL)
		return;
	users = server_config->users;
	while (users != NULL) {
		o_user = users->elem;
		if (o_user != NULL &&
			o_user->logged_state != ZAPPY_USER_QUIT &&
			user->team == o_user->team)
			dprintf(o_user->fd, "%s\r\n", message);
		users = users->next;
	}
}

void user_connect(server_user_t *user)
{
	if (user->logged_state == ZAPPY_USER_QUIT)
		return;
	user->logged_state = ZAPPY_USER_CONNECTED;
}