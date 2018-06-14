/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.h
*/

#ifndef PSU_ZAPPY_2017_CLIENT_SENDER_H
#define PSU_ZAPPY_2017_CLIENT_SENDER_H

#include "client.h"

#define NB_REQUESTS() (13)

request_t requests[13] = {
	{BROADCAST, "broadcast", clt_cmd_get_args_broadcast},
	{CONNECT, "connect_nbr", clt_cmd_get_args_connect_nbr},
	{EJECT, "eject", clt_cmd_get_args_eject},
	{FORK, "fork", clt_cmd_get_args_fork},
	{FORWARD, "forward", clt_cmd_get_args_forward},
	{INCANTATION, "incantation", clt_cmd_get_args_incantation},
	{INVENTORY, "inventory", clt_cmd_get_args_inventory},
	{LEFT, "left", clt_cmd_get_args_left},
	{LOOK, "look", clt_cmd_get_args_look},
	{RIGHT, "right", clt_cmd_get_args_right},
	{SET, "set", clt_cmd_get_args_set},
	{TAKE, "take", clt_cmd_get_args_take}
};

#endif /* PSU_ZAPPY_2017_CLIENT_SENDER_H */