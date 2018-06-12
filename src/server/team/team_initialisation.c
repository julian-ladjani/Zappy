/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	team_initialisation source file
*/

#include "server_struct.h"

server_team_t *initialise_server_team(char *name)
{
	server_team_t *server_team;

	if (name == NULL)
		return (NULL);
	server_team = malloc(sizeof(server_team_t));
	if (server_team == NULL)
		return (NULL);
	server_team->name = name;
	server_team->users = NULL;
	return (server_team);
}