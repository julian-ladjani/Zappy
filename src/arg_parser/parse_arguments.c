/*
** EPITECH PROJECT, 2018
** Julian's library
** File description:
** 	parse_arguments source file
*/

#include <regex.h>
#include <unistd.h>
#include "arg_parser.h"

void *parse_arguments(arg_parser_input_t *input_data,
	void *(*tokenize_func)(void *save, char *data))
{
	regex_t *search_regex = NULL;
	regex_t *stop_regex = NULL;

	if (input_data == NULL)
		return (NULL);
	if (input_data->search_regexp != NULL)
		search_regex = init_regex(input_data->search_regexp);
	if (input_data->stop_regexp != NULL)
		stop_regex = init_regex(input_data->stop_regexp);
	if ((input_data->search_regexp != NULL && search_regex == NULL) ||
		(input_data->stop_regexp != NULL && stop_regex == NULL))
		return (cleanup_argument_parsing(NULL, search_regex,
			stop_regex, NULL));
}
