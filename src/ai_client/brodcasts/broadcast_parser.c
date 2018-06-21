/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_parser.c
*/

#include "client.h"
#include "broadcast.h"
#include "broadcast_parser.h"

static void broadcast_set_content(clt_config_t *client, clt_msg_t *msg,
					char *content)
{
	size_t flaglen;

	msg->type = MSG_UNKNOWN;
	msg->content = NULL;
	for (int i = 0; msg_parser[i].flag; ++i) {
		flaglen = strlen(msg_parser[i].flag);
		if (!strncmp(msg_parser[i].flag, content, flaglen)) {
			return msg_parser[i].func(msg, content + flaglen);
		}
	}
	msg->content = strdup(content);
	(void) client;
}

int broadcast_parser(clt_config_t *client, clt_msg_t *msg)
{
	char *tmp;

	tmp = sstrtok(NULL, ":");
	if (!tmp || strncmp(tmp, client->specs->team,
			    strlen(client->specs->team)))
		return (ZAPPY_EXIT_FAILURE);
	tmp = sstrtok(NULL, ":");
	if (!tmp)
		return (ZAPPY_EXIT_FAILURE);
	msg->from = atoi(tmp);
	tmp = sstrtok(NULL, ":");
	if (!tmp)
		return (ZAPPY_EXIT_FAILURE);
	msg->id = atoi(tmp);
	tmp = sstrtok(NULL, ":");
	if (!tmp)
		return (ZAPPY_EXIT_FAILURE);
	broadcast_set_content(client, msg, tmp);
	return ((msg->type == MSG_UNKNOWN) ? ZAPPY_EXIT_FAILURE :
		ZAPPY_EXIT_SUCCESS);
}