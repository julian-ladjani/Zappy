/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** follower.c
*/

#include "client.h"

int ai_follower(clt_config_t *clt)
{
	send_request(FORWARD, clt);
	return (ZAPPY_EXIT_SUCCESS);
}