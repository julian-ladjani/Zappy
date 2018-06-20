/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** shouter.c
*/

#include "client.h"

int ai_shouter(clt_config_t *clt)
{
	send_request(BROADCAST, clt, "incantation;need_players");
	return (ZAPPY_EXIT_SUCCESS);
}