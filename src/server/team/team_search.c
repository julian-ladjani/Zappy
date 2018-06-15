/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	team_search source file
*/

#include "server_struct.h"

int team_name_search_criteria(void *team, void *name)
{
	char *name_str = name;

	if (team == NULL || name == NULL)
		return (0);
	if (((server_team_t *) team)->name == NULL)
		return (0);
	if (strcmp(((server_team_t *) team)->name, name_str) == 0)
		return (1);
	return (0);
}

server_team_t *find_team_by_user(server_config_t *server_config,
					server_user_t *user)
{
	list_t *team_list = server_config->teams;
	server_team_t *team;

	while (team_list) {
		team = team_list->elem;
		if (team && list_get_elem_with_content(team->users, user))
			return (team);
		team_list = team_list->next;
	}
	return (NULL);
}

int get_team_free_slots(server_team_t *team)
{
	if (!team)
		return (-1);
	return (team->slots - list_size(team->users));
}
