/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast_parser.c
*/

#include "client.h"
#include "broadcast.h"

incantation_state_t get_incantation_state(char *str)
{
	if (!strncmp(str, ZPY_MSG_INC_START, strlen(ZPY_MSG_INC_START)))
		return (START);
	if (!strncmp(str, ZPY_MSG_INC_CANCELED, strlen(ZPY_MSG_INC_CANCELED)))
		return (CANCELED);
	if (!strncmp(str, ZPY_MSG_INC_HELPING, strlen(ZPY_MSG_INC_HELPING)))
		return (HELPING);
	if (!strncmp(str, ZPY_MSG_INC_STOP_HELPING,
			strlen(ZPY_MSG_INC_STOP_HELPING)))
		return (STOP_HELPING);
	if (!strncmp(str, ZPY_MSG_INC_NEED_STOP_HELPING,
			strlen(ZPY_MSG_INC_NEED_STOP_HELPING)))
		return (NEED_STOP_HELPING);
	return (NEED_HELP);
}

void broadcast_setter_incantation(clt_msg_t *msg, char *str)
{
	msg_infos_incantation_t *infos =
		malloc(sizeof(msg_infos_incantation_t));

	if (!infos)
		return;
	str = sstrtok(NULL, ":");
	if (!str) {
		free(infos);
		return;
	}
	infos->state = get_incantation_state(str);
	str = sstrtok(NULL, ":");
	if (!str) {
		free(infos);
		return;
	}
	infos->level = atoi(str);
	infos->_for = (infos->state == NEED_STOP_HELPING) ?
			atoi(sstrtok(NULL, ":")) : 0;
	msg->type = MSG_INCANTATION;
	msg->content = (void *)infos;
}