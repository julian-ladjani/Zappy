/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include <string.h>
#include <stdlib.h>

char *str_append(char *str, char *append)
{
	if (!append)
		return (str);
	str = realloc(str, sizeof(char) * (strlen(str) + strlen(append) + 1));
	str = strcat(str, append);
	return (str);
}
