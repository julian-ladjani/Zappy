/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** create_map.c
*/

#include <math.h>
#include "map.h"

static ssize_t get_dir(ssize_t from, ssize_t to, size_t size)
{
	if (abs((int) (from - to)) * 2 < size)
		return from - to;
	else
		return size - from - to;
}

vec_t map_get_dir(map_t *map, vec_t from, vec_t to)
{
	vec_t vec = {get_dir(from.x, to.x, map->width),
		     get_dir(from.y, to.y, map->height)};
	return (vec);
}

uint8_t map_get_orientation(vec_t dir)
{
	double angle = atan2(dir.y, dir.x);
	uint8_t piece;

	if (angle < 0)
		angle += 2 * M_PI;
	piece = (uint8_t) (8 * angle / (2 * M_PI));
	if (piece >= 8)
		piece = 0;
	piece = (uint8_t) (8 - (piece + 1));
	return (uint8_t) (piece == 0 ? 8 : piece);
}