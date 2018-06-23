/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_timer.c
*/

#include "broadcast.h"

void increment_broadcast_timer(void *elem)
{
	clt_msg_t *msg = (clt_msg_t *)elem;

	++msg->timer;
}

int test_broadcast_timer(void *elem, __attribute__((unused))void *criteria)
{
	clt_msg_t *msg = (clt_msg_t *)elem;

	return (msg->timer > 3);
}

void manage_broadcast_timer(clt_config_t *clt)
{
	list_t *list = clt->server->broadcasts_queue;
	list_dump(list, increment_broadcast_timer);
	list_t *elem = list_get_elem_by_search(
		list, NULL, test_broadcast_timer);

	while (elem) {
		list = list_delete_elem(elem, clean_broadcast);
		elem = list_get_elem_by_search(list, NULL,
						test_broadcast_timer);
	}
	clt->server->broadcasts_queue = list;
}