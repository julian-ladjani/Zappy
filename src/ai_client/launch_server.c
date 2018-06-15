/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** launch_server.c
*/

#include <client_connection.h>

static void parse_infos(clt_config_t *client)
{
	if (!strncmp(client->server->response_request, "dead", 4)) {
		free(client->server->response_request);
		client->server->response_request = NULL;
		client->dead = 1;
	} else if (!strncmp(client->server->response_request, "message", 7)) {
		list_add_elem_at_pos(
			client->server->broadcasts_queue,
			(void *) client->server->response_request,
			LIST_END);
		client->server->response_request = NULL;
	}
}

static void read_command(clt_config_t *client)
{
	long pos = circbuf_strstr(client->server->buf, "\n");

	while (pos > 0) {
		client->server->buf->debug(1, client->server->buf);
		if (!pos)
			break;
		client->server->active_request = NULL;
		if (client->server->active_request)
			free(client->server->active_request);
		client->server->response_request = circbuf_nbufferise
			(client->server->buf, (unsigned int) pos);
		printf("Receive : %s\n", client->server->response_request);
		parse_infos(client);
		circbuf_free_nspace(client->server->buf,
					(unsigned int) pos + 1);
		pos = circbuf_strstr(client->server->buf, "\n");
	}
}

void *launch_server(void *clt)
{
	int poll_rv;
	clt_config_t *client = (clt_config_t *)clt;
	unsigned int i = 0;

	printf("Entering server thread\n");
	client->server->pollfd->fd = client->server->socket->fd;
	while (!client->dead) {
		poll_rv = poll(client->server->pollfd, 1, 200);
		if (poll_rv < 0) {
			dprintf(2, "poll() failed\n");
			return (NULL);
		}
		if (poll_rv >= 0 && client->server->pollfd->revents == POLLIN) {
			client->server->buf->recv(
				client->server->pollfd->fd,
				client->server->buf, 1025);
			if (!pre_requests[i])
				read_command(client);
			else if (!pre_requests[i++](client))
				return (NULL);
		}
	}
	return (NULL);
}
