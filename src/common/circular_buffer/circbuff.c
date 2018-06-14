/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** circbuff.c
*/

#include <stdlib.h>
#include "circbuff.h"

void circbuf_free(circbuf_t *cb)
{
	if (cb) {
		if (cb->buf)
			free(cb->buf);
		free(cb);
	}
}

static void circbuf_fillfunc(circbuf_t *cb)
{
	cb->recv = circbuf_recv;
	cb->send = circbuf_send;
	cb->next = circbuf_next;
	cb->bufferise = circbuf_bufferise;
	cb->nbufferise = circbuf_nbufferise;
	cb->get_buf = circbuf_get_buf;
	cb->get_space = circbuf_get_space;
	cb->get_used = circbuf_get_used_space;
	cb->get_hspace = circbuf_get_hspace;
	cb->get_tspace = circbuf_get_tspace;
	cb->print = circbuf_print;
	cb->debug = circbuf_print_debug;
	cb->free_space = circbuf_free_space;
	cb->free_nspace = circbuf_free_nspace;
	cb->free = circbuf_free;
}

circbuf_t *circbuf_create(unsigned int size)
{
	circbuf_t *cb = malloc(sizeof(circbuf_t));
	if (!cb)
		return (cb);
	cb->size = size + 1;
	cb->buf = calloc(cb->size * sizeof(char), sizeof(char));
	if (!cb->buf) {
		free(cb);
		return (NULL);
	}
	cb->head = cb->buf;
	cb->tail = cb->buf;
	circbuf_fillfunc(cb);
	return (cb);
}
