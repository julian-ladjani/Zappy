/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** game_end.c
*/

#include "server_function.h"

static server_team_t *get_winning_team(server_config_t *server)
{
	list_t *team_list = server->teams;
	server_team_t *team;

	while (team_list) {
		team = team_list->elem;
		if (team_find_nb_user_at_level(team, 8) >= 6)
			return (team);
		team_list = team_list->next;
	}
	return (NULL);
}

char check_game_end(server_config_t *server)
{
	server_team_t *team = get_winning_team(server);
	char *msg;

	if (!team)
		return (0);
	asprintf(&msg, "seg %s\n", team->name);
	send_msg_to_all_graphic(server, msg);
	free(msg);
	server->state = ZAPPY_SERVER_STOP;
	return (1);
}
