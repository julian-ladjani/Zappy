/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_parse_arg_func source file
*/

#include "server_struct.h"
#include "server_function.h"
#include "arg_parser.h"

void parse_argument_port(server_argument_t *server_argument,
	arg_parser_input_t *input)
{
	arg_parser_output_t *output;

	input->start_regexp = "-p\0";
	output = get_arg(input);
	if (output != NULL && output->nb_arg == 1 &&
		output->output_type == ARG_PARSER_OUTPUT_PTR)
		server_argument->port = (unsigned short) atoi(output->args);
	cleanup_argument_parsing_output(output);
}