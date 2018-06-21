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

int team_find_nb_user_at_level(server_team_t *team, unsigned int level)
{
	list_t *user_list = team->users;
	server_user_t *user;
	int nb_user = 0;

	while (user_list) {
		user = user_list->elem;
		if (user && user->level == level)
			++nb_user;
		user_list = user_list->next;
	}
	return (nb_user);
}

int get_team_free_slots(server_team_t *team)
{
	if (!team)
		return (-1);
	return (team->slots - list_size(team->users));
}
