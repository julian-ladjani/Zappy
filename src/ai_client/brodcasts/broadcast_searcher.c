/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_searcher.c
*/

#include "broadcast.h"

clt_msg_t *broadcast_search_for(list_t *msgs, msg_types_t type)
{
	list_t *elem;
	clt_msg_t *msg;

	elem = list_get_elem_at_pos(msgs, LIST_FIRST);
	while (elem != NULL) {
		msg = (clt_msg_t *)elem->elem;
		if (msg->type == type)
			return (msg);
		elem = elem->next;
	}
	return (NULL);
}

clt_msg_t *broadcast_search_for_incantation(list_t *msgs)
{
	return (broadcast_search_for(msgs, MSG_INCANTATION));
}
