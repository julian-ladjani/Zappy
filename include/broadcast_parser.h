/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_parser.h
*/

#ifndef PSU_ZAPPY_2017_BROADCAST_PARSER_H
#define PSU_ZAPPY_2017_BROADCAST_PARSER_H

#include <stdio.h>
#include "broadcast.h"

void msg_parser_unknown(clt_msg_t *msg, char *str);
void broadcast_setter_incantation(clt_msg_t *msg, char *str);

typedef struct msg_parser_s {
	char *flag;
	void (*func)(clt_msg_t *msg, char *str);
} msg_parser_t;

const msg_parser_t msg_parser[2] = {
	{ZPY_MSG_INCANTATION, broadcast_setter_incantation},
	{NULL, NULL}
};

#endif /* PSU_ZAPPY_2017_BROADCAST_PARSER_H */