/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_poll.c
*/

#include <client_connection.h>

static int handle_info(clt_config_t *client, size_t j)
{
	int r_value = srv_requests[j].request(client);

	if (r_value == ZAPPY_EXIT_FAILURE) {
		client->server->active_request = NULL;
		return (ZAPPY_EXIT_SUCCESS);
	}
	free(client->server->response_request);
	client->server->response_request = NULL;
	return (ZAPPY_EXIT_SUCCESS);
}

static int parse_infos(clt_config_t *client)
{
	static int i = 0;
	int r_value;

	if (pre_requests[i]) {
		r_value = pre_requests[i++](client);
		if (pre_requests[i] == NULL && r_value == ZAPPY_EXIT_SUCCESS)
			client->status = ZAPPY_CLT_READY;
		return (r_value);
	}
	for (size_t j = 0; srv_requests[j].flag; ++j) {
		if (!strncmp(client->server->response_request,
				srv_requests[j].flag,
				strlen(srv_requests[j].flag))) {
			return (handle_info(client, j));
		}
	}
	client->server->active_request = NULL;
	return (ZAPPY_EXIT_SUCCESS);
}

static void fill_command(clt_config_t *client, unsigned int pos, char end)
{
	if (client->server->long_command == 0) {
		free(client->server->response_request);
		client->server->response_request = circbuf_nbufferise
			(client->server->buf, pos);
		circbuf_free_nspace(client->server->buf, pos + end);
	} else {
		client->server->response_request = str_append
			(client->server->response_request,
				circbuf_nbufferise(client->server->buf, pos));
		client->server->buf->free_nspace(client->server->buf,
							pos + end);
	}
}

static int read_command(clt_config_t *client)
{
	long pos = circbuf_strstr(client->server->buf, "\n");
	int r_value;

	if (pos < 0 &&
		client->server->buf->get_space(client->server->buf) <= 1) {
		fill_command(client, client->server->buf->size, 0);
		client->server->long_command = 1;
	}
	while (pos >= 0) {
		fill_command(client, (unsigned int) pos, 1);
		client->server->long_command = 0;
		if (ZAPPY_DEBUG)
			printf("\e[31m%s\e[0m\n",
				client->server->response_request);
		r_value = parse_infos(client);
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
	poll_rv = poll(client->server->pollfd, 1, 3000);
	if (poll_rv < 0) {
		dprintf(2, "poll() failed\n");
		return (ZAPPY_EXIT_FAILURE);
	}
	if (poll_rv >= 0 && client->server->pollfd->revents == POLLIN) {
		if (client->server->buf->recv(client->server->pollfd->fd,
			client->server->buf, CIRCBUF_SIZE()) <= 0) {
			cleanup_client_exit(client, ZAPPY_EXIT_FAILURE);
		}
		return (read_command(client));
	}
	return (ZAPPY_EXIT_NOTHING);
}
