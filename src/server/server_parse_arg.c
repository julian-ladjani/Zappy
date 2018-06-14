/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_parse_arg source file
*/

#include "arg_parser.h"
#include "server_struct.h"
#include "server_function.h"

arg_parser_output_t *get_arg(arg_parser_input_t *input)
{
	arg_parser_output_t *output;

	asprintf(&input->stop_regexp, "^-(?!%s$).*$",
		input->start_regexp + 1);
	if (input->stop_regexp == NULL)
		return (NULL);
	output = arg_parser_parse_arguments(input);
	free(input->stop_regexp);
	return (output);
}

static server_argument_t *init_server_argument(void)
{
	server_argument_t *server_argument =
		malloc(sizeof(server_argument_t));

	if (server_argument == NULL)
		return (NULL);
	server_argument->port = 0;
	server_argument->client_nb = 0;
	server_argument->frequency = 0;
	server_argument->height = 0;
	server_argument->width = 0;
	return (server_argument);
}

server_argument_t *parse_server_argument(int ac, char **av)
{
	server_argument_t *server_argument = init_server_argument();
	arg_parser_input_t *input;

	if (server_argument == NULL)
		return (NULL);
	input = initialise_arg_parser_input();
	if (input == NULL)
		return (NULL);
	input->argv = av;
	input->argc = ac;
	input->tokenize_func = parse_string_arg;
	input->interval = ARG_PARSER_CLOSE;
	parse_argument_port(server_argument, input);
	return (server_argument);
}