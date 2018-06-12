/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_create.c
*/

#include "map.h"

void map_free(map_t *map)
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