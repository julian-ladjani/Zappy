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

static int channel_lists_have_same_elem(list_t *channel_list,
	list_t *o_channel_list)
{
	if (o_channel_list == NULL || channel_list == NULL)
		return (ZAPPY_EXIT_FAILURE);
	while (channel_list != NULL) {
		if (list_get_elem_with_content(o_channel_list,
			channel_list->elem) != NULL)
			return (ZAPPY_EXIT_SUCCESS);
		channel_list = channel_list->next;
	}
	return (ZAPPY_EXIT_FAILURE);
}

void user_send_message_users_same_channel(server_config_t *server_config,
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
			channel_lists_have_same_elem(user->teams,
				o_user->teams) == ZAPPY_EXIT_SUCCESS)
			dprintf(o_user->fd, "%s\r\n", message);
		users = users->next;
	}
}

void user_connect(server_user_t *user)
{
	if (user->logged_state == ZAPPY_USER_QUIT)
		return;
	if (user->logged_state != ZAPPY_USER_CONNECTED)
		dprintf(user->fd, ":serv 001 %s :%s %s!%s@%s\r\n",
			user->nick, "Welcome to the Internet Relay Network",
			user->nick, user->name, "localhost");
	user->logged_state = ZAPPY_USER_CONNECTED;
}