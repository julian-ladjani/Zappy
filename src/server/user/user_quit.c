/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_quit source file
*/

#include "server_struct.h"
#include "server_function.h"

void user_quit_part_teams(server_config_t *server_config,
	server_user_t *user)
{
	list_t *teams = user->teams;
	server_team_t *elem;

	while (teams != NULL) {
		elem = teams->elem;
		elem->users = list_delete_elem(
			list_get_elem_with_content(elem->users, user), NULL);
		user->teams = list_delete_elem(
			list_get_elem_with_content(user->teams, elem),
			NULL);
		teams = user->teams;
		if (elem->users != NULL)
			return;
		printf("Remove Team: %s\n", elem->name);
		server_config->teams = list_delete_elem(
			list_get_elem_with_content(server_config->teams,
				elem),
			cleanup_team_list_elem);
	}
}

void user_quit(server_config_t *server_config, server_user_t *user,
	char *message)
{
	char *str;

	if (server_config == NULL || user == NULL || message == NULL)
		return;
	printf("Connection - %d Quit With Message: %s\n", user->fd,
		message);
	user->logged_state = ZAPPY_USER_QUIT;
	asprintf(&str, ":%s QUIT :%s", user->nick, message);
	user_send_message_users_same_team(server_config, user, str);
	free(str);
	user_quit_part_teams(server_config, user);
}