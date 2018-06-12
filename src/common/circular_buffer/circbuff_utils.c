/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** circbuff_utils.c
*/

#include <unistd.h>
#include "include/circbuff.h"

char *circbuf_next(circbuf_t *cb, char *pos)
{
	if (pos >= cb->buf && pos < cb->buf + cb->size)
		return (cb->buf + ((++pos - cb->buf) % cb->size));
	return (NULL);
}

unsigned int circbuf_get_space(const circbuf_t *cb)
{
	if (cb->head >= cb->tail)
		return (cb->size - (unsigned int)(cb->head - cb->tail));
	else
		return ((unsigned int)(cb->tail - cb->head));
}

unsigned int circbuf_get_used_space(const circbuf_t *cb)
{
	return (cb->size - circbuf_get_space(cb));
}

unsigned int circbuf_get_hspace(const circbuf_t *cb)
{
	return (cb->size - (unsigned int)(cb->head - cb->buf) -1);
}

unsigned int circbuf_get_tspace(const circbuf_t *cb)
{
	return (cb->size - (unsigned int)(cb->tail - cb->buf) - 1);
}
