/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_check_arg source file
*/

#include <stdio.h>
#include "server_struct.h"
#include "server_function.h"
#include "arg_parser.h"

static void check_server_argument_number(long number, int *error,
	char *error_message)
{
	if (number == 0 || number < 0) {
		*error = ARG_PARSER_FAILURE;
		printf("%s", error_message);
	}
}

static void check_server_argument_tab(char **tab, int *error,
	char *error_message)
{
	if (tab == NULL || tab[0] == NULL) {
		*error = ARG_PARSER_FAILURE;
		printf("%s", error_message);
	}
}

int check_server_arguments(server_argument_t *server_argument)
{
	int error = ARG_PARSER_SUCCESS;

	check_server_argument_tab(server_argument->team_names,
		&error, "Error: No team name given\n");
	check_server_argument_number(server_argument->port, &error,
		"Error: No valid port given\n");
	check_server_argument_number(server_argument->width, &error,
		"Error: No valid width given\n");
	check_server_argument_number(server_argument->height, &error,
		"Error: No valid height given\n");
	check_server_argument_number(server_argument->client_nb,
		&error, "Error: No valid client number given\n");
	check_server_argument_number(server_argument->frequency,
		&error, "Error: No valid frequency given\n");
	if (error == ARG_PARSER_FAILURE) {
		cleanup_server_arguments(server_argument);
		return (ARG_PARSER_FAILURE);
	}
	return (ARG_PARSER_SUCCESS);
}
