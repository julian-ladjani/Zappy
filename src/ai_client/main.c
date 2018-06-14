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

void free_client_config(client_config_t *client)
{
	map_free(client->map);
	free(client->server_socket);
}

static void init_server_socket_informations(
	char *machine, in_port_t port, client_config_t *client)
{
	client->server_socket = malloc(sizeof(zappy_socket_t));
	if (!client->server_socket) {
		printf("Invalid malloc\n");
		free(client);
		client->server_socket = NULL;
		return;
	}
	client->server_socket->port = port;
	client->server_socket->ip = machine;
}

static client_config_t *init_config(
	char *machine, in_port_t port, char *team)
{
	client_config_t *client = calloc(
		sizeof(client_config_t), sizeof(client_config_t));

	if (!client)
		return (NULL);
	init_server_socket_informations(machine, port, client);
	if (!client->server_socket)
		return (NULL);
	client->server->fd = -1;
	client->server->events = POLLIN;
	client->team = team;
	return (client);
}

int main(int ac, char **av)
{
	client_config_t *client = init_config("127.0.0.1", 4242, "golelan");

	if (!client || !init_server(client))
		return (84);
	launch_client(client);
	return (0);
}