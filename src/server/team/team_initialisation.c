/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	team_initialisation source file
*/

#include "server_struct.h"
#include "server_function.h"

server_team_t *initialise_server_team(server_config_t *server_config,
	char *name)
{
	server_team_t *server_team;

	if (name == NULL)
		return (NULL);
	printf("Info: Initialise Server Team: %s\n", name);
	server_team = malloc(sizeof(server_team_t));
	if (server_team == NULL)
		return (NULL);
	server_team->name = strdup(name);
	if (server_team->name == NULL) {
		cleanup_team_list_elem(server_team);
		return (NULL);
	}
	server_team->slots = (int) server_config->arguments->client_nb;
	server_team->users = NULL;
	return (server_team);
}

list_t *initialise_server_teams(server_config_t *server_config)
{
	list_t *server_teams = NULL;
	server_team_t *team;

	printf("Info: Initialise Server teams\n");
	for (size_t i = 0; server_config->arguments->team_names[i] != NULL;
		i++) {
		team = initialise_server_team(server_config,
			server_config->arguments->team_names[i]);
		if (team == NULL) {
			list_delete_all(server_teams,
				cleanup_team_list_elem);
			return (NULL);
		}
		server_teams = list_add_elem_at_pos_releasably(
			server_teams, team, LIST_END, LIST_RELEASABLE);
	}
	return (server_teams);
}