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

long int circbuf_recv(int fd, circbuf_t *cb, unsigned int size)
{
	const char *end = cb->buf + cb->size - 1;
	unsigned int space = circbuf_get_hspace(cb) + 1;
	unsigned int fspace = circbuf_get_space(cb);
	long int n;

	if (end < cb->head)
		return (-1);
	n = read(fd, cb->head, MIN(space, size));
	if (cb->head + n > end + 1)
		return (-1);
	cb->head += n;
	if (cb->head > end)
		cb->head = cb->buf;
	if (n >= fspace)
		cb->tail = cb->next(cb, cb->head);
	return (n);
}

void circbuf_send(int fd, circbuf_t *cb)
{
	if (cb->get_hspace(cb) >= cb->get_tspace(cb)) {
		send(fd, cb->tail, cb->get_tspace(cb), 0);
		send(fd, cb->buf, cb->size - cb->get_hspace(cb), 0);
	} else {
		send(fd, cb->tail, (unsigned int)abs(
			(int)(cb->head - cb->tail)), 0);
	}
}
