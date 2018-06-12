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
#include "include/circbuff.h"

void circbuf_print(int fd, circbuf_t *cb)
{
	if (cb->get_hspace(cb) >= cb->get_tspace(cb)) {
		write(fd, cb->tail, cb->get_tspace(cb));
		write(fd, cb->buf, cb->size - cb->get_hspace(cb));
	} else {
		write(fd, cb->tail, (unsigned int)abs(
			(int)(cb->head - cb->tail)));
	}
}

void circbuf_print_debug(int fd, circbuf_t *cb)
{
	if (cb->get_hspace(cb) > cb->get_tspace(cb)) {
		write(fd, cb->buf, cb->size - cb->get_hspace(cb) - 1);
		write(fd, "\e[31mH\e[0m", strlen("\e[31mH\e[0m"));
		write(fd, cb->head + 1, (unsigned int)abs(
			(int)(cb->head - cb->tail)) - 1);
		write(fd, "\e[32mT\e[0m", strlen("\e[32mT\e[0m"));
		write(fd, cb->tail + 1, cb->get_tspace(cb));
	} else if (cb->get_hspace(cb) < cb->get_tspace(cb)) {
		write(fd, cb->buf, cb->size - cb->get_tspace(cb) - 1);
		write(fd, "\e[32mT\e[0m", strlen("\e[32mT\e[0m"));
		write(fd, cb->tail + 1, (unsigned int)abs(
			(int)(cb->head - cb->tail)) - 1);
		write(fd, "\e[31mH\e[0m", strlen("\e[31mH\e[0m"));
		write(fd, cb->head + 1, cb->get_hspace(cb));
	} else {
		write(fd, cb->buf, cb->size - cb->get_tspace(cb) - 1);
		write(fd, "\e[33mM\e[0m", strlen("\e[32mM\e[0m"));
		write(fd, cb->head + 1, cb->get_hspace(cb));
	}
	write(fd, "\n", 1);
}
