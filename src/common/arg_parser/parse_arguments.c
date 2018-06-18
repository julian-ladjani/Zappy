/*
** EPITECH PROJECT, 2018
** Julian's library
** File description:
** 	parse_arguments source file
*/

#include <regex.h>
#include <unistd.h>
#include "arg_parser.h"

static char *get_start_arg(arg_parser_input_t *input,
	arg_parser_output_t *output, regex_t *start_regex, char *arg)
{
	if (argument_correspond_to_regex(start_regex,
		arg) == ARG_PARSER_SUCCESS) {
		if (input->interval == ARG_PARSER_OPEN ||
			input->interval == ARG_PARSER_SEMI_OPEN_LEFT)
			input->tokenize_func(output, arg);
		return (arg);
	}
	return (NULL);
}

static char *get_stop_arg(arg_parser_input_t *input,
	arg_parser_output_t *output, regex_t *stop_regex, char *arg)
{
	if (argument_correspond_to_regex(stop_regex,
		arg) == ARG_PARSER_SUCCESS) {
		if (input->interval == ARG_PARSER_OPEN ||
			input->interval == ARG_PARSER_SEMI_OPEN_RIGHT)
			input->tokenize_func(output, arg);
		return (arg);
	}
	return (NULL);
}

static int do_action_multiple_occurrence(arg_parser_input_t *input,
	arg_parser_output_t *output, regex_t *start_regex, char *arg)
{
	if (argument_correspond_to_regex(start_regex,
		arg) != ARG_PARSER_SUCCESS)
		return (ARG_PARSER_FAILURE);
	if (input->occurrence_action == ARG_PARSER_OVERWRITE)
		cleanup_argument_parsing_output_args(output);
	return (ARG_PARSER_SUCCESS);
}

static arg_parser_output_t *parse_argument_loop(
	arg_parser_input_t *input, arg_parser_output_t *output,
	regex_t *start_regex, regex_t *stop_regex)
{
	char *start_arg = NULL;

	for (size_t i = input->offset; input->argv[i] != NULL; i++) {
		if (start_arg == NULL)
			start_arg = get_start_arg(input, output,
				start_regex, input->argv[i]);
		if (argument_correspond_to_regex(start_regex,
			input->argv[i]) == ARG_PARSER_FAILURE &&
			get_stop_arg(input, output, stop_regex,
				input->argv[i]) != NULL)
			start_arg = NULL;
		if (start_arg != NULL &&
			do_action_multiple_occurrence(input, output,
				start_regex,
				input->argv[i]) != ARG_PARSER_SUCCESS)
			input->tokenize_func(output, input->argv[i]);
	}
	return (cleanup_argument_parsing(output, start_regex, stop_regex,
		output));
}

arg_parser_output_t *arg_parser_parse_arguments
	(arg_parser_input_t *input)
{
	regex_t *start_regex = NULL;
	regex_t *stop_regex = NULL;
	arg_parser_output_t *output;

	if (input == NULL)
		return (NULL);
	if (input->start_regexp != NULL)
		start_regex = init_regex(input->start_regexp);
	if (input->stop_regexp != NULL)
		stop_regex = init_regex(input->stop_regexp);
	output = initialise_arg_parser_output();
	if (start_regex == NULL || output == NULL || stop_regex == NULL)
		return (cleanup_argument_parsing(output, start_regex,
			stop_regex, NULL));
	return (parse_argument_loop(input, output, start_regex,
		stop_regex));
}
