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