/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	cleanup_server_arguments source file
*/

#include "server_struct.h"

void cleanup_server_arguments(server_argument_t *arguments)
{
	if (arguments == NULL)
		return;
	if (arguments->team_names != NULL)
		for(size_t i = 0; arguments->team_names[i] != NULL; i++)
			free(arguments->team_names[i]);
	free(arguments->team_names);
	free(arguments);
}