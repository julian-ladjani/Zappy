/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"

char *tile_to_str(tile_t tile)
{
	char *ressources[7] = {"food", "linemate", "deraumere", "sibur",
				"mendiane", "phiras", "thystame"};
	char *str = NULL;

	for (int i = FOOD; i < THYSTAME; ++i) {
		if (str)
			str = str_append(str, " ");
		if (tile[i])
			str = str_append(str, ressources[i]);
	}
	return (str);
}

char *tile_to_str_quantity(tile_t tile)
{
	return (asprintf("%u %u %u %u %u %u %u", tile[FOOD], tile[LINEMATE],
			tile[DERAUMERE], tile[SIBUR], tile[MENDIANE],
			tile[PHIRAS], tile[THYSTAME]));
}
