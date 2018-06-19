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
		obj_names[FOOD], user->inventory[FOOD],
		obj_names[LINEMATE], user->inventory[LINEMATE],
		obj_names[DERAUMERE], user->inventory[DERAUMERE],
		obj_names[SIBUR], user->inventory[SIBUR],
		obj_names[MENDIANE], user->inventory[MENDIANE],
		obj_names[PHIRAS], user->inventory[PHIRAS],
		obj_names[THYSTAME], user->inventory[THYSTAME]);
	user->wait += 1;
	return (0);
}
