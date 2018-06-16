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
	{BROADCAST, "Broadcast", clt_cmd_get_args_broadcast,
		clt_cmd_broadcast_receiver},
	{CONNECT, "Connect_nbr", clt_cmd_get_args_connect_nbr,
		clt_cmd_connect_nbr_receiver},
	{EJECT, "Eject", clt_cmd_get_args_eject,
		clt_cmd_eject_receiver},
	{FORK, "Fork", clt_cmd_get_args_fork,
		clt_cmd_fork_receiver},
	{FORWARD, "Forward", clt_cmd_get_args_forward,
		clt_cmd_forward_receiver},
	{INCANTATION, "Incantation", clt_cmd_get_args_incantation,
		clt_cmd_incantation_receiver},
	{INVENTORY, "Inventory", clt_cmd_get_args_inventory,
		clt_cmd_inventory_receiver},
	{LEFT, "Left", clt_cmd_get_args_left,
		clt_cmd_left_receiver},
	{LOOK, "Look", clt_cmd_get_args_look,
		clt_cmd_look_receiver},
	{RIGHT, "Right", clt_cmd_get_args_right,
		clt_cmd_right_receiver},
	{SET, "Set", clt_cmd_get_args_set,
		clt_cmd_set_receiver},
	{TAKE, "Take", clt_cmd_get_args_take,
		clt_cmd_take_receiver}
};

#endif /* PSU_ZAPPY_2017_CLIENT_SENDER_H */