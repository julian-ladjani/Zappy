/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_parser.c
*/

#include "client.h"
#include "broadcast.h"

void clean_broadcast(void *elem)
{
	clt_msg_t *msg = (clt_msg_t *) elem;

	free(msg->content);
}

int broadcast_compare_from(void *elem, void *criteria)
{
	clt_msg_t *msg = (clt_msg_t *) elem;
	clt_msg_t *msg_copy = (clt_msg_t *) criteria;

	return (msg && msg_copy && msg_copy->from == msg->from);
}

int broadcast_add_elem(clt_config_t *client, clt_msg_t *msg)
{
	list_t *elem = list_get_elem_by_search
		(client->server->broadcasts_queue, (void *)msg,
		 broadcast_compare_from);

	if (elem)
		client->server->broadcasts_queue =
			list_delete_elem(elem, clean_broadcast);
	client->server->broadcasts_queue = list_add_elem_at_pos
		(client->server->broadcasts_queue, (void *)msg, LIST_FIRST);
	return (0);
}