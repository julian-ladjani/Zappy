/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** circbuff_utils.c
*/

#include <unistd.h>
#include "include/circbuff.h"
#include <string.h>

static int circbuf_strncmp(circbuf_t *cb, char *pos, char *str, size_t size)
{
	size_t bsize = cb->buf + cb->size - pos;

	if (bsize >= size)
		return (strncmp(str, pos, size));
	return (strncmp(str, pos, bsize) +
		strncmp(str, cb->head, size - bsize));
}

long int circbuf_strstr(circbuf_t *cb, char *to_find)
{
	size_t count = 0;

	for (char *i = cb->tail; i != cb->head; i = cb->next(cb, i)) {
		if (!circbuf_strncmp(cb, i, to_find, strlen(to_find)))
			return (count);
		++count;
	}
	return (-1);
}
