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

void cleanup_argument_parsing_output(arg_parser_output_t *output)
{
	if (output == NULL)
		return;
	free(output->args);
	free(output);
}

void *cleanup_argument_parsing(arg_parser_output_t *output,
	regex_t *start_regex, regex_t *stop_regex, void *return_value)
{
	if (return_value == NULL)
		cleanup_argument_parsing_output(output);
	cleanup_regex(stop_regex);
	cleanup_regex(start_regex);
	return (output);
}
