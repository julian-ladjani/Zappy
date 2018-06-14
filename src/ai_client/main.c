/*
** EPITECH PROJECT, 2018
** SfmlTests
** File description:
** main.c
*/

#include <stdio.h>
#include <malloc.h>
#include <client.h>
#include "../../include/parser.h"
#include "../../include/map.h"

void free_client_config(clt_config_t *client)
{
	map_free(client->map);
	free(client->server->socket);
}

static void init_server_socket_informations(
	char *machine, in_port_t port, clt_config_t *client)
{
	client->server = malloc(sizeof(clt_socket_t));
	if (!client->server) {
		printf("Invalid malloc\n");
		free(client);
		client->server->socket = NULL;
		return;
	}
	client->server->socket = malloc(sizeof(zappy_socket_t));
	if (!client->server->socket) {
		printf("Invalid malloc\n");
		free(client->server);
		free(client);
		client->server->socket = NULL;
		return;
	}
	client->server->socket->port = port;
	client->server->socket->ip = machine;
}

static clt_config_t *init_config(
	char *machine, in_port_t port, char *team)
{
	clt_config_t *client = calloc(
		sizeof(clt_config_t), sizeof(clt_config_t));

	if (!client)
		return (NULL);
	init_server_socket_informations(machine, port, client);
	if (!client->server)
		return (NULL);
	client->server->pollfd->fd = -1;
	client->server->pollfd->events = POLLIN;
	client->team = team;
	return (client);
}

int main(int ac, char **av)
{
	clt_config_t *client = init_config("127.0.0.1", 4242, "golelan");

	if (!client || !init_server(client))
		return (84);
//	launch_client(client);
	return (0);
}