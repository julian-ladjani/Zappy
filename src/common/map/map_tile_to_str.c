/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"

char *tile_to_str(tile_t *tile)
{
	char *str = NULL;

	for (int i = FOOD; i <= THYSTAME; ++i) {
		for (unsigned int j = 0; j < (*tile)[i]; ++j) {
			str = str_append(str, str ? " " : NULL);
			str = str_append(str, OBJ_NAMES[i]);
		}
	}
	return (str);
}

char *tile_to_str_quantity(tile_t *tile)
{
	char *str = NULL;

	asprintf(&str, "%lu %lu %lu %lu %lu %lu %lu", (*tile)[FOOD],
		(*tile)[LINEMATE], (*tile)[DERAUMERE], (*tile)[SIBUR],
		(*tile)[MENDIANE], (*tile)[PHIRAS], (*tile)[THYSTAME]);
	return (str);
}
