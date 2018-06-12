/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** circuff_file.c
*/

#include <sys/param.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "circbuff.h"

char *circbuf_bufferise(circbuf_t *cb)
{
	char *buf = calloc((cb->get_used(cb) + 1), sizeof(char));
	char *pos = cb->tail;

	if (!buf)
		return (NULL);
	for (unsigned int i = 0; i < cb->get_used(cb) && pos; ++i) {
		buf[i] = *pos;
		pos = cb->next(cb, pos);
	}
	return (buf);
}

char *circbuf_nbufferise(circbuf_t *cb, unsigned int n)
{
	char *buf;
	char *pos = cb->tail;

	if (n >= cb->get_used(cb))
		return (circbuf_bufferise(cb));
	buf = calloc((n + 1), sizeof(char));
	if (!buf)
		return (NULL);
	for (unsigned int i = 0; i < n && pos; ++i) {
		buf[i] = *pos;
		pos = cb->next(cb, pos);
	}
	return (buf);
}

char *circbuf_get_buf(circbuf_t *cb)
{
	*(cb->head) = '\0';
	return (cb->tail);
}

long int circbuf_free_nspace(circbuf_t *cb, unsigned int size)
{
	long int i = 0;

	while (size - i != 0 && cb->tail != cb->head) {
		cb->tail = cb->next(cb, cb->tail);
		++i;
	}
	return (i);
}

void circbuf_free_space(circbuf_t *cb)
{
	cb->head = cb->buf;
	cb->tail = cb->head;
}
