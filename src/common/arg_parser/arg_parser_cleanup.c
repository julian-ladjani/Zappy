/*
** EPITECH PROJECT, 2018
** Julian's library
** File description:
** 	arg_parser_cleanup source file
*/

#include <regex.h>
#include <unistd.h>
#include <stdlib.h>
#include "arg_parser.h"

void cleanup_argument_parsing_output_args(arg_parser_output_t *output)
{
	if (output->output_type == ARG_PARSER_OUTPUT_TAB)
		for (size_t i = 0; i < output->nb_arg; i++)
			free(((void **) (output->args))[i]);
	free(output->args);
	output->args = NULL;
	output->nb_arg = 0;
}

void cleanup_argument_parsing_output(arg_parser_output_t *output)
{
	if (output == NULL)
		return;
	cleanup_argument_parsing_output_args(output);
	free(output);
}

void cleanup_argument_parsing_input(arg_parser_input_t *input)
{
	free(input);
}

void *cleanup_argument_parsing(arg_parser_output_t *output,
	regex_t *start_regex, regex_t *stop_regex, void *return_value)
{
	if (return_value == NULL) {
		cleanup_argument_parsing_output(output);
		return (NULL);
	}
	cleanup_regex(stop_regex);
	cleanup_regex(start_regex);
	return (output);
}
