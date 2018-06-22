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

int srvrequest_message(clt_config_t *client)
{
	clt_msg_t *msg = calloc(sizeof(clt_msg_t), sizeof(clt_msg_t));
	char *tmp;

	if (!msg)
		return (ZAPPY_EXIT_FAILURE);
	tmp = sstrtok(client->server->response_request, ",");
	msg->dir = atoi(strchr(tmp, ' ') + 1);
	if (msg->dir < 0 || msg->dir > 8 ||
		broadcast_parser(client, msg) == ZAPPY_EXIT_FAILURE) {
		free(msg);
		free(tmp);
		return (ZAPPY_EXIT_FAILURE);
	}
	free(tmp);
	list_add_elem_at_pos(client->server->broadcasts_queue,
				(void *)msg, LIST_FIRST);
	return (ZAPPY_EXIT_SUCCESS);
}

int srvrequest_elevation_underway(clt_config_t *client)
{
	client->incantation = 1;
	return (ZAPPY_EXIT_SUCCESS);
}