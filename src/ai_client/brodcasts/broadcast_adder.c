/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_parser.c
*/

#include "client.h"
#include "broadcast.h"

void dump_broadcast(void *elem)
{
	clt_msg_t *msg = elem;

	printf("Message : %d - %d - %s\n", msg->id, msg->from,
		broadcast_type_str
			(((msg_infos_inc_t *)msg->content)->state));
}

char *broadcast_type_str(incantation_state_t s)
{
	if (s == NEED_STOP_HELPING)
		return ("need stop helping");
	if (s == HELPING)
		return ("helping");
	if (s == NEED_HELP)
		return ("need help");
	if (s == START)
		return ("start");
	if (s == STOP_HELPING)
		return ("stop helping");
	if (s == CANCELED)
		return ("canceled");
	return (NULL);
}

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
	int _for = ((msg_infos_inc_t *)msg->content)->_for;

	if (elem && (_for == (int) client->specs->id || _for == 0)) {
		client->server->broadcasts_queue =
			list_delete_elem(elem, clean_broadcast);
	}
	client->server->broadcasts_queue = list_add_elem_at_pos
		(client->server->broadcasts_queue, (void *)msg, LIST_FIRST);
	return (0);
}