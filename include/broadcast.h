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
#define ZPY_MSG_INC_HELPING "helping"
#define ZPY_MSG_INC_STOP_HELPING "stop_helping"
#define ZPY_MSG_INC_NEED_STOP_HELPING "need_stop_helping"

#include "client.h"

typedef enum client_brocasted_types_s {
	MSG_UNKNOWN,
	MSG_INCANTATION
} msg_types_t;

typedef enum client_incantation_state_s {
	START,
	NEED_HELP,
	NEED_STOP_HELPING,
	HELPING,
	STOP_HELPING,
	CANCELED
} incantation_state_t;

typedef struct client_message_incantation_s {
	incantation_state_t state;
	int level;
	int _for;
} msg_infos_inc_t;

typedef struct client_message_s {
	void *content;
	msg_types_t type;
	int from;
	int dir;
	int id;
	int timer;
} clt_msg_t;

int broadcast_parser(clt_config_t *client, clt_msg_t *msg);
int condition_search_incantation(clt_config_t *clt, void *elem);
int condition_targeted_incantation(clt_config_t *clt, void *elem);
clt_msg_t *broadcast_search_for(
	clt_config_t *clt, int (*checker)(clt_config_t *, void *));
int broadcast_add_elem(clt_config_t *client, clt_msg_t *msg);
void manage_broadcast_timer(clt_config_t *clt);
char *broadcast_type_str(incantation_state_t s);
void dump_broadcast(void *elem);

#endif /* PSU_ZAPPY_2017_BROADCAST_H */