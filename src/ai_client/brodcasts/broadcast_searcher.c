/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_searcher.c
*/

#include "broadcast.h"

int condition_search_incantation(clt_config_t *clt, void *elem)
{
	clt_msg_t *msg = (clt_msg_t *)elem;
	msg_infos_inc_t *infos;

	if (!msg)
		return (0);
	infos = (msg_infos_inc_t *) msg->content;
	return (infos && msg->type == MSG_INCANTATION &&
		infos->level == (int) clt->specs->level &&
		infos->state == NEED_HELP);
}

int condition_targeted_incantation(clt_config_t *clt, void *elem)
{
	clt_msg_t *msg = (clt_msg_t *)elem;
	msg_infos_inc_t *infos;

	if (!msg)
		return (0);
	infos = (msg_infos_inc_t *) msg->content;
	return (infos && msg->type == MSG_INCANTATION &&
		(infos->state == NEED_HELP || infos->state == START) &&
		infos->level == (int) clt->specs->level);
}

clt_msg_t *broadcast_search_for(clt_config_t *clt,
				int (* checker)(clt_config_t *, void *))
{
	list_t *elem = list_get_elem_at_pos(
		clt->server->broadcasts_queue, LIST_FIRST);

	while (elem != NULL) {
		if (checker(clt, elem->elem))
			return ((clt_msg_t *)elem->elem);
		elem = elem->next;
	}
	return (NULL);
}