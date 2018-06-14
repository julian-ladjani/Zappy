/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	argument_regex source file
*/

#include <regex.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arg_parser.h"

regex_t *init_regex(char *regex_string)
{
	regex_t *regex = malloc(sizeof(regex_t));

	if (regex == NULL)
		return NULL;
	if (regcomp(regex, regex_string,
		REG_NOSUB) != 0) {
		free(regex);
		return (NULL);
	}
	return (regex);
}

int argument_correspond_to_regex(regex_t *start_regex, char *arg)
{
	if (arg == NULL || start_regex == NULL)
		return (ARG_PARSER_FAILURE);
	if (argument_check_regex(arg, start_regex) == ARG_PARSER_SUCCESS)
		return (ARG_PARSER_SUCCESS);
	return (ARG_PARSER_FAILURE);
}

void cleanup_regex(regex_t *regex)
{
	if (regex == NULL)
		return;
	regfree(regex);
	free(regex);
}

int argument_check_regex(char *string, regex_t *regex)
{
	int match;

	printf("%s\n", string);
	if (string == NULL || regex == NULL)
		return (ARG_PARSER_FAILURE);
	match = regexec(regex, string, 0, NULL, 0);
	if (match == 0)
		return (ARG_PARSER_SUCCESS);
	return (ARG_PARSER_FAILURE);
}