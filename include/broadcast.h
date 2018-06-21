/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.h
*/

#ifndef PSU_ZAPPY_2017_BROADCAST_H
#define PSU_ZAPPY_2017_BROADCAST_H

#define ZPY_MSG_INCANTATION "incantation"
#define ZPY_MSG_INC_START "start"
#define ZPY_MSG_INC_CANCELED "canceled"

#include "client.h"

typedef enum client_brocasted_types_s {
	MSG_UNKNOWN,
	MSG_INCANTATION
} msg_types_t;

typedef enum client_incantation_state_s {
	START,
	NEED_HELP,
	CANCELED
} incantation_state_t;

typedef struct client_message_incantation_s {
	incantation_state_t state;
	int level;
} msg_infos_incantation_t;


typedef struct client_message_s {
	void *content;
	msg_types_t type;
	int from;
	int dir;
	int id;
} clt_msg_t;

int broadcast_parser(clt_config_t *client, clt_msg_t *msg);
clt_msg_t *broadcast_search_for(list_t *msgs, msg_types_t);
clt_msg_t *broadcast_search_for_incantation(list_t *msgs);

#endif /* PSU_ZAPPY_2017_BROADCAST_H */