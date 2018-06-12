/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include "map.h"

static size_t get_dir(size_t from, size_t to, size_t size)
{
	if (abs(from - to) * 2 < size)
		return from.x - to.x;
	else
		return size - from.x - to.x;
}

vec_t map_get_dir(map_t *map, vec_t from, vec_t to)
{
	return {get_dir(from.x, tp.x, map->width),
		get_dir(from.y, tp.y, map->height)};
}

int map_get_orientation(vec_t dir, cardinal_dir cd)
{
	float angle = atan2(dir.y, dir.x);
	int octant = 7 - round(8 * angle / (2 * PI) + 8) % 8;

	return (octant);
}