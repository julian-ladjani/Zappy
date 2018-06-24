/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** follower.c
*/

#include <broadcast.h>
#include "client.h"

int ai_test(clt_config_t *clt)
{
	send_request(INVENTORY, clt);
}