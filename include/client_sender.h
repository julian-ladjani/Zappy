/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.h
*/

#ifndef PSU_ZAPPY_2017_CLIENT_SENDER_H
#define PSU_ZAPPY_2017_CLIENT_SENDER_H

#include "client.h"

request_t requests[13] = {
	{BROADCAST, "broadcast", clt_get_args_cmd_broadcast},
	{CONNECT, "connect_nbr", clt_get_args_cmd_connect_nbr},
	{EJECT, "eject", clt_get_args_cmd_eject},
	{FORK, "fork", clt_get_args_cmd_fork},
	{FORWARD, "forward", clt_get_args_cmd_forward},
	{INCANTATION, "incantation", clt_get_args_cmd_incantation},
	{INVENTORY, "inventory", clt_get_args_cmd_inventory},
	{LEFT, "left", clt_get_args_cmd_left},
	{LOOK, "look", clt_get_args_cmd_look},
	{RIGHT, "right", clt_get_args_cmd_right},
	{SET, "set", clt_get_args_cmd_set},
	{TAKE, "take", clt_get_args_cmd_take}
};

#endif /* PSU_ZAPPY_2017_CLIENT_H */