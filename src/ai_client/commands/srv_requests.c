/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** pre_requests.c
*/

#include "broadcast.h"
#include "client.h"

int srvrequest_dead(clt_config_t *client)
{
	client->status = ZAPPY_CLT_DEAD;
	return (ZAPPY_EXIT_SUCCESS);
}

int srvrequest_message(clt_config_t *client)
{
	printf("%d\n", list_size(client->server->broadcasts_queue));
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
	broadcast_add_elem(client, msg);
	return (ZAPPY_EXIT_SUCCESS);
}

int srvrequest_elevation_underway(clt_config_t *client)
{
	if (client->server->active_request &&
		!strcmp(client->server->active_request, "Incantation")) {
		send_request(INCANTATION_WAIT, client);
		client->server->active_request = NULL;
	}
	return (ZAPPY_EXIT_SUCCESS);
}

int srvrequest_current_level(clt_config_t *client)
{
	if (client->server->active_request &&
	    !strcmp(client->server->active_request, "IncantationWait"))
		client->server->active_request = NULL;
	client->specs->level =
		(unsigned int) atoi(client->server->response_request + 14) - 1;
	client->incantation = 0;
	return (ZAPPY_EXIT_SUCCESS);
}