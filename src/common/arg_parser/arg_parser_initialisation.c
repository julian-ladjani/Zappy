/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	arg_parser_initalisation source file
*/

#include <stdlib.h>
#include "arg_parser.h"

arg_parser_input_t *initialise_arg_parser_input(void)
{
	arg_parser_input_t *input = malloc(sizeof(*input));

	if (input == NULL)
		return (NULL);
	input->argv = NULL;
	input->offset = 0;
	input->start_regexp = NULL;
	input->stop_regexp = NULL;
	input->tokenize_func = NULL;
	input->interval = ARG_PARSER_CLOSE;
	return (input);
}

arg_parser_output_t *initialise_arg_parser_output(void)
{
	arg_parser_output_t *output = malloc(sizeof(*output));

	if (output == NULL)
		return (NULL);
	output->args = NULL;
	output->nb_arg = 0;
	output->next_arg = NULL;
	return (NULL);
}