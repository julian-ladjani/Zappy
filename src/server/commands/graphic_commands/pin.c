/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** pln.c
*/

#include "server_function.h"

uint8_t srv_cmd_pin(server_config_t *server,
	server_user_t *user, cmdparams_t *cmd)
{
	server_user_t *player;
	char *inventory;

	if (cmd->nb_args < 1 || cmd->args[0][0] != '#') {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	player = find_user_by_id(server, atoi(cmd->args[0] + 1));
	if (!player) {
		dprintf(user->fd, "sbp\n");
		return (1);
	}
	inventory = tile_to_str_quantity(player->inventory);
	dprintf(user->fd, "pin %d %s\n", player->id, inventory);
	if (inventory)
		free(inventory);
	return (0);
}
