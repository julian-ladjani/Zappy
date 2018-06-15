/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** connect.c
*/

#include <client.h>
#include <netdb.h>
#include <arpa/inet.h>

static int connect_to_serv(clt_config_t *client)
{
	struct protoent *pe = getprotobyname("TCP");
	struct sockaddr_in s_in;

	if (!pe)
		return (0);
	printf("Connecting to %s/%d...\n", client->server->socket->ip,
		client->server->socket->port);
	client->server->socket->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	s_in.sin_addr.s_addr = inet_addr(client->server->socket->ip);
	s_in.sin_port = htons(client->server->socket->port);
	s_in.sin_family = AF_INET;
	printf("%d\n", client->server->socket->fd);
	if (client->server->socket->fd >= 0
		&& !connect(client->server->socket->fd,
			(struct sockaddr *)&s_in, sizeof(s_in)))
		return (1);
	return (0);
}

int init_server(clt_config_t *client)
{
	if (!connect_to_serv(client)) {
		dprintf(2, "Connection failed\n");
		return (0);
	}
	printf("Connection ok !\n");
	return (1);
}