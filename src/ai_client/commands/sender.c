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

int send_request(send_cmd_t request_id, clt_config_t *client, ...)
{
	va_list av;

	for (size_t i = 0; i < NB_REQUESTS(); ++i) {
		if (requests[i].cmd_id == request_id) {
			va_start(av, client);
			client->server->active_request = requests[i].cmd_name;
			requests[i].sender(client, &av, 1);
			while (client->server->active_request) {
				if (handle_poll(client) == ZAPPY_EXIT_FAILURE) {
					va_end(av);
					return (84);
				}
			}
			va_end(av);
			va_start(av, client);
			requests[i].sender(client, &av, 0);
			va_end(av);
		}
	}
	return (1);
}