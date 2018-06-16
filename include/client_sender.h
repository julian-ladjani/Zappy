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

const request_t requests[13] = {
	{BROADCAST, "Broadcast", clt_cmd_get_args_broadcast},
	{CONNECT, "Connect_nbr", clt_cmd_get_args_connect_nbr},
	{EJECT, "Eject", clt_cmd_get_args_eject},
	{FORK, "Fork", clt_cmd_get_args_fork},
	{FORWARD, "Forward", clt_cmd_get_args_forward},
	{INCANTATION, "Incantation", clt_cmd_get_args_incantation},
	{INVENTORY, "Inventory", clt_cmd_get_args_inventory},
	{LEFT, "Left", clt_cmd_get_args_left},
	{LOOK, "Look", clt_cmd_get_args_look},
	{RIGHT, "Right", clt_cmd_get_args_right},
	{SET, "Set", clt_cmd_get_args_set},
	{TAKE, "Take", clt_cmd_get_args_take}
};

#endif /* PSU_ZAPPY_2017_CLIENT_SENDER_H */