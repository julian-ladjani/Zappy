/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sender.c
*/

#define _GNU_SOURCE

#include <stdio.h>
#include "client_sender.h"

void vsend_active_request(clt_config_t *client, char *msg, va_list *av)
{
	char *rslt = NULL;
	char *formated_msg = NULL;
	char *request = client->server->active_request;

	vasprintf(&rslt, msg, *av);
	if (rslt && strlen(rslt) > 0)
		asprintf(&formated_msg, "%s %s\n", request, rslt);
	else
		asprintf(&formated_msg, "%s\n", request);
	send(client->server->pollfd->fd, formated_msg, strlen(formated_msg), 0);
	free(rslt);
	free(formated_msg);
}

void send_active_request(clt_config_t *client, char *msg, ...)
{
	va_list va;

	va_start(va, msg);
	vsend_active_request(client, msg, &va);
	va_end(va);
}

static int handle_request(size_t i, clt_config_t *client,
				va_list *av_send, va_list *av_receive)
{
	requests[i].sender(client, av_send, 1);
	while (client->server->active_request) {
		if (handle_poll(client) != ZAPPY_EXIT_FAILURE)
			continue;
		va_end(*av_send);
		va_end(*av_receive);
		return (84);
	}
	va_end(*av_send);
	if (client->server->response_request)
		requests[i].sender(client, av_receive, 0);
	va_end(*av_receive);
	return (0);
}

int send_request(send_cmd_t request_id, clt_config_t *client, ...)
{
	va_list av_send;
	va_list av_receive;

	for (size_t i = 0; i < NB_REQUESTS(); ++i) {
		if (requests[i].cmd_id != request_id)
			continue;
		va_start(av_send, client);
		va_copy(av_receive, av_send);
		client->server->active_request = requests[i].cmd_name;
		if (ZAPPY_DEBUG)
			printf("\e[33m[%d %s] \e[32mSend : %s\e[0m\n",
				client->specs->level + 1,
				get_ai_name(client->specs->ai_mode),
				requests[i].cmd_name);
		if (handle_request(i, client, &av_send, &av_receive) == 84)
			return (0);
	}
	if (client->incantation == 1)
		send_request(INCANTATION_WAIT, client);
	return (1);
}