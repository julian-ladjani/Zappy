/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** launch_server.c
*/

#include <client.h>

int launch_server(client_config_t *client)
{
	int poll_rv;

	while (1) {
		poll_rv = poll(client->server, 1, 200);
		if (poll_rv < 0) {
			dprintf(2, "poll() failed\n");
			return (1);
		}
		if (poll_rv >= 0 && client->server->revents == POLLIN)
			update_queue(client);
	}
	return (0);
}