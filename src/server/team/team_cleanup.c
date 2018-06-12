/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	team_cleanup source file
*/

#include "server_struct.h"

void cleanup_team_list_elem(void *elem)
{
	server_team_t *server_team = elem;

	if (elem == NULL)
		return;
	free(server_team->name);
	list_delete_all(server_team->users, NULL);
	free(elem);
}

void cleanup_teams(list_t *server_teams)
{
	printf("Info: Cleanup Users\n");
	if (server_teams == NULL)
		return;
	list_delete_all(server_teams, cleanup_team_list_elem);
}
