/*
** EPITECH PROJECT, 2018
** SfmlTests
** File description:
** main.c
*/

#include <stdio.h>
#include <client.h>
#include <pthread.h>
#include "parser.h"
#include "map.h"
#include "ressources_str.h"

void free_client_config(clt_config_t *client)
{
	if (!client)
		return;
	map_free(client->map);
	free(client->server->broadcasts_queue);
	if (client->server)
		free(client->server->socket);
	free(client->server);
	free(client->specs);
	client->server = NULL;
	client->specs = NULL;
	free(client);
}

static void init_server_socket_informations(
	char *machine, in_port_t port, clt_config_t *client)
{
	client->server = calloc(sizeof(clt_socket_t), sizeof(clt_socket_t));
	if (!client->server) {
		free_client_config(client);
		return;
	}
	client->server->broadcasts_queue = list_create(NULL);
	client->server->socket = calloc(sizeof(zappy_socket_t),
					sizeof(zappy_socket_t));
	if (!client->server->socket) {
		free_client_config(client);
		return;
	}
	client->server->buf = circbuf_create(1025);
	if (client->server->buf == NULL) {
		free_client_config(client);
		return;
	}
	client->server->socket->port = port;
	client->server->socket->ip = machine;
}

static clt_specs_t *init_client_specs(char *team)
{
	clt_specs_t *specs = calloc(sizeof(clt_specs_t), sizeof(clt_specs_t));

	if (!specs)
		return (NULL);
	specs->orientation = NORTH;
	specs->team = team;
	return (specs);
}

static clt_config_t *init_config(clt_params_t *params)
{
	clt_config_t *client = calloc(
		sizeof(clt_config_t), sizeof(clt_config_t));

	if (!client || !params)
		return (NULL);
	init_server_socket_informations(
		params->machine, (in_port_t) params->port, client);
	if (!client->server)
		return (NULL);
	client->specs = init_client_specs(params->team);
	client->server->pollfd->fd = -1;
	client->server->pollfd->events = POLLIN;
	return (client);
}

int main(int ac, char **av)
{
	clt_config_t *client = init_config(
		client_parse_arguments(ac - 1, av + 1));

	if (!client || !init_server(client)) {
		free_client_config(client);
		return (84);
	}
	while (client->status == ZAPPY_CLT_WAITING)
		if (handle_poll(client) == ZAPPY_EXIT_FAILURE)
			return (84);
	launch_ai(client);
	free_client_config(client);
	return (0);
}