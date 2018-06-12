/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include "../../../include/map.h"

void free_map(map_t *map)
{
	if (!map)
		return;
	if (!map->tiles)
		return free(map);
	if (*map->tiles)
		free(*map->tiles);
	free(map->tiles);
	free(map);
}