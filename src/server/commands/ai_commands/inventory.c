/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include "server_struct.h"

uint8_t srv_cmd_inventory(__attribute__((unused))server_config_t *server,
				server_user_t *user,
			  __attribute__((unused))cmdparams_t *cmd)
{
	dprintf(user->fd,
		"[%s %lu, %s %lu, %s %lu, %s %lu, %s %lu, %s %lu, %s %lu]\n",
		"food", user->inventory[FOOD],
		"linemate", user->inventory[LINEMATE],
		"deraumere", user->inventory[DERAUMERE],
		"sibur", user->inventory[SIBUR],
		"mendiane", user->inventory[MENDIANE],
		"phiras", user->inventory[PHIRAS],
		"thystame", user->inventory[THYSTAME]);
	return (0);
}
