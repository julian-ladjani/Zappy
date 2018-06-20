/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** pre_requests.c
*/

#include "client.h"

int srvrequest_dead(clt_config_t *client)
{
	client->status = ZAPPY_CLT_DEAD;
	return (ZAPPY_EXIT_SUCCESS);
}

int fill_msg(clt_config_t *client, clt_msg_t *msg)
{
	char *tmp;

	tmp = sstrtok(NULL, ":");
	if (!tmp || strncmp(tmp, client->specs->team,
				strlen(client->specs->team)))
		return (ZAPPY_EXIT_FAILURE);
	tmp = sstrtok(NULL, ":");
	if (!tmp)
		return (ZAPPY_EXIT_FAILURE);
	msg->from = atoi(tmp);
	tmp = sstrtok(NULL, ":");
	if (!tmp)
		return (ZAPPY_EXIT_FAILURE);
	msg->content = strdup(tmp);
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
	if (fill_msg(client, msg) == ZAPPY_EXIT_FAILURE)
	if (msg->dir < 1 || msg->dir > 8 ||
		fill_msg(client, msg) == ZAPPY_EXIT_FAILURE) {
		free(msg);
		free(tmp);
		return (ZAPPY_EXIT_FAILURE);
	}
	free(tmp);
	list_add_elem_at_pos(client->server->broadcasts_queue,
				(void *)msg, LIST_END);
	return (ZAPPY_EXIT_SUCCESS);
}