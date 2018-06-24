/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** cleanup.c
*/

#include "client.h"

void free_client_config(clt_config_t *client)
{
	if (!client)
		return;
	map_free(client->map);
	list_delete_all(client->server->broadcasts_queue, clean_broadcast);
	if (client->server)
		free(client->server->socket);
	circbuf_free(client->server->buf);
	free(client->server->response_request);
	free(client->server);
	free(client->specs);
	client->server = NULL;
	client->specs = NULL;
	free(client);
}

void cleanup_client_exit(clt_config_t *client, int exit_value)
{
	free_client_config(client);
	exit(exit_value);
}