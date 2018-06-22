/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** pre_requests.c
*/

#include <broadcast.h>
#include "client.h"

int srvrequest_dead(clt_config_t *client)
{
	client->status = ZAPPY_CLT_DEAD;
	return (ZAPPY_EXIT_SUCCESS);
}

int test(void *elem, void *criteria)
{
	clt_msg_t *msg = (clt_msg_t *) criteria;
	clt_msg_t *msg_copy = (clt_msg_t *) criteria;

	return (msg_copy->from == msg->from);
}

void clean_broadcast(void *elem)
{
	clt_msg_t *msg = (clt_msg_t *) elem;

	free(msg->content);
	free(elem);
}

int srvrequest_message(clt_config_t *client)
{
	clt_msg_t *msg = calloc(sizeof(clt_msg_t), sizeof(clt_msg_t));
	char *tmp;

	if (!msg)
		return (ZAPPY_EXIT_SUCCESS);
	tmp = sstrtok(client->server->response_request, ",");
	msg->dir = atoi(strchr(tmp, ' ') + 1);
	if (msg->dir < 0 || msg->dir > 8 ||
		broadcast_parser(client, msg) == ZAPPY_EXIT_FAILURE) {
		free(msg);
		free(tmp);
		return (ZAPPY_EXIT_SUCCESS);
	}
	free(tmp);
	list_t *elem = list_get_elem_by_search
		(client->server->broadcasts_queue,
			(void *)msg, test);
	client->server->broadcasts_queue =
		list_delete_elem(elem, clean_broadcast);
	client->server->broadcasts_queue = list_add_elem_at_pos
		(client->server->broadcasts_queue, (void *)msg, LIST_FIRST);
	printf("%d\n", list_size(client->server->broadcasts_queue));
	return (ZAPPY_EXIT_SUCCESS);
}

int srvrequest_elevation_underway(clt_config_t *client)
{
	client->incantation = 1;
	return (ZAPPY_EXIT_SUCCESS);
}

int srvrequest_elevation_ko(clt_config_t *client)
{
	if (client->incantation == 1 &&
		strcmp(client->server->active_request, "Incantation") == 0) {
		client->incantation = 0;
		return (ZAPPY_EXIT_SUCCESS);
	}
	return (ZAPPY_EXIT_FAILURE);
}