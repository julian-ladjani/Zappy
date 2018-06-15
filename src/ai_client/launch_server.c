/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_poll.c
*/

#include <client_connection.h>

static int parse_infos(clt_config_t *client)
{
	static int i = 0;
	int r_value;

	if (pre_requests[i]) {
		r_value = pre_requests[i++](client);
		if (pre_requests[i] == NULL &&
			r_value == ZAPPY_EXIT_SUCCESS)
				client->status = ZAPPY_CLT_READY;
		free(client->server->response_request);
		return (r_value);
	}
	if (!strncmp(client->server->response_request, "dead", 4)) {
		free(client->server->response_request);
		client->server->response_request = NULL;
		client->status = ZAPPY_CLT_DEAD;
	} else if (!strncmp(client->server->response_request, "message", 7)) {
		list_add_elem_at_pos(client->server->broadcasts_queue,
			(void *) client->server->response_request, LIST_END);
		client->server->response_request = NULL;
	}
	return (ZAPPY_EXIT_SUCCESS);
}

static int read_command(clt_config_t *client)
{
	long pos = circbuf_strstr(client->server->buf, "\n");
	int r_value;

	while (pos > 0) {
		if (!pos)
			break;
		client->server->active_request = NULL;
		if (client->server->active_request)
			free(client->server->active_request);
		client->server->response_request = circbuf_nbufferise
			(client->server->buf, (unsigned int) pos);
		r_value = parse_infos(client);
		circbuf_free_nspace(client->server->buf,
					(unsigned int) pos + 1);
		if (r_value == ZAPPY_EXIT_FAILURE)
			return (ZAPPY_EXIT_FAILURE);
		pos = circbuf_strstr(client->server->buf, "\n");
	}
	return (ZAPPY_EXIT_SUCCESS);
}

int handle_poll(clt_config_t *client)
{
	int poll_rv;

	client->server->pollfd->fd = client->server->socket->fd;
	if (client->status == ZAPPY_CLT_DEAD)
		return (ZAPPY_EXIT_FAILURE);
	poll_rv = poll(client->server->pollfd, 1, 200);
	if (poll_rv < 0) {
		dprintf(2, "poll() failed\n");
		return (ZAPPY_EXIT_FAILURE);
	}
	if (poll_rv >= 0 && client->server->pollfd->revents == POLLIN) {
		client->server->buf->recv(
			client->server->pollfd->fd,
			client->server->buf, 1025);
		return (read_command(client));
	}
	return (ZAPPY_EXIT_NOTHING);
}
