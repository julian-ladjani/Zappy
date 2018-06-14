/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	arg_parser_string source file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arg_parser.h"

static int parse_first_arg(arg_parser_output_t *output, char *data)
{
	output->output_type = ARG_PARSER_OUTPUT_PTR;
	output->args = strdup(data);
	if (output->args == NULL)
		return (ARG_PARSER_FAILURE);
	return (ARG_PARSER_SUCCESS);
}

static int parse_intermediate_arg(arg_parser_output_t *output, char *data)
{
	char *temp_arg;

	output->output_type = ARG_PARSER_OUTPUT_TAB;
	temp_arg = output->args;
	output->args = malloc(2 * sizeof(char *));
	if (output->args == NULL)
		return (ARG_PARSER_FAILURE);
	((char **) output->args)[0] = temp_arg;
	((char **) output->args)[1] = strdup(data);
	if (((char **) output->args)[1] == NULL)
		return (ARG_PARSER_FAILURE);
	return (ARG_PARSER_SUCCESS);
}

static int parse_in_tab_arg(arg_parser_output_t *output, char *data)
{
	output->args = realloc(output->args,
		(output->nb_arg + 1) * sizeof(char *));
	if (output->args == NULL)
		return (ARG_PARSER_FAILURE);
	((char **) output->args)[output->nb_arg] = strdup(data);
	if (((char **) output->args)[output->nb_arg] == NULL)
		return (ARG_PARSER_FAILURE);
	return (ARG_PARSER_SUCCESS);
}

void *parse_string_arg(arg_parser_output_t *output, char *data)
{
	int error;

	if (output->nb_arg == 0)
		error = parse_first_arg(output, data);
	else if (output->nb_arg == 1)
		error = parse_intermediate_arg(output, data);
	else
		error = parse_in_tab_arg(output, data);
	if (error == ARG_PARSER_FAILURE) {
		cleanup_argument_parsing_output_args(output);
		return (NULL);
	}
	output->nb_arg++;
	return (output->args);
}
