/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** my_strtok.c
*/

#include <memory.h>
#include <stdio.h>

char *sstrtok(char *str, char const *delims)
{
	static char *src = NULL;
	char *tmp;

	if (str)
		src = strdup(str);
	if (!src)
		return (NULL);
	tmp = strstr(src, delims);
	if (tmp) {
		char *save = src;
		*tmp = '\0';
		src = tmp + strlen(delims);
		return (save);
	}
	tmp = src;
	src = NULL;
	return (tmp);
}