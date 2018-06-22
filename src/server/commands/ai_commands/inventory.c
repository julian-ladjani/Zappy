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
		OBJ_NAMES[FOOD], (size_t)((float)user->inventory[FOOD] / 126),
		OBJ_NAMES[LINEMATE], user->inventory[LINEMATE],
		OBJ_NAMES[DERAUMERE], user->inventory[DERAUMERE],
		OBJ_NAMES[SIBUR], user->inventory[SIBUR],
		OBJ_NAMES[MENDIANE], user->inventory[MENDIANE],
		OBJ_NAMES[PHIRAS], user->inventory[PHIRAS],
		OBJ_NAMES[THYSTAME], user->inventory[THYSTAME]);
	user->wait += 1;
	return (0);
}
