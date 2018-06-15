/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	tab_cpy source file
*/

#include <stdlib.h>
#include <string.h>

char **tab_ncpy(char **dst, char **src, size_t len)
{
	for (size_t i = 0; i < len; i++)
		dst[i] = src[i];
	return (dst);
}

char **tab_mncpy(char **dst, char **src, size_t len)
{
	short error = 0;

	for (size_t i = 0; i < len; i++) {
		dst[i] = strdup(src[i]);
		if (dst[i] == NULL) {
			error = 1;
		}
	}
	if (error == 1)
		for (size_t i = 0; i < len; i++) {
			free(dst[i]);
			dst[i] = NULL;
		}
	return (dst);
}

size_t tab_len(char **tab)
{
	size_t len = 0;

	while (tab[len] != NULL)
		len++;
	return (len);
}

char **tab_mcpy(char **dst, char **src)
{
	return (tab_mncpy(dst, src, tab_len(src)));
}

char **tab_cpy(char **dst, char **src)
{
	return (tab_ncpy(dst, src, tab_len(src)));
}