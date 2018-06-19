/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** epurstr.c
*/

#include "utils.h"

static void mvstr(char *str, size_t size)
{
	for (; *str; ++str)
		*str = str[size];
}

void epurstr(char *str, checker_t checker)
{
	size_t i;

	for (i = 0; str[i] && checker(str[i]); ++i);
	mvstr(str, i);
	while (str[0] && str[1]) {
		for (i = 0; str[i] && str[i + 1] &&
				checker(str[i]) && checker (str[i + 1]); ++i);
		i ? mvstr(str, i) : ++str;
	}
	if (str[0] && !str[1] && checker(str[0]))
		mvstr(str, 1);
}