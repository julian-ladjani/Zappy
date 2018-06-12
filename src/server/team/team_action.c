/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	team_action source file
*/

#include "server_struct.h"
#include "server_function.h"

static void team_name_reply_team_users(server_team_t *team,
	server_user_t *cur_user)
{
	list_t *users;
	char first = 0;
	server_user_t *user;

	if (team == NULL || cur_user == NULL)
		return;
	users = list_get_first(team->users);
	while (users != NULL) {
		user = users->elem;
		if (user != NULL && user->nick != NULL && first == 0)
			dprintf(cur_user->fd, ":serv 353 %s = %s :%s",
				cur_user->nick, team->name, user->nick);
		else if (user != NULL && user->nick != NULL)
			dprintf(cur_user->fd, " %s", user->nick);
		users = users->next;
		first = 1;
	}
	if (first == 1)
		dprintf(cur_user->fd, "\r\n");
}

void team_name_reply(list_t *team, server_user_t *user, char *name)
{
	server_team_t *elem;

	if (user == NULL)
		return;
	team = list_get_first(team);
	while (team != NULL) {
		elem = team->elem;
		if (team->elem != NULL && elem->name != NULL &&
			(name == NULL || strcmp(name, elem->name) == 0)) {
			team_name_reply_team_users(team->elem, user);
		}
		team = team->next;
	}
	if (name != NULL)
		dprintf(user->fd, ":serv 366 %s %s :End of /NAMES list\r\n",
			user->nick, name);
}

void team_send_message(server_team_t *team, char *message)
{
	list_t *user;

	if (message == NULL || team == NULL)
		return;
	user = team->users;
	while (user != NULL) {
		user_send_message(user->elem, message);
		user = user->next;
	}
}

void team_priv_msg_send_message(server_team_t *team, char *message,
	server_user_t *cur_user)
{
	list_t *user;

	if (message == NULL || team == NULL)
		return;
	user = team->users;
	while (user != NULL) {
		if (user->elem != cur_user)
			user_send_message(user->elem, message);
		user = user->next;
	}
}