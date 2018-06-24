/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** str_append.c
*/

#include "utils.h"

char *str_append(char *str, const char *append)
{
	size_t str_len = (str ? strlen(str) : 0);
	size_t len = str_len + (append ? strlen(append) : 0) + 1;

	if (!append)
		return (str);
	str = realloc(str, sizeof(char) * len);
	if (str_len == 0)
		memset(str, 0, len);
	str = strcat(str, append);
	return (str);
}

char *str_append_number(char *str, const unsigned int num)
{
	char *number;

	asprintf(&number, "%u", num);
	str = str_append(str, number);
	free(number);
	return (str);
}
