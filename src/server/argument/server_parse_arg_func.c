/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_parse_arg_func source file
*/

#include "server_struct.h"
#include "server_function.h"
#include "arg_parser.h"
#include "utils.h"

void parse_argument_ushort(unsigned short *data, char *start_regexp,
	arg_parser_input_t *input)
{
	arg_parser_output_t *output;

	input->start_regexp = start_regexp;
	output = get_arg(input);
	if (output != NULL && output->nb_arg == 1 &&
		output->output_type == ARG_PARSER_OUTPUT_PTR)
		*data = (unsigned short) atoi(output->args);
	cleanup_argument_parsing_output(output);
}

void parse_argument_uint(unsigned int *data, char *start_regexp,
	arg_parser_input_t *input)
{
	arg_parser_output_t *output;

	input->start_regexp = start_regexp;
	output = get_arg(input);
	if (output != NULL && output->nb_arg == 1 &&
		output->output_type == ARG_PARSER_OUTPUT_PTR)
		*data = (unsigned int) atoi(output->args);
	cleanup_argument_parsing_output(output);
}

void parse_argument_size_t(size_t *data, char *start_regexp,
	arg_parser_input_t *input)
{
	arg_parser_output_t *output;

	input->start_regexp = start_regexp;
	output = get_arg(input);
	if (output != NULL && output->nb_arg == 1 &&
		output->output_type == ARG_PARSER_OUTPUT_PTR)
		*data = (size_t) atoi(output->args);
	cleanup_argument_parsing_output(output);
}

void parse_argument_tab(char ***data, char *start_regexp,
	arg_parser_input_t *input)
{
	arg_parser_output_t *output;

	input->start_regexp = start_regexp;
	output = get_arg(input);
	if (output == NULL)
		return;
	if (output->nb_arg > 0)
		*data = malloc(sizeof(char *) * (output->nb_arg + 1));
	else
		return (cleanup_argument_parsing_output(output));
	if (*data == NULL)
		return (cleanup_argument_parsing_output(output));
	memset(*data, 0, sizeof(char *) * (output->nb_arg + 1));
	if (output->nb_arg == 1 &&
		output->output_type == ARG_PARSER_OUTPUT_PTR)
		*data[0] = strdup(output->args);
	else
		tab_mncpy(*data, output->args, output->nb_arg);
	cleanup_argument_parsing_output(output);
}
