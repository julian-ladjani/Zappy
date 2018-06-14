/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** sender.c
*/

#include "client_sender.h"

uint8_t send_request(send_cmd_t request_id, clt_config_t *client, ...)
{
	va_list av;

	for (size_t i = 0; i < NB_REQUESTS(); ++i) {
		if (requests[i].cmd_id == request_id) {
			va_start(av, client);
			client->server->active_request = requests[i].cmd_name;
			requests[i].sender(client, &av);
			while (client->server->active_request);
			va_end(av);
		}
	}
	return (1);
}