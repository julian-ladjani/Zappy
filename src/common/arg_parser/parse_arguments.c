/*
** EPITECH PROJECT, 2018
** Julian's library
** File description:
** 	parse_arguments source file
*/

#include <regex.h>
#include <unistd.h>
#include "arg_parser.h"

static int argument_correspond_to_regex(regex_t *start_regex, char *arg)
{
	if (arg == NULL || start_regex == NULL)
		return (ARG_PARSER_FAILURE);
	if (argument_check_regex(arg, start_regex) == ARG_PARSER_SUCCESS)
		return (ARG_PARSER_SUCCESS);
	return (ARG_PARSER_FAILURE);
}

static char *get_start_arg(arg_parser_input_t *input_data,
	arg_parser_output_t *output_data, regex_t *start_regex, char *arg)
{
	if (argument_correspond_to_regex(start_regex,
		arg) == ARG_PARSER_SUCCESS) {
		if (input_data->interval == ARG_PARSER_OPEN ||
			input_data->interval == ARG_PARSER_SEMI_OPEN_LEFT)
			input_data->tokenize_func(output_data, arg);
		return (arg);
	}
	return (NULL);
}

static char *get_stop_arg(arg_parser_input_t *input_data,
	arg_parser_output_t *output_data, regex_t *stop_regex, char *arg)
{
	if (argument_correspond_to_regex(stop_regex,
		arg) == ARG_PARSER_SUCCESS) {
		if (input_data->interval == ARG_PARSER_OPEN ||
			input_data->interval == ARG_PARSER_SEMI_OPEN_RIGHT)
			input_data->tokenize_func(output_data, arg);
		return (arg);
	}
	return (NULL);
}

static void *parse_argument_loop(arg_parser_input_t *input_data,
	arg_parser_output_t *output_data,
	regex_t *start_regex, regex_t *stop_regex)
{
	char *start_arg = NULL;
	char *stop_arg = NULL;

	for (size_t i = input_data->offset;
		input_data->argv[i] != NULL && stop_arg == NULL; i++) {
		if (start_arg == NULL)
			start_arg = get_start_arg(input_data, output_data,
				start_regex, input_data->argv[i]);
		else
			input_data->tokenize_func(output_data,
				input_data->argv[i]);
		stop_arg = get_start_arg(input_data, output_data,
			stop_regex, input_data->argv[i]);
	}
	return (output_data);
}

void *parse_program_arguments(arg_parser_input_t *input_data)
{
	regex_t *start_regex = NULL;
	regex_t *stop_regex = NULL;
	arg_parser_output_t *output;

	if (input_data == NULL)
		return (NULL);
	if (input_data->start_regexp != NULL)
		start_regex = init_regex(input_data->start_regexp);
	if (input_data->stop_regexp != NULL)
		stop_regex = init_regex(input_data->stop_regexp);
	output = initialise_arg_parser_output();
	if ((input_data->start_regexp != NULL && start_regex == NULL) ||
		output == NULL ||
		(input_data->stop_regexp != NULL && stop_regex == NULL))
		return (cleanup_argument_parsing(output, start_regex,
			stop_regex, NULL));
	return (parse_argument_loop(input_data, output, start_regex,
		stop_regex));
}
